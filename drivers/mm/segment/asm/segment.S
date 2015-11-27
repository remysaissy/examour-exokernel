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

#include	<examour/event/syscall.h>

.text

/*
 *	4(%esp)	amount
 */
.globl	_segmentmm_init
_segmentmm_init:
	push	%ebx
	push	%ecx
	push	%edx
	push	%esi
	xor	%ebx,%ebx
	mov	$(SEGMENT_TYPE_DATA_RW|SEGMENT_PRIV_3|SEGMENT_32BITS),%ecx
	mov	$(PADDR_ERROR),%edx
	mov	20(%esp),%esi
	int	$(SYS_base_mm_syscalls+SYS_ldt_add_entry)
	pop	%esi
	pop	%edx
	pop	%ecx
	pop	%ebx
	ret
	
/*
 * 12(%esp)	size
 * 8(%esp)	src
 * 4(%esp)	dst_sel
 */
.globl	_copy_to_buffer
_copy_to_buffer:
	/* Save the registers. */
	subl	$12,			%esp
	movl	%ecx,			8(%esp)
	movl	%edi,			4(%esp)
	movl	%es,			%eax
	movl	%eax,			(%esp)

/*
 * 24(%esp)	size
 * 20(%esp)	src
 * 16(%esp)	dst_sel
 */

	movl	16(%esp),		%eax
	movl	%eax,			%es
	
	/* Reset the buffer. */
	movl	24(%esp),	%ecx
	shl	$1,		%ecx
	movl	20(%esp),	%esi
	shl	$1,		%esi
	xorl	%edi,		%edi
	cld
        rep
	 movsl

	/* Restore the registers. */
	movl	8(%esp),	%ecx
	movl	4(%esp),	%edi
	movl	(%esp),		%eax
	movl	%eax,		%es
	addl	$12,		%esp
	ret


