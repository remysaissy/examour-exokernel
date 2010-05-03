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
 * - kmemory.cpp creation
 * - 
 *
*/

#include "../include/kmemory.h"

inline void * kmem_t::alloc (kmem_group_t * group, word_t size)
{
    return (alloc(size));
}

inline void * kmem_t::alloc_aligned (kmem_group_t * group, word_t size,
		word_t alignment, word_t mask)
{
    return (alloc_aligned(size, alignment, mask));
}

inline void kmem_t::free (kmem_group_t * group, void * address, word_t size)
{
    free(address, size);
}
void	kmem_t::add(void *address, word_t size)
{
	free(address, size);
}