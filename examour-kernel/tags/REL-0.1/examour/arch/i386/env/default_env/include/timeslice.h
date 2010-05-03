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

#ifndef	__TIMESLICE_H__
#define	__TIMESLICE_H__

/**
 * \brief	Header of the timeslice subsystem.
 *		Belongs to the env component.
 */

#include	<examour/env/timeslice_types.h>

#ifndef	__ASM__

/**
 * \brief	Initialize the timeslice subsystem.
 */
void		timeslice_init(void);

/**
 * \param ms		The amount of cpu time the env wants
 *			(expressed in milliseconds).
 * \return		True on success, false if no time remains.
 * \brief		Used by an application to request a certain
 *			amount of cpu time.
 */
bool		timeslice_add(uint32_t ms, uint32_t flags);

/**
 * \param ms		The amount of cpu time the env wants
 *			(expressed in milliseconds).
 * \param env		The env concerned by the timeslice request.
 * \return		True on success, false if no time remains.
 * \brief		Used by an application to request a certain amount
 *			of cpu time.
 */
bool		_timeslice_add(uint32_t ms, uint32_t flags, examour_env_t **env);

/**
 * \param ms		The amount of cpu time the env wants to give up.
 * \return		True on succes, false if the give up is not possible.
 * \brief		Used by an application to release a certain amount of
 *			cpu time.
 */
bool		timeslice_remove(uint32_t ms);

/**
 * \param entry		The timeslice unit to be updated.
 * \return		True if the timeslice unit is empty and has been
 *			destroyed, false otherwise.
 * \brief		Updates a timeslice entry by decrementing one timer
 *			tick. Once all the slices has been consumed, the entry
 *			is destroyed.
 */
bool		timeslice_update(examour_timeslice_t *entry);

/**
 * \param eid		The eid of the env's timeslices to flush.
 * \brief		Flush out all the timeslices allocated for
 *			the env identified by eid.
 */
void		timeslice_flush(eid_t eid);

/**
 * \brief		Dumps the content of the timeslice subsystem
 *			on the standard output.
 *			Useful to know about the currently allocated
 *			timeslices.
 */
void		timeslice_dump(void);

#endif /* __ASM__ */

#endif /* __TIMESLICE_H__ */
