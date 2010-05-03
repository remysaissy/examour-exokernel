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

#ifndef	__EXCEPTION_H__
#define	__EXCEPTION_H__

#include	<examour/core/segment_types.h>

/* exceptions number */

/**
 * \brief	Division by zero exception number.
 */
#define	EXCEPTION_DIVIDE_ERROR		0

/**
 * \brief	Debug exception number.
 */
#define	EXCEPTION_DEBUG			1

/**
 * \brief	NMI exception number.
 */
#define	EXCEPTION_NMI_INTR		2

/**
 * \brief	Breakpoint (int3) exception number.
 */
#define	EXCEPTION_BREAKPOINT		3

/**
 * \brief	 Overflow exception number.
 */
#define	EXCEPTION_OVERFLOW		4

/**
 * \brief	Bound exceed exception number.
 */
#define	EXCEPTION_BOUND_EXCEED		5

/**
 * \brief	Invalid opcode exception number.
 */
#define	EXCEPTION_INVL_OPCODE		6

/**
 * \brief	Device not available exception number.
 */
#define	EXCEPTION_DEV_NOT_AVL		7

/**
 * \brief	Double fault exception number.
 */
#define	EXCEPTION_DOUBLE_FAULT		8

/**
 * \brief	Cop seg overrun exception number.
 */
#define	EXCEPTION_COP_SEG_OVERRUN	9

/**
 * \brief	Invalid tss descriptor exception number.
 */
#define	EXCEPTION_INVL_TSS		10

/**
 * \brief	Segment not present exception number.
 */
#define	EXCEPTION_SEGMENT_NOT_PRESENT	11

/**
 * \brief	Stack fault exception number.
 */
#define	EXCEPTION_STACK_FAULT		12

/**
 * \brief	General protection exception number.
 */
#define	EXCEPTION_GENERAL_PROTECTION	13

/**
 * \brief	Page fault exception number.
 */
#define	EXCEPTION_PAGE_FAULT		14

/**
 * \brief	Unused exception number.
 */
#define	EXCEPTION_UNUSED		15

/**
 * \brief	FPU error exception number.
 */
#define	EXCEPTION_FPU_ERROR		16

/**
 * \brief	Alignement check exception number.
 */
#define	EXCEPTION_ALIGNMENT_CHECK	17

/**
 * \brief	Machine check exception number.
 */
#define	EXCEPTION_MACHINE_CHECK		18

/**
 * \brief	SIMD check exception number.
 */
#define	EXCEPTION_SIMD_FPU		19

/**
 * \brief	Maximum exception number.
 */
#define	EXCEPTION_MAX_NUM		20

#ifndef	__ASM__

/* functions */

/* exception handler functions  */

#define	EXCEPTION_ENTRY(id, gtype, code_seg, ring, handler) void handler (void);

#include	"exception.def"

#undef EXCEPTION_ENTRY

#endif /* __ASM__ */

#endif /* __EXCEPTION_H__ */
