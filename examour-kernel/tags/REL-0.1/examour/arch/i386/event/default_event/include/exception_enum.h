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

#ifndef	__EXCEPTION_ENUM_H__
#define	__EXCEPTION_ENUM_H__

#ifndef	__ASM__

/**
 * \brief	Informs from where an exception was thrown
 */
typedef enum
  {
    exception_code_location_gdt = 0,
    exception_code_location_idt,
    exception_code_location_ldt,
    exception_code_location_idt_bis

  }	exception_code_location_e;


#endif /* __ASM__ */

#endif /* __EXCEPTION_ENUM_H__ */
