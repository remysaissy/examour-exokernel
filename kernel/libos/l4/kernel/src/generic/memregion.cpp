/*
 *  Authors: 
 *    modifiy by Franck Chevallereau (cheval_f@epitech.net)
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
#include "../../include/generic/memregion.h"

inline void mem_region_t::operator += (const mem_region_t & reg)
{
    if (this->low > reg.low) this->low = reg.low;
    if (this->high < reg.high) this->high = reg.high;
}

inline  bool mem_region_t::is_adjacent(const mem_region_t & reg)
{
    return ((this->high == reg.low) ||
	    (this->low == reg.high));
}

inline  bool mem_region_t::is_intersection(const mem_region_t & reg)
{
    return ((reg.low >= this->low) && (reg.low < this->high)) ||
	   ((reg.high > this->low) && (reg.high <= this->high)) ||
	   ((reg.low <= this->low) && (reg.high >= this->high));
}

inline  bool mem_region_t::is_empty()
{
    return high == 0;
}
 
inline  void mem_region_t::set_empty()
{
    high = 0; 
}

inline  void mem_region_t::set(addr_t low, addr_t high)
{ 
    this->low = low; 
    this->high = high; 
}

word_t mem_region_t::get_size()
{
	return is_empty() ? 0 : (word_t)high-(word_t)low; 
}