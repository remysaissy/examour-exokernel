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

#ifndef	__SEGMENT_H__
#define	__SEGMENT_H__

#include	"segment_types.h"

/**
 * \param idx	The GDT's descriptor index
 * \return	The corresponding segment selector assuming
 *		a privilege level of 0
 * \brief	Retrieve a ring0 gdt segment selector from its
 *		index
 */
#define	GDT_GET_OFFSET(idx)	(idx << 3)

#ifndef	__ASM__

/**
 * \param idx	The gdt index of the descriptor
 * \return	The corresponding segment selector assuming
 *		the descriptor privilege level
 * \brief	Retrieve a gdt segment selector from its
 *		index. Unlike GDT_GET_OFFSET the selector returned
 *		is a selector_t type and the privilege level is the
 *		one of the descriptor
 */
#define	GDT_GET_SELECTOR(idx)				\
 (GDT_GET_OFFSET(idx) | get_segment_dpl(gl_gdt[idx]))

/**
 * \param idx	The gdt index of the descriptor
 * \return	The corresponding segment selector assuming
 *		a privilege level of 0
 * \brief	Retrieve a ring0 gdt segment selector from its
 *		index. Unlike GDT_GET_OFFSET the selector returned
 *		is a selector_t type
 */
#define	GDT_GET_SELECTOR0(idx)	(GDT_GET_OFFSET(idx))


/* Segment control macros. */

/**
 * \param type	Type of the segment.
 * \param base	Base addres of the segment.
 * \param limit	Limit of the segment. (expressed in unit of granularity).
 * \param dpl	Privilege level of the segment.
 * \param gran	Granularity of the segment.
 * \param sz	16bit or 32bit segment ?
 * \return	A well formed struct dtr_s entry.
 * \brief	Creates a new segment entry.
 * \warning	This macro is expected to be used only for static array
 *		initialization.
 * \todo	The warning must be checked.
 */
#define	_set_segment(type, base, limit, dpl, gran, sz)	\
{							\
  ((((base) & 0xffff) << 16) | ((limit) & 0xffff)),	\
    ((((base) >> 16) & 0xff) | ((base) & 0xff000000) |	\
     (dpl) | (gran) | (sz) | (type) | SEGMENT_PRESENT |	\
     ((limit) & 0xf0000))				\
}

/**
 * \param seg	The segment to reset.
 * \brief	Set the fields of a segment descriptor to 0.
 * \warning	This macro should be used every time you create a segment.
 */
#define	reset_segment(seg)			\
do						\
{						\
  (seg)[0] = 0;					\
  (seg)[1] = 0;					\
} while (0)

/**
 * \param seg	The segment.
 * \return      Non zero value if the segment is activated. 0 otherwise.
 * \brief	Get the activation state of a segment.
 * \see		present_e
 */
#define	get_segment_present(seg)	((seg)[1] & SEGMENT_PRESENT)

/**
 * \param seg	The segment.
 * \return      The granularity of the segment.
 * \brief	Get the granularity of a segment.
 * \see		segdesc_granularity_e
 */
#define	get_segment_granularity(seg)	((seg)[1] & SEGMENT_GRANULARITY_4KB)

/**
 * \param seg	The segment.
 * \return      The size (16bits or 32bits) of the segment.
 * \brief	Get size of a segment.
 * \see		segdesc_size_e
 */
#define	get_segment_size(seg)		((seg)[1] & SEGMENT_32BITS)

/**
 * \param seg	The segment.
 * \param base	The base address.
 * \brief	Set the base address of a segment.
 */
#define	set_segment_base_address(seg, base)	\
do						\
{						\
 (seg)[0] |= (((base) & 0xffff) << 16);		\
 (seg)[1] |= (((base) >> 16) & 0xff) |		\
	     ((base) & 0xff000000);		\
} while (0)

/**
 * \param seg	The segment.
 * \param limit	The limit.
 * \brief	Set the limit of a segment.
 * \warning	The limit is expressed in unit of granularity.
 */
#define	set_segment_limit(seg, limit)		\
do						\
{						\
  (seg)[0] |= ((limit) & 0xffff);		\
  (seg)[1] |= ((limit) & 0xf0000);		\
} while (0)

/**
 * \param seg   The segment.
 * \param v	The type of the segment.
 * \brief       Set the type of a segment.
 */
#define	set_segment_type(seg, v)		\
do						\
{						\
  (seg)[1] &= ~(0x1f00);			\
  (seg)[1] |= (v);				\
} while (0)

/**
 * \param seg   The segment.
 * \return      The base address of the segment.
 * \brief       Get the base address of a segment.
 */
#define	get_segment_base_address(seg)		\
({						\
  paddr_t	___paddr;			\
						\
  ___paddr = ((seg)[0] >> 16);			\
  ___paddr |= (((seg)[1] << 16) & 0xff0000);	\
  ___paddr |= ((seg)[1] & 0xff000000);		\
 (___paddr);					\
})

/**
 * \param seg   The segment.
 * \param v     The present value.
 * \brief       Set the present state of a segment.
 */
#define	set_segment_present(seg, v)	(seg)[1] |= (v)

/**
 * \param seg   The segment.
 * \return      The limit of the segment.
 * \brief       Get the limit of a segment.
 */
#define	get_segment_limit(seg)			\
({						\
  uint32_t	___l;				\
						\
  ___l = ((seg)[0] & 0xffff) | ((seg)[1] & 0xf0000);	\
  (___l);					\
})

/**
 * \param seg   The segment.
 * \return      The type of the segment.
 * \brief       Get type of a segment.
 */
#define get_segment_type(seg)		((seg)[1] & 0x1f00)

/**
 * \param seg   The segment.
 * \return      The privilege level of the segment.
 * \brief       Get privilege level of a segment.
 */
#define	get_segment_dpl(seg)	GET_SEGMENT_PRIV_LEVEL((seg)[1])

/**
 * \param seg   The segment.
 * \return      The privilege level of the segment.
 * \brief       Get privilege level of a segment.
 */
#define	set_segment_dpl(seg, v)			\
do						\
{						\
  (seg)[1] &= ~(SEGMENT_PRIV_LEVELS);		\
  (seg)[1] |= ((v) & SEGMENT_PRIV_LEVELS);	\
} while (0)

/**
 * \brief	Set a null segment. The descriptor is a segdesc_t
 */
#define	_set_null_segment			\
{0, 0}


/* segment manipulation macros. */

/**
 * \param sys_reg	The name of the system register
 * \param value		The value to be loaded
 * \brief		Loads a new value in a system register.
 *			Examples are: gdt,tr,ldt,idt
 */
#define	reload_system_reg(sys_reg, value)	\
do						\
{						\
  __asm__ volatile ("l"#sys_reg " %0\n\t"	\
		:: "m" (value));		\
} while (0)

/**
 * \param selector	The selector to be loaded as code segment
 * \brief		Loads a new code segment
 */
#define	reload_code_segment(selector)		\
do						\
{						\
  __asm__ volatile ("ljmp %0,$l1\n\t"		\
		"l1:" :: "g"(selector));	\
} while (0)

/**
 * \param seg		The name of the segment
 * \param selector	The selector to be loaded
 * \brief		Loads a new selector in a given segment.
 *			Examples are: ds,es,fs,gs
 */
#define	reload_data_segment(seg, selector)	\
do						\
{						\
  __asm__ volatile ("movw %%ax,%%"#seg		\
		:: "a"(selector));		\
} while (0)

#endif /* __ASM__ */

#endif /* __SEGMENT_H__ */
