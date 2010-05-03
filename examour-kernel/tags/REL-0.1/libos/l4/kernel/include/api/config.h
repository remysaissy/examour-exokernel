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
 * 05-04-2006 Chevallereau Franck
 * - config.h creation
 * - L4_FPAGE_BASE_BITS
 *
*/
#ifndef _API_CONFIG_H
#define _API_CONFIG_H

#if defined(CONFIG_IS_32BIT)
#define L4_FPAGE_BASE_BITS	22
#elif defined(CONFIG_IS_64BIT)
#define L4_FPAGE_BASE_BITS	54
#endif /* !_CONFIG_IS_? */

#endif /* !_API_CONFIG_H */
