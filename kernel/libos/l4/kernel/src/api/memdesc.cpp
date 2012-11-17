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
 * - memdesc.c creation
 * - 
 *
*/

#include "../../include/api/memdesc.h"

memdesc_t::type_e	memdesc_t::type()
{
	return ((type_e)_type);
}

word_t	memdesc_t::subtype()
{ 
	return ((word_t)_t);
}

bool	memdesc_t::is_virtual ()
{
	return (_v);
}

addr_t	memdesc_t::low()
{
	return ((addr_t)(_low << 10));
}

addr_t	memdesc_t::high(void)
{
	return ((addr_t)((_high << 10) + 0x3ff)); 
}

word_t	memdesc_t::size(void)
{
	return ((_high-_low+1) << 10);
}

void	memdesc_t::set(type_e type, word_t t, bool virt, addr_t low, addr_t high)
{
    _type = type;
    _t    = t;
    _v    = virt;
    _low  = ((word_t) low) >> 10;
    _high = ((word_t) high) >> 10;
}

void memdesc_t::set(memdesc_t & memdesc)
{
    *this = memdesc;
}