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

#ifndef	__VMM_H__
#define	__VMM_H__

/**
 * This header contains declarations for the slab allocator's
 * virtual memory regions manager.
 * Without precision, the page size is 4kb.
 * \todo	The vmm doesn't allow us to control where the region
 *		is allocated. Maybe it could be useful...
 */

/**
 * Allocate a memory region mapped to physical memory.
 * Default behavior.
 */
#define	VMM_ALLOC_MAP	0

/**
 * Allocate a memory region not mapped to physical memory.
 * \warning the caller will get a page fault if it access to this memory.
 */
#define	VMM_ALLOC_NOMAP	1

/**
 * Reclaim physical memory from the rest of the system if none is available.
 */
#define	VMM_RECLAIM	2

#ifndef	__ASM__

#include	<queue.h>
#include	<stdint.h>
#include	"slab_types.h"	/* can be removed if you already have the types within. */


struct	vmm_pages_s
{
  _clist_t	pages_list;	/** list of free pages. */
  uint32_t	offset;		/** offset of the page. (4kb aligned) */

};

/**
 * A virtual memory region.
 */
struct	vm_region_s
{
  _clist_t	region_list;	/** list of virtual memory regions. */
  vaddr_t	region_base;	/** base address of the region. */
  uint32_t	free_pages_cnt;	/** number of free pages in the region. */
  uint32_t	total_pages_cnt; /** total number of pages in the region. */
  uint32_t	default_perms;	/** permission of the pages of the region. */
  uint32_t	default_options; /** mapping behavior of the pages of the region. */
  struct vmm_pages_s	*used_pages; /** list of free pages in the region. */
  struct vmm_pages_s	*free_pages; /** list of free pages in the region. */

};

/**
 * The virtual memory manager data structure.
 */
struct	vmm_s
{
  struct vm_region_s	*regions; /** list of allocated regions. */
  uint32_t		total_regions_cnt; /** total number of regions. */
  vaddr_t		vmm_addr;	/** base virtual address of the vmm management structures. */
  uint32_t		vmm_total_pages; /** maximum number of the vmm pages. */
  uint32_t		vmm_pages_cnt; /** current number of vmm pages. */
  struct vmm_pages_s	*vmm_pages; /** vmm management structures pages. */
};

/**
 * \param vmm_struct	Offset of virtual memory to put the vmm management structures.
 * \param size		Maximmum size of the vmm management structure area.
 * \return		true on success, false on failure.
 * \brief		Initialize the virtual memory manager.
 */
bool			vmm_init(vaddr_t vmm_struct, size_t size);

/**
 * \param base_addr	Base virtual address of the region.
 * \param size		Size, in bytes, of the region.
 * \param perms		Permission to apply to the memory pages of the region.
 * \param options	Options to apply to the region.
 * \return		A pointer to the region management structure on success,
 *			NULL on error.
 * \brief		Allocate a new virtual addressing region within the
 *			virtual memory space of the running environment.
 */
struct vm_region_s	*vmm_create_region(vaddr_t base_addr, size_t size,
					   uint32_t perms, uint32_t options);

/**
 * \param region	The region to destroy.
 * \return		true on success, false on error.
 * \brief		Destroy a virtual memory region.
 */
bool			vmm_destroy_region(struct vm_region_s *region);

/**
 * \param region	The region of the pages.
 * \param num_pages	The number of pages to allocate. (4kb pages)
 * \param flags		Flags to apply during allocation.
 * \return		The virtual memory address on success,
 *			VADDR_ERROR on failure.
 * \brief		Allocate a new virtual memory set of pages.
 * \warning		If both NOMAP and RECLAIM flags are set, the allocator
 *			will put some pages unmapped to physical memory if not enough
 *			memory left and if the reclaim fails.
 * \todo		Code the behavior of NOMAP and RECLAIM and the behavior of RECLAIM.
 */
vaddr_t			vmm_alloc(struct vm_region_s *region, uint32_t num_pages);

/**
 * \param region	The region of the page.
 * \param vaddr		The virtual memory to be freed.
 * \return		true on success, false on failure.
 * \brief		Free a virtual memory page previously allocated.
 */
bool			vmm_free(struct vm_region_s *region, vaddr_t vaddr);


#endif /* !__ASM__ */

#endif /* __VMM_H__ */
