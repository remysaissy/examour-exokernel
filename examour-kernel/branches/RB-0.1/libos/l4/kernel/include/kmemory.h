/*
 *  Authors: 
 *    modified by Franck Chevallereau (cheval_f@epitech.net)
 * 
 *  Copyright:
 *	  Copyright (C) 2003,  Karlsruhe University
 * 
 *  This file is part of Pistachio
 * 
 *  See the file "PISTACHIO LICENSE" for information on usage and redistribution 
 *  of this file, and for a DISCLAIMER OF ALL WARRANTIES.
 *  
 */
/*
 * 06-04-2006 Chevallereau Franck
 * - kmemory.h creation
 * - functions definition
 * - 
 *
*/

/*
 *
 * TODO : 
 * - declare kmem_t
 * - kmem_t must be thread safe
 * - all ...
 */
/*
 *
 * - alloc() function allocates size bytes of memory and returns a
 *     pointer to the allocated memory. alloc() returns a NULL pointer if
 *     there is an error.
 * - realloc() function tries to change the size of the allocation pointed
 *     to by ptr to size, and return ptr.  If there is not enough room to
 *     enlarge the memory allocation pointed to by ptr, realloc() creates a new
 *     allocation, copies as much of the old data pointed to by ptr as will fit
 *     to the new allocation, frees the old allocation, and returns a pointer to
 *     the allocated memory.  realloc() returns a NULL pointer if there is an
 *     error, and the allocation pointed to by ptr is still valid.
 *
 * - free() function deallocates the memory allocation pointed to by ptr.
 *
*/

#ifndef _KMEMORY_H
#define _KMEMORY_H

#include "./arch/ia32/types.h"
#include "./arch/ia32/sync.h"

class kmem_group_t
{
public:
    word_t	mem;
    char *	name;
};

class kmem_t
{
    word_t		*kmem_free_list;
    word_t		free_chunks;
    spinlock_t	spinlock;

    void		free(void * address, word_t size);
    void		*alloc(word_t size);
    void		*alloc_aligned(word_t size, word_t alignement, word_t mask);

public:
    void		init(void * start, void * end);
    void		free(kmem_group_t * group, void * address, word_t size);
    void		*alloc(kmem_group_t * group, word_t size);
    void		*alloc_aligned(kmem_group_t * group, word_t size, word_t alignment,
				word_t mask);

    void		add(void * address, word_t size);
	

    friend class kdb_t;
};


/* THE kernel memory allocator */
extern kmem_t kmem;

#endif /* !_KMEMORY_H */