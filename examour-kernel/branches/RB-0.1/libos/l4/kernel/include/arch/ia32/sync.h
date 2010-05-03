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
 * 07-04-2006 Chevallereau Franck
 * - sync.h creation
 * - 
 * - 
 *
*/
#ifndef _ARCH_IA32_SYNC_H
#define _ARCH_IA32_SYNC_H

#include "types.h"

class spinlock_t
{
private:
	word_t	_lock;
public:
	void	init(word_t val = 0);
	void	lock();
	void	unlock();
	bool	is_locked();
};



#endif /* !_ARCH_IA32_SYNC_H */