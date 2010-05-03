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
 * 31-03-2006 Chevallereau Franck
 * - bitmask.c creation
 * - 
 *
*/
#include <stdlib.h>
#include <string.h>
#include "../include/bitmask.h"

inline bitmask_t::bitmask_t()
{
}

inline bitmask_t::bitmask_t (word_t initvalue)
{
	maskvalue = initvalue;
}

// Modification

inline bitmask_t bitmask_t::operator + (int n)
{
    bitmask_t m (maskvalue | (1UL << n));
    return (m);
}

inline bitmask_t bitmask_t::operator - (int n)
{
    bitmask_t m (maskvalue & ~(1UL << n));
    return (m);
}

inline bitmask_t bitmask_t::operator +=(int n)
{
    maskvalue = maskvalue | (1UL << n);
    return ((bitmask_t) maskvalue);
}

inline bitmask_t bitmask_t::operator -=(int n)
{
    maskvalue = maskvalue & ~(1UL << n);
    return ((bitmask_t) maskvalue);
}

// Predicates

inline bool bitmask_t::is_set(int n)
{
    return ((maskvalue & (1UL << n)) != 0);
}

// Conversion

inline bitmask_t::operator word_t()
{
    return (maskvalue);
}