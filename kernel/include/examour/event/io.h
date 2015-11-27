/*
 * This file is part of ExAmour

 * Copyright (C) Remy Saissy <remy.saissy@gmail.com>
 * ExAmour is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.

 * ExAmour is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#ifndef	__CAPS_H__
#define	__CAPS_H__

#include	<examour/event/io_types.h>

#ifndef	__ASM__

#include	<stdbool.h>

/**
 * \brief	Initialize the capability allocator.
 */
void		io_init(void);

/* SYSCALL */
/**
 * \param ioport	The ioport requested.
 * \param exclusive	Exclusive mode or not ?
 * \return		true on success, false otherwise.
 * \brief		Grants a new cap.
 */
bool		io_grant(uint16_t ioport, bool exclusive);

/* SYSCALL */
/**
 * \param ioport	The ioport requested.
 * \return		true on success, false otherwise.
 * \brief		Revoke a cap.
 */
bool		io_revoke(uint16_t ioport);

/**
 * \param eid		The eid to flush.
 * \brief		Flush the caps granted by the env.
 */
void		io_flush(eid_t eid);

#endif /* !__ASM__ */

#endif /* __CAPS_H__ */
