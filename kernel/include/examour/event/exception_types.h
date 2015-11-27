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

#ifndef	__EXCEPTION_TYPES_H__
#define	__EXCEPTION_TYPES_H__

#include	<examour/core/segment_types.h>
#include	<examour/event/exception_enum.h>

#ifndef	__ASM__

#include	<stdbool.h>
#include	<stdint.h>

/**
 * \brief	Layout of the optional error code of an exception.
 */
typedef struct			exception_error_code_s
{
  bool				external : 1;
  exception_code_location_e	location : 2;
  selector_t			index;
  uint32_t			reserved : 13;

}				exception_error_code_t;

/* the page fault exception has a specific error code layout */
/**
 * \brief	Layout of the optional error code of an exception.
 *		The page fault exception has a specific error code layout.
 */
typedef struct	exception_page_fault_error_code_s
{
  bool		protection_violation : 1; /** false == not present page. */
  bool		write_access : 1;	  /** false == read access */
  bool		from_usermode : 1;	  /** false == from supervisor mode */
  bool		reserved_bits_page_dir : 1;/** false == reserved bits violation, true == reserved bits in a page directory */
  uint32_t	reserved : 27;

}		exception_page_fault_error_code_t;


#endif /* __ASM__ */

#endif /* __EXCEPTION_TYPES_H__ */
