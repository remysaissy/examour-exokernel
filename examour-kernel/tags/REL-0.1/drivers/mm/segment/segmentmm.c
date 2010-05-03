/*
 * This file is part of ExAmour

 * Copyright (C) Remy Saissy <remy.saissy@gmail.com>
 * ExAmour is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.

 * ExAmour is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/* Simple slab implementation along with the segmented memory manager. */
/* The manager basically copies the data section in a new segment. */

#include	<examour/event/syscall.h>
#include	<string.h>
#include	<list.h>
#include	"../../video/vga/vga.h"
#include	"segmentmm.h"

#define		_16B_BLOCKS	0
#define		_32B_BLOCKS	1
#define		_64B_BLOCKS	2
#define		_256B_BLOCKS	3
#define		_1KB_BLOCKS	4
#define		_4KB_BLOCKS	5
#define		_8KB_BLOCKS	6
#define		_32KB_BLOCKS	7
#define		NSIZES		8

typedef struct	slab_object_s
{
  dlist_t	object_list;

}		slab_object_t;

static slab_object_t	*blocks[] =
  {
    [_16B_BLOCKS] = NULL,
    [_32B_BLOCKS] = NULL,
    [_64B_BLOCKS] = NULL,
    [_256B_BLOCKS] = NULL,
    [_1KB_BLOCKS] = NULL,
    [_4KB_BLOCKS] = NULL,
    [_8KB_BLOCKS] = NULL,
    [_32KB_BLOCKS] = NULL
  };


/* data area delimiters from the ld script. */
uint32_t	data_start;
uint32_t	data_end;

static void	init_mm(size_t amount)
{
  slab_object_t	*obj;
  char		*p;
  int		i;

  p = (char *)&data_end;
  /* 10 32kb blocks. */
  for (i = 0; i < 10; i++)
    {
      obj = (slab_object_t *)p;
      _dlist_add_head((void **)(blocks + _32KB_BLOCKS),
		      (void *)(obj),
		      0);
      p += 0x8000;		/* 32kb. */
    }
  /* 10 8kb blocks. */
  for (i = 0; i < 10; i++)
    {
      obj = (slab_object_t *)p;
      _dlist_add_head((void **)(blocks + _8KB_BLOCKS),
		      (void *)(obj),
		      0);
      p += 0x2000;		/* 8kb. */
    }
  /* 20 4kb blocks. */
  for (i = 0; i < 20; i++)
    {
      obj = (slab_object_t *)p;
      _dlist_add_head((void **)(blocks + _4KB_BLOCKS),
		      (void *)(obj),
		      0);
      p += 0x1000;		/* 4kb. */
    }
  /* 20 1kb blocks. */
  for (i = 0; i < 20; i++)
    {
      obj = (slab_object_t *)p;
      _dlist_add_head((void **)(blocks + _1KB_BLOCKS),
		      (void *)(obj),
		      0);
      p += 0x400;		/* 1kb. */
    }
  /* 30 256kb blocks. */
  for (i = 0; i < 30; i++)
    {
      obj = (slab_object_t *)p;
      _dlist_add_head((void **)(blocks + _256B_BLOCKS),
		      (void *)(obj),
		      0);
      p += 256;		/* 256b. */
    }
  /* 40 64b blocks. */
  for (i = 0; i < 40; i++)
    {
      obj = (slab_object_t *)p;
      _dlist_add_head((void **)(blocks + _64B_BLOCKS),
		      (void *)(obj),
		      0);
      p += 64;		/* 64b. */
    }
  /* 60 32b blocks. */
  for (i = 0; i < 60; i++)
    {
      obj = (slab_object_t *)p;
      _dlist_add_head((void **)(blocks + _32B_BLOCKS),
		      (void *)(obj),
		      0);
      p += 32;		/* 32b. */
    }
/*   /\* 400 16b blocks. *\/ */
/*   for (i = 0; i < 400; i++) */
/*     { */
/*       obj = (slab_object_t *)p; */
/*       _dlist_add_head((void **)(blocks + _16B_BLOCKS), */
/* 		      (void *)(obj), */
/* 		      0); */
/*       p += 16;		/\* 16b. *\/ */
/*     } */

  /* Now the memory is initialized. */

}

bool		segmentmm_init(size_t amount)
{
  uint32_t	old_ds;
  uint32_t	old_es;
  uint32_t	new_data_sel;

  new_data_sel = _segmentmm_init(amount);
  if (new_data_sel == PADDR_ERROR)
    return (false);
  new_data_sel <<= 3;
  new_data_sel |= 7;
  _copy_to_buffer(new_data_sel, (uint32_t)&data_start, (uint32_t)&data_end - (uint32_t)&data_start);
  __asm__ volatile ("movl %%ds, %%eax": "=a"(old_ds));
  __asm__ volatile ("movl %%es, %%eax": "=a"(old_es));
  /* \todo	It doesn't work... */
/*   __asm__ volatile ("int %0" */
/* 		    :: "i"(SYS_base_mm_syscalls+SYS_ldt_remove_entry), */
/* 		    "b"(NULL), */
/* 		    "c"(old_ds)); */
/*   if (old_es != old_ds) */
/*     { */
/*       __asm__ volatile ("int %0" */
/* 			:: "i"(SYS_base_mm_syscalls+SYS_ldt_remove_entry), */
/* 			"b"(NULL), */
/* 			"c"((old_es >> 3) & 0x1fff)); */
/*     } */

/*   /\* now the old data segment has been removed, set the new data segments in the address space. *\/ */

  __asm__ volatile ("movl %%eax, %%ds; movl %%eax, %%es" :: "a" (new_data_sel));
  __asm__ volatile ("movl %%eax, %%fs; movl %%eax, %%gs" :: "a" (new_data_sel));
  init_mm(amount);
  /* Now set the malloc/free variables. */
  return (true);
}


void		*malloc(size_t size)
{
  char		*p;
  int		idx;

  p = NULL;
  if (size < 0x8000)
    idx = _32KB_BLOCKS;
  else
    return (NULL);
  if (size < 0x2000)
    idx = _8KB_BLOCKS;
  if (size < 0x1000)
    idx = _4KB_BLOCKS;
  if (size < 0x400)
    idx = _1KB_BLOCKS;
  if (size < 256)
    idx = _256B_BLOCKS;
  if (size < 64)
    idx = _64B_BLOCKS;
  if (size < 32)
    idx = _32B_BLOCKS;
  if (size < 16)
    idx = _16B_BLOCKS;
  p = (void *)blocks[idx];
  _dlist_remove((void **)(blocks + idx),
		(void *)(p),
		0);
  if (p)
    {
      *p = (char)idx;
      p++;
    }
   return (p);
}


void		*calloc(size_t nmemb, size_t size)
{
  void		*p;

  p = malloc(nmemb * size);
  if (p)
    memset(p, 0, nmemb * size);
  return (p);
}

void		free(void *p)
{
  slab_object_t	*obj;
  char		idx;
  char		*p2;

  p2 = (char *)p;
  p2--;
  idx = *p2;
  obj = (slab_object_t *)(p2);
  _dlist_add_head((void **)(blocks + idx),
		  (void *)(obj),
		  0);
}

char		*strdup(const char *s)
{
  char		*ret;
  int		sz;

  sz = strlen(s);
  ret = malloc(sz + 1);
  if (ret == NULL)
    return (NULL);
  strncpy(ret, s, sz);
  ret[sz] = 0;
  return (ret);
}
