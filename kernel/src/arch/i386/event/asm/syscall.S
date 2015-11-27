/*
 * This file is part of exAmour

 * Copyright (C) Remy Saissy <remy.saissy@epitech.net>
 * exAmour is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.

 * exAmour is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

/* This file contains the syscall entry points. */

#include	<examour/core/segment_types.h>
#include	<examour/event/syscall.h>
#include	<examour/core/asm.h>
#include	<examour/event/idt.h>

#define		SYSCALL_ENTRY(ret_type, syscall_name, n_params)			\
.globl	asm_ ## syscall_name;							\
asm_ ## syscall_name:;								\
	/* error_code */							\
	pushl	$syscall_name;							\
	pushl   $( SYS_ ## syscall_name );					\
	jmp	generic_syscall_isr;

#include	<examour/mm/syscalls_mm.def>
#include	<examour/env/syscalls_env.def>
#include	<examour/event/syscalls_event.def>

#undef	SYSCALL_ENTRY


generic_syscall_isr:
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

  /* in a multi segment context, some relocation is needed here. */

 /* todo (vomi sur ce addl/subl) */
	movl	ERROR_ID_OFFSET(%esp),		%eax
	call	*%eax

  /* for the sake of simplicity, assume a syscall always has a return value. */
	movl	%eax,EAX_OFFSET(%esp)

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

	/* error_code and ev_id. */
	addl	$8, %esp
	iret

