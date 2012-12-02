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

#ifndef	__IDT_H__
#define	__IDT_H__

#include	<examour/core/segment_types.h>

#define	IDT_BASE_SYSCALL	0x30

#ifndef	__ASM__

/**
 * \param gate		The gate entry.
 * \param type		The gate type.
 * \param seg_sel	The segment selector of the handler.
 * \param offset	The handler.
 * \param dpl		The entry privilege level.
 * \brief		Setup a new idt entry.
 */
#define	set_idt_segment(gate, type, seg_sel, offset, dpl)			\
(gate)[0] = ((paddr_t)(offset) & 0xffff) | (((seg_sel) << 16) & 0xffff0000);	\
(gate)[1] = (type)| (dpl) | SEGMENT_PRESENT | ((paddr_t)(offset) & 0xffff0000);

/**
 * \brief		Setup a null idt entry.
 */
#define	set_idt_null_segment				\
{0, 0}

/* trap gate */

/**
 * \param gate		The gate entry.
 * \param offset	The handler.
 * \brief		Setup a gate handler.
 */
#define	set_gate_handler(gate, offset)			\
do							\
{							\
  (gate)[0] |= ((paddr_t)(offset) & 0xffff);		\
  (gate)[1] |= ((paddr_t)(offset) & 0xffff0000);	\
} while (0)

/**
 * \param gate		The gate entry.
 * \return		The gate entry handler.
 * \brief		Get a gate handler.
 */
#define	get_gate_handler(gate)		\
(((gate)[0] & 0xffff) | ((gate)[1] & 0xffff0000))

/**
 * \param gate		The gate entry.
 * \param tss		The tss selector.
 * \param _dpl		The entry privilege level.
 * \brief		Creates a task gate.
 */
#define	make_task_gate(gate, tss, _dpl)		\
do						\
{						\
 (gate)[0] = (((tss) << 16) & 0xffff);		\
  (gate)[1] = GATE_TASK_GATE | (_dpl) | SEGMENT_PRESENT;	\
} while (0)

/**
 * \param gate		The gate entry.
 * \param offset	The handler.
 * \param segsel	The handler's segment selector.
 * \param _dpl		The entry privilege level.
 * \param _type		The gate type.
 * \brief		Creates a generic gate.
 */
#define	make_generic_gate(gate, offset, segsel, _dpl, _type)	\
do								\
{								\
  (gate)[0] = 0;						\
  (gate)[1] = 0;						\
  set_gate_handler(gate, offset);				\
  (gate)[0] |= (((segsel) << 16) & 0xffff);			\
  (gate)[1] |= (_type) | (_dpl) | SEGMENT_PRESENT;		\
} while (0)


/**
 * \param gate		The gate entry.
 * \param offset	The handler.
 * \param segsel	The handler's segment selector.
 * \param dpl		The entry privilege level.
 * \brief		Creates a 16 bits trap gate.
 */
#define	make_16bit_trap_gate(gate, offset, segsel, dpl)			     \
make_generic_gate(gate, offset, segsel, dpl, GATE_TRAP_GATE_16BITS)

/**
 * \param gate		The gate entry.
 * \param offset	The handler.
 * \param segsel	The handler's segment selector.
 * \param dpl		The entry privilege level.
 * \brief		Creates a 32 bits trap gate.
 */
#define	make_32bit_trap_gate(gate, offset, segsel, dpl)			     \
make_generic_gate(gate, offset, segsel, dpl, GATE_TRAP_GATE_32BITS)

/**
 * \param gate		The gate entry.
 * \param offset	The handler.
 * \param segsel	The handler's segment selector.
 * \param dpl		The entry privilege level.
 * \brief		Creates a 16 bits interrupt gate.
 */
#define	make_16bit_intr_gate(gate, offset, segsel, dpl)			     \
make_generic_gate(gate, offset, segsel, dpl, GATE_INTR_GATE_16BITS)

/**
 * \param gate		The gate entry.
 * \param offset	The handler.
 * \param segsel	The handler's segment selector.
 * \param dpl		The entry privilege level.
 * \brief		Creates a 32 bits interrupt gate.
 */
#define	make_32bit_intr_gate(gate, offset, segsel, dpl)			     \
make_generic_gate(gate, offset, segsel, dpl, GATE_INTR_GATE_32BITS)


/* IDT functions. */

/**
 * \brief	Initialize the idt.
 */
void		idt_init(void);

bool		idt_add_entry(int *gate_id, uint32_t type,
			      selector_t code_segment,
			      uint32_t priv_lvl,
			      void (*handler)());

#define		idt_remove_entry(gate_id) gl_idt[gate_id][1] = 0

void		idt_dump(void);

#endif /* __ASM__ */

#endif /* __IDT_H__ */
