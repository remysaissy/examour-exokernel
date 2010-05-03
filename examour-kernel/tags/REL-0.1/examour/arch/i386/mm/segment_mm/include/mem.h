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

#ifndef	__MEM_H__
#define	__MEM_H__

#include	<examour/mm/mem_types.h>

/**
 * \brief	The shift of a page size
 */
#define	PAGE_SHIFT		12

/**
 * \brief	The size of a page
 */
#define	PAGE_SIZE		0x1000

/**
 * \brief	The shift of a 4mb page
 */
#define	BIG_PAGE_SHIFT		22

/**
 * \brief	The size of a 4mb page
 */
#define	BIG_PAGE_SIZE		0x1000000

/**
 * \brief	The size of a kernel stack
 */
#define	STACK0_SIZE		0x3000

/**
 * \brief	The binary mask of a paged address
 */
#define	PAGE_MASK		(~(PAGE_SIZE - 1))

/**
 * \brief	The binary mask of a paged address
 */
#define	BIG_PAGE_MASK		(~(BIG_PAGE_SIZE - 1))

/**
 * \brief	The binary mask of a kernel stack address
 */
#define	STACK0_MASK		(~(STACK0_SIZE - 1))

#ifndef	__ASM__

#include	<stddef.h>

/**
 * \param _addr		The address to align
 * \param pgsz		The size of a page
 * \param pgmsk		The binary mask of a page
 * \brief		Align an address to a given page size
 */
#define	_ALIGN_ADDR(_addr, pgsz, pgmsk) (((_addr) + pgsz - 1) & pgmsk)

/**
 * \param obj_size	Real size of the object to align
 * \param align		Alignment to apply
 * \return		The aligned value of obj_size.
 * Align an object size by excess.
 */
#define ROUNDUP(obj_size, align)			\
(((obj_size) <= (align)) ?				\
(((obj_size) + ((align) - 1)) & (align)) :		\
(((align) == 0) ?					\
(obj_size) :						\
(((obj_size) + ((align) - 1)) & ~(align))))

/**
 * \param _addr		The address to align
 * \brief		Align an address to the default PAGE_SIZE
 */
#define	ALIGN_ADDR(_addr)	_ALIGN_ADDR(_addr, PAGE_SIZE, PAGE_MASK)


/*
 * there is a bug with the + STACK0_SIZE when _addr
 * is the actual stack0 base addr.
 */

/**
 * \param _addr		The address to align
 * \brief		Align an address to the default STACK0_SIZE
 */
#define	GET_STACK0(_addr)					\
 (_ALIGN_ADDR(_addr, STACK0_SIZE, STACK0_MASK) + STACK0_SIZE)

/**
 * \param _addr		An address within the kernel stack
 * \brief		Get the base address of a kernel stack
 */
#define	GET_STACK0_BASE_ADDR(addr)	((addr) & STACK0_MASK)

/**
 * \param _addr		An address within the kernel stack
 * \brief		Get the top address of a kernel stack
 */
#define	GET_STACK0_TOP_ADDR(addr)	((addr) | (STACK0_SIZE - 1))

/**
 * \param first_env		The first environment.
 * \param first_env_size	The size in bytes of the first environment.
 * \brief			Initialize the memory subsystem.
 */
void	mem_init(paddr_t *first_env, int first_env_size);

/**
 * \param size	The number of bytes to allocate
 * \return	A pointer to the newly allocated memory area,
 *		NULL if not enough memory remains
 * \brief	Allocate a given amount of memory
 */
void	*kmalloc(size_t size);

/**
 * \param size	The number of bytes to allocate
 * \return	A pointer to the newly zeroed allocated
 *		memory area, NULL if not enough memory remains
 * \brief	Allocate a given amount of memory and fill it with
 *		zeros
 */
void	*kcalloc(size_t size);

/**
 * \param p	The pointer to the memory to free
 * \brief	Free the memory area allocated at a given address
 */
void	kfree(void *p);

#endif /* __ASM__ */

#endif /* __MEM_H__ */
