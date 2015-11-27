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

/* exAmour's memory manager layer 0 */
/* Physical memory manager */
/** \todo	A torture test function. A better backend algorithm. */

#include	<examour/mm/phymem.h>
#include	<examour/mm/mem.h>
#include	<examour/support/log.h>
#include	<examour/core/globals.h>
#include	<examour/core/multiboot.h>
#include	<examour/event/io.h>

/** Index of the list sorted by address. */
#define	ADDR_LIST	0
/** Index of the list sorted by size. */
#define	SIZE_LIST	1
/** Number of lists for every type track. */
#define	N_LIST		2

/** The reserved zone used blocks of memory.  */
static	phymem_block_t	*reserved_used[N_LIST] = {NULL, NULL};
/** The reserved zone free blocks of memory.  */
static	phymem_block_t	*reserved_free[N_LIST] = {NULL, NULL};

/** The dma zone used blocks of memory.  */
static	phymem_block_t	*dma_used[N_LIST] = {NULL, NULL};
/** The dma zone free blocks of memory.  */
static	phymem_block_t	*dma_free[N_LIST] = {NULL, NULL};

/** The regular zone used blocks of memory.  */
static	phymem_block_t	*regular_used[N_LIST] = {NULL, NULL};
/** The regular zone free blocks of memory.  */
static	phymem_block_t	*regular_free[N_LIST] = {NULL, NULL};

/** Variable located at the physical address where the kernel starts. */
uint32_t		_start;
/** Variable located at the physical address where the kernel ends. */
uint32_t		_end;


/* Helper functions */

/**
 * \param blocks	The track to use.
 * \param size		The size in bytes to look for.
 * \brief		Lookup for a block which has at least the requested
 *			size.
 * \warning		Both size and addr are sorted by increasing value.
 */
static inline phymem_block_t	*_approx_by_size(phymem_block_t **blocks,
						 size_t size)
{
  phymem_block_t		*p;

  if (blocks == NULL)
    return (NULL);
  p = blocks[SIZE_LIST];
  while (p)
    {
      if (p->size >= size)
	return (p);
      p = p->addr_list.next;
    }
  return (NULL);
}


/**
 * \param blocks	The track to use.
 * \param size		The size in bytes to look for.
 * \param paddr		The physical address to look for.
 * \return		The block on success, NULL on error.
 * \brief		Lookup for a block which matchs the requested size
 *			and physical address.
 * \warning		Both size and addr are sorted by increasing value.
 */
static inline phymem_block_t	*_lookup_by_size_addr(phymem_block_t **blocks,
						      size_t size,
						      paddr_t paddr)
{
  phymem_block_t		*p;

  if (blocks == NULL)
    return (NULL);
  p = blocks[ADDR_LIST];
  while (p)
    {
      if (p->addr == paddr && p->size == size)
	return (p);
      p = p->addr_list.next;
    }
  return (NULL);
}

/**
 * \param blocks	The track to use.
 * \param size		The size in bytes to look for.
 * \param paddr		The physical address to look for.
 * \return		The block on success, NULL on error.
 * \brief		Lookup for a block which includes the requested block
 *			bounded by paddr and size within.
 * \warning		Both size and addr are sorted by increasing value.
 */
static inline phymem_block_t	*_approx_by_size_addr(phymem_block_t **blocks,
						      size_t size,
						      paddr_t paddr)
{
  phymem_block_t		*p;

  if (blocks == NULL)
    return (NULL);
  p = blocks[ADDR_LIST];
  while (p)
    {
      if (p->addr >= paddr && p->addr + p->size >= paddr + size)
	return (p);
      p = p->addr_list.next;
    }
  return (NULL);
}

/**
 * \param blocks	The track to use.
 * \param paddr		The physical address to look for.
 * \return		The block on success, NULL on error.
 * \brief		Lookup for a block which matchs the requested physical
 *			address.
 * \warning		Both size and addr are sorted by increasing value.
 */
static inline phymem_block_t	*_lookup_by_addr(phymem_block_t **blocks,
						 paddr_t paddr)
{
  phymem_block_t		*p;

  if (blocks == NULL)
    return (NULL);
  p = blocks[ADDR_LIST];
  while (p)
    {
      if (p->addr == paddr)
	return (p);
      p = p->addr_list.next;
    }
  return (NULL);
}

/**
 * \param blocks	The track to use.
 * \param block		The block to merge.
 * \brief		Remove a block from a track.
 * \warning		Both size and addr are sorted by increasing value.
 */
static inline void		_remove(phymem_block_t **blocks,
					phymem_block_t *block)
{
  dlist_remove(blocks[SIZE_LIST], block, size_list);
  dlist_remove(blocks[ADDR_LIST], block, addr_list);
}

/**
 * \param blocks	The track to use.
 * \param block		The block to split.
 * \param size		The size in bytes of the new block.
 * \return		The new block on success, NULL on error.
 * \brief		Split a given block to create a new block of a given
 *			size.
 * \warning		Both size and addr are sorted by increasing value.
 */
static inline phymem_block_t	*_split(phymem_block_t **blocks,
					phymem_block_t *block,
					size_t size)
{
  phymem_block_t		*new;

  if (block->size > size)
    {
      new = (phymem_block_t *)(block->addr + size - sizeof(*new));
      new->addr = block->addr;
      new->size = size;
      block->addr += size;
      block->size -= size;
    }
  else
    {
      if (block->size == size)
	{
	  _remove(blocks, block);
	  new = block;
	}
      else
	{
	  panic("Critical split physical memory block error."
		" requested size too big.\n");
	  new = NULL;
	}
    }
  return (new);
}


/**
 * \param blocks	The track to use.
 * \param block		The block to merge.
 * \brief		Insert a block in a track.
 * \warning		Both size and addr are sorted by increasing value.
 */
static inline void		_add(phymem_block_t **blocks,
				     phymem_block_t *block)
{
  phymem_block_t		*p;
  phymem_block_t		*prev;
  phymem_block_t		*p2;
  phymem_block_t		*prev2;

  if (blocks == NULL || block == NULL)
    return;
  prev = NULL;
  p = blocks[ADDR_LIST];
  while (p)
    {
      if (p->addr < block->addr)
	{
	  /* We've found the next node in the addr_list. */
	  break;
	}
      prev = p;
      p = p->addr_list.next;
    }
  prev2 = NULL;
  p2 = blocks[SIZE_LIST];
  while (p2)
    {
      if (p->size < block->size)
	{
	  /* We've found the next node in the size_list. */
	  break;
	}
      prev2 = p2;
      p2 = p2->size_list.next;
    }
  dlist_add_after(blocks[ADDR_LIST], prev, block, addr_list);
  dlist_add_after(blocks[SIZE_LIST], prev2, block, size_list);
}

/**
 * \param blocks	The track to use.
 * \param block		The block to split.
 * \param size		The size in bytes of the new block.
 * \param paddr		The physical address where the split must begin.
 * \return		The new block on success, NULL on error.
 * \brief		Split a given block at paddr to create a new block
 *			of a given size.
 * \warning		Both size and addr are sorted by increasing value.
 */
static inline phymem_block_t	*_split_at_addr(phymem_block_t **blocks,
						phymem_block_t *block,
						size_t size,
						paddr_t paddr)
{
  phymem_block_t		*new;

  if (block->size > size)
    {
      _remove(blocks, block);
      /* Is there is a split before. */
      if (block->addr != paddr)
	{
	  new = (phymem_block_t *)(paddr - sizeof(*new));
	  new->addr = block->addr;
	  new->size = paddr - block->addr;
	  block->addr = paddr;
	  block->size -= new->size;
	  _add(blocks, new);
	}
      /* Is there is a split after. */
      if (block->size != size)
	{
	  new = (phymem_block_t *)(block->addr + size - sizeof(*new));
	  new->addr = block->addr; /* paddr is the same. */
	  new->size = size;
	  block->addr += size;
	  block->size -= size;
	  _add(blocks, block);
	  block = new;
	}
    }
  else
    {
      if (block->size == size)
	_remove(blocks, block);
      else
	panic("Critical split physical memory block error. requested size too big.\n");
    }
  return (block);
}

/**
 * \param blocks	The track to use.
 * \param block		The block to merge.
 * \brief		Insert a block in a track and tries to merge it.
 * \warning		Both size and addr are sorted by increasing value.
 */
static inline void		_merge(phymem_block_t **blocks,
				       phymem_block_t *block)
{
  phymem_block_t		*p;
  phymem_block_t		*prev;
  phymem_block_t		*tmp;

  if (blocks == NULL || block == NULL)
    return;
  prev = NULL;
  p = blocks[ADDR_LIST];
  while (p)
    {
      if (p->addr < block->addr)
	{
	  /* We've found the next node in the addr_list. */
	  break;
	}
      prev = p;
      p = p->addr_list.next;
    }
  /* Here is the addr_list merge code. */
  if (prev)
    {
      if (prev->addr + prev->size == block->addr)
	{
	  /* merge before */
	  tmp = prev->addr_list.prev;
	  dlist_remove(blocks[ADDR_LIST], prev, addr_list);
	  block->size += prev->size;
	  block->addr = prev->addr;
	  prev = tmp;
	}
    }
  if (p)
    {
      if (block->addr + block->size == p->addr)
	{
	  /* merge after */
	  tmp = p->addr_list.prev;
	  dlist_remove(blocks[ADDR_LIST], p, addr_list);
	  p->size += block->size;
	  p->addr = block->addr;
	  prev = tmp;
	}
    }
  dlist_add_after(blocks[ADDR_LIST], prev, block, addr_list);

  prev = NULL;
  p = blocks[SIZE_LIST];
  while (p)
    {
      if (p->size < block->size)
	{
	  /* We've found the next node in the size_list. */
	  break;
	}
      prev = p;
      p = p->size_list.next;
    }
  dlist_add_after(blocks[SIZE_LIST], prev, block, size_list);
}

/* Functions */

void			phymem_init(paddr_t *first_env, int first_env_sz)
{
  int			total_memory;
  size_t		tmp;
  phymem_block_t	*p;
  paddr_t		reloc_init;

  /* use the mbi structure in order to initialize the memory map. */
  /* memory is in kb but we need the number of bytes. */
  total_memory = (mbi->mem_upper + 1024) * 1024;

  /* The block header is at the end of the block. */
  p = (phymem_block_t *)(((char *)total_memory) - sizeof(*p));
  p->addr = 0x1000000;	/* It begins at 16MB, right after the Dma. */
  p->size = total_memory - 0x1000000;
  p->is_exclusive = false;
  p->ref_cnt = 0;
  dlist_init(p, addr_list);
  dlist_init(p, size_list);
  regular_free[ADDR_LIST] = p;
  regular_free[SIZE_LIST] = p;

  /* Now we have the first memory block, Initialize the Reserved zone */
  /* and the Dma zone. */

  /* The Dma zone */
  p = (phymem_block_t *)(((char *)0x1000000) - sizeof(*p));
  p->addr = 0x100000;	/* It begins at 1MB, right after the Reserved. */
  p->size = 0x1000000 - 0x100000;
  p->is_exclusive = false;
  p->ref_cnt = 0;
  dlist_init(p, addr_list);
  dlist_init(p, size_list);
  dma_free[ADDR_LIST] = p;
  dma_free[SIZE_LIST] = p;

  if (phymem_ref_new(&reloc_init,
		     first_env_sz,
		     REGULAR_ZONE|EXCLUSIVE) == false)
    panic("Unable to allocate init memory blocks.\n");

  memcpy((void *)reloc_init, (void *)*first_env, first_env_sz);

  *first_env = reloc_init;

  if (phymem_ref_at((paddr_t)&_start,
		    (paddr_t)&_end - (paddr_t)&_start,
		    DMA_ZONE|EXCLUSIVE) == false)
    panic("Unable to allocate kernel memory blocks.\n");

  /* The reserved zone */
  tmp = 11 * sizeof(*p);
  if (phymem_ref_new((paddr_t *)&p,
		     tmp,
		     REGULAR_ZONE|EXCLUSIVE) == false)
    panic("Unable to allocate reserved zone memory blocks.\n");

  p->addr = 0xf0000;
  p->size = 0x10000;
  p->is_exclusive = false;
  p->ref_cnt = 0;
  _add(reserved_free, p);

  p[1].addr = 0xc0000;
  p[1].size = 0x8000;
  p[1].is_exclusive = false;
  p[1].ref_cnt = 0;
  _add(reserved_free, p + 1);

  p[2].addr = 0xb8000;
  p[2].size = 0x8000;
  p[2].is_exclusive = false;
  p[2].ref_cnt = 0;
  _add(reserved_free, p + 2);

  p[3].addr = 0xb0000;
  p[3].size = 0x8000;
  p[3].is_exclusive = false;
  p[3].ref_cnt = 0;
  _add(reserved_free, p + 3);

  p[4].addr = 0xa0000;
  p[4].size = 0x10000;
  p[4].is_exclusive = false;
  p[4].ref_cnt = 0;
  _add(reserved_free, p + 4);

  p[5].addr = 0x9fc00;
  p[5].size = 0x400;
  p[5].is_exclusive = false;
  p[5].ref_cnt = 0;
  _add(reserved_free, p + 5);

  p[6].addr = 0x9fc00;
  p[6].size = 0x400;
  p[6].is_exclusive = false;
  p[6].ref_cnt = 0;
  _add(reserved_free, p + 6);

  p[7].addr = 0x500;
  p[7].size = 0x9f900;
  p[7].is_exclusive = false;
  p[7].ref_cnt = 0;
  _add(reserved_free, p + 7);

  p[8].addr = 0x500;
  p[8].size = 0x9f900;
  p[8].is_exclusive = false;
  p[8].ref_cnt = 0;
  _add(reserved_free, p + 8);

  p[9].addr = 0x400;
  p[9].size = 0x100;
  p[9].is_exclusive = false;
  p[9].ref_cnt = 0;
  _add(reserved_free, p + 9);

  p[10].addr = 0;
  p[10].size = 0x400;
  p[10].is_exclusive = false;
  p[10].ref_cnt = 0;
  _add(reserved_free, p + 10);
}

/* Attempt to allocate a new blk_sz set of physical blocks. */
/* the ref_cnt of every block must be 0. */
/* size is expressed in bytes. */
bool			phymem_ref_new(paddr_t *paddr,
				       size_t size,
				       uint32_t opt)
{
  phymem_block_t	*new;

  if (paddr == NULL)
    return (false);
  size += sizeof(*new);
  switch ((opt & ZONE_MASK))
    {
    case REGULAR_ZONE:
      new = _approx_by_size(regular_free, size);
      if (new == NULL)
	return (false);
      new = _split(regular_free, new, size);
      _add(regular_used, new);
      break;
    case DMA_ZONE:
      new = _approx_by_size(dma_free, size);
      if (new == NULL)
	return (false);
      new = _split(dma_free, new, size);
      _add(dma_used, new);
      break;
    case RESERVED_ZONE:
    default:
      return (false);
    };
  *paddr = new->addr;
  if ((opt & EXCLUSIVE))
    new->is_exclusive = true;
  new->ref_cnt = 1;
  return (true);
}

/* same as ref_new but here we don't care of the ref_cnt. */
bool			phymem_ref_at(paddr_t addr,
				      size_t size,
				      uint32_t opt)
{
  phymem_block_t	*new;

  size += sizeof(*new);
  switch ((opt & ZONE_MASK))
    {
    case REGULAR_ZONE:
      new = _lookup_by_size_addr(regular_free, size, addr);
      if (new == NULL)
	{
	  new = _lookup_by_size_addr(regular_used, size, addr);
	  if (new == NULL || new->is_exclusive == true)
	    return (false);
	}
      else
	{
	  new = _split(regular_free, new, size);
	  _add(regular_used, new);
	  new->ref_cnt = 0;
	}
      break;
    case DMA_ZONE:
      new = _lookup_by_size_addr(dma_free, size, addr);
      if (new == NULL)
	{
	  new = _lookup_by_size_addr(dma_used, size, addr);
	  if (new == NULL)
	    {
	      new = _approx_by_size_addr(dma_free, size, addr);
	      if (new)
		{
		  new = _split_at_addr(dma_free, new, size, addr);
		  _add(dma_used, new);
		  break;
		}
	      return (false);
	    }
	  if (new->is_exclusive == true)
	    return (false);
	}
      else
	{
	  new = _split(dma_free, new, size);
	  _add(dma_used, new);
	  new->ref_cnt = 0;
	}
      break;
    case RESERVED_ZONE:
      new = _lookup_by_size_addr(reserved_free, size, addr);
      if (new == NULL)
	{
	  new = _lookup_by_size_addr(reserved_used, size, addr);
	  if (new == NULL || new->is_exclusive == true)
	    return (false);
	}
      else
	{
	  _remove(reserved_free, new);
	  _add(reserved_used, new);
	  new->ref_cnt = 0;
	}
      break;
    default:
      return (false);
    };
  if ((opt & EXCLUSIVE))
    new->is_exclusive = true;
  new->ref_cnt++;
  return (true);
}

void			phymem_unref(paddr_t addr)
{
  phymem_block_t	*new;

  new = _lookup_by_addr(regular_used, addr);
  if (new == NULL)
    {
      new = _lookup_by_addr(dma_used, addr);
      if (new == NULL)
	{
	  new = _lookup_by_addr(reserved_used, addr);
	  if (new == NULL)
	    return;
	  _remove(reserved_used, new);
	  _add(reserved_free, new);
	}
      else
	{
	  _remove(dma_used, new);
	  _merge(dma_free, new);
	}
    }
  else
    {
      _remove(regular_used, new);
      _merge(regular_free, new);
    }
  new->ref_cnt = 0;
}


#if 0
static inline void	_dump_list(phymem_block_t **blocks, char *s)
{
  phymem_block_t	*p;

  if (blocks == NULL || s == NULL)
    return;
  message("%s by addr: ", s);
  p = blocks[ADDR_LIST];
  while (p)
    {
      message("[%p:%pB] ", p->addr, p->size);
      p = p->addr_list.next;
    }
  message("\n%s by size: ", s);
  p = blocks[SIZE_LIST];
  while (p)
    {
      message("[%p:%pB] ", p->addr, p->size);
      p = p->size_list.next;
    }
  message("\n");
}

void			phymem_dump(int flag)
{


  if (flag == 0)
    {
      message("\nRegular:\n");
      _dump_list(regular_free, "free");
      message("\nDma:\n");
      _dump_list(dma_free, "free");
      message("\nReserved:\n");
      _dump_list(reserved_free, "free");
    }
  else
    {
      message("\nRegular:\n");
      _dump_list(regular_used, "used");
      message("\nDma:\n");
      _dump_list(dma_used, "used");
      message("\nReserved:\n");
      _dump_list(reserved_used, "used");
    }
}
#endif
