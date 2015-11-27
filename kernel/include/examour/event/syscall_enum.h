/*
** This file is part of exAmour

** Copyright (C) Remy Saissy <remy.saissy@epitech.net>
** exAmour is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 2 of the License, or
** (at your option) any later version.

** exAmour is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.

** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef	__SYSCALL_ENUM_H__
#define	__SYSCALL_ENUM_H__

/**
 * \brief	Base index of the syscalls in the idt.
 *		That means the first syscall in SYSCALL_LIST
 *		is called through int IDT_BASE_SYSCALL and so on...
 */
#include	<examour/mm/mm_syscalls.h>
#include	<examour/env/env_syscalls.h>
#include	<examour/event/event_syscalls.h>

#define	SYS_base_mm_syscalls	(IDT_BASE_SYSCALL)

#define	SYS_base_env_syscalls	(SYS_base_mm_syscalls+SYS_num_mm_syscalls)

#define	SYS_base_event_syscalls	(SYS_base_env_syscalls+SYS_num_env_syscalls)

/**
 * \brief	total number of syscalls.
 */
#define	SYS_num_syscalls		(SYS_num_mm_syscalls+SYS_num_env_syscalls+SYS_num_event_syscalls)

#endif /* __SYSCALL_ENUM_H__ */
