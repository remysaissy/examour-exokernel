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

#ifndef	__MM_SYSCALLS_H__
#define	__MM_SYSCALLS_H__

#include	<examour/event/idt.h>

/**
 * \brief	Index of the ldt_create syscall.
 */
#define	SYS_ldt_create		0

/**
 * \brief	Index of the ldt_destroy syscall.
 */
#define	SYS_ldt_destroy		1

/**
 * \brief	Index of the ldt_add_entry syscall.
 */
#define	SYS_ldt_add_entry	2

/**
 * \brief	Index of the ldt_remove_entry syscall.
 */
#define	SYS_ldt_remove_entry	3

#define	SYS_num_mm_syscalls	4

#ifndef	__ASM__

#endif /* __ASM__ */

#endif /* __MM_SYSCALLS_H__ */
