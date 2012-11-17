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
#include    <list.h>

#include	"include/hdr_mem_blk.h"
#include	"include/mem_blk.h"

/* The first slab of memory header blocks. */
static	char	*sgl_first_hdr_slab[HDR_MEM_BLK_MAP_SIZE];

/* The memory header block list. This list is sorted by increasing memory address. */
static	hdr_mem_blk_t	*sgl_hdr_mem_blk;

/* Internal header block counter. For tracking. */
static	uint32_t     sgl_hdr_mem_blk_count;

/* Helper functions. */

static  void    __hdr_mem_blk_add_block(hdr_mem_blk_t *blk)
{
  hdr_mem_blk_t *p;
  hdr_mem_blk_t *pp;

  if (blk == NULL)
    return;
  pp = NULL;
  p = sgl_hdr_mem_blk;
  while (p != NULL && (paddr_t)blk > (paddr_t)p)
  {
    pp = p;
    p = p->entries.next;
  }
  if (pp == NULL)
    slist_add_head(sgl_hdr_mem_blk, blk, entries);
  else
    slist_add_after(sgl_hdr_mem_blk, pp, blk, entries);
  ++sgl_hdr_mem_blk_count;
}

static hdr_mem_blk_t  *__hdr_mem_blk_remove_block(hdr_mem_blk_t *blk)
{
  hdr_mem_blk_t *p;

  if (blk != NULL)
    p = blk;
  else
      p = sgl_hdr_mem_blk;
  slist_remove(sgl_hdr_mem_blk, p, entries);
  --sgl_hdr_mem_blk_count;
  return (p);
}

/* API */

uint32_t    hdr_mem_blk_get_counter(void)
{
  return (sgl_hdr_mem_blk_count);
}

void  hdr_mem_blk_init(void)
{
	int		i;

	sgl_hdr_mem_blk = NULL;
	sgl_hdr_mem_blk_count = 0;
	/* Ok, we have a new slab of HDR_MEM_BLK_MAP_SIZE bytes to slice. */
	for (i = 0; i < HDR_MEM_BLK_MAP_SIZE; i += MEM_BLK_SIZE)
	  __hdr_mem_blk_add_block((hdr_mem_blk_t *)(sgl_first_hdr_slab + i));
}

bool	hdr_mem_blk_get(void **hdr)
{
	if (hdr == NULL)
		return (false);
	/* There is a big problem... or init was not called yet. */
	if (sgl_hdr_mem_blk == NULL)
		return (false);
	*hdr = __hdr_mem_blk_remove_block(NULL);
	if (sgl_hdr_mem_blk_count == 1)
	{
		/* This is the last header block. Let's request a new slab. */
		hdr_mem_blk_t	*p;
		hdr_mem_blk_t   *hdr2;
		char		    *slab;
        int             i;

		p = *hdr;
		hdr2 = __hdr_mem_blk_remove_block(NULL);
		if (_mem_blk_ref_by_size((paddr_t *)&slab, HDR_MEM_BLK_MAP_SIZE, EXAMEM_TYPE_REGULAR | EXAMEM_ALIGNED_4KB, (void *)p, (void *)hdr2) == true)
		{
          /* Ok, we have a new slab. */
          for (i = 0; i < HDR_MEM_BLK_MAP_SIZE; i += MEM_BLK_SIZE)
          {
                p = (hdr_mem_blk_t *)(slab + i);
                __hdr_mem_blk_add_block(p);
          }
          *hdr = __hdr_mem_blk_remove_block(NULL);
		}
		else
		{
          /**
           * Don't give that memory block.
           */
          /* TODO: think about a disaster recovery procedure. (reclaim memory?) */
            *hdr = NULL;
            return (false);
        }
    }
	return (true);
}

void	hdr_mem_blk_free(void *hdr)
{
	if (hdr == NULL)
		return;
	__hdr_mem_blk_add_block(hdr);
}

void    hdr_mem_blk_rationalize(void)
{
  hdr_mem_blk_t *p;
  hdr_mem_blk_t *tmp;
  hdr_mem_blk_t *next;
  hdr_mem_blk_t *marker;
  int           counter;

  p = sgl_hdr_mem_blk;
  /* first_slab is excluded. */
  while (p && (paddr_t)p <= ((paddr_t)sgl_first_hdr_slab + HDR_MEM_BLK_MAP_SIZE))
    p = p->entries.next;
  while (p != NULL)
  {
    /* go to the first 4kb aligned blocks. */
    while (p && ((paddr_t)p & 0xfff))
      p = p->entries.next;
    if (p != NULL)
    {
      /* We have found a candidate. */
      marker = p;
      counter = 0;
      while (p != NULL && counter < HDR_BLK_BY_MAP && (paddr_t)p->entries.next == (paddr_t)p + MEM_BLK_SIZE)
      {
        p = p->entries.next;
        ++counter;
      }
      if (counter == HDR_BLK_BY_MAP)
      {
        /* We can remove that slice. */
        tmp = marker;
        while (tmp != p)
        {
          next = tmp->entries.next;
          slist_remove(tmp, tmp, entries);
          tmp = next;
        }
        mem_blk_unref((paddr_t)marker);
      }
      else
        p = marker->entries.next;
    }
  }
}
