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

/* I must care about the argument of the predicate. */
/* Presently, the argument is pushed on the stack before the call */
/* but strangely access to its members is made through ds... Everything */
/* is on the stack however. */
	
.globl	_zerodiv
_zerodiv:
	push	8(%esp)
	call	zerodiv
	add	$4,			%esp
	lret

.globl	_prologue
_prologue:
	push	8(%esp)
	call	prologue
	add	$4,			%esp
	lret
	
.globl	_epilogue
_epilogue:
	push	8(%esp)
	call	epilogue
	add	$4,			%esp
	lret

.globl	_segment_outofbound
_segment_outofbound:
	push	8(%esp)
	call	segment_outofbound
	add	$4,			%esp
	lret

