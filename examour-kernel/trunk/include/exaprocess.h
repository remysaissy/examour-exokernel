/*
** This file is part of ExAmour

** Copyright (C) Remy Saissy <remy.saissy@gmail.com>
** examour is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 2 of the License, or
** (at your option) any later version.

** examour is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.

** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#ifndef EXAPROCESS_H_
#define EXAPROCESS_H_

#include	<stdbool.h>
#include	<stddef.h>
#include	<stdint.h>
#include	<list.h>

#include	"exaboot.h"

/******************* Public data structures *****************************/

/**
 * A process identifier.
 */
typedef unsigned long	pid_t;

/**
 * Exabus's namespace.
 */
#define	EXAPROCESS_NAMESPACE	"kernel.process"

/**
 * The interface of exaprocess.
 *
 * Content of kernel.event.exaprocess:
 *
 */
#define	EXAPROCESS_INTERFACE	"exaprocess"


/******************* Kernel data structures *****************************/

/**
 * Description of a process.
 */
typedef struct	exaprocess_s
{
	pid_t			   pid; /** Pid of the process. */
	clist_t        entries;    /** The process list. */

}				exaprocess_t;

/********************** Kernel internal API *******************************/

/**
 * Initialize exaprocess.
 * @param   inf exaboot informations about the machine.
 * @return  true on success, false otherwise.
 */
bool			_exaprocess_init(const exaboot_t * const inf);

/********************** Public API ****************************************/

/**
 * Retrieve the current process's pid.
 * @return  the current process's pid.
 */
pid_t       exaprocess_get_current_pid(void);

/**
 * Grants an I/O to the current process. (call from exaevent).
 * @param   ioport The ioport requested for grant.
 */
void        exaprocess_grant_io(uint16_t ioport);

/**
 * Revoke an I/O from the current process. (call from exaevent).
 * @param   ioport The I/O port to revoke.
 */
void        exaprocess_revoke_io(uint16_t ioport);

/**
 * Switch to the next process.
 */
void        exaprocess_switch(void);
#endif /* EXAPROCESS_H_ */
