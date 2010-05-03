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
 * 10-04-2006 Chevallereau Franck
 * - memdesc.h creation
 * - 
 *
*/

#ifndef _API_MEMDESC_H
#define _API_MEMDESC_H

#include "../types.h"
#include "../macros.h"

class memdesc_t
{
private:
	BITFIELD5(word_t,
	_type		: 4,
	_t			: 4,
				: 1,
	_v			: 1,
	_low		: BITS_WORD - 10
	);
	BITFIELD2(word_t,
				: 10,
	_high		: BITS_WORD - 10
	);

public:

    enum type_e {
	undefined		= 0x0,
	conventional	= 0x1,
	reserved		= 0x2,
	dedicated		= 0x3,
	shared			= 0x4,
	max_type
    };

    /**
     * @return type of memory region
     */
	type_e type();

    /**
     * @return subtype of memory region
     */
    word_t subtype();
	
    /**
     * @return true if region is in virtual memory, false otherwise
     */
    bool is_virtual();
	
    /**
     * @return lower address of memory region
     */
    addr_t low();
	
    /**
     * @return upper address of memory region
     */
    addr_t high();
	
    /**
     * @return size of memory region in bytes
     */
    word_t size();

    /**
     * Modify memory descriptor.
     * @param type	new type of descriptor
     * @param t		new subtype of descriptor
     * @param virt	is new descriptor for vitual memory
     * @param low	new lower address of descriptor
     * @param high	new upper address of descriptor
     */
    void set(type_e type, word_t t, bool virt, addr_t low, addr_t high);

    void set(memdesc_t & memdesc);
};



#endif /* !_API_MEMDESC_H */