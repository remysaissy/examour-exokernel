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

#ifndef HDR_MEM_BLK_H_
#define HDR_MEM_BLK_H_

#include    <stdint.h>
#include	<stdbool.h>
#include	<list.h>

/* Module internal datatypes. */

/**
 * The size of a memory block map is 4Kb.
 */
#define	HDR_MEM_BLK_MAP_SIZE	(1 << 12)

/**
 * Header memory block as it is when it is on the waiting stack.
 * The double linked list is used instead of a stack because
 * it allows further optimization in order to decrease superfluous
 * memory blocks dedicated to HMB.
 */
typedef struct		hdr_mem_blk_s
{
	slist_t			entries;

}					hdr_mem_blk_t;

/**
 * Size (virtual) of a header block when it is in the waiting stack of the
 * header memory block manager.
 */
#define	HDR_BLK_SIZE		(sizeof(mem_blk_t))

/**
 * The number of blocks per block map.
 */
#define HDR_BLK_BY_MAP      (HDR_MEM_BLK_MAP_SIZE / HDR_BLK_SIZE)

/* Module internal functions. */

/**
 * Initialize the memory header block.
 */
void  hdr_mem_blk_init(void);

/**
 * Get a new header block from the waiting stack.
 * @return true on success, false if no memory left.
 */
bool	hdr_mem_blk_get(void **hdr);

/**
 * Give a memory header block back to HMB.
 */
void	hdr_mem_blk_free(void *hdr);

/**
 * Rationalizes the number of blocks available.
 */
void    hdr_mem_blk_rationalize(void);

/**
 * Get the number of blocks available.
 */
uint32_t    hdr_mem_blk_get_counter(void);

#endif /*HDR_MEM_BLK_H_*/
