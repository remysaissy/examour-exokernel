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

#ifndef	__EVENT_H__
#define	__EVENT_H__

#include	<examour/mm/mem.h>
#include	<examour/core/segment_types.h>
#include	<examour/env/env_types.h>
#include	<examour/event/event_types.h>

#ifndef	__ASM__

#include	<stddef.h>

/* Macros for flags used in event_register. */

/**
 * \brief	Upon success of event_register, the handler
 *		won't be removable.
 */
#define	EVENT_REGISTER_LOCKED	0x1

/**
 * \brief	Upon success of event_register, the handler
 *		will be automagically removed after a first call.
 */
#define	EVENT_REGISTER_ONESHOT	0x2

/**
 * \brief	Initialize the event subsystem.
 */
void		event_init(void);

/**
 * \param vector_id	The id of event to register.
 * \param cs		The code segment selector.
 * \param offset	The offset of the handler.
 * \param flags		Flags that can be used along with the registration.
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


bool		event_forge(void *forgery, uint32_t *event_id);


bool		event_throw(uint32_t event_id, uint32_t flags);

/**
 * \param env		The env to flush the event handlers.
 * \brief		Flush the event handlers of a given env.
 */
void		event_flush(examour_env_t *env);

#endif /* __ASM__ */

#endif /* __EVENT_H__ */
