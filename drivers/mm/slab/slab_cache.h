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

/**
 * This header contains the declaration of the cache manager for the
 * slab allocator's memory manager.
 * Without precision, the page size is 4kb.
 * \todo	Maybe I should handle alloc errors in a more complex way,
 *		there is two kind of errors : no physical memory left and
 *		no virtual space left. for physical memory I can reclaim
 *		memory from the other environments but for the virtual
 *		space I can't. Either I can allocate a new vmm region
 *		automaticaly or let the caller doing it. By now I leave
 *		the caller doing it but there is no proper return error code...
 *		In spite of it, by now the cache_create doesn't provide any
 *		information about the vm region to use along with it...
 */

#ifndef	__SLAB_CACHE_H__
#define	__SLAB_CACHE_H__

/**
 * Allocate a slab and map it.
 * If no object left, ask to the vmm
 * for a new slab. Return false if no memory
 * left on the system.
 * Default behavior.
 */
#define	SLAB_CREATE_MAP		0

/**
 * Allocate a slab and zero its content.
 */
#define	SLAB_CREATE_ZERO	1

/**
 * Reclaim and wait for memory if no memory left.
 * \warning     By reclaiming we mean ask to the other
 *		environments, reclaim new slabs to the
 *		vmm is an implicit and automatic behavior.
 */
#define	SLAB_CREATE_RECLAIM	2


#ifndef	__ASM__

#include	<queue.h>
#include	<stdint.h>
#include	<stddef.h>
#include	<stdbool.h>
#include	"slab_types.h"	/* Can be removed if you already have the types within. */
#include	"slab.h"

/**
 * A cache of the slab allocator.
 * The cache is the top level structure
 * of the slab allocator.
 */
struct	slab_cache_s
{
  clist_t	cache_list;	/** list of caches. */
  char		*name;		/** name of the cache. (for debugging) */
  size_t	obj_size;	/** user supplied size for objects of the slab. */
  size_t	alloc_size;	/** aligned size for objects of the slab. */
  uint32_t	slab_obj_cnt;	/** number of object per slab. */
  uint32_t	slab_pages_cnt;	/** number of pages per slab. */
  uint32_t	free_obj_cnt;	/** number of free objects in the cache. */
  uint32_t	first_slab;	/** the slab where the cache is located. */
  struct slab_s	*free_slabs;	/** free slabs of the cache. */
  struct slab_s	*partial_slabs;	/** partially full slabs of the cache. */
  struct slab_s	*full_slabs;	/** full slabs of the cache. */

};

/* Helper macros */

/**
 * \param cache	The cache of the slab.
 * \param slab	The slab to remove.
 * \brief	Removes a slab from its slab list.
 */
#define	SLAB_REMOVE_FROM_LIST(cache, slab)		\
do							\
{							\
  if ((slab)->free_cnt == 0)				\
    clist_remove((cache)->free_slabs, (slab));		\
  else							\
    {							\
      if ((slab)->free_cnt == (cache)->slab_obj_cnt)	\
	clist_remove((cache)->full_slabs, (slab));	\
      else						\
	clist_remove((cache)->partial_slabs, (slab));	\
    }							\
} while (0)


/* Front end functions. */

/**
 * \param name		Name of the cache to create. Used for debugging.
 * \param obj_size	Size of the objects in the cache.
 * \param align		Alignment to perform on objects. 0 means not aligned.
 * \return		An allocated empty cache structure or NULL on failure.
 * \brief		Create a new object cache.
 * \warning		Alignement is bound to 4KB.
 */
struct slab_cache_s	*slab_cache_create(char *name, size_t obj_size,
					   uint32_t align);

/**
 * \param cache		Structure of the cache to destroy.
 * \return		true on success, false on error.
 * \brief		Destroy a cache. All slabs and their respective objects
 *			sent back to the vmm.
 * \warning		If the function returns false, the status of the cache
 *			is unpredictable; only some slabs can have been removed.
 *			In the present implementation, free slabs are first removed,
 *			then partially filled slabs and at last full slabs.
 */
bool			slab_cache_destroy(struct slab_cache_s *cache);

/**
 * \param cache		The cache structure to where the objects are located.
 * \param flags		Flags to define a behavior during allocation.
 * \return		The virtual address of the object on success, NULL on error.
 * \brief		Allocate a new object. Take it from the cache and feed it if
 *			necessary.
 */
vaddr_t			slab_cache_alloc(struct slab_cache_s *cache,
					 uint32_t flags);

/**
 * \param cache		The cache structure of the object to free.
 * \param obj		The virtual address of the object to free.
 * \return		true on success, false on failure.
 * \brief		Give an object back to the cache.
 */
bool			slab_cache_free(struct slab_cache_s *cache,
					vaddr_t obj);

/* Backend functions */

/**
 * \param cache		The cache to feed.
 * \param size		The number of bytes we want the cache to request.
 * \return		true on success, false on failure.
 * \brief		Tells the cache to request some food.
 */
bool			slab_cache_feed(struct slab_cache_s *cache,
					size_t size);

/**
 * \param cache		The cache to reaped.
 * \param size		The number of bytes we need to reap from the cache.
 * \return		true on success, false on error.
 * \brief		Reap memory from a cache. If there is not enough memory
 *			that can be reaped, false is returned but a part of the memory
 *			have been reaped.
 */
bool			slab_cache_reap(struct slab_cache_s *cache,
					size_t size);

#endif /* !__ASM__ */

#endif /* __SLAB_CACHE_H__ */
