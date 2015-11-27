/*
** This file is part of ExAmour

** Copyright (C) Remy Saissy <remy.saissy@gmail.com>
** ExAmour is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 2 of the License, or
** (at your option) any later version.

** ExAmour is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.

** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

/** Basic framebuffer driver */

#include	<examour/event/syscall.h>

.text

/* success:	eax == 1 */
/* failure:	eax == 0 */
.globl	vesa_init
vesa_init:
	pushl	%ebx
	pushl	%ecx
	pushl	%edx
	pushl	%esi
	movl	$0x10000,						%esi
	movl	$0xa0000,						%edx
	movl	$(SEGMENT_TYPE_DATA_RW|SEGMENT_PRIV_3|SEGMENT_32BITS),	%ecx
	movl	$0,							%ebx
	int	$(SYS_base_mm_syscalls+SYS_ldt_add_entry)

	cmpl	$-1,							%eax
	je	1f

	/* Create the selector. */
	shl	$3,		%eax
	orl	$7,		%eax
	movl	%eax,		vesa_selector
	movl	$1,		%eax

1:
	popl	%esi
	popl	%edx
	popl	%ecx
	popl	%ebx
	ret

.globl	vesa_cls
vesa_cls:
	pushl	%es
	pushl	%edi
	pushl	%ecx
	
	movl	vesa_selector,	%eax
	movl	%eax,		%es

	xorl	%edi,		%edi
	movl	$(640*480),	%ecx
	shr	$2,		%ecx
	movl	$0,		%eax
 	 rep   stosl
	popl	%ecx
	popl	%edi
	popl	%es
	ret


/*
 * putpixel(int x, int y, int color)
 * on the stack we have:
 * 12(%esp) -> color
 *  8(%esp) -> y
 *  4(%esp) -> x
 * Colors vary from 0 (black) ... to 255 (white)
 */
.globl	vesa_putpixel
vesa_putpixel:
	pushl	%fs
	pushl	%edi
	
	movl	vesa_selector,	%eax
	movl	%eax,		%fs

/*
 * 20(%esp) -> color
 * 16(%esp) -> y
 * 12(%esp) -> x
 */
	movl	16(%esp),	%edi	/* setup y. */
	movl	$640,		%eax
	mul	%edi
	movl	%eax,		%edi
	addl	12(%esp),	%edi	/* setup x. */
	movl	20(%esp),	%eax    /* setup the color. */
	movb	%al,		%fs:(%edi)

	popl	%edi
	popl	%fs
	ret


.data
vesa_selector:	
	.long	0

