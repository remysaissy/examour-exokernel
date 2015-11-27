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
#include	"../kbd.h"

.text

.globl	kbd_init
kbd_init:
	movl	$0,				kbd_off
	movl	$0,				kbd_usize
	movl	$1,				%ebx
	movl	%cs,				%ecx
	movl	$kbd_handler,			%edx
	int	$(SYS_base_event_syscalls+SYS_event_register)
	ret

.globl	kbd_handler
kbd_handler:
	xorl	%eax,				%eax
	movw	$0x60,				%dx
	inb	%dx,				%al
	pushl	%eax
	call	kbd_add_char
	addl	$4,				%esp
	lret

