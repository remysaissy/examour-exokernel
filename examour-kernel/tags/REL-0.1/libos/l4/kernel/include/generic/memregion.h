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

#ifndef _GENERIC_MEMREGION_H
#define _GENERIC_MEMREGION_H

#include "../types.h"

/**
 * mem_region_t:
 */
class mem_region_t
{
public:
    addr_t	low;
    addr_t	high;

	bool is_adjacent(const mem_region_t & reg);
    bool is_intersection(const mem_region_t & reg);
    bool is_empty();
    void set_empty();
    void operator += (const mem_region_t & reg);
    void set(addr_t low, addr_t high);
    word_t get_size();
};

#endif /* !_GENERIC_MEMREGION_H*/
