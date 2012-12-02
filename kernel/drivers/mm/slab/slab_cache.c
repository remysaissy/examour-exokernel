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

#include	"slab_cache.h"

/**
 * This file contains the definition of the cache functions
 * for the slab allocator.
 * \todo        Test the functions.
 */

/* Private functions */

/**
 * \param obj		The object to find the belonging slab.
 * \param slabs		The slab list to lookup.
 * \param slab_size	The size of a slab in memory.
 * \brief		Helper function which find which slab an object belongs to.
 */
static inline struct slab_s	*_slab_obj_to_slab(vaddr_t obj, struct slab_s *slabs,
						   uint32_t slab_size)
{
  struct slab_s		*p;

  /* don't forget that slabs is a circular list... */
  p = slabs;
  do
    {
      if (obj >= p->first_obj &&
	  obj <= p->first_obj + slab_size)
	return (p);
      p = p->slab_list.next;
    }  while (p != slabs);
  return (NULL);
}

/**
 * Used by slab_lookup.
 */
#define	SLAB_ONLY_LOOKUP	0

/**
 * Used by slab_lookup.
 */
#define	SLAB_LOOKUP_AND_REMOVE	1

/**
 * \param cache	The cache structure to investigate to find a slab.
 * \param rem	SLAB_LOOKUP_AND_REMOVE if the slab must be removed.
 *		SLAB_ONLY_LOOKUP otherwise.
 * \return	A slab containing a free object, NULL if the cache is full.
 * \brief	Lookup for a free object in the cache.
 */
static inline struct slab_s	*slab_lookup(struct slab_cache_s *cache,
					     uint32_t rem)
{
  if (cache == NULL || cache->free_obj_cnt == 0)
    return (NULL);
  if (cache->partial_slabs)
    {
      if (rem == SLAB_LOOKUP_AND_REMOVE)
	clist_remove(cache->partial_slabs, cache->partial_slabs);
      return (cache->partial_slabs);
    }
  else
    {
      if (rem = SLAB_LOOKUP_AND_REMOVE)
	clist_remove(cache->free_slabs, cache->free_slabs);
      return (cache->free_slabs);
    }
  return (NULL);
}

/**
 * \param cache	The cache for which the new slab is.
 * \return	A pointer to the newly created slab on success, NULL on failure.
 * \brief	Create a new slab for a cache and add it into the cache's free slabs list.
 */
static inline struct slab_s	*slab_create(struct slab_cache_s *cache)
{
  vaddr_t		object;
  struct slab_s		*slab;

  if (cache == NULL)
    return (NULL);
  if ((object = vmm_alloc(cache->slab_pages_cnt, VMM_ALLOC_MAP)) == VADDR_ERROR)
    return (NULL);
  slab = (struct slab_s *)(object + cache->slab_pages_cnt * PAGE_SIZE - sizeof(*slab));
  slab->free_cnt = cache->slab_obj_cnt;
  slab->first_obj = object;
/*   slab->range = VADDR_ERROR; /\* belongs to nothing. *\/ */
/*   slab->cache = cache; */
  /* Initialize the slab's objects. */
  slab->free_obj = (struct free_slab_object_s *)object;
  clist_init(slab->free_obj);
  /* Always add before the head so the list is sorted by memory address. */
  /*
   * The layout of the slab is as follow:
   *
   * +-------------------------------------------+
   * | obj1 | obj2 | ... | objn | slab structure |
   * +-------------------------------------------+
   *
   * This slab is protected because removing it destroys the cache.
   * Obviously the other slabs can have more objects since there
   * is no cache structure in it.
   */
  for (i = 1; i < cache->slab_obj_cnt; i++)
    {
      struct free_slab_object_s	*p;

      p = (struct free_slab_object_s *)
	(slab->first_obj + i * cache->alloc_size);
      clist_add_before(slab->free_obj, slab->free_obj, p);
    }
  cache->free_obj_cnt += cache->slab_obj_cnt;
  /* Insert free slab at the end of the slab list. */
  clist_add_before(cache->free_slabs, cache->free_slabs, slab);
  return (slab);
}

/**
 * \param cache		The cache of the slab to remove.
 * \param slab		The slab to remove.
 * \return		true on success, false on failure.
 * \brief		Destroy a slab and update its cache.
 */
static inline bool	slab_destroy(struct slab_cache_s *cache,
				     struct slab_s **slab)
{
  if (cache == NULL || slab == NULL || *slab == NULL)
    return (false);
  cache->free_obj_cnt -= (*slab)->free_cnt;
  SLAB_REMOVE_FROM_LIST(cache, *slab);
  vmm_free((*slab)->first_obj);
  return (true);
}

/* Frontend functions */

struct slab_cache_s	*slab_cache_create(char *name, size_t obj_size,
					   uint32_t align)
{
  vaddr_t		object;
  struct slab_cache_s	*cache;
  struct slab_s		*slab;
  uint32_t		alloc_size;
  uint32_t		num_pages;
  uint32_t		num_object;
  int			i;

  /**
   * \todo Add ROUNDUP() and PAGE_SIZE in slab_types.h
   *	   Add slab_types.h in the svn repository.
   */
  alloc_size = ROUNDUP(obj_size, align);
  num_pages = alloc_size / PAGE_SIZE + alloc_size % PAGE_SIZE;
  /*
   * If the object fits exactly in one page, add a new one
   * for the cache structure.
   */
  /*
   * Note: I could use a loop to do the job but I prefer two
   * cmoputations and a if statement. I think/hope it is faster...
   */
  if ((num_pages * PAGE_SIZE) - sizeof(*cache) - sizeof(*slab) < alloc_size)
    num_pages++;
  num_object =
    ((num_pages * PAGE_SIZE) - sizeof(*cache) - sizeof(*slab)) / alloc_size;
  /* Allocate the cache along with its first slab. */
  if ((object = vmm_alloc(num_pages, VMM_ALLOC_MAP)) == VADDR_ERROR)
    return (NULL);
  /* The cache is located at the very end of the cache. */
  cache =
    (struct slab_cache_s *)(object + num_pages * PAGE_SIZE - sizeof(*cache));
  /*
   * Unused by the slab_cache. This field is initialized and up to
   * the caller.
   */
  clist_init(cache);
  cache->name = name;
  cache->obj_size = obj_size;
  cache->alloc_size = alloc_size;
  /* initialize the first slab. */
  slab = (struct slab_cache_s *)
    (object + num_pages * PAGE_SIZE - sizeof(*cache) - sizeof(*slab));
  cache->free_slabs = slab;
  cache->partial_slabs = NULL;
  cache->full_slabs = NULL;
  cache->first_slab = (vaddr_t)slab;
  clist_init(slab);
  slab->free_cnt = num_object;
  slab->first_obj = object;
/*   slab->range = VADDR_ERROR; /\* belongs to nothing. *\/ */
/*   slab->cache = cache; */
  /* Initialize the first slab's objects. */
  slab->free_obj = (struct free_slab_object_s *)object;
  clist_init(slab->free_obj);
  /* Always add before the head so the list is sorted by memory address. */
  /*
   * The layout of the first slab is as follow:
   *
   * +-------------------------------------------------------------+
   * | obj1 | obj2 | ... | objn | slab structure | cache structure |
   * +-------------------------------------------------------------+
   *
   * This slab is protected because removing it destroys the cache.
   * Obviously the other slabs can have more objects since there
   * is no cache structure in it.
   */
  for (i = 1; i < num_object; i++)
    {
      struct free_slab_object_s	*p;

      p = (struct free_slab_object_s *)
	(slab->first_obj + i * alloc_size);
      clist_add_before(slab->free_obj, slab->free_obj, p);
    }
  cache->free_obj_cnt = num_object;
  /*
   * Compute the number of object per slab and the number of pages
   * per slab for the normal ones. (not the first slab)
   */
  num_pages = alloc_size / PAGE_SIZE + alloc_size % PAGE_SIZE;
  if ((num_pages * PAGE_SIZE) - sizeof(*slab) < alloc_size)
    num_pages++;
  cache->slab_pages_cnt = num_pages;
  cache->slab_obj_cnt =
    ((num_pages * PAGE_SIZE) - sizeof(*slab)) / alloc_size;
  /*
   * The cache is not put in a cache list, the clist field is here for
   * upper layer use.
   */
  return (cache);
}

bool			slab_cache_destroy(struct slab_cache_s *cache)
{
  struct slab_s		*first_slab;

  if (cache == NULL)
    return (false);
  first_slab = (struct slab_s *)cache->first_slab;
  /* put the first slab at a safe location. */
  SLAB_REMOVE_FROM_LIST(cache, first_slab);
  /* remove the remaining slabs. */
  /* free slabs. */
  while (cache->free_slabs)
    {
      if (slab_destroy(cache, &cache->free_slabs) == false)
	return (false);
    }
  /* partially filled slabs. */
  while (cache->partial_slabs)
    {
      if (slab_destroy(cache, &cache->partial_slabs) == false)
	return (false);
    }
  /* full slabs. */
  while (cache->full_slabs)
    {
      if (slab_destroy(cache, &cache->full_slabs) == false)
	return (false);
    }
  /* Now we can remove the first slab. */
  vmm_free(first_slab->first_obj);
  /* Here the cache has been destroyed. */
  return (true);
}

/**
 * \todo	Presently, RECLAIM is not used. Use it.
 */
vaddr_t			slab_cache_alloc(struct slab_cache_s *cache,
					 uint32_t flags)
{
  struct slab_s		*slab;
  vaddr_t		object;

  if (cache->free_obj_cnt > 0)
    {
      /* always succeed here. */
      slab = slab_lookup(cache, SLAB_LOOKUP_AND_REMOVE);
      /* the slab has been removed from the list. */
    }
  else
    {
      if ((slab = slab_create(cache)) == NULL)
	return (VADDR_ERROR);
    }
  object = (vaddr_t)slab->free_obj;
  clist_remove(slab->free_obj, slab->free_obj);
  slab->free_cnt--;
  cache->free_obj_cnt--;

  /* Reorder the slab in the slab_list. */
  /* First slabs are the full ones. */
  if (slab->free_cnt == 0)
    clist_add_before(cache->full_slabs, slab);
  else
    clist_add_before(cache->partial_slabs, slab);
  if ((flags & SLAB_CREATE_ZERO))
    memset((void *)object, 0, cache->alloc_size);
  return (object);
}

bool			slab_cache_free(struct slab_cache_s *cache,
					vaddr_t obj)
{
  struct slab_s		*slab;

  /* First look for the slab of the object. */

  /* Among the full slabs. */
  slab = cache->full_slabs;
  if ((slab = _slab_obj_to_slab(obj, cache->full_slabs,
				cache->slab_pages_cnt * PAGE_SIZE)))
    clist_remove(cache->full_slabs, slab);
  else
    {
      if ((slab = _slab_obj_to_slab(obj, cache->partial_slabs,
				    cache->slab_pages_cnt * PAGE_SIZE)))
	clist_remove(cache->partial_slabs, slab);
    }
  if (slab)
    {
      struct free_slab_object_s	*new_obj;

      new_obj = (struct free_slab_object_s *)obj;
      clist_add_before(slab->free_obj, new_obj);
      slab->free_cnt++;
      if (slab->free_cnt != cache->slab_obj_cnt)
	clist_add_before(cache->partial_slabs, slab);
      else
	clist_add_before(cache->free_slabs, slab);
      cache->free_obj_cnt++;
      return (true);
    }
  else
    return (false);
}

/* Backend functions */

bool			slab_cache_feed(struct slab_cache_s *cache,
					size_t size)
{
  uint32_t		num_slabs;

  num_slabs = size / (cache->slab_pages_cnt * PAGE_SIZE) +
    size % (cache->slab_pages_cnt * PAGE_SIZE);
  while (num_slabs-- > 0)
    if (slab_create(cache) == NULL)
      return (false);
  return (true);
}

bool			slab_cache_reap(struct slab_cache_s *cache,
					size_t size)
{
  uint32_t		num_slabs;

  num_slabs = size / (cache->slab_pages_cnt * PAGE_SIZE) +
    size % (cache->slab_pages_cnt * PAGE_SIZE);
  while (num_slabs--)
    if (slab_destroy(cache, &cache->free_slabs) == false)
      return (false);
  return (true);
}
