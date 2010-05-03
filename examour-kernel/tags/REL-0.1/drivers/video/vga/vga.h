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

#ifndef	__VGA_H__
#define	__VGA_H__

#include	<examour/mm/ldt.h>

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
 * \brief	Number of space of a tabulation.
 */
#define	TABULATION_SIZE		4

#ifndef	__ASM__

#include	<stddef.h>
#include	<string.h>
#include	<examour/mm/mem_types.h>

typedef struct	vga_color_s
{
  const char	*id;
  int		value;

}		vga_color_t;

/** Transforms the argument in string. (call STR(x)) */
#define	_STR(x)	#x
/** Transforms the argument in string. */
#define	STR(x)	_STR(x)

/**
 * \return	true on success, false otherwise.
 * \brief	Initialize the vga capability.
 */
bool		vga_init(void);

/**
 * \param s	The string to print
 * \return	the number of written bytes.
 * \brief	Prints a given string to the standard output
 */
int		puts(const char *s);

/**
 * \param c	The character to print
 * \return	The number of written bytes.
 * \brief	Prints a given character to the standard output
 */
int		putchar(int c);

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
void		ltoa(long n, long base_sz);

/**
 * \param n		The short value to convert in a string
 * \param base_sz	The numeric base to use for conversion
 * \brief		Converts a short value into its string representation
 *			according to a numeric base
 */
void		htoa(short n, long base_sz);

/**
 * \param fmt		The format string
 * \return		The number of bytes written
 * \brief		Prints on the standard output a string formatted using
 *			special directives and variable parameter list.
 */
int		printf(char *fmt, ...);

void		list_bg_colors(void);

int		set_background_color(char *id);

void		list_fg_colors(void);

int		set_foreground_color(char *id);

#endif /* !__ASM__ */

#endif /* !__VGA_H__ */
