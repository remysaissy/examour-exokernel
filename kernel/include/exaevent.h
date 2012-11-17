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

#ifndef EXAEVENT_H_
#define EXAEVENT_H_

#include        <stdbool.h>
#include		<stdint.h>
#include        "exaboot.h"

/* Public Datatypes */

/**
 * Exabus's namespace.
 */
#define	EXAEVENT_NAMESPACE	"kernel.event"

/**
 * The interface of exaevent.
 *
 * Content of kernel.event.exaevent:
 */
#define	EXAEVENT_INTERFACE	"exaevent"

/* Kernel internal Datatypes */


/**********************************************/
/* Kernel API. */

/**
 *  Initialize exaevent.
 */
bool    _exaevent_init(const exaboot_t * const inf);

/* Public API. It is bounded to exabus. */

bool	exaevent_register(/* TODO: determines the arguments. */);

bool	exaevent_unregister(/* TODO: determine the arguments. */);

bool	exaevent_iogrant(uint16_t ioport);

bool	exaevent_iorevoke(uint16_t ioport);

#endif /*EXAEVENT_H_*/
