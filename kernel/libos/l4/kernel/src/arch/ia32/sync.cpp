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
 * - sync.cpp creation
 * - first version of init, lock, unlock and is_locked
 *
 * TODO : this is not really thread safe so... use volatile asm...
 *
*/

#include "../../../include/arch/ia32/sync.h"

void	spinlock_t::init(word_t val)
{
	this->_lock= val;
}

void	spinlock_t::lock()
{
	// volatile??? maybe after ;)
	this->_lock = 1;
}

void	spinlock_t::unlock()
{
	this->_lock = 0;
}

bool		spinlock_t::is_locked()
{
	if (_lock == 0)
	{
		return (true);
	}
	else
	{
		return (true);
	}
}
