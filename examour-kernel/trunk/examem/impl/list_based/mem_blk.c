/*
** This file is part of ExAmour

** Copyright (C) Rémy Saissy <remy.saissy@gmail.com>
** examour is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 2 of the License, or
** (at your option) any later version.

** examour is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.

** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#include	<stddef.h>
#include	<stdbool.h>
#include	"include/mem_blk.h"
#include	"include/hdr_mem_blk.h"

#include    "../debugging/log.h"

/**
 *
 * This file implements the memory allocator.
 * It does not contain user space level methods.
 * It aims at being platform independent.
 *
 * @todo        Implement a better data structure for by_size nodes. The binary tree presently in use is not consistent for by_size sorting. A list ordered by growing size would be far better.
 * @todo        Implement real flags check. Presently, only a type check matching is performed.
 * @todo        Implement interactions with exaprocess.
 * @todo        Implement tree nodes fusion. Localized in _mem_blk_populate_free.
 */


// TODO: Add support for ALIGNED_*, SCOPE_* flags.

static mem_blk_t	*sgl_mem_blk_used_by_size = NULL;
static mem_blk_t 	*sgl_mem_blk_used_by_address = NULL;

static mem_blk_t	*sgl_mem_blk_free_by_size = NULL;
static mem_blk_t	*sgl_mem_blk_free_by_address = NULL;

/* Helpers. */

/* Validate the compatibility of two flags. */
bool _mem_blk_flags_compat_check(uint32_t flags1, uint32_t flags2)
{
  int   res1;
  int   res2;

  res1 = (flags1 & EXAMEM_TYPE_ALL);
  res2 = (flags2 & EXAMEM_TYPE_ALL);
  if (res1 && res1 == res2)
    return (true);
  return (false);
}

/* Add the entry new described by addr,size and flags in the free list. */
static void  _mem_blk_populate_free(paddr_t addr, size_t size, uint32_t flags, mem_blk_t *new)
{
  mem_blk_t *p;
  mem_blk_t *pp;
  bool      fusion_happened;

  if (new == NULL)
      return;
  new->address = addr;
  new->flags = flags;
  new->size = size;
  new->count = 0;
  do
  {
    fusion_happened = false;
    p = sgl_mem_blk_free_by_address;
    pp = NULL;
    while (p && new->address > p->address)
    {
      pp = p;
      p = p->by_addr.next;
    }
    if (pp && pp->address + pp->size == new->address && _mem_blk_flags_compat_check(pp->flags, new->flags) == true)
    {
      /* fusion before. */
      dlist_remove(sgl_mem_blk_free_by_address, pp, by_addr);
      dlist_remove(sgl_mem_blk_free_by_size, pp, by_size);
      new->address = pp->address;
      new->size += pp->size;
      hdr_mem_blk_free(pp);
      fusion_happened = true;
    }
    if (p && new->address + new->size == p->address && _mem_blk_flags_compat_check(p->flags, new->flags) == true)
    {
      /* fusion after. */
      dlist_remove(sgl_mem_blk_free_by_address, p, by_addr);
      dlist_remove(sgl_mem_blk_free_by_size, p, by_size);
      new->size += p->size;
      hdr_mem_blk_free(p);
      fusion_happened = true;
    }
  } while (fusion_happened == true);
  p = sgl_mem_blk_free_by_address;
  pp = NULL;
  while (p && p->address < new->address)
  {
    pp = p;
    p = p->by_addr.next;
  }
  if (p != NULL)
    dlist_add_before(sgl_mem_blk_free_by_address, p, new, by_addr);
  else
    dlist_add_after(sgl_mem_blk_free_by_address, pp, new, by_addr);
  p = sgl_mem_blk_free_by_size;
  pp = NULL;
  while (p && p->size < new->size)
  {
    pp = p;
    p = p->by_size.next;
  }
  if (p != NULL)
    dlist_add_before(sgl_mem_blk_free_by_size, p, new, by_size);
  else
    dlist_add_after(sgl_mem_blk_free_by_size, pp, new, by_size);
}

/* Insert new described by addr,size and flags in used list. */
static void _mem_blk_populate_used(paddr_t addr, size_t size, uint32_t flags, mem_blk_t *new)
{
  mem_blk_t *p;
  mem_blk_t *pp;

  if (new == NULL)
	  return;
  new->address = addr;
  new->flags = flags;
  new->size = size;
  new->count = 1;
  p = sgl_mem_blk_used_by_address;
  pp = NULL;
  while (p && p->address < new->address)
  {
    pp = p;
    p = p->by_addr.next;
  }
  if (p != NULL)
    dlist_add_before(sgl_mem_blk_used_by_address, p, new, by_addr);
  else
    dlist_add_after(sgl_mem_blk_used_by_address, pp, new, by_addr);
  p = sgl_mem_blk_used_by_size;
  pp = NULL;
  while (p && p->size < new->size)
  {
    pp = p;
    p = p->by_size.next;
  }
  if (p != NULL)
    dlist_add_before(sgl_mem_blk_used_by_size, p, new, by_size);
  else
    dlist_add_after(sgl_mem_blk_used_by_size, pp, new, by_size);
}

/* Remove node from used list. */
static void _mem_blk_unpopulate_used(mem_blk_t *node)
{
  if (node == NULL)
    return;
  dlist_remove(sgl_mem_blk_used_by_address, node, by_addr);
  dlist_remove(sgl_mem_blk_used_by_size, node, by_size);
}

/* Remove the size@addr subpart of node from free list and updates node consequently. */
static void	__mem_blk_unpopulate_free(paddr_t addr, size_t size, mem_blk_t *node, mem_blk_t *hdr1, mem_blk_t *hdr2)
{
  if (node == NULL || hdr1 == NULL || hdr2 == NULL)
  {
    if (hdr1 != NULL)
      hdr_mem_blk_free(hdr1);
    if (hdr2 != NULL)
      hdr_mem_blk_free(hdr2);
    return;
  }
  dlist_remove(sgl_mem_blk_free_by_address, node, by_addr);
  dlist_remove(sgl_mem_blk_free_by_size, node, by_size);
  /* Check if there is a part before size@addr. */
  if (node->address < addr)
   {
          _mem_blk_populate_free(node->address, addr - node->address, node->flags, hdr1);
          node->size -= (addr - node->address);
          node->address = addr;
   }
   else
          hdr_mem_blk_free(hdr1);
  /* Check if there is a part after size@addr. */
   if (size < node->size)
   {
          _mem_blk_populate_free(node->address + size, node->size - size, node->flags, hdr2);
          node->size = size;
   }
   else
          hdr_mem_blk_free(hdr2);
   node->count = 0;
}

/* Remove size@addr from node. */
static bool _mem_blk_unpopulate_free(paddr_t addr, size_t size, mem_blk_t *node)
{
  mem_blk_t *hdr1;
  mem_blk_t *hdr2;

  if (node == NULL)
    return (false);
  if (hdr_mem_blk_get((void **)&hdr1) == false)
      return (false);
  if (hdr_mem_blk_get((void **)&hdr2) == false)
  {
      hdr_mem_blk_free(hdr1);
      return (false);
  }
  __mem_blk_unpopulate_free(addr, size, node, hdr1, hdr2);
   return (true);
}


/* Module API. */

bool		mem_blk_init(void)
{
	hdr_mem_blk_init();
	return (true);
}


bool  mem_blk_populate(paddr_t addr, size_t size, uint32_t flags)
{
  mem_blk_t *new;

  if (hdr_mem_blk_get((void **)&new) == false)
    return (false);
  _mem_blk_populate_free(addr, size, flags, new);
  return (true);
}

bool		_mem_blk_ref_by_size(paddr_t *addr, size_t size, uint32_t flags, void *hdr1, void *hdr2)
{
  mem_blk_t *node;
  paddr_t   aligned_addr;
  uint32_t  align_value;

  if (addr == NULL || size == 0 || hdr1 == NULL || hdr2 == NULL)
    return (false);
  /* Default type is regular. */
  if ((flags & EXAMEM_TYPE_ALL) == 0)
    flags |= EXAMEM_TYPE_REGULAR;
  node = sgl_mem_blk_free_by_address;
  while (node != NULL)
  {
    if ((node->size >= size && _mem_blk_flags_compat_check(node->flags, flags) == true))
    {
      aligned_addr = node->address;
      align_value = 0;
      switch ((flags & EXAMEM_ALIGNED_ALL))
      {
        case EXAMEM_ALIGNED_8B:
          align_value = 0x7;
          break;
        case EXAMEM_ALIGNED_16B:
          align_value = 0xf;
          break;
        case EXAMEM_ALIGNED_4KB:
          align_value = 0xfff;
          break;
        case EXAMEM_ALIGNED_4MB:
          align_value = 0x3FFFFF;
          break;
        case EXAMEM_ALIGNED_NONE:
          align_value = 0;
          break;
        default:
          align_value = 0xf;
      }
      while ((aligned_addr & align_value) != 0)
        ++aligned_addr;
      if (aligned_addr + size > node->address + node->size)
      {
          node = node->by_size.next;
          continue;
      }
      __mem_blk_unpopulate_free(aligned_addr, size, node, hdr1, hdr2);
      node->flags = flags;
      _mem_blk_populate_used(node->address, node->size, node->flags, node);
      *addr = node->address;
      return (true);
    }
    node = node->by_size.next;
  }
  hdr_mem_blk_free(hdr1);
  hdr_mem_blk_free(hdr2);
  return (false);
}

/* lookup by size. */
bool        mem_blk_ref_by_size(paddr_t *addr, size_t size, uint32_t flags)
{
  void      *hdr1;
  void      *hdr2;

  if (addr == NULL)
    return (false);
  if (hdr_mem_blk_get(&hdr1) == false)
    return (false);
  if (hdr_mem_blk_get(&hdr2) == false)
  {
    hdr_mem_blk_free(hdr1);
    return (false);
  }
  return (_mem_blk_ref_by_size(addr, size, flags, hdr1, hdr2));
}

bool    	mem_blk_ref_by_addr(paddr_t addr, size_t size, uint32_t flags)
{
	mem_blk_t	*node;

	  /* Default type is regular. */
	  if ((flags & EXAMEM_TYPE_ALL) == 0)
	    flags |= EXAMEM_TYPE_REGULAR;
	node = sgl_mem_blk_used_by_address;
	while (node && node->address != addr)
	  node = node->by_addr.next;
	if (node == NULL)
	{
	  node = sgl_mem_blk_free_by_address;
	     while (node && (addr < node->address || addr + size > node->address + node->size))
	       node = node->by_addr.next;
	  if (node == NULL || _mem_blk_flags_compat_check(node->flags, flags) == false)
	    return (false);
	  if (_mem_blk_unpopulate_free(addr, size, node) == false)
	    return (false);
	  node->flags = flags;
	  _mem_blk_populate_used(node->address, node->size, node->flags, node);
	}
	else
	{
      if (node->size != size)
          return (false);
      if (_mem_blk_flags_compat_check(node->flags, flags) == false)
          return (false);
      node->count++;
	}
	return (true);
}

void		mem_blk_unref(paddr_t addr)
{
  mem_blk_t *node;

  node = sgl_mem_blk_used_by_address;
  while (node && node->address != addr)
    node = node->by_addr.next;
  if (node == NULL)
    return;
  if (node->count == 1)
  {
    _mem_blk_unpopulate_used(node);
    _mem_blk_populate_free(node->address, node->size, node->flags, node);
  }
  else
    node->count--;
}
