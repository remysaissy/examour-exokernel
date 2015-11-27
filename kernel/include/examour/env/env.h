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

#ifndef	__ENV_H__
#define	__ENV_H__

#include	<examour/env/env_types.h>
#include	<examour/event/io_types.h>

#ifndef	__ASM__

/**
 * \brief	Initialize the environment subsystem.
 */
void		env_init(void);

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
 * \brief	Creates the idle env
 */
void		env_create_idle(void);

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
 * \param new_env	The new environment structure pointer
 * \brief		Switch to the next env context.
 */
void		__switch_to(examour_env_t *new_env);

#endif /* __ASM__ */

#endif /* __ENV_H__ */
