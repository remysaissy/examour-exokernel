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

#ifndef	__REGS_H__
#define	__REGS_H__

/**
 * \brief	This file contains useful macros to manipulate
 *		IA-32's registers.
 */

#ifndef	__ASM__

/**
 * \param reg	The register to modify
 * \param val	The value to set
 * \brief	Sets a memory reference value in a register
 */
#define set_register(reg, val)			\
do						\
{						\
  __asm__ volatile ("mov %0,%%"#reg:: "m"(val));\
} while (0)

/**
 * \param reg	The register to modify
 * \param val	The value to set
 * \brief	Sets an immediate value in a given register
 */
#define set_register_i(reg, val)		\
do						\
{						\
  __asm__ volatile ("mov %0,%%"#reg:: "i"(val));\
} while (0)

/**
 * \param reg	The register to read from
 * \return	the value in a given register
 * \brief	Gets the value of a given register
 */
#define get_register(reg)				\
({							\
  int   __v;						\
							\
  __asm__ volatile ("mov %%"#reg ",%0\n\t" : "=m"(__v));\
  (__v);						\
})

#endif /* __ASM__ */

#endif /* __REGS_H__ */
