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

#ifndef	__CAPS_TYPES_H__
#define	__CAPS_TYPES_H__

#include	<examour/mm/mem.h>

#ifndef	__ASM__

#include	<stddef.h>
#include	<stdbool.h>
#include	<libslds/list.h>

#include	<examour/env/env_types.h>

/**
 * \brief	This structure describes a capability.
 */
typedef struct	iocap_s
{
  dlist_t	iocaps_list;	/** list of the capabilities. (for caps.c) */
  dlist_t	envs_list;	/** list of env of the cap. (for env.c) */
  struct examour_env_s *envs;	/** list of the env which are using the cap. (cap_list member) */
  bool		exclusive;	/** true is the cap can't be shared. */
  uint32_t	ref_cnt;	/** reference counter of the cap. */
  uint16_t	ioport;		/** io ports of the cap. */

}		iocap_t;

#endif /* !__ASM__ */

#endif /* __CAPS_TYPES_H__ */
