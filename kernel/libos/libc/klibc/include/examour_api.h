/* 
 * This file is part of ExAmour

 * Copyright (C) Remy Saissy <remy.saissy@gmail.com>
 * ExAmour is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.

 * ExAmour is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#ifndef	__CRT_H__
#define	__CRT_H__

/*
 * Important notes:
 *  - -1 on index value for memcopoy and memset means ds based access.
 *  - -1 value on write and read means no change to ds.
 *  - the value parameter of read and write functions is assumed to be ss. Means that it
 *    is considered as a stack parameter. Take care when passing the pointer of read.
 *    If you want heap pointer, consider using memcopy and memset functions instead.
 */

/* C99 headers. */
#include	<stdint.h>
#include	<stddef.h>
#include	<stdbool.h>

/* ExAmour headers. */
#include	<examour/mm/ldt.h>
#include	<examour/mm/mem.h>
#include	<examour/env/env.h>
#include	<examour/event/event.h>

/* SYSCALLS */

/**
 * \param context	The context to be created. Filled during the call.
 * \return		True on success, false otherwise.
 * \brief		Creates a new ldt context and fills it with kernel
 *			entries.
 */
bool		ldt_create(ldtr_t *context);

/**
 * \param context	The ldt context to be destroyed.
 * \return		True on success, false otherwise.
 * \brief		Destroy a given ldt context.
 * \warning		If context is NULL, the current env context
 *			is destroyed,
 *			therefore this call can definitely break an
 *			environment.
 */
bool		ldt_destroy(ldtr_t *context);

/**
 * \param context	The context to be used.
 * \param flags		Flags used to indicate the kind of memory segment
 *			to be allocated.
 * \param base_addr	Whished base address or PADDR_ERROR for a new
 *			allocation.
 * \param size		The size in bytes of the memory segment.
 * \return		-1 on error, a non negative value on success.
 * \brief		Add a new entry to a given ldt context.
 */
int		ldt_add_entry(ldtr_t *context,
			      uint32_t flags,
			      paddr_t base_addr,
			      size_t size);

/**
 * \param context	The context to be used.
 * \param selector	Index of the entry to remove.
 * \return		true on success, false otherwise.
 * \brief		Remove an entry from a given ldt context.
 */
bool		ldt_remove_entry(ldtr_t *context,
				 uint32_t index);


/**
 * \param id		The string unique identifier of the environment.
 * \param basic_cap	The basic capabilities of the env.
 *			(mem alloc, env_create, ...)
 * \param sections	The sections of the new env binary.
 * \param n_sections	The number of sections
 * \return		In case of an alive env, the eid in case of succes,
 *			a negative number in case of error.
 *			If it is a dead env, the index of the code segment in
 *			the current ldt or -1 in case of error.
 * \brief		Creates a new env in the system and schedule it
 */
int		env_create(char *id,
			   basic_cap_t basic_cap,
			   examour_env_section_t *sections,
			   int n_sections);

/**
 * \brief	Yield the execution timeslice.
 * \warning	The env put itself into an io sleeping state
 *		and give its timeslices back to the cpu.
 *		It can only be awakened through an event.
 * \todo	Todo.
 */
void		env_yield(void);

/**
 * \param eid	The eid of the env to delete.
 * \return	true on success, false otherwise
 * \brief	Delete an env. an eid of 0 means the calling env
 * \todo	Todo.
 */
bool		env_delete(eid_t eid);

/**
 * \param ms		The amount of cpu time the env wants
 *			(expressed in milliseconds).
 * \return		True on success, false if no time remains.
 * \brief		Used by an application to request a certain
 *			amount of cpu time.
 */
bool		timeslice_add(uint32_t ms, uint32_t flags);


/**
 * \param ioport	The ioport requested.
 * \param exclusive	Exclusive mode or not ?
 * \return		true on success, false otherwise.
 * \brief		Grants a new cap.
 */
bool		io_grant(uint16_t ioport, bool exclusive);

/**
 * \param ioport	The ioport requested.
 * \return		true on success, false otherwise.
 * \brief		Revoke a cap.
 */
bool		io_revoke(uint16_t ioport);

/**
 * \param vector_id	The id of event to register.
 * \param cs		The code segment selector.
 * \param offset	The offset of the handler.
 * \param flags		Flags of the new event.
 * \return		true on success, false otherwise.
 * \brief		Register a new event handler.
 */
bool		event_register(uint32_t vector_id,
			       selector_t cs,
			       paddr_t offset,
			       uint32_t	flags);

/**
 * \param vector_id	The id of event to unregister.
 * \param cs		The code segment selector.
 * \param offset	The offset of the handler.
 * \return		true on success, false otherwise.
 * \brief		Unregister an event handler.
 */
bool		event_unregister(uint32_t vector_id,
				 selector_t cs,
				 paddr_t offset);

/**
 * \todo	Forge a new, user defined event.
 *		Not yet implemented.
 */
bool		event_forge(void *forgery,
			    uint32_t *event_id);

/**
 * \todo	Throw a user defined event.
 *		Not yet implemented.
 */
bool		event_throw(uint32_t event_id,
			    uint32_t	flags);


/* Prologue/Epilogue functions. */

/**
 * \brief			Set the epilogue handler of an environnement.
 * \param epilogue_handler	The epilogue function callback.
 */
void		set_epilogue(paddr_t epilogue_handler);

/**
 * \brief	Unset the epilogue handler of an environnement.
 */
void		unset_epilogue(void);

/**
 * \brief			Set the prologue handler of an environnement.
 * \param prologue_handler	The epilogue function callback.
 */
void		set_prologue(paddr_t prologue_handler);

/**
 * \brief	Unset the prologue handler of an environnement.
 */
void		unset_prologue(void);

/* Upcalls. */

/**
 * \brief		Set an exception handler.
 * \param exception_id	The id of the exception according to the intel reference book.
 * \param exception_handler	The function callback to use when the exception is rose.
 */
void		set_exception_handler(uint32_t exception_id, 
				      paddr_t exception_handler);

/**
 * \brief		Unset an exception handler.
 * \param exception_id	The id of the exception according to the intel reference book.
 */
void		unset_exception_handler(uint32_t exception_id);

/**
 * \brief	Get the base address of the stack.
 * \return	The base address of the stack.
 */
paddr_t		get_stack_base_address(void);

/* Segment memory access. */

/**
 * \brief	Get the LDT's index of the cs's code segment descriptor.
 * \return	The LDT's index.
 */
int		get_cs_index(void);

/**
 * \brief	Get the LDT's index of the ss's stack segment descriptor.
 * \return	The LDT's index.
 */
int		get_ss_index(void);

/**
 * \brief	Get the LDT's index of the ds's data segment descriptor.
 * \return	The LDT's index.
 */
int		get_ds_index(void);

/**
 * \brief	Get the LDT's index of the es's data segment descriptor.
 * \return	The LDT's index.
 */
int		get_es_index(void);

/**
 * \brief	Get the LDT's index of the fs's data segment descriptor.
 * \return	The LDT's index.
 */
int		get_fs_index(void);

/**
 * \brief	Get the LDT's index of the gs's data segment descriptor.
 * \return	The LDT's index.
 */
int		get_gs_index(void);

/**
 * \brief	Get the current stack pointer value.
 * \return	The current stack pointer value.
 */
paddr_t		get_sp(void);

/**
 * \brief	Get the current process counter value.
 * \return	The current process counter value.
 */
paddr_t		get_pc(void);

/**
 * \brief		Performs a memcopy operation by identifying offsets according to their descriptor index in the ldt.
 * \param out_index	The ldt's index of the destination pointer segment.
 * \param out_offset	The destination pointer.
 * \param in_index	The ldt's index of the source pointer segment.
 * \param in_offset	The source pointer.
 * \param nmemb		The number of object to copy.
 * \param size		The size of an object.
 * \warning		Value -1 on out_index or in_index means using the current segment descriptor value. out_index is ES and in_index is DS as specified by intel for data copy.
 */
void		segment_memcopy_by_index(int out_index, paddr_t out_offset,
				int in_index, paddr_t in_offset,
				size_t nmemb, size_t size);

/**
 * \brief		Performs a memcopy operation by identifying offsets according to their descriptor selectors. They can be either in ldt or gdt.
 * \param out_selector	The segment selector of the destination pointer segment.
 * \param out_offset	The destination pointer.
 * \param in_selector	The segment selector of the source pointer segment.
 * \param in_offset	The source pointer.
 * \param nmemb		The number of object to copy.
 * \param size		The size of an object.
 */
void		segment_memcopy_by_selector(selector_t out_selector, paddr_t out_offset,
				selector_t in_selector, paddr_t in_offset,
				size_t nmemb, size_t size);

/**
 * \brief		Performs a memset operation by identifying offset according to its descriptor index in the ldt.
 * \param index		The ldt's index of the pointer segment.
 * \param offset	The pointer.
 * \param value		The value to put.
 * \param nmemb		The number of object to copy.
 * \param size		The size of an object.
 * \warning		Value -1 on index means using the current DS segment descriptor value. Valid sizes are 1,2,4. A 4 bytes size means that 4 bytes are taken from value and copied everywhere from offset to offset+nmemb*size.
 */
void		segment_memset_by_index(int index, paddr_t offset,
					int value, size_t nmemb, size_t size);

/**
 * \brief		Performs a memset operation by identifying offset according to its segment selector.
 * \param selector	The segment selector of the pointer segment.
 * \param offset	The pointer.
 * \param value		The value to put.
 * \param nmemb		The number of object to copy.
 * \param size		The size of an object.
 * \warning		We use the DS register. Valid sizes are 1,2,4. A 4 bytes size means that 4 bytes are taken from value and copied everywhere from offset to offset+nmemb*size.
 */
void		segment_memset_by_selector(selector_t selector, paddr_t offset,
					   int value, size_t nmemb, size_t size);

/**
 * \brief		Write 1 byte of data to a specific location.
 * \param index		The ldt's index of the pointer segment.
 * \param offset	The pointer.
 * \param value		The value to put.
 */
void		segment_write1_by_index(int index, paddr_t offset,
					uint8_t value);
/**
 * \brief		Write 1 byte of data to a specific location.
 * \param selector	The segment selector of the pointer segment.
 * \param offset	The pointer.
 * \param value		The value to put.
 */
void		segment_write1_by_selector(selector_t selector, paddr_t offset,
					uint8_t value);

/**
 * \brief		Write 2 bytes of data to a specific location.
 * \param index		The ldt's index of the pointer segment.
 * \param offset	The pointer.
 * \param value		The value to put.
 */
void		segment_write2_by_index(int index, paddr_t offset,
					uint16_t value);

/**
 * \brief		Write 2 bytes of data to a specific location.
 * \param selector	The segment selector of the pointer segment.
 * \param offset	The pointer.
 * \param value		The value to put.
 */
void		segment_write2_by_selector(selector_t selector, paddr_t offset,
					uint16_t value);

/**
 * \brief		Write 4 bytes of data to a specific location.
 * \param index		The ldt's index of the pointer segment.
 * \param offset	The pointer.
 * \param value		The value to put.
 */
void		segment_write4_by_index(int index, paddr_t offset,
					uint32_t value);

/**
 * \brief		Write 4 bytes of data to a specific location.
 * \param selector	The segment selector of the pointer segment.
 * \param offset	The pointer.
 * \param value		The value to put.
 */
void		segment_write4_by_selector(selector_t selector, paddr_t offset,
					uint32_t value);

/**
 * \brief		Read 1 byte of data from a specific location.
 * \param index		The ldt's index of the pointer segment.
 * \param offset	The pointer.
 * \param value		The value read.
 */
void		segment_read1_by_index(int index, paddr_t offset,
					uint8_t *value);

/**
 * \brief		Read 1 byte of data from a specific location.
 * \param selector	The segment selector of the pointer segment.
 * \param offset	The pointer.
 * \param value		The value read.
 */
void		segment_read1_by_selector(selector_t selector, paddr_t offset,
					uint8_t *value);

/**
 * \brief		Read 2 bytes of data from a specific location.
 * \param index		The ldt's index of the pointer segment.
 * \param offset	The pointer.
 * \param value		The value read.
 */
void		segment_read2_by_index(int index, paddr_t offset,
					uint16_t *value);

/**
 * \brief		Read 2 bytes of data from a specific location.
 * \param selector	The segment selector of the pointer segment.
 * \param offset	The pointer.
 * \param value		The value read.
 */
void		segment_read2_by_selector(selector_t selector, paddr_t offset,
					uint16_t *value);

/**
 * \brief		Read 4 bytes of data from a specific location.
 * \param index		The ldt's index of the pointer segment.
 * \param offset	The pointer.
 * \param value		The value read.
 */
void		segment_read4_by_index(int index, paddr_t offset,
					uint32_t *value);

/**
 * \brief		Read 4 bytes of data from a specific location.
 * \param selector	The segment selector of the pointer segment.
 * \param offset	The pointer.
 * \param value		The value read.
 */
void		segment_read4_by_selector(selector_t selector, paddr_t offset,
					   uint32_t *value);


/* set_*_by_index assumes a privilege level 3 ldt selector. */
/* Nothing is returned but an exception can be raised if the */
/* segment check of the cpu fails. */

/**
 * \brief	Set the code segment register.
 * \param index	The ldt's index of the segment.
 * \param pc	The new process counter to set.
 */
void		set_cs_by_index(int index, paddr_t pc);

/**
 * \brief		Set the code segment register.
 * \param selector	The segment selector of the segment.
 * \param pc		The new process counter to set.
 */
void		set_cs_by_selector(selector_t selector, paddr_t pc);

/**
 * \brief	Set the stack segment register.
 * \param index	The ldt's index of the segment.
 * \param sp	The new stack pointer to set.
 */
void		set_ss_by_index(int index, paddr_t sp);

/**
 * \brief		Set the stack segment register.
 * \param selector	The segment selector of the segment.
 * \param sp		The new stack pointer to set.
 */
void		set_ss_by_selector(selector_t selector, paddr_t sp);

/**
 * \brief	Set the ds data segment register.
 * \param index	The ldt's index of the segment.
 */
void		set_ds_by_index(int index);

/**
 * \brief		Set the ds data segment register.
 * \param selector	The segment selector.
 */
void		set_ds_by_selector(selector_t selector);

/**
 * \brief	Set the es data segment register.
 * \param index	The ldt's index of the segment.
 */
void		set_es_by_index(int index);

/**
 * \brief		Set the es data segment register.
 * \param selector	The segment selector.
 */
void		set_es_by_selector(selector_t selector);

/**
 * \brief	Set the fs data segment register.
 * \param index	The ldt's index of the segment.
 */
void		set_fs_by_index(int index);

/**
 * \brief		Set the fs data segment register.
 * \param selector	The segment selector.
 */
void		set_fs_by_selector(selector_t selector);

/**
 * \brief	Set the gs data segment register.
 * \param index	The ldt's index of the segment.
 */
void		set_gs_by_index(int index);

/**
 * \brief		Set the gs data segment register.
 * \param selector	The segment selector.
 */
void		set_gs_by_selector(selector_t selector);

/* Performance monitoring functions. */

/**
 * \brief		Get the timestamp.
 * \param timestamp	The timestamp.
 */
void		read_timestamp(uint64_t *timestamp);

/**
 * \brief	Send data to a port.
 * \param port	The port number to send data to.
 * \param value	The value to be sent.
 * \param size	Size of the data to be sent. Valid values are 1,2,4
 */
void		io_send(uint16_t port, uint32_t value, size_t size);

/**
 * \brief	Receive data from a port.
 * \param port	The port number to receive data from.
 * \param value	The received value.
 * \param size	Size of the data to be received. Valid values are 1,2,4
 */
void		io_receive(uint16_t port, uint32_t *value, size_t size);

/*  - memory mapped information control functions; */

#endif /* __CRT_H__ */
