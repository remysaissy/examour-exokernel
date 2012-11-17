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

#ifndef	__SECURITY_H__
#define	__SECURITY_H__

/**
 * \brief	Specifies an alive environnement.
 */
#define	CAP_ALIVE		0x1

/**
 * \brief	Capability to create environments.
 */
#define	CAP_CREATE_ENV		0x2

/**
 * \brief	Capability to destroy environments.
 */
#define	CAP_DESTROY_ENV		0x4

/**
 * \brief	Capability to create and delete memory contexts.
 */
#define	CAP_CREATE_MEM_CTX	0x8

/**
 * \brief	Capability to allocate and free memory.
 */
#define	CAP_ALLOC_MEM		0x10

/**
 * \brief	Capability to grant and revoke i/o.
 */
#define	CAP_GRANT_IO		0x20

/**
 * \brief	Capability to register and unregister events.
 */
#define	CAP_EVENT		0x40

#ifndef	__ASM__

#include	<stdint.h>

/**
 * \brief	A Basic cap type.
 */
typedef uint32_t	basic_cap_t;


/**
 * \param _basic_cap	The basic cap to grant.
 * \brief		Grants a basic cap.
 */
#define		cap_grant_basic(_basic_cap)	\
    gl_current_env->basic_cap = (_basic_cap);

#endif /* __ASM__ */

#endif /* __SECURITY_H__ */
