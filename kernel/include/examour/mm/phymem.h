/*
** This file is part of examour

** Copyright (C) Remy Saissy <remy.saissy@epitech.net>
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

#ifndef	__PHYMEM_H__
#define	__PHYMEM_H__

#include	<examour/mm/mem_types.h>

/* Values of opt in phymem_ref_*(). */
/**
 * \brief	Allocation in the regular zone.
 */
#define	REGULAR_ZONE	0

/**
 * \brief	Allocation in the dma zone.
 */
#define	DMA_ZONE	1

/**
 * \brief	Allocation in the reserved zone (mapped i/o).
 */
#define	RESERVED_ZONE	2

/**
 * \brief	Allocation in exclusive mode.
 */
#define	EXCLUSIVE	4

/**
 * \brief	Mask for zone allocation.
 */
#define	ZONE_MASK	3

#ifndef	__ASM__

#include	<stddef.h>
#include	<stdbool.h>
#include	<libslds/list.h>

/**
 * \brief	Structure of a memory block.
 *		The structure is located at the
 *		end of the memory block. Therefore
 *		at addr + size - sizeof(phymem_block_t)
 */
typedef struct	phymem_block_s
{
  paddr_t	addr;		  /** base address. */
  size_t	size;		  /** size. */
  bool		is_exclusive : 1; /** exclusive flag. */
  uint32_t	ref_cnt : 31;	  /** reference counter. */
  dlist_t	addr_list;	  /** increasing sorted list of addr. */
  dlist_t	size_list;	  /** increasing sorted list of size. */

}		phymem_block_t;

/**
 * \param first_env	The first environment pointer.
 * \param first_env_sz	The size in bytes of the first environment.
 * \brief		Initialize the physical memory allocator.
 */
void	phymem_init(paddr_t *first_env, int first_env_size);

/**
 * \param paddr	The address of the newly allocated memory block. Filled
 *		during the call.
 * \param size	The size in bytes of the requested memory block.
 * \param opt	Hints about the kind of allocation wanted.
 * \return	Returns true on success, false otherwise.
 * \brief	Allocates a physical memory block according to opt.
 */
bool	phymem_ref_new(paddr_t *paddr, size_t size, uint32_t opt);

/**
 * \param paddr	The address of the requested allocated memory block.
 * \param size	The size in bytes of the requested memory block.
 * \param opt	Hints about the kind of allocation wanted.
 * \return	Returns true on success, false otherwise.
 * \brief	Allocates a physical memory block at a given address
 *		and according to opt.
 */
bool	phymem_ref_at(paddr_t paddr, size_t size, uint32_t opt);

/**
 * \param paddr	The address of the memory block to unreference.
 * \brief	unreference a given memory block.
 */
void	phymem_unref(paddr_t paddr);

/**
 * \param flags	Flag to indicate wether to dump the free memory blocks
 *		or the used ones.
 * \brief	Dumps the physical memory allocator state.
 */
void	phymem_dump(int flags);

#endif /* __ASM__ */

#endif /* __PHYMEM_H__ */
