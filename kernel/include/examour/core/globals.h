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

#ifndef	__GLOBALS_H__
#define	__GLOBALS_H__

#include	"multiboot.h"
#include	"segment.h"
#include	<examour/mm/mem.h>
#include	<examour/env/env_types.h>
#include	<examour/env/timeslice_types.h>

#ifndef	__ASM__

/**
 * \brief	The global descriptor table.
 */
extern gdt_t				gl_gdt[GDT_NR_ENTRIES];

/**
 * \brief	The interrupt descriptor table.
 */
extern gate_t				*gl_idt;

/**
 * \brief	The current env.
 */
extern examour_env_t			*gl_current_env;

/**
 * \brief	The environments informastions structure.
 */
extern examour_env_informations_t	gl_envs;

/**
 * \brief	The timeslices structure.
 */
extern examour_timeslice_t		*gl_timeslices;

/**
 * \brief	The multiboot information.
 * \warning	After system initialization step, this pointer
 *		is not usable.
 */
extern multiboot_info_t			*mbi;

/**
 * \brief	The task state segment.
 * \todo	Presently there is one tss for the system. Try with
 *		one per env for efficient iomap with physical memory.
 */
extern tss_t				gl_tss;

#endif /* __ASM__ */

#endif /* __GLOBALS_H__ */


