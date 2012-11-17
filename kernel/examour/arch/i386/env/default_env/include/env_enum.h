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
** Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef	__ENV_ENUM_H__
#define	__ENV_ENUM_H__

#ifndef	__ASM__

/**
 * \brief	States which can be taken by an env.
 */
typedef enum
  {
    env_empty = 0,	/* yes, currently it is a static array... */
    env_stopped,
    env_running,	/* means that this env is the current one */
    env_out_of_cpu,
    env_in_syscall	/* the environement is currently in a syscall. */
  }		env_state_e;

#endif /* __ASM__ */

#endif /* __ENV_ENUM_H__ */
