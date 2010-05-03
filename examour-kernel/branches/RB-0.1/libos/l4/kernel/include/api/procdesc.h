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

#ifndef _API_PROCDESC_H
#define _API_PROCDESC_H

//#if !defined(ASSEMBLY)

// make sure sizeof(procdesc_t) == 2^n
class procdesc_t
{
public:
    word_t external_freq;
    word_t internal_freq;
    word_t freq_change;

    /*
     * Usage:
     *   ia64	ITC frequency
     */
    word_t arch1;

public:
    void set_external_frequency(word_t freq);
    void set_internal_frequency(word_t freq);
};


//#endif /* !ASSEMBLY */
//
//#if defined(CONFIG_IS_64BIT)
//#define KIP_PROC_DESC_LOG2SIZE	5
//#else
//#define KIP_PROC_DESC_LOG2SIZE	4
//#endif

#endif /* !_API_PROCDESC_H */
