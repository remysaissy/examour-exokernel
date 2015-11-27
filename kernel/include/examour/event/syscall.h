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
** Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#ifndef	__SYSCALL_H__
#define	__SYSCALL_H__

/**
 * \brief	Syscall declaration and interruption mapping.
 */

#include	"syscall_enum.h"

#ifndef			__ASM__

/**
 * \brief	Generates the prototype of the assembly syscalls
 *		entry points defined in syscall.S.
 */
#define	SYSCALL_ENTRY(ret_type, syscall_name, n_params)	\
	void	asm_ ## syscall_name (void);

#include	<examour/mm/syscalls_mm.def>
#include	<examour/env/syscalls_env.def>
#include	<examour/event/syscalls_event.def>

#undef	SYSCALL_ENTRY

#endif /* __ASM__ */

#endif /* __SYSCALL_H__ */
