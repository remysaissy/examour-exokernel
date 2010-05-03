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

#ifndef	__EVENT_SYSCALLS_H__
#define	__EVENT_SYSCALLS_H__

#include	<examour/event/idt.h>

/**
 * \brief	Index of the cap_grant syscall.
 */
#define	SYS_io_grant		0

/**
 * \brief	Index of the cap_revoke syscall.
 */
#define	SYS_io_revoke		1

/**
 * \brief	Index of the event_register syscall.
 */
#define	SYS_event_register	2

/**
 * \brief	Index of the event_unregister syscall.
 */
#define	SYS_event_unregister	3

/**
 * \brief	Forge an event.
 */
#define	SYS_event_forge		4

/**
 * \brief	Raise a forged event.
 */
#define	SYS_event_throw		5

#define	SYS_num_event_syscalls	6

#ifndef	__ASM__

#endif /* __ASM__ */

#endif /* __EVENT_SYSCALLS_H__ */
