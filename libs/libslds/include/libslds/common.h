/*
 * This file is part of libslds

 * Copyright (C) Remy Saissy <remy.saissy@gmail.com>
 * libslds is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.

 * libslds is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#ifndef	__LIBSLDS_COMMON_H__
#define	__LIBSLDS_COMMON_H__

/**
 * This header contains code common to all kind of data structures in the library.
 */

#ifndef	typeof
#define	typeof(x)	__typeof__(x)
#endif

#ifndef	offsetof
#define	offsetof(tp, member)	__builtin_offsetof(tp, member)
#endif


/* Data structures macros. */

#ifdef	GET_FIELD
#undef	GET_FIELD
#endif
/**
 * Get a field of a data structure. The field is expressed by the member name.
 */
#define	GET_FIELD(st, m, t)	((t *)(((char *)(st)) + (m)))

#endif /* __LIBSLDS_COMMON_H__ */
