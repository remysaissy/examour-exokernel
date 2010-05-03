/*
** This file is part of exAmour

** Copyright (C) Remy Saissy <remy.saissy@epitech.net>
** exAmour is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Softw
** are Foundation; either version 2 of the License, or
** (at your option) any later version.

** exAmour is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.

** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#ifndef	__SUPPORT_H__
#define	__SUPPORT_H__

/**
 * \brief	Header of support.c which contains some helper routines
 *		for common operations in the kernel code.
 * \todo	Some code (kprintf for example) should be removed in favor
 *		of a real logging subsystem.
 */

#include	<string.h>
#include    "stdarg.h"

/**
 * \brief	The number of columns in a terminal.
 * \todo	Used in the builtin video output driver. Must be removed.
 */
#define COLUMNS			80

/**
 * \brief	The number of lines in a terminal.
 * \todo	Used in the builtin video output driver. Must be removed.
 */
#define ROWS			25

/**
 * \brief	The attribute of a character, it defines foreground and
 *		background color.
 * \todo	Used in the builtin video output driver. Must be removed.
 */
#define ATTRIBUTE		0x0c00

#define VGA_COLOR               0xb8000

#ifndef	__ASM__

#include	<stddef.h>

/**
 * \param x	The object to be transformed in string.
 * \brief	Transforms the argument in string. (call STR(x)).
 */
#define	_STR(x)	#x

/**
 * \param x	The object to be transformed in string.
 * \brief	Transforms the argument in string.
 */
#define	STR(x)	_STR(x)

/**
 * \param s	The string to print
 * \brief	Prints a given string to the standard output
 */
void		kputstr(const char *s);

/**
 * \param c	The character to print
 * \brief	Prints a given character to the standard output
 */
void		kputchar(long c);

/**
 * \brief	Clear the output
 */
void		cls(void);

/**
 * \param n		The long value to convert in a string
 * \param base_sz	The numeric base to use for conversion
 * \brief		Converts a long value into its string representation
 *			according to a numeric base
 */
void		kltoa(unsigned long n, long base_sz);

/**
 * \param n		The short value to convert in a string
 * \param base_sz	The numeric base to use for conversion
 * \brief		Converts a short value into its string representation
 *			according to a numeric base
 */
void		khtoa(unsigned short n, long base_sz);

/**
 * \param fmt		The format string
 * \return		The number of bytes written
 * \brief		Prints on the standard output a string formatted using
 *			special directives and variable parameter list.
 */
int		kprintf(const char *fmt, ...);

/**
 * \param fmt		The format string
 * \param ap		The variable parameter list context
 * \return		The number of bytes written
 * \brief		Prints a string formatted using special directives and
 *			variable parameter list.
 */
int		kvprintf(const char *fmt, va_list ap);

#endif /* __ASM__ */

#endif /* __SUPPORT_H__ */
