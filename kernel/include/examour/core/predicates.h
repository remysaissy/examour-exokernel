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

#ifndef	__PREDICATES_H__
#define	__PREDICATES_H__

#include	<examour/mm/mem_types.h>
#include	<examour/core/segment_types.h>

#ifndef	__ASM__

#include	<stdint.h>

#pragma pack(push,1)

/**
 * \brief	A predicate.
 */
typedef struct	PACKED predicate_s
{
  selector_t	cs;		/** The code segment selector. */
  uint16_t	padding;
  paddr_t	offset;		/** address to jump to. */

}		predicate_t;

#pragma pack(pop)

#else

/**
 * \brief	Offset of the code segment selector.
 */
#define	PREDICATE_CS_OFFSET	0

/**
 * \brief	Offset of the handler address.
 */
#define	PREDICATE_ADDR_OFFSET	4


#define	PREDICATE_SIZE		8

#endif /* !__ASM__ */

#endif /* __PREDICATES_H__ */
