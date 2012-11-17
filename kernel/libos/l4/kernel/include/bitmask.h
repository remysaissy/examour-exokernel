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
/* 31-03-2006 Chevallereau Franck
 * - bitmask.h creation
 * - typedef bitmask_t
 * - function definition of : bitmask_add and bitmask_sub
 *
*/

#ifndef _BITMASK_H
#define _BITMASK_H

#include "./arch/ia32/types.h"

class bitmask_t
{
    word_t	maskvalue;

public:

    // Constructors

    inline bitmask_t();
    inline bitmask_t(word_t initvalue);

    // Modification

    inline bitmask_t operator + (int n);
	
    inline bitmask_t operator - (int n);

    inline bitmask_t operator +=(int n);
   
    inline bitmask_t operator -=(int n);

    // Predicates

    inline bool is_set(int n);

    // Conversion

    inline operator word_t();

	
};


#endif /* !_BITMASK_H */