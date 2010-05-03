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

#ifndef	__ENV_SYSCALLS_H__
#define	__ENV_SYSCALLS_H__

#include	<examour/event/idt.h>

/**
 * \brief	Index of the env_create syscall.
 */
#define	SYS_env_create		0

/**
 * \brief	Index of the env_delete syscall.
 */
#define	SYS_env_delete		1

/**
 * \brief	Index of the env_yield syscall.
 */
#define	SYS_env_yield		2

/**
 * \brief	Index of the timeslice_add syscall.
 */
#define	SYS_timeslice_add	3

#define	SYS_num_env_syscalls	4

#ifndef	__ASM__

#endif /* __ASM__ */

#endif /* __ENV_SYSCALLS_H__ */
