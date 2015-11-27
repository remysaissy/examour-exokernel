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

/* The actual name of this file is unrelevant since */
/* its content is focused on the 8259A chip. */
/* TODO: rename the file and add the lapic support */

#ifndef	__IRQ_H__
#define	__IRQ_H__

/**
 * \brief	The IRQ base index in the idt.
 */
#define	IRQ_BASE_IDX	0x20

/**
 * \brief	Irq 0.
 */
#define	IRQ_0		0

/**
 * \brief	Irq 1.
 */
#define	IRQ_1		1

/**
 * \brief	Irq 2.
 */
#define	IRQ_2		2

/**
 * \brief	Irq 3.
 */
#define	IRQ_3		3

/**
 * \brief	Irq 4.
 */
#define	IRQ_4		4

/**
 * \brief	Irq 5.
 */
#define	IRQ_5		5

/**
 * \brief	Irq 6.
 */
#define	IRQ_6		6

/**
 * \brief	Irq 7.
 */
#define	IRQ_7		7

/**
 * \brief	Irq 8.
 */
#define	IRQ_8		8

/**
 * \brief	Irq 9.
 */
#define	IRQ_9		9

/**
 * \brief	Irq 10.
 */
#define	IRQ_10		10

/**
 * \brief	Irq 11.
 */
#define	IRQ_11		11

/**
 * \brief	Irq 12.
 */
#define	IRQ_12		12

/**
 * \brief	Irq 13.
 */
#define	IRQ_13		13

/**
 * \brief	Irq 14.
 */
#define	IRQ_14		14

/**
 * \brief	Irq 15.
 */
#define	IRQ_15		15

/**
 * \brief	The last irq.
 */
#define	LAST_IRQ	IRQ_15

/**
 * \brief	The number of irqs.
 */
#define	IRQ_MAX_NUM	(LAST_IRQ + 1)

#ifndef	__ASM__

#include	<stdint.h>

/**
 * \param id		This is one of the exception id macro set in irq.h.
 * \param type		This is one of the gate_type_e defined in segment_enum.
 *			but without the leading gate_type_.
 * \param code_seg	This is the segment selector of the code segment of
 *			the irq handler.
 * \param handler	This is the irq handler.
 * \brief		Irq handler functions.
 */
#define	IRQ_ENTRY(id, gtype, code_seg, ring, handler) void handler (void);

#include	"irq.def"

#undef IRQ_ENTRY

/* internal use functions. */

/**
 * \brief	Initialize the irq subsystem.
 */
void	irq_init(void);

/**
 * \brief	Shutdown the irq subsystem.
 */
void	irq_shutdown(void);

/**
 * \param irq	The irq number to acknowledge.
 * \brief	Acknowledge an irq.
 */
void	irq_ack(uint32_t irq);

/**
 * \param irq	The irq number to enable.
 * \brief	Enable an irq.
 */
void	irq_enable(uint32_t irq);

/**
 * \param irq	The irq number to disable.
 * \brief	Disable an irq.
 */
void	irq_disable(uint32_t irq);

#endif /* __ASM__ */

#endif /* __IRQ_H__ */
