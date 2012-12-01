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

#ifndef MEM_BLK_H_
#define MEM_BLK_H_

#include	<stdbool.h>
#include	<stdint.h>
#include	<list.h>
#include  	<examem.h>

/* Module internal datatypes. */

/* Must be 32 bytes length. */
typedef struct	__attribute__((aligned(4))) mem_blk_s
{
  dlist_t       by_addr;
  dlist_t	    by_size;
  paddr_t	    address;
  size_t        size;
  uint32_t      count;
  uint32_t      flags;

}				mem_blk_t;

/**
 * The size (real) of a memory block.
 * It is not the size of the header+its content, but only the header
 * which references a content.
 * It must be as least HDR_BLK_SIZE bytes and must be a power of 2.
 */
#define		MEM_BLK_SIZE	(sizeof(mem_blk_t))


/* Module internal functions. */

/**
 * Validates the compatibility of two flags.
 * @return true if flags are compatible, false otherwise.
 */
bool _mem_blk_flags_compat_check(uint32_t flags1, uint32_t flags2);

/**
 * Initialize the memory block manager.
 * @return true on success, false otherwise.
 */
bool		mem_blk_init(void);

/**
 * Populates the memory block manager with a new free memory block.
 * @param	addr	The physical address of the block.
 * @param	size	The size, in bytes, of the block.
 * @param	flags	Flags applied to that block.
 * @return true on success, false otherwise.
 */
bool    	mem_blk_populate(paddr_t addr, size_t size, uint32_t flags);

/**
 * Used by the header memory block manager when it needs a new
 * memory block to map its headers to. The size of the map is in the
 * HDR_MEM_BLK_MAP_SIZE macro.
 * @return true on success, false if no memory left.
 */
bool        _mem_blk_ref_by_size(paddr_t *addr, size_t size, uint32_t flags, void *hdr1, void *hdr2);

/**
 * Allocate a memory block of a given size.
 * @param	size	The size of the block to be allocated.
 * @param	flags	Flags to be applied to the allocated memory.
 * @return	true on success, false otherwise.
 */
bool		mem_blk_ref_by_size(paddr_t *addr, size_t size, uint32_t flags);

/**
 * Allocate a memory block at a given address, size and flags.
 * @param	addr	The physical address of the memory area to allocate.
 * @param	size	The size of the block to be allocated.
 * @param	flags	Flags to be applied to the allocated memory.
 * @return	True on success, false otherwise.
 * @note	The memory can be referenced several times, it depends on its flags.
 * 			If the memory has been previously allocated, flags of the first allocation
 * 			apply, the ones provided here are only for "matching" purpose.
 */
bool	   	mem_blk_ref_by_addr(paddr_t addr, size_t size, uint32_t flags);

/**
 *	Free a memory block.
 *	@param	addr	The physical address of the block to free.
 */
void		mem_blk_unref(paddr_t addr);

#endif /*MEM_BLK_H_*/
