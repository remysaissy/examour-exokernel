/*
** This file is part of ExAmour

** Copyright (C) Remy Saissy <remy.saissy@epitech.net>
** ExAmour is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 2 of the License, or
** (at your option) any later version.

** ExAmour is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.

** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#include	<examour/phymem.h>
#include	<examour/paging.h>
#include	<examour/log.h>

#include	"vmm.h"

/**
 * My apologize to the readers, I know this is ugly
 * but I'm in a hurry and I'm learning about it.
 * Anyway, a clean and reliable version is planned on
 * as soon as I can.
 * -- Remy
 */

/**
 * \todo	Use this data structure in vmm_init, and the region
 * manipulation functions.
 */
static struct vmm_s	vmm;

/** The free list is sorted increasingly. */
static inline void	_vmm_insert_in_free_list(struct vm_region_s *region,
						 struct vm_pages_s **p)
{
  struct vm_pages_s	*p2;
  
  p2 = region->free_pages;
  while (p2)
    {
      if ((*p)->offset > p2->offset)
	break;
      p2 = region->free_pages;
    }
  dlist_add_before(region->free_pages, p2, *p);
  region->free_pages_cnt++;
}

/* 
 * _vm_alloc_vm_region fills:
 *  - region_list
 *  - region_base
 *  - free_pages_cnt
 *  - total_pages_cnt
 *  - used_pages
 *  - free_pages
 */
static inline struct vm_region_s	*_vm_alloc_vm_region(vaddr_t start,
							     size_t size)
{
  struct vm_region_s	*new_region;
  size_t		region_struct_size;
  uint32_t		pages_cnt;
  vaddr_t		region_vaddr;
  paddr_t		region_paddr;
  struct vmm_pages_s	*pg;
  int			i;

  pages_cnt = ((size - start) / PAGE_SIZE);
  region_struct_size = sizeof(*new_region) + sizeof(struct vmm_pages_s) * pages_cnt;
  if (region_struct_size > PAGE_SIZE - sizeof(*vmm.vmm_pages))
    return (NULL);
  if (vmm.vmm_pages && region_struct_size <=
      PAGE_SIZE - vmm.vmm_pages->offset - (vaddr_t)vmm.vmm_pages)
    {
      new_region = vmm.vmm_pages->offset;
      vmm.vmm_pages->offset += region_struct_size;
    }
  else
    {
      if (phymem_ref(&region_paddr, PAGE_SIZE, PROTECTED_PAGE) == false)
	return (NULL);
      if (vmm.vmm_pages)
	region_vaddr = (vaddr_t)((vmm.vmm_pages) + PAGE_SIZE);
      else
	region_vaddr = vmm.vmm_addr;
      if (paging_alloc(NULL, region_vaddr, region_paddr, PG_V | PG_WR | PG_USR | PG_NOCACHE) == false)
	{
	  phymem_unref(region_paddr);
	  return (NULL);
	}
      dlist_add_head(vmm.vmm_pages, region_vaddr);
      vmm.vmm_pages->offset = (vaddr_t)vmm.vmm_pages + sizeof(*vmm.vmm_pages);
      new_region = vmm.vmm_pages->offset;
      vmm.vmm_pages->offset += region_struct_size;
    }
  dlist_add_head(vmm, new_region);
  new_region->region_base = start;
  new_region->free_pages_cnt = pages_cnt;
  new_region->total_pages_cnt = pages_cnt;
  new_region->used_pages = NULL;
  new_region->free_pages = NULL;
  for (i = 0; i < pages_cnt; i++)
    {
      pg = (struct vmm_pages_s *)((vaddr_t)new_region + sizeof(*new_region) + i * PAGE_SIZE);
      clist_add_before(new_region->free_pages, pg);
    }
  return (new_region);
}

/*
 * _vm_release_vm_region unregister the region data structure,
 * it doesn't care about any mapped pages within.
 */
static inline void	_vm_release_vm_region(struct vm_region_s *region)
{
  /** \todo To be done. */
  message("_vm_release_vm_region presently not implemented.\n");
  return;
}

/**
 * Clean release of a virtual page.
 * This function take care about the cache, dirty bit, mapping
 * and default behavior of the region.
 */
static inline void	_vm_release_page(struct vm_region_s *region,
					 vaddr_t vaddr)
{
  invlpg(vaddr);
  /*
   * \todo find an efficient way to avoid the syscall
   *  when it is useless by using the region's default_options.
   */
  paging_release(vaddr);
}

bool			vmm_init(vaddr_t vmm_struct, size_t size)
{
  vmm.regions = NULL;
  vmm.total_regions_cnt = 0;
  vmm.vmm_addr = vmm_struct;
  vmm.vmm_total_pages = size / PAGE_SIZE;
  vmm.vmm_pages_cnt = 0;
  vmm.vmm_pages = NULL;
  return (true);
}

struct vm_region_s	*vmm_create_region(vaddr_t base_addr, size_t size,
					   uint32_t perms, uint32_t options)
{
  struct vm_region_s	*region;

  if ((region = _vm_alloc_vm_region(base_addr, size)) == NULL)
    return (NULL);
  region->default_perms = perms;
  region->default_options = options;
  return (region);
}

bool			vmm_destroy_region(struct vm_region_s *region)
{
  struct vm_pages_s	*p;

  if (region == NULL)
    return (false);
  while (region->used_pages)
    {
      p = region->used_pages;
      dlist_remove(region->used_pages, p);
      _vm_release_page(region, p->offset);

      /* Here we no longer care about the sort because the region */
      /* is going to be destroyed few lines below. */
      dlist_add_head(region->free_pages, p);
    }
  /* the region has been cleaned up so destroy it. */
  _vm_release_vm_region(region);  
  return (true);
}

/** \todo To be tested */
/** \todo Simplify the function */
/** \todo take into account the default_options of the region. */
vaddr_t			vmm_alloc(struct vm_region_s *region, uint32_t num_pages)
{
  struct vm_pages_s	*p;
  struct vm_pages_s	*psav;
  paddr_t		paddr;
  uint32_t		cnt;

  if (region == NULL || vaddr == VADDR_ERROR)
    return (false);
  p = region->free_pages;
  cnt = 0;
  psav = p;
  while (p)
    {
      if (cnt == num_pages)
	{
	  while (--cnt > 0)
	    {
	      /* Allocate the page to physical. */
	      if ((region->default_options & VMM_ALLOC_MAP))
		{
		  if (phymem_ref_new(&paddr, PAGE_SIZE, USED_PAGE) == false)
		    goto vmm_alloc_error;
		  if (paging_alloc(NULL, psav->offset + cnt * PAGE_SIZE, paddr,
				   region->default_perms, PAGE_SIZE) == false)
		    {
		      phymem_unref(paddr);
		      goto vmm_alloc_error;
		    }
		}
	      p = psav;
	      psav = p->pages_list.next;
	      dlist_remove(region->free_pages, p);
	      dlist_add_head(region->used_pages, p);
	    }
	  region->free_pages_cnt -= num_pages;
	  return (true);
	}
      else
	{
	  if (p->offset == p->offset + cnt * PAGE_SIZE)
	    cnt++;
	  else
	    {
	      cnt = 1;
	      psav = p;
	    }
	}
      p = p->pages_list.next;
    }
  return (false);
  
vmm_alloc_error:
  while (++cnt < num_pages)
    {
      p = region->used_pages;
      dlist_remove(region->used_pages, p);
      /*
       * here we don't use _vm_release_page(region, p->offset);
       * because the page has just been allocated and _vm_release_page
       * is useful to manage pages that lived more... in caller space.
       */
      paging_release(p->offset);
      _vmm_insert_in_free_list(region, &p);
    }
  return (false);
}

/** To be tested */
bool			vmm_free(struct vm_region_s *region, vaddr_t vaddr)
{
  struct vm_pages_s	*p;
  struct vm_pages_s	*p2;

  if (region == NULL || vaddr == VADDR_ERROR || vaddr == region->region_page)
    return (false);
  p = region->used_pages;
  while (p)
    {
      if (p->offset == vaddr)
	{
	  invlpg(vaddr);
	  /*
	   * Don't care about VMM_ALLOC_MAP here
	   * because the page could have been mapped
	   * during its lifetime and the _vm_release_page()
	   * function can manage if it is not the case.
	   */
	  _vm_release_page(region, vaddr);
	  dlist_remove(region->used_pages, p);
	  _vmm_insert_in_free_list(region, &p);
	  return (true);
	}
      p = p->pages_list.next;
    }
  return (false);
}

