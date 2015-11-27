/*
** This file is part of exAmour

** Copyright (C) Remy Saissy <remy.saissy@epitech.net>
** exAmour is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 2 of the License, or
** (at your option) any later version.

** exAmour is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.

** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

/**
 * This header contains the declaration of the slab manager for the
 * slab allocator's memory manager.
 * Without precision, the page size is 4kb.
 */


#ifndef	__SLAB_H__
#define	__SLAB_H__

#ifndef	__ASM__

#include	<queue.h>
#include	<stdint.h>
#include	"slab_types.h"	/* can be removed if you already have the types within. */

struct	free_slab_object_s
{
  clist_t	object_list;	/** list of free objects. */

};

/**
 * A slab.
 */
struct slab_s
{
  clist_t			slab_list;	/** list of slabs. */
  uint32_t			free_cnt;	/** number of free objects. */
  struct free_slab_object_s	*free_obj;	/** list of free objects. */
  uint32_t			first_obj;	/** memory address of the beginning of the slab. */
/*   vaddr_t			range;		/\** memory range of the slab. *\/ */
/*   void				*cache;		/\** cache of the slab. *\/ */

};

#endif /* !__ASM__ */

#endif /* __SLAB_H__ */

