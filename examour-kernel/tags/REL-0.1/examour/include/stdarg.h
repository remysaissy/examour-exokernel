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

#ifndef	__STDARG_H__
#define	__STDARG_H__

#ifndef	_VA_LIST_DEFINED
#define _VA_LIST_DEFINED

/**
 * \brief	The va_list type from gcc builtin.
 * \todo	Perhaps it is useless.
 */
typedef char *va_list;

/* only correct for i386 */
/**
 * \param ap	The va_list variable.
 * \param last	The last known argument.
 * \brief	Initialize a new va_list variable according
 *		to the last known argument.
 */
#define va_start(ap,last) ap = ((char *)&(last)) + ((sizeof(last)+3)&~3)

/**
 * \param ap	The va_list variable.
 * \param type	The type of the returned argument.
 * \return	The next argument in the the va_list
 *		with type type.
 * \brief	Get the next argument in a given va_list.
 */
#define va_arg(ap,type) (ap += (sizeof(type)+3)&~3, *(type *)(ap - ((sizeof(type)+3)&~3)))

/**
 * \param ap	The va_list variable.
 * \brief	Uninitialize a va_list.
 */
#define va_end(ap)

/* fix a buggy dependency on GCC in libio.h */
typedef va_list __gnuc_va_list;

#endif /* _VA_LIST_DEFINED */

#endif /* __STDARG_H__ */
