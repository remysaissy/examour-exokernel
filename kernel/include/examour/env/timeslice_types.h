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

#ifndef	__TIMESLICES_TYPES_H__
#define	__TIMESLICES_TYPES_H__

#include	<examour/env/env_types.h>

#ifndef	__ASM__

#include	<stdint.h>
#include	<libslds/list.h>

/**
 * \brief	Storage of environment's timeslice requests.
 */
typedef struct		examour_timeslice_s
{
  clist_t		timeslices_list;/** it is a circular list. */
  examour_env_t		*env;		/** pointer to the relevant env. */
  uint32_t		ms_cnt;		/** Remaining milliseconds. */

}			examour_timeslice_t;

#endif /* __ASM__ */

#endif /* __TIMESLICES_TYPES_H__ */
