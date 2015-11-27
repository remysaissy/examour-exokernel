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

#ifndef	__ASM_TOOLKIT_H__
#define	__ASM_TOOLKIT_H__

/**
 * This file contains a set of assembly macros useful in environment programming.
 * \warning This file must be used along with seg_wrapper.S from the toolkit directory.
 */

#include	<examour/event/syscall.h> /** for IDT_BASE_SYSCALL */

#ifdef	__ASM__

/**
 * syscalls list. This list must be synchronized with examour/syscall.def
 * \todo I must find a better way to do it...
 */

/**
 * \brief	Creates a new ldt entry int number.
 */
#define	SYS_LDT_CREATE		IDT_BASE_SYSCALL

/**
 * \brief	Destroy a new ldt entry int number.
 */
#define	SYS_LDT_DESTROY		SYS_LDT_CREATE+1

/**
 * \brief	Add an ldt entry int number.
 */
#define	SYS_LDT_ADD_ENTRY	SYS_LDT_DESTROY+1

/**
 * \brief	Remove an ldt entry int number.
 */
#define	SYS_LDT_REMOVE_ENTRY	SYS_LDT_ADD_ENTRY+1

/**
 * \brief	Grant a cap int number.
 */
#define	SYS_CAP_GRANT		SYS_LDT_REMOVE_ENTRY+1

/**
 * \brief	Remove a cap int number.
 */
#define	SYS_CAP_REVOKE		SYS_CAP_GRANT+1

/**
 * \brief	Creates an env int number.
 */
#define	SYS_ENV_CREATE		SYS_CAP_REVOKE+1

/**
 * \brief	Deletes an env int number.
 */
#define	SYS_ENV_DELETE		SYS_ENV_CREATE+1

/**
 * \brief	Yield an env int number.
 */
#define	SYS_ENV_YIELD		SYS_ENV_DELETE+1

/**
 * \brief	Request timeslice int number.
 */
#define	SYS_TIMESLICE_ADD	SYS_ENV_YIELD+1

/**
 * \param segreg	Segment register name
 * \param address	Offset to linearize.
 * \return		The linearized address in eax
 * \brief		Linearize an offset according to a segment register.
 *			Must be used when providing addressed to syscalls.
 */
/* .macro	linearize_address	segreg, address */
/*	pushl	\segreg */
/*	call	get_segment_base_address */
/*	addl	$4,		%esp */
/*	addl	\address,	%eax */
/* .endm */


#endif /* __ASM__ */


#endif /* __ASM_TOOLKIT_H__ */
