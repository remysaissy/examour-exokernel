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

#include "../../include/api/procdesc.h"


void procdesc_t::set_external_frequency(word_t freq)
{
	external_freq = freq;
}
    
void procdesc_t::set_internal_frequency(word_t freq)
{
	internal_freq = freq;
}
};

