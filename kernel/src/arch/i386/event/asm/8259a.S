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

#include	<examour/event/8259a.h>
#include	<examour/event/irq.h>
#include	<examour/core/segment_types.h>
#include	<examour/core/asm.h>

.text

/*
 * This file contains the irqs wrappers routines.
 * By now they don't call any function but in future they'll
 * call the task associated one.
 */

/*
 * Once the lapic will be added, this file will probably be the 8259A
 * irq wrappers since the apic allows us to have more than 15 irqs...
 * I still need to read the books for now.
 */

/*
 * Note that no register saving is provided since it is the job
 * of the userspace handler in an exokernel. The purpose of those
 * routines is only to manage the boring and mandatory work.
 */

/*
 * The exceptions routines are generated within the irp loop
 * The only information which is pushed onto the stack is
 * the irq number, therefore we have the following layout:
 * | ss
 * | esp             ---> like ss, only if there was a priv switch
 * | eflags
 * | cs
 * | eip
 * | register layout (segment desc, gp regs)
 * | irq number
 */

.globl examour_do_irq_1
examour_do_irq_1:
	/* error_code */
	pushl	$0
	pushl   $IRQ_1
	jmp	generic_irq_isr

.globl examour_do_irq_3
examour_do_irq_3:
	/* error_code */
	pushl	$0
	pushl   $IRQ_3
	jmp	generic_irq_isr

.globl examour_do_irq_4
examour_do_irq_4:
	/* error_code */
	pushl	$0
	pushl   $IRQ_4
	jmp	generic_irq_isr

.globl examour_do_irq_5
examour_do_irq_5:
	/* error_code */
	pushl	$0
	pushl   $IRQ_5
	jmp	generic_irq_isr

.globl examour_do_irq_6
examour_do_irq_6:
	/* error_code */
	pushl	$0
	pushl   $IRQ_6
	jmp	generic_irq_isr

.globl examour_do_irq_7
examour_do_irq_7:
	/* error_code */
	pushl	$0
	pushl   $IRQ_7
	jmp	generic_irq_isr

.globl examour_do_irq_8
examour_do_irq_8:
	/* error_code */
	pushl	$0
	pushl   $IRQ_8
	jmp	generic_irq_isr

.globl examour_do_irq_9
examour_do_irq_9:
	/* error_code */
	pushl	$0
	pushl   $IRQ_9
	jmp	generic_irq_isr

.globl examour_do_irq_10
examour_do_irq_10:
	/* error_code */
	pushl	$0
	pushl   $IRQ_10
	jmp	generic_irq_isr

.globl examour_do_irq_11
examour_do_irq_11:
	/* error_code */
	pushl	$0
	pushl   $IRQ_11
	jmp	generic_irq_isr

.globl examour_do_irq_12
examour_do_irq_12:
	/* error_code */
	pushl	$0
	pushl   $IRQ_12
	jmp	generic_irq_isr

.globl examour_do_irq_13
examour_do_irq_13:
	/* error_code */
	pushl	$0
	pushl   $IRQ_13
	jmp	generic_irq_isr

.globl examour_do_irq_14
examour_do_irq_14:
	/* error_code */
	pushl	$0
	pushl   $IRQ_14
	jmp	generic_irq_isr

.globl examour_do_irq_15
examour_do_irq_15:
	/* error_code */
	pushl	$0
	pushl   $IRQ_15
	jmp	generic_irq_isr
	
/*
 * irq0 is hardcoded because there is no upcall on the timer.
 */
.globl examour_do_irq_0
examour_do_irq_0:
	/* error_code */
	pushl	$0
	pushl   $IRQ_0
	
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
	movl	gl_current_env,		%eax
	subl	$4,			%eax
	movl	%esp,			(%eax)

	call	do_epilogue

/* the scheduler selects the new env to be executed. */
/* and updates gl_current_env. */
	call	sched_next

/* move toward the stack0 of the new env. */
/* restore its esp0. */
	movl	gl_current_env,%eax
	subl	$4,		 %eax
	movl	(%eax),		 %esp

/* restore_context installs the new context then we can */
/* run a prologue. */
	call	do_prologue

/* no need to save %ax and %dx since they are on the stack. */

/* acknowledge the intr */
	pushl	$0
	call	_8259a_ack
	addl	$4,%esp

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

	/* error_code and ev_id. */
	addl	$8,	%esp
	iret


generic_irq_isr:
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

	call 	event_process_request
/*	upcall_do_upcall \irq_number INTR_OFFSET */

/* move toward the stack0 of the new env. */
/* restore its esp0. */
	movl	gl_current_env,	 %eax
	subl	$4,		 %eax
	movl	(%eax),		 %esp

	/* acknowledge the intr */
	pushl	$IRQ_1
  	call	_8259a_ack
	addl	$4,%esp

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

	/* error_code and ev_id. */
	addl	$8,	%esp
	iret
