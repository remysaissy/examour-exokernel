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

#ifndef	__LDT_H__
#define	__LDT_H__

#include	<examour/mm/mem.h>
#include	<examour/core/segment_types.h>

/**
 * \brief	Index in every ldt where the ldt is mapped.
 *		Read-only mapping.
 */
#define	LDT_ENTRY_IDX		0

/**
 * \brief	Index in every ldt where the env's kernel data structures
 *		are mapped. Read-only mapping.
 */
#define	KENV_ENTRY_IDX		1

/**
 * \brief	Index in every ldt where the env's predicates are located.
 *		Read-write mapping.
 */
#define	KENV_PREDICATE_IDX	2

/**
 * \brief	Maximum number of entries in of an ldt.
 */
#define	LDT_MAX_SIZE		PAGE_SIZE

#ifndef	__ASM__

#include	<stdbool.h>
#include	<stddef.h>

/**
 * \brief	Initialize the ldt subsystem.
 */
void		ldt_init(void);

/**
 * \param context	The context to be created. Filled during the call.
 * \param new_env	The environment that requested the context creation.
 * \return		true on success, false otherwise.
 * \brief		Creates a new ldt context and fills it with kernel
 *			entries. Internal function.
 *			This function is used both buy ldt_create and during
 *			an env_create.
 */
bool		_ldt_create(ldtr_t *context,
			    paddr_t new_env);

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
 * \param selector	Selector of the entry to remove.
 * \return		true on success, false otherwise.
 * \brief		Remove an entry from a given ldt context.
 */
bool		ldt_remove_entry(ldtr_t *context,
				 uint32_t selector);

/**
 * \param ldtr		The context to be used.
 * \brief		Flush the content of a memory context.
 *			This is used for deleting environments.
 */
void		ldt_flush(ldtr_t *ldtr);

/**
 * \param ldtr		The context to be used.
 * \brief		Dumps the content of a memory context.
 */
void		ldt_dump(ldtr_t *ldtr);

#endif /* __ASM__ */

#endif /* __LDT_H__ */
