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

#include	<examour/mm/ldt.h>
#include	<examour/core/asm.h>
#include	<examour/core/predicates.h>
#include	<examour/event/syscall.h>
#include	<examour/env/env.h>

.text

/* bool		ldt_create(ldtr_t *context); */
/*
 * 4(%esp)	context
 */
.globl	ldt_create
ldt_create:
	push	%ebx
	mov	8(%esp),	%ebx
	int	$(SYS_base_mm_syscalls+SYS_ldt_create)
	pop	%ebx
	ret

/* bool		ldt_destroy(ldtr_t *context); */
/*
 * 4(%esp)	context
 */
.globl	ldt_destroy
ldt_destroy:
	push	%ebx
	mov	8(%esp),	%ebx
	int	$(SYS_base_mm_syscalls+SYS_ldt_destroy)
	pop	%ebx
	ret

/* int		ldt_add_entry(ldtr_t *context, */
/* 			      uint32_t flags, */
/* 			      paddr_t base_addr, */
/* 			      size_t size); */
/*
 * 16(%esp)	size
 * 12(%esp)	base_addr
 * 8(%esp)	flags
 * 4(%esp)	context
 */
.globl	ldt_add_entry
ldt_add_entry:
	sub	$16,		%esp
	mov	%ebx,		(%esp)
	mov	%ecx,		4(%esp)
	mov	%edx,		8(%esp)
	mov	%esi,		12(%esp)
	mov	20(%esp),	%ebx
	mov	24(%esp),	%ecx
	mov	28(%esp),	%edx
	mov	32(%esp),	%esi
	int	$(SYS_base_mm_syscalls+SYS_ldt_add_entry)
	pop	%ebx
	pop	%ecx
	pop	%edx
	pop	%esi
	ret

/* bool		ldt_remove_entry(ldtr_t *context, */
/* 				 uint32_t selector); */
/*
 * 8(%esp)	selector
 * 4(%esp)	context
 */
.globl	ldt_remove_entry
ldt_remove_entry:
	sub	$8,		%esp
	mov	%ebx,		(%esp)
	mov	%ecx,		4(%esp)
	mov	12(%esp),	%ebx
	mov	16(%esp),	%ecx
	int	$(SYS_base_mm_syscalls+SYS_ldt_remove_entry)
	pop	%ebx
	pop	%ecx
	ret

/* int		env_create(char *id, */
/* 			   basic_cap_t basic_cap, */
/* 			   examour_env_section_t *sections, */
/* 			   int n_sections); */
/*
 * 16(%esp)	n_sections
 * 12(%esp)	sections
 * 8(%esp)	basic_cap
 * 4(%esp)	id
 */
.globl	env_create
env_create:
	sub	$16,		%esp
	mov	%ebx,		(%esp)
	mov	%ecx,		4(%esp)
	mov	%edx,		8(%esp)
	mov	%esi,		12(%esp)
	mov	20(%esp),	%ebx
	mov	24(%esp),	%ecx
	mov	28(%esp),	%edx
	mov	32(%esp),	%esi
	int	$(SYS_base_mm_syscalls+SYS_env_create)
	pop	%ebx
	pop	%ecx
	pop	%edx
	pop	%esi
	ret

/* void		env_yield(void); */
.globl	env_yield
env_yield:
	int	$(SYS_base_mm_syscalls+SYS_env_yield)
	ret

/* bool		env_delete(eid_t eid); */
/*
 * 4(%esp)	eid
 */
.globl	env_delete
env_delete:
	push	%ebx
	mov	8(%esp),	%ebx
	int	$(SYS_base_mm_syscalls+SYS_env_delete)
	pop	%ebx
	ret

/* bool		timeslice_add(uint32_t ms, uint32_t flags); */
/*
 * 8(%esp)	flags
 * 4(%esp)	ms
 */
.globl	timeslice_add
timeslice_add:
	sub	$8,		%esp
	mov	%ebx,		(%esp)
	mov	%ecx,		4(%esp)
	mov	12(%esp),	%ebx
	mov	16(%esp),	%ecx
	int	$(SYS_base_mm_syscalls+SYS_timeslice_add)
	pop	%ebx
	pop	%ecx
	ret

/* bool		io_grant(uint16_t ioport, bool exclusive); */
/*
 * 8(%esp)	exclusive
 * 4(%esp)	ioport
 */
.globl	io_grant
io_grant:
	sub	$8,		%esp
	mov	%ebx,		(%esp)
	mov	%ecx,		4(%esp)
	mov	12(%esp),	%ebx
	mov	16(%esp),	%ecx
	int	$(SYS_base_mm_syscalls+SYS_io_grant)
	pop	%ebx
	pop	%ecx
	ret

/* bool		io_revoke(uint16_t ioport); */
/*
 * 4(%esp)	ms
 */
.globl	io_revoke
io_revoke:
	sub	$8,		%esp
	mov	%ebx,		(%esp)
	mov	%ecx,		4(%esp)
	mov	12(%esp),	%ebx
	mov	16(%esp),	%ecx
	int	$(SYS_base_mm_syscalls+SYS_io_revoke)
	pop	%ebx
	pop	%ecx
	ret

/* bool		event_register(uint32_t vector_id, */
/* 			       selector_t cs, */
/* 			       paddr_t offset, */
/*			       uint32_t	flags); */
/*
 * 16(%esp)	flags
 * 12(%esp)	offset
 * 8(%esp)	cs
 * 4(%esp)	vector_id
 */
.globl	event_register
event_register:
	sub	$16,		%esp
	mov	%ebx,		(%esp)
	mov	%ecx,		4(%esp)
	mov	%edx,		8(%esp)
	mov	%esi,		12(%esp)
	mov	16(%esp),	%ebx
	mov	20(%esp),	%ecx
	mov	24(%esp),	%edx
	mov	28(%esp),	%esi
	int	$(SYS_base_mm_syscalls+SYS_event_register)
	pop	%ebx
	pop	%ecx
	pop	%edx
	ret

/* bool		event_unregister(uint32_t vector_id, */
/* 				 selector_t cs, */
/* 				 paddr_t offset); */
/*
 * 12(%esp)	offset
 * 8(%esp)	cs
 * 4(%esp)	vector_id
 */
.globl	event_unregister
event_unregister:
	sub	$12,		%esp
	mov	%ebx,		(%esp)
	mov	%ecx,		4(%esp)
	mov	%edx,		8(%esp)
	mov	16(%esp),	%ebx
	mov	20(%esp),	%ecx
	mov	24(%esp),	%edx
	int	$(SYS_base_mm_syscalls+SYS_event_unregister)
	pop	%ebx
	pop	%ecx
	pop	%edx
	pop	%esi
	ret

/* bool		event_forge(void *forgery, */
/* 			    uint32_t *event_id);*/
/*
 * 8(%esp)	event_id
 * 4(%esp)	forgery
 */
.globl	event_forge
event_forge:
	sub	$8,		%esp
	mov	%ebx,		(%esp)
	mov	%ecx,		4(%esp)
	mov	12(%esp),	%ebx
	mov	16(%esp),	%ecx
	int	$(SYS_base_mm_syscalls+SYS_event_forge)
	pop	%ebx
	pop	%ecx
	ret

/* bool		event_throw(uint32_t event_id, */
/*			     uint32_t	flags); */
/*
 * 4(%esp)	event_id
 */
.globl	event_throw
event_throw:
	push	%ebx
	push	%ecx
	mov	8(%esp),	%ebx
	mov	12(%esp),	%ecx
	int	$(SYS_base_mm_syscalls+SYS_event_throw)
	pop	%ebx
	pop	%ecx
	ret

/* Prologue/Epilogue functions. */

/* void		set_epilogue(paddr_t epilogue_handler); */
/*
 * 4(%esp)	epilogue_handler
 */
.globl	set_epilogue
set_epilogue:
	push	%gs
	mov	$(KENV_PREDICATE_IDX << 3 | 7),	%eax
	mov	%eax,				%gs
	mov	%cs,				%eax
	mov	%eax,				%gs:EPILOGUE_OFFSET+PREDICATE_CS_OFFSET
	mov	8(%esp),			%eax
	mov	%eax,				%gs:EPILOGUE_OFFSET+PREDICATE_ADDR_OFFSET
	pop	%gs
	ret

/* void		unset_epilogue(void); */
.globl	unset_epilogue
unset_epilogue:
	push	%gs
	mov	$(KENV_PREDICATE_IDX << 3 | 7),	%eax
	mov	%eax,				%gs
	mov	$PADDR_ERROR,			%eax
	mov	%eax,				%gs:EPILOGUE_OFFSET+PREDICATE_CS_OFFSET
	mov	$PADDR_ERROR,			%eax
	mov	%eax,				%gs:EPILOGUE_OFFSET+PREDICATE_ADDR_OFFSET
	pop	%gs
	ret

/* void		set_prologue(paddr_t prologue_handler); */
/*
 * 4(%esp)	prologue_handler
 */
.globl	set_prologue
set_prologue:
	push	%gs
	mov	$(KENV_PREDICATE_IDX << 3 | 7),	%eax
	mov	%eax,				%gs
	mov	%cs,				%eax
	mov	%eax,				%gs:PROLOGUE_OFFSET+PREDICATE_CS_OFFSET
	mov	8(%esp),			%eax
	mov	%eax,				%gs:PROLOGUE_OFFSET+PREDICATE_ADDR_OFFSET
	pop	%gs
	ret

/* void		unset_prologue(void); */
.globl	unset_prologue
unset_prologue:
	push	%gs
	mov	$(KENV_PREDICATE_IDX << 3 | 7),	%eax
	mov	%eax,				%gs
	mov	$PADDR_ERROR,			%eax
	mov	%eax,				%gs:PROLOGUE_OFFSET+PREDICATE_CS_OFFSET
	mov	$PADDR_ERROR,			%eax
	mov	%eax,				%gs:PROLOGUE_OFFSET+PREDICATE_ADDR_OFFSET
	pop	%gs
	ret

/* Upcalls. */

/* void		set_exception_handler(uint32_t exception_id,  */
/* 				      paddr_t exception_handler); */
/*
 * 8(%esp)	exception_handler
 * 4(%esp)	exception_id
 */
.globl	set_exception_handler
set_exception_handler:
	push	%gs
	push	%ecx
	mov	$(KENV_PREDICATE_IDX << 3 | 7),	%eax
	mov	%eax,				%gs
	mov	12(%esp),			%eax
	mov	$8,				%ecx
	imul	%ecx,				%eax
	add	$EXCEPTION_OFFSET,		%eax
	mov	%cs,				%ecx
	mov	%ecx,				%gs:PREDICATE_CS_OFFSET(%eax)
	mov	16(%esp),			%ecx
	mov	%ecx,				%gs:PREDICATE_ADDR_OFFSET(%eax)
	pop	%ecx
	pop	%gs
	ret

/* void		unset_exception_handler(uint32_t exception_id); */
/*
 * 4(%esp)	exception_id
 */
.globl	unset_exception_handler
unset_exception_handler:
	push	%gs
	push	%ebx
	mov	$(KENV_PREDICATE_IDX << 3 | 7),	%eax
	mov	%eax,				%gs
	mov	12(%esp),			%ebx
	imul	$PREDICATE_SIZE,		%ebx
	add	$EXCEPTION_OFFSET,		%ebx
	mov	$PADDR_ERROR,			%eax
	mov	%eax,				%gs:PREDICATE_CS_OFFSET(%ebx)
	mov	$PADDR_ERROR,			%eax
	mov	%eax,				%gs:PREDICATE_ADDR_OFFSET(%ebx)
	pop	%ebx
	pop	%gs
	ret

/* paddr_t		get_stack_base_address(void); */
.globl	get_stack_base_address
get_stack_base_address:
	call	get_stack_base_address_eip
get_stack_base_address_eip:
	subl	$get_stack_base_address_eip,	(%esp)
	pop	%eax
	ret

/* Segment memory access. */

/* int		get_cs_index(void); */
.globl	get_cs_index
get_cs_index:
	mov	%cs,		%eax
	ret

/* int		get_ss_index(void); */
.globl	get_ss_index
get_ss_index:
	mov	%ss,		%eax
	ret

/* int		get_ds_index(void); */
.globl	get_ds_index
get_ds_index:
	mov	%ds,		%eax
	ret

/* int		get_es_index(void); */
.globl	get_es_index
get_es_index:
	mov	%es,		%eax
	ret

/* int		get_fs_index(void); */
.globl	get_fs_index
get_fs_index:
	mov	%fs,		%eax
	ret

/* int		get_gs_index(void); */
.globl	get_gs_index
get_gs_index:
	mov	%gs,		%eax
	ret

/* paddr_t		get_sp(void); */
.globl	get_sp
get_sp:
	mov	%esp,		%eax
	ret

/* paddr_t		get_pc(void); */
.globl	get_pc
get_pc:
	call	get_pc2
get_pc2:
	pop	%eax
	ret

/* void		segment_memcopy_by_index(int out_index, paddr_t out_offset, */
/* 			     int in_index, paddr_t in_offset, */
/* 			     size_t nmemb, size_t size); */
/*
 * 24(%esp)	size
 * 20(%esp)	nmemb
 * 16(%esp)	in_offset
 * 12(%esp)	in_index
 * 8(%esp)	out_offset
 * 4(%esp)	out_index
 */
.globl	segment_memcopy_by_index
segment_memcopy_by_index:
	mov	4(%esp),	%eax
	cmp	$-1,		%eax
	je	no_out_memcpy
	shl	$3,		%eax
	or	$7,		%eax
no_out_memcpy:
	mov	%eax,		4(%esp)
	cmp	$-1,		%eax
	je	no_in_memcpy
	mov	12(%esp),	%eax
	shl	$3,		%eax
	or	$7,		%eax
	mov	%eax,		12(%esp)
no_in_memcpy:
	jmp	segment_memcopy_by_selector

/* void		segment_memcopy_by_selector(selector_t out_selector, paddr_t out_offset, */
/* 			     selector_t in_selector, paddr_t in_offset, */
/* 			     size_t nmemb, size_t size); */
/*
 * 24(%esp)	size
 * 20(%esp)	nmemb
 * 16(%esp)	in_offset
 * 12(%esp)	in_selector
 * 8(%esp)	out_offset
 * 4(%esp)	out_selector
 */
.globl	segment_memcopy_by_selector
segment_memcopy_by_selector:
	/* Save the registers. */
	sub	$16,		%esp
	mov	%ecx,		12(%esp)
	mov	%edi,		8(%esp)
	mov	%es,		%eax
	mov	%eax,		4(%esp)
	mov	%ds,		%eax
	mov	%eax,		(%esp)

/*
 * 40(%esp)	size
 * 36(%esp)	nmemb
 * 32(%esp)	in_offset
 * 28(%esp)	in_selector
 * 24(%esp)	out_offset
 * 20(%esp)	out_selector
 */

	mov	28(%esp),	%eax
	cmp	$-1,		%eax
	je	no_ds_memcopy
	mov	%eax,		%ds
no_ds_memcopy:
	mov	20(%esp),	%eax
	cmp	$-1,		%eax
	je	no_es_memcopy
	mov	%eax,		%es
no_es_memcopy:
	mov	36(%esp),	%ecx
	mov	32(%esp),	%esi
	mov	24(%esp),	%edi
	cld
	cmp	$1,		40(%esp)
	je	memcopy_byte
	cmp	$2,		40(%esp)
	je	memcopy_2bytes
	cmp	$4,		40(%esp)
	je	memcopy_4bytes
memcopy_byte:
        rep
	 movsb
	jmp	memcopy_done
memcopy_2bytes:
        rep
	 movsw
	jmp	memcopy_done
memcopy_4bytes:
        rep
	 movsl
memcopy_done:
	/* Restore the registers. */
	movl	12(%esp),	%ecx
	movl	8(%esp),	%edi
	movl	4(%esp),	%eax
	movl	%eax,		%es
	movl	(%esp),		%eax
	movl	%eax,		%ds
	addl	$16,		%esp
	ret

/* void		segment_memset_by_index(int index, paddr_t offset, */
/* 			       int value, size_t nmemb, size_t size); */
/*
 * 20(%esp)	size
 * 16(%esp)	nmemb
 * 12(%esp)	value
 * 8(%esp)	offset
 * 4(%esp)	index
 */
.globl	segment_memset_by_index
segment_memset_by_index:
	mov	4(%esp),	%eax
	cmp	$-1,		%eax
	je	segment_memset_by_selector
	shl	$3,		%eax
	or	$7,		%eax
	mov	%eax,		4(%esp)
	jmp	segment_memset_by_selector

/* void		segment_memset_by_selector(selector_t selector, paddr_t offset, */
/* 			       int value, size_t nmemb, size_t size); */
/*
 * 20(%esp)	size
 * 16(%esp)	nmemb
 * 12(%esp)	value
 * 8(%esp)	offset
 * 4(%esp)	selector
 */
.globl	segment_memset_by_selector
segment_memset_by_selector:
	/* Save the registers. */
	sub	$12,		%esp
	mov	%ecx,		8(%esp)
	mov	%edi,		4(%esp)
	mov	%es,		%eax
	mov	%eax,		(%esp)

/*
 * 32(%esp)	size
 * 28(%esp)	nmemb
 * 24(%esp)	value
 * 20(%esp)	offset
 * 16(%esp)	index
 */
	mov	16(%esp),	%eax
	cmp	$-1,		%eax
	je	no_memset_es
	mov	%eax,		%es

no_memset_es:
	/* Reset the buffer. */
	mov	28(%esp),	%ecx
	mov	24(%esp),	%eax
	mov	20(%esp),	%edi
	cld
	cmp	$1,		32(%esp)
	je	memset_byte
	cmp	$2,		32(%esp)
	je	memset_2bytes
	cmp	$4,		32(%esp)
	je	memset_4bytes
memset_byte:
        rep
	 stosb
	jmp	memset_done
memset_2bytes:
        rep
	 stosw
	jmp	memset_done
memset_4bytes:
        rep
	 stosl
memset_done:
	/* Restore the registers. */
	mov	8(%esp),	%ecx
	mov	4(%esp),	%edi
	mov	(%esp),		%eax
	mov	%eax,		%es
	add	$12,		%esp
	ret


/* void		segment_write1_by_index(int index, paddr_t offset, */
/* 					uint8_t value); */
/*
 * 12(%esp)	value
 * 8(%esp)	offset
 * 4(%esp)	index
 */
.globl	segment_write1_by_index
segment_write1_by_index:
	mov	4(%esp),	%eax
	cmp	$-1,		%eax
	je	segment_write1_by_selector
	shl	$3,		%eax
	or	$7,		%eax
	mov	%eax,		4(%esp)
	jmp	segment_write1_by_selector

/* void		segment_write1_by_selector(selector_t selector, paddr_t offset, */
/* 					uint8_t value); */
/*
 * 12(%esp)	value
 * 8(%esp)	offset
 * 4(%esp)	selector
 */
.globl	segment_write1_by_selector
segment_write1_by_selector:
	/* Save the registers. */
	sub	$8,		%esp
	mov	%ds,		4(%esp)
	mov	%ebx,		(%esp)

/*
 * 20(%esp)	value
 * 16(%esp)	offset
 * 12(%esp)	selector
 */

	mov	12(%esp),	%eax
	cmp	$-1,		%eax
	je	segment_write1_no_ds
	mov	%eax,		%ds

segment_write1_no_ds:
	/* Write the value. */
	mov	16(%esp),	%eax
	mov	20(%esp),	%ebx
	mov	%bl,		%ds:(%eax)

	/* Restore the registers. */
	mov	4(%esp),	%ds
	mov	(%esp),		%ebx
	add	$8,		%esp
	ret

/* void		segment_write2_by_index(int index, paddr_t offset, */
/* 					uint16_t value); */
/*
 * 12(%esp)	value
 * 8(%esp)	offset
 * 4(%esp)	index
 */
.globl	segment_write2_by_index
segment_write2_by_index:
	mov	4(%esp),	%eax
	cmp	$-1,		%eax
	je	segment_write2_by_selector
	shl	$3,		%eax
	or	$7,		%eax
	mov	%eax,		4(%esp)
	jmp	segment_write2_by_selector

/* void		segment_write2_by_selector(selector_t selector, paddr_t offset, */
/* 					uint16_t value); */
/*
 * 12(%esp)	value
 * 8(%esp)	offset
 * 4(%esp)	selector
 */
.globl	segment_write1_by_selector
segment_write2_by_selector:
	/* Save the registers. */
	sub	$8,		%esp
	mov	%ds,		4(%esp)
	mov	%ebx,		(%esp)

/*
 * 20(%esp)	value
 * 16(%esp)	offset
 * 12(%esp)	selector
 */

	mov	12(%esp),	%eax
	cmp	$-1,		%eax
	je	segment_write2_no_ds
	mov	%eax,		%ds

segment_write2_no_ds:
	/* Write the value. */
	mov	16(%esp),	%eax
	mov	20(%esp),	%ebx
	mov	%bx,		%ds:(%eax)

	/* Restore the registers. */
	mov	4(%esp),	%ds
	mov	(%esp),		%ebx
	add	$8,		%esp
	ret

/* void		segment_write4_by_index(int index, paddr_t offset, */
/* 					uint32_t value); */
/*
 * 12(%esp)	value
 * 8(%esp)	offset
 * 4(%esp)	index
 */
.globl	segment_write4_by_index
segment_write4_by_index:
	mov	4(%esp),	%eax
	cmp	$-1,		%eax
	je	segment_write4_by_selector
	shl	$3,		%eax
	or	$7,		%eax
	mov	%eax,		4(%esp)
	jmp	segment_write4_by_selector

/* void		segment_write4_by_selector(selector_t selector, paddr_t offset, */
/* 					uint32_t value); */
/*
 * 12(%esp)	value
 * 8(%esp)	offset
 * 4(%esp)	selector
 */
.globl	segment_write4_by_selector
segment_write4_by_selector:
	/* Save the registers. */
	sub	$8,		%esp
	mov	%ds,		4(%esp)
	mov	%ebx,		(%esp)

/*
 * 20(%esp)	value
 * 16(%esp)	offset
 * 12(%esp)	selector
 */

	mov	12(%esp),	%eax
	cmp	$-1,		%eax
	je	segment_write4_no_ds
	mov	%eax,		%ds

segment_write4_no_ds:
	/* Write the value. */
	mov	16(%esp),	%eax
	mov	20(%esp),	%ebx
	mov	%ebx,		%ds:(%eax)

	/* Restore the registers. */
	mov	4(%esp),	%ds
	mov	(%esp),		%ebx
	add	$8,		%esp
	ret

/* void		segment_read1_by_index(int index, paddr_t offset, */
/* 					uint8_t *value); */
/*
 * 12(%esp)	value
 * 8(%esp)	offset
 * 4(%esp)	index
 */
.globl	segment_read1_by_index
segment_read1_by_index:
	mov	4(%esp),	%eax
	cmp	$-1,		%eax
	je	segment_read1_by_selector
	shl	$3,		%eax
	or	$7,		%eax
	mov	%eax,		4(%esp)
	jmp	segment_read1_by_selector

/* void		segment_read1_by_selector(selector_t selector, paddr_t offset, */
/* 					uint8_t *value); */
/*
 * 12(%esp)	value
 * 8(%esp)	offset
 * 4(%esp)	selector
 */
.globl	segment_read1_by_selector
segment_read1_by_selector:
	/* Save the registers. */
	sub	$8,		%esp
	mov	%ds,		%eax
	mov	%eax,		4(%esp)
	mov	%ebx,		(%esp)

/*
 * 20(%esp)	value
 * 16(%esp)	offset
 * 12(%esp)	selector
 */

	mov	12(%esp),	%eax
	cmp	$-1,		%eax
	je	segment_read1_no_ds
	mov	%eax,		%ds

segment_read1_no_ds:
	/* Read the value. */
	mov	16(%esp),	%eax
	mov	%ds:(%eax),	%ebx
	mov	20(%esp),	%eax
	mov	%bl,		%ss:(%eax)

	/* Restore the registers. */
	mov	%ebx,		(%esp)
	mov	4(%esp),	%eax
	mov	%eax,		%ds
	add	$8,		%esp
	ret

/* void		segment_read2_by_index(int index, paddr_t offset, */
/* 					uint16_t *value); */
/*
 * 12(%esp)	value
 * 8(%esp)	offset
 * 4(%esp)	index
 */
.globl	segment_read2_by_index
segment_read2_by_index:
	mov	4(%esp),	%eax
	cmp	$-1,		%eax
	je	segment_read2_by_selector
	shl	$3,		%eax
	or	$7,		%eax
	mov	%eax,		4(%esp)
	jmp	segment_read2_by_selector

/* void		segment_read2_by_selector(selector_t selector, paddr_t offset, */
/* 					uint16_t *value); */
/*
 * 12(%esp)	value
 * 8(%esp)	offset
 * 4(%esp)	selector
 */
.globl	segment_read2_by_selector
segment_read2_by_selector:
	/* Save the registers. */
	sub	$8,		%esp
	mov	%ds,		%eax
	mov	%eax,		4(%esp)
	mov	%ebx,		(%esp)

/*
 * 20(%esp)	value
 * 16(%esp)	offset
 * 12(%esp)	selector
 */

	mov	12(%esp),	%eax
	cmp	$-1,		%eax
	je	segment_read2_no_ds
	mov	%eax,		%ds

segment_read2_no_ds:
	/* Read the value. */
	mov	16(%esp),	%eax
	mov	%ds:(%eax),	%ebx
	mov	20(%esp),	%eax
	mov	%bx,		%ss:(%eax)

	/* Restore the registers. */
	mov	%ebx,		(%esp)
	mov	4(%esp),	%eax
	mov	%eax,		%ds
	add	$8,		%esp

/* void		segment_read4_by_index(int index, paddr_t offset, */
/* 					uint32_t *value); */
/*
 * 12(%esp)	value
 * 8(%esp)	offset
 * 4(%esp)	index
 */
.globl	segment_read4_by_index
segment_read4_by_index:
	mov	4(%esp),	%eax
	cmp	$-1,		%eax
	je	segment_read4_by_selector
	shl	$3,		%eax
	or	$7,		%eax
	mov	%eax,		4(%esp)
	jmp	segment_read4_by_selector

/* void		segment_read4_by_selector(selector_t selector, paddr_t offset, */
/* 					   uint32_t *value); */
/*
 * 12(%esp)	value
 * 8(%esp)	offset
 * 4(%esp)	selector
 */
.globl	segment_read4_by_selector
segment_read4_by_selector:
	/* Save the registers. */
	sub	$8,		%esp
	mov	%ds,		%eax
	mov	%eax,		4(%esp)
	mov	%ebx,		(%esp)

/*
 * 20(%esp)	value
 * 16(%esp)	offset
 * 12(%esp)	selector
 */

	mov	12(%esp),	%eax
	cmp	$-1,		%eax
	je	segment_read4_no_ds
	mov	%eax,		%ds

segment_read4_no_ds:
	/* Read the value. */
	mov	16(%esp),	%eax
	mov	%ds:(%eax),	%ebx
	mov	20(%esp),	%eax
	mov	%ebx,		%ss:(%eax)

	/* Restore the registers. */
	mov	%ebx,		(%esp)
	mov	4(%esp),	%eax
	mov	%eax,		%ds
	add	$8,		%esp
	ret

/* void		set_cs_by_index(int index, paddr_t pc); */
/*
 * 8(%esp)	pc
 * 4(%esp)	index
 */
.globl	set_cs_by_index
set_cs_by_index:
	mov	4(%esp),	%eax
	shl	$3,		%eax
	or	$7,		%eax
	mov	%eax,		4(%esp)
	jmp	set_cs_by_selector

/* void		set_cs_by_selector(selector_t selector, paddr_t pc); */
/*
 * 8(%esp)	pc
 * 4(%esp)	selector
 */
.globl	set_cs_by_selector
set_cs_by_selector:
	push	4(%esp)
	push	8(%esp)
	ljmp	(%esp)
	ret

/* void		set_ss_by_index(int index, paddr_t sp); */
/*
 * 8(%esp)	sp
 * 4(%esp)	index
 */
.globl	set_ss_by_index
set_ss_by_index:
	mov	4(%esp),	%eax
	shl	$3,		%eax
	or	$7,		%eax
	mov	%eax,		4(%esp)
	jmp	set_ss_by_index

/* void		set_ss_by_selector(selector_t selector, paddr_t sp); */
/*
 * 8(%esp)	sp
 * 4(%esp)	selector
 */
.globl	set_ss_by_selector
set_ss_by_selector:
	push	4(%esp)
	push	8(%esp)
/*	lss	(%esp) */
	ret

/* void		set_ds_by_index(int index); */
/*
 * 4(%esp)	index
 */
.globl	set_ds_by_index
set_ds_by_index:
	mov	4(%esp),	%eax
	shl	$3,		%eax
	or	$7,		%eax
	mov	%eax,		%ds
	ret

/* void		set_ds_by_selector(selector_t selector); */
/*
 * 4(%esp)	selector
 */
.globl	set_ds_by_selector
set_ds_by_selector:
	mov	4(%esp),	%eax
	mov	%eax,		%ds
	ret

/* void		set_es_by_index(int index); */
/*
 * 4(%esp)	index
 */
.globl	set_es_by_index
set_es_by_index:
	mov	4(%esp),	%eax
	shl	$3,		%eax
	or	$7,		%eax
	mov	%eax,		%es
	ret

/* void		set_es_by_selector(selector_t selector); */
/*
 * 4(%esp)	selector
 */
.globl	set_es_by_selector
set_es_by_selector:
	mov	4(%esp),	%eax
	mov	%eax,		%es
	ret

/* void		set_fs_by_index(int index); */
/*
 * 4(%esp)	index
 */
.globl	set_fs_by_index
set_fs_by_index:
	mov	4(%esp),	%eax
	shl	$3,		%eax
	or	$7,		%eax
	mov	%eax,		%fs
	ret

/* void		set_fs_by_selector(selector_t selector); */
/*
 * 4(%esp)	selector
 */
.globl	set_fs_by_selector
set_fs_by_selector:
	mov	4(%esp),	%eax
	mov	%eax,		%fs
	ret

/* void		set_gs_by_index(int index); */
/*
 * 4(%esp)	index
 */
.globl	set_gs_by_index
set_gs_by_index:
	mov	4(%esp),	%eax
	shl	$3,		%eax
	or	$7,		%eax
	mov	%eax,		%gs
	ret

/* void		set_gs_by_selector(selector_t selector); */
/*
 * 4(%esp)	selector
 */
.globl	set_gs_by_selector
set_gs_by_selector:
	mov	4(%esp),	%eax
	mov	%eax,		%gs
	ret

/* void		read_timestamp(uint64_t *timestamp); */
/*
 *	4(%esp)	timestamp
 */
.globl	read_timestamp
read_timestamp:
	push	%edx
	push	%ebx
	rdtsc
/*
 * 12(%esp)	timestamp
 */
	mov	12(%esp),	%ebx
	mov	%eax,		(%ebx)
	mov	%edx,		4(%ebx)
	pop	%ebx
	pop	%edx
	ret

/* void		io_send(uint16_t port, uint32_t value, size_t size); */
/*
 * 12(%esp)	size
 * 8(%esp)	value
 * 4(%esp)	port
 */
.globl	io_send
io_send:
	push	%edx
/*
 * 16(%esp)	size
 * 12(%esp)	value
 * 8(%esp)	port
 */
	mov	8(%esp),	%edx
	mov	12(%esp),	%eax
	cmp	$1,		16(%esp)
	je	io_send1
	cmp	$2,		16(%esp)
	je	io_send2
	cmp	$4,		16(%esp)
	je	io_send4
	jmp	io_send_end
io_send1:
	outb	%al,	%dx
	jmp	io_send_end
io_send2:
	outw	%ax,	%dx
	jmp	io_send_end
io_send4:
	outl	%eax,	%dx
	jmp	io_send_end
io_send_end:	
	pop	%edx
	ret

/* void		io_receive(uint16_t port, uint32_t *value, size_t size); */
/*
 * 12(%esp)	size
 * 8(%esp)	value
 * 4(%esp)	port
 */
.globl	io_receive
io_receive:
	push	%edx
/*
 * 16(%esp)	size
 * 12(%esp)	value
 * 8(%esp)	port
 */
	mov	8(%esp),	%edx
	cmp	$1,		16(%esp)
	je	io_receive1
	cmp	$2,		16(%esp)
	je	io_receive2
	cmp	$4,		16(%esp)
	je	io_receive4
	jmp	io_receive_end
io_receive1:
	inb	%dx,		%al
	mov	12(%esp),	%edx
	mov	%al,		(%edx)
	jmp	io_receive_end
io_receive2:
	inw	%dx,		%ax
	mov	12(%esp),	%edx
	mov	%ax,		(%edx)
	jmp	io_receive_end
io_receive4:
	inl	%dx,		%eax
	mov	12(%esp),	%edx
	mov	%eax,		(%edx)
	jmp	io_receive_end
io_receive_end:	
	pop	%edx
	ret
