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

#ifndef	__SCHED_H__
#define	__SCHED_H__

/* scheduler functions */
#include	<examour/env/env_types.h>
#include	<examour/core/segment_types.h>
#include	<examour/mm/mem.h>
#include	<examour/event/event_types.h>

#ifndef	__ASM__

/**
 * \brief	Initialize the scheduler subsystem.
 */
void	sched_init(void);

/**
 * \return	1 if a switch occured, 0 otherwise.
 * \brief	Selects the next env to be executed.
 */
int	sched_next(void);

/**
 * \param env		The env to schedule.
 * \param cs		The env's  code segment selector.
 * \param offset	The env's program counter.
 * \brief		Schedule an environment for event handling.
 *			This is used on reception of interruptions,
 *			event_register() and prologue and epilogue.
 * \todo		Todo. Activate prologue and epilogue with it.
 */
void	timed_sched(examour_env_t *env, selector_t cs, paddr_t offset, kevent_cpu_context_t *args);

#endif /* __ASM__ */

#endif /* __SCHED_H__ */
