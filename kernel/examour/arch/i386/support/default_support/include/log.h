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

#ifndef	__LOG_H__
#define	__LOG_H__

#include	<examour/support/support.h>

#ifndef	__ASM__

/**
 * \brief	Prints a panic message.
 */
#define	panic(fmt, args...)			\
do						\
{						\
  kprintf("[PANIC]" fmt, ## args);		\
  while (1);					\
} while (0)

/**
 * \brief	Prints a debug message.
 */
#define	debug(fmt, args...)			\
do						\
{						\
  kprintf("[DEBUG]" fmt, ## args);		\
} while (0)

/**
 * \brief	Prints a error message.
 */
#define	error(fmt, args...)			\
do						\
{						\
  kprintf("[ERROR]" fmt, ## args);		\
} while (0)

/**
 * \brief	Prints a info message.
 */
#define	info(fmt, args...)			\
do						\
{						\
  kprintf("[INFO]" fmt, ## args);		\
} while (0)

/**
 * \brief	Prints a message.
 */
#define	message(fmt, args...)			\
do						\
{						\
  kprintf(fmt, ## args);			\
} while (0)


#endif /* __ASM__ */


#endif /* __LOG_H__ */
