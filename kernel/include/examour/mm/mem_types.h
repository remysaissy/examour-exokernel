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

#ifndef	__MEM_TYPES_H__
#define	__MEM_TYPES_H__

/**
 * \brief	Available memory mapped areas.
 */


/**
 * \brief	The invalid physical address.
 */
#define	PADDR_ERROR	0xffffffff

#define	ADDR_ERROR	0xffffffff

#ifndef	__ASM__

#include	<stdint.h>

/**
 * \brief	Generic address type.
 */
typedef uint32_t	addr_t;

/**
 * \brief	A physical address.
 */
typedef addr_t		paddr_t;

/**
 * \brief	Enumeration of the memory areas.
 */
enum mem_area_e
  {
#define	MEM_ENTRY(id, base_addr, length, type)	\
 id = base_addr,				\
 id ## _SZ = length,

#include "mem.def"

#undef MEM_ENTRY
  };

#endif /* __ASM__ */


#endif /* __MEM_TYPES_H__ */
