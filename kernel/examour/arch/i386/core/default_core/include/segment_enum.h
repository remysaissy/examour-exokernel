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
** Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef	__SEGMENT_ENUM_H__
#define	__SEGMENT_ENUM_H__

/**
 * \brief	Enumerators of flags of segments.
 * \todo	An unified naming convention must be used.
 */

/* Intel vol3 System programming. Section 3.10: protected mode mm. */
/* 0x1000 is implied. */
/* 0x1f00 */

/**
 * \brief	Read only segment.
 */
#define	SEGMENT_TYPE_DATA_RD		0x1000

/**
 * \brief	Read write segment.
 */
#define	SEGMENT_TYPE_DATA_RW		0x1200

/**
 * \brief	Expdown segment.
 */
#define	SEGMENT_EXPDOWN			0x400

/**
 * \brief	Code execute only segment.
 */
#define	SEGMENT_TYPE_CODE_EXEC		0x1800

/**
 * \brief	Code execute and readonly segment.
 */
#define	SEGMENT_TYPE_CODE_EXEC_RD	0x1a00

/**
 * \brief	Conforming segment.
 */
#define	SEGMENT_CONFORMING		0x400

/**
 * \brief	Privilege level 0 segment.
 */
#define	SEGMENT_PRIV_0			0

/**
 * \brief	Privilege level 1 segment.
 */
#define	SEGMENT_PRIV_1			0x2000

/**
 * \brief	Privilege level 2 segment.
 */
#define	SEGMENT_PRIV_2			0x4000

/**
 * \brief	Privilege level 3 segment.
 */
#define	SEGMENT_PRIV_3			0x6000

/**
 * \brief	Mask with all the privileges bits.
 */
#define	SEGMENT_PRIV_LEVELS		SEGMENT_PRIV_3

/**
 * \brief	Shift of the privileges bits.
 */
#define	SEGMENT_PRIV_SHIFT		13

/**
 * \param x	the flag, tipically an uint32_t.
 * \brief	Retrieve the privilege level from a flag.
 */
#define	GET_SEGMENT_PRIV_LEVEL(x)			\
(((x) & SEGMENT_PRIV_LEVELS) >> SEGMENT_PRIV_SHIFT)

/*
 * \brief	16bits segment.
 */
#define	SEGMENT_16BITS			0

/**
 * \brief	32bits segment.
 */
#define	SEGMENT_32BITS			0x400000

/* no system type segment for now. */

/* Don't use these macros in ldt_add_entry(). */

/**
 * \brief	code or data segment.
 */
#define	SEGMENT_NOT_SYSTEM		0x1000

/**
 * \brief	flag the segment as present.
 */
#define	SEGMENT_PRESENT			0x8000

/**
 * \brief	flag the segment as not present.
 */
#define	SEGMENT_NO_PRESENT		0

/**
 * \brief	4kb segment's granularity limit (mandatory from 1mb).
 */
#define	SEGMENT_GRANULARITY_4KB		0x800000

/**
 * \brief	1b segment's granularity limit (segments up to 1mb).
 */
#define	SEGMENT_GRANULARITY_BYTE	0

/**
 * \brief	ldt system segment.
 */
#define	SEGMENT_TYPE_LDT		0x200

/**
 * \brief	32 bits tss system segment.
 */
#define	SEGMENT_TYPE_TSS_32BITS		0x900

/**
 * \brief	Cleanup invalid options in ldt_add_entry flags parameter.
 */
#define	CLEANUP_MASK			(0x00407f00)

/* ldt values. */
/**
 * \brief	Hint for a segment allocated in the dma zone.
 */
#define	LDT_OPT_DMA			0x1

/**
 * \brief	Hint for a segment allocated in the reserver zone (mapped i/o).
 */
#define	LDT_OPT_RESERVED		0x2

/**
 * \brief	Hint for a segment allocated in exclusive mode.
 */
#define	LDT_OPT_EXCLUSIVE		0x4


/* TODO: remove those stuffs. */
/* present is the 15th bit, */

/* selectors */

/**
 * \brief       gdt segment selector.
 */
#define	SELECTOR_GDT	0

/**
 * \brief       ldt segment selector.
 */
#define	SELECTOR_LDT	0x4

/**
 * \brief       privilege level 0's segment selector.
 */
#define	SELECTOR_PRIV_0	0

/**
 * \brief       privilege level 1's segment selector.
 */
#define	SELECTOR_PRIV_1	1

/**
 * \brief       privilege level 2's segment selector.
 */
#define	SELECTOR_PRIV_2	2

/**
 * \brief       privilege level 3's segment selector.
 */
#define	SELECTOR_PRIV_3	3


/* idt gates */

/**
 * \brief	Task gate segment.
 */
#define	GATE_TASK_GATE		0x500

/**
 * \brief	16bits interrupt gate segment.
 */
#define	GATE_INTR_GATE_16BITS	0x600

/**
 * \brief	32bits interrupt gate segment.
 */
#define	GATE_INTR_GATE_32BITS	0xe00

/**
 * \brief	16bits trap gate segment.
 */
#define	GATE_TRAP_GATE_16BITS	0x700

/**
 * \brief	32bits trap gate segment.
 */
#define	GATE_TRAP_GATE_32BITS	0xf00

#endif /* __SEGMENT_ENUM_H__ */
