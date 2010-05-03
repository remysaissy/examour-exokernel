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

/**
 * This file contains the bootstrap entry point and the multiboot header.
 */

#include	<examour/core/multiboot.h>
#include	<examour/core/segment.h>

.text
.globl  start
.globl  _start
start:
_start:
       jmp     multiboot_entry

/* Align 32 bits boundary.  */
.align  4

        /* Multiboot header.  */
multiboot_header:
	        /* magic */
	        .long   MULTIBOOT_HEADER_MAGIC
	        /* flags */
	        .long   MULTIBOOT_HEADER_FLAGS
	        /* checksum */
	        .long   -(MULTIBOOT_HEADER_MAGIC + MULTIBOOT_HEADER_FLAGS)
#ifndef __ELF__
	        /* header_addr */
	        .long   multiboot_header
	        /* load_addr */
	        .long   _start
	        /* load_end_addr */
	        .long   _edata
	        /* bss_end_addr */
	        .long   _end
	        /* entry_addr */
	        .long   multiboot_entry
#endif /* ! __ELF__ */

multiboot_entry:
	/* Set up a stack */
	movl	$(stack + STACK_SIZE),		%esp

	/* Reset EFLAGS. */
	pushl	$0
	popf
	finit

	/* Push the magic and the address on the stack, so that they
	will be the parameters of the cmain function */
/* This one is not in the multiboot specification but grub keeps */
/* multiboot_header_t in it. */
/*	pushl	%ecx */
/* Save this parameter in an unused register. */
	movl	%eax,				%edx

/* Clear BSS. */
/* Warning: It resets the content of the stack ! */
        xorl	%eax,				%eax
        movl	$bss,				%edi
        movl	$end,				%ecx
	subl	%edi,				%ecx
        shrl	$2,				%ecx
        rep
	 stosl

/* Push multiboot parameters on the stack. */
	pushl	%ebx
	pushl	%edx

/* Lock the smi handler. */
/* TODO: it doens't work. Verify it. */
/*
	movl	$0x8000009c,	%eax
	movw	$0xcf8,		%dx
	out	%eax,		%dx

	movw	$0xcfc,		%dx
	in	%dx,		%eax

	orl	$0x3000,	%eax
	movl	%eax,		%ebx

	movl	$0x8000009c,	%eax
	movw	$0xcf8,		%dx
	out	%eax,		%dx

	movl	%ebx,		%eax
	movw	$0xcfc,		%dx
	out	%eax,		%dx
*/

/*
 * Memory layout from 1Mb:
 *
 * 1Mb      end    end+16Kb end+20kb
 * | kernel  | gdt   |   free         |
 * +----------------------------------+
 * For now everything is embeeded because we don't
 * want to loose informations provided by grub.
 */

/*
 * Set up gdt
 * 8192 entries * 8 bytes per entry == 65536 bytes == 16kb == 0x10000
 */
	movl	$gl_gdt,	%eax
	leal	(%eax),		%eax
	pushl	%eax		/* base address */
	pushl	$0xffff		/* limit */
	shll	$16,					(%esp)
	lgdt	2(%esp)
	ljmp	$(GDT_SEG_KCODE << 3),			$gdt_up
gdt_up:
	movl	$(GDT_SEG_KDATA << 3),			%eax
	movl	%eax,					%ds
	movl	%eax,					%es
	movl	%eax,					%fs
	movl	%eax,					%gs
	movl	%eax,					%ss
	/* restore the stack for multiboot. */
	addl	$8,					%esp

	/* Call the kernel's main function (base/main.c) */
	/* For a fully functionnal kernel, idt, tss and kernel stack */
	/* need to be created. */
	call	kmain

	/* Should never go there */
loop:
	hlt
	jmp loop

/*
 * Data section
 */
.data
	.align	4
stack:
	/* Here is the stack */
	.fill	STACK_SIZE

