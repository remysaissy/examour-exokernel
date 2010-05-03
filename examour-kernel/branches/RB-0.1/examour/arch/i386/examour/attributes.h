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

/**
 * This header contains macros to support specific compiler options
 * used in ExAmour in a more portable way.
 * If you want ExAmour to compile with your compiler, you should have a look here.
 * By convention, all macros are embrased by one '_'. No special reason to it,
 * just one more silly rule...
 */

#ifndef	__ATTRIBUTES_H__
#define	__ATTRIBUTES_H__

#ifndef	__ASM__

#ifdef	__GNUC__

#define	PACKED			__attribute__ ((__packed__))

/**
 * \param size	The number of byte for the alignement
 * \brief	Gcc attribute to force alignement
 */
#define	__ALIGNED__(size)	__attribute__((__aligned__(size)))


#define	__INLINE__		__inline__

#elif defined (__TINYC__)


#define	PACKED			__attribute__ ((__packed__))

/**
 * \param size	The number of byte for the alignement
 * \brief	Gcc attribute to force alignement
 */
#define	__ALIGNED__(size)	__attribute__((__aligned__(size)))


#define	__INLINE__		inline

#else

#error	"Compiler not recognized. Please add its attributes macros in examour/attribues.h."

#endif /* Compiler unrecognized. */

#endif /* __ASM__ */

#endif /* __ATTRIBUTES_H__ */
