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

#include	<examour/core/segment_types.h>
#include	<examour/event/exception.h>
#include	<examour/core/asm.h>
#include	<examour/mm/mem_types.h>

.text

/* TODO: use exception.def with a new flag to specify if wether of not */
/* an error code comes along with the exception. */

/*
 * This file contains the exceptions wrappers routines.
 * By now they don't call any function but in future they'll
 * call the task associated one.
 */

/*
 * Note that no register saving is provided since it is the job
 * of the userspace handler in an exokernel. The purpose of those
 * routines is only to manage the boring and mandatory work.
 */

/*
 * The exceptions routines are generated within the irp loop
 * The only information which is pushed onto the stack is
 * the exception number, therefore we have the following layout:
 * | ss
 * | esp             ---> like ss, only if there was a priv switch
 * | eflags
 * | cs
 * | eip
 * | error code	     ---> 0 means no particular error code
 * | registers (segment selectors, gp)
 * | exception number
 */

/*
 * Loop of with error code exceptions
 */

/* invl tss */
.globl examour_do_exception_10
examour_do_exception_10:
	/* error code to 0 */
	pushl	$0
	pushl   $EXCEPTION_INVL_TSS
	jmp	generic_exception_isr


/* Segment not present */
.globl examour_do_exception_11
examour_do_exception_11:
	/* error code to 0 */
	pushl	$0
	pushl   $EXCEPTION_SEGMENT_NOT_PRESENT
	jmp	generic_exception_isr

/* stack fault */
.globl examour_do_exception_12
examour_do_exception_12:
	/* error code to 0 */
	pushl	$0
	pushl   $EXCEPTION_STACK_FAULT
	jmp	generic_exception_isr

/* General protection */
.globl examour_do_exception_13
examour_do_exception_13:
	/* error code to 0 */
	pushl	$0
	pushl   $EXCEPTION_GENERAL_PROTECTION
	jmp	generic_exception_isr

/* Page fault */
.globl examour_do_exception_14
examour_do_exception_14:
	/* error code to 0 */
	pushl	$0
	pushl   $EXCEPTION_PAGE_FAULT
	jmp	generic_exception_isr

/* Alignment check */
.globl examour_do_exception_17
examour_do_exception_17:
	/* error code to 0 */
	pushl	$0
	pushl   $EXCEPTION_ALIGNMENT_CHECK
	jmp	generic_exception_isr


/* Divide error */
.globl examour_do_exception_0
examour_do_exception_0:
	/* error code to 0 */
	pushl	$0
	pushl   $EXCEPTION_DIVIDE_ERROR
	jmp	generic_exception_isr

/* exception debug */
.globl examour_do_exception_1
examour_do_exception_1:
	/* error code to 0 */
	pushl	$0
	pushl   $EXCEPTION_DEBUG
	jmp	generic_exception_isr

/* nmi intr */
.globl examour_do_exception_2
examour_do_exception_2:
	/* error code to 0 */
	pushl	$0
	pushl   $EXCEPTION_NMI_INTR
	jmp	generic_exception_isr

/* breakpoint */
.globl examour_do_exception_3
examour_do_exception_3:
	/* error code to 0 */
	pushl	$0
	pushl   $EXCEPTION_BREAKPOINT
	jmp	generic_exception_isr

/* overflow */
.globl examour_do_exception_4
examour_do_exception_4:
	/* error code to 0 */
	pushl	$0
	pushl   $EXCEPTION_OVERFLOW
	jmp	generic_exception_isr

/* bound exceed */
.globl examour_do_exception_5
examour_do_exception_5:
	/* error code to 0 */
	pushl	$0
	pushl   $EXCEPTION_BOUND_EXCEED
	jmp	generic_exception_isr

/* invl opcode */
.globl examour_do_exception_6
examour_do_exception_6:
	/* error code to 0 */
	pushl	$0
	pushl   $EXCEPTION_INVL_OPCODE
	jmp	generic_exception_isr

/* dev not avl */
.globl examour_do_exception_7
examour_do_exception_7:
	/* error code to 0 */
	pushl	$0
	pushl   $EXCEPTION_DEV_NOT_AVL
	jmp	generic_exception_isr

/* cop seg overrun */
.globl examour_do_exception_9
examour_do_exception_9:
	/* error code to 0 */
	pushl	$0
	pushl   $EXCEPTION_COP_SEG_OVERRUN
	jmp	generic_exception_isr

/* fpu error */
.globl examour_do_exception_16
examour_do_exception_16:
	/* error code to 0 */
	pushl	$0
	pushl   $EXCEPTION_FPU_ERROR
	jmp	generic_exception_isr

/* machine check */
.globl examour_do_exception_18
examour_do_exception_18:
	/* error code to 0 */
	pushl	$0
	pushl   $EXCEPTION_MACHINE_CHECK
	jmp	generic_exception_isr

/* simd fpu */
.globl examour_do_exception_19
examour_do_exception_19:
	/* error code to 0 */
	pushl	$0
	pushl   $EXCEPTION_SIMD_FPU
	jmp	generic_exception_isr


/* hardcoded handlers. */
/* (for system stability requirements) */

/* EXCEPTION_DOUBLE_FAULT	8 */

.globl examour_do_exception_8

examour_do_exception_8:

	/* error code to 0 */
	pushl	$0
	pushl   $EXCEPTION_DOUBLE_FAULT

	pushl	%ds
	pushl	%es
	pushl	%fs
	pushl	%gs
	pushl	%eax
	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%edx
	pushl	%ecx
	pushl	%ebx


/* install the kernel data segment to be able to access to gl_current_env. */
	movw	$(GDT_SEG_KDATA << 3),%ax
	movw	%ax,%ds
	movw	%ax,%es

/* save esp0. */
	movl	gl_current_env,%eax
	subl	$4,		 %eax
	movl	%esp,(%eax)

	pushl	(%esp)

	call	do_unhandled

/* move toward the stack0 of the new env. */
/* restore its esp0. */
	movl	gl_current_env,%eax
	subl	$4,		 %eax
	movl	(%eax),		 %esp

	orl	$(EFLAGS_INTR), EFLAGS_OFFSET(%esp)
	popl	%ebx
	popl	%ecx
	popl	%edx
	popl	%esi
	popl	%edi
	popl	%ebp
	popl	%eax
	popl	%gs
	popl	%fs
	popl	%es
	popl	%ds

	/* pops the error code off the stack. */
	addl	$8,%esp

	iret



generic_exception_isr:
	pushl	%ds
	pushl	%es
	pushl	%fs
	pushl	%gs
	pushl	%eax
	pushl	%ebp
	pushl	%edi
	pushl	%esi
	pushl	%edx
	pushl	%ecx
	pushl	%ebx

/* install the kernel data segment to be able to access to gl_current_env. */
	movw	$(GDT_SEG_KDATA << 3),			%ax
	movw	%ax,					%ds
	movw	%ax,					%es

/* save esp0. */
	movl	gl_current_env,				%eax
	subl	$4,					%eax
	movl	%esp,					(%eax)

	call	do_exception

/* move toward the stack0 of the new env. */
/* restore its esp0. */
	movl	gl_current_env,				%eax
	subl	$4,					%eax
	movl	(%eax),					%esp

	orl	$(EFLAGS_INTR),				EFLAGS_OFFSET(%esp)
	popl	%ebx
	popl	%ecx
	popl	%edx
	popl	%esi
	popl	%edi
	popl	%ebp
	popl	%eax
	popl	%gs
	popl	%fs
	popl	%es
	popl	%ds

	/* pops the error code off the stack. */
	addl	$8,					%esp
	iret
