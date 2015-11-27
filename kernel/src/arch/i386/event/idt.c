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

/* exAmour's event manager layer 0 */
/* Interruption descriptor table manager */

#include	<examour/event/idt.h>
#include	<examour/mm/mem.h>
#include	<examour/event/irq.h>
#include	<examour/event/syscall.h>
#include	<examour/event/exception.h>
#include	<examour/core/globals.h>
#include	<examour/support/log.h>

void		idt_init(void)
{
  idtr_t	idtr;
  int		cnt;

  /* idt is dynamically allocated. */
  if ((gl_idt = kcalloc((IDT_BASE_SYSCALL + SYS_num_syscalls) * sizeof(*gl_idt))) == NULL)
    panic("IDT allocation error.\n");

  idtr.limit = (IDT_BASE_SYSCALL + SYS_num_syscalls) * sizeof(*gl_idt) - 1;
  idtr.base_addr = (paddr_t)gl_idt;

/* exceptions. */
#define	EXCEPTION_ENTRY(id, gtype, code_seg, ring, handler)	\
set_idt_segment(gl_idt[id], GATE_ ## gtype,			\
			     GDT_GET_SELECTOR(code_seg),	\
			     handler, ring);

#include	<examour/event/exception.def>

#undef EXCEPTION_ENTRY

/* interruptions. */
/* TODO: would be different with apic... */
#define	IRQ_ENTRY(id, gtype, code_seg, ring, handler)			\
 set_idt_segment(gl_idt[IRQ_BASE_IDX + id], GATE_ ## gtype,		\
					    GDT_GET_SELECTOR(code_seg),	\
					    handler, ring);

#include	<examour/event/irq.def>

#undef IRQ_ENTRY

  cnt = SYS_base_mm_syscalls;
/* TODO: we must use a trapgate instead. */
/**
 * \brief	The SYSCALL_ENTRY used to generate the idt registration.
 */
#define	SYSCALL_ENTRY(ret_type, syscall_name, n_params)		\
     set_idt_segment(gl_idt[cnt],				\
		     GATE_INTR_GATE_32BITS,			\
		     GDT_GET_SELECTOR0(GDT_SEG_KCODE),		\
		     asm_ ## syscall_name, SEGMENT_PRIV_3);	\
     cnt++;

#include	<examour/mm/syscalls_mm.def>
#include	<examour/env/syscalls_env.def>
#include	<examour/event/syscalls_event.def>

#undef	SYSCALL_ENTRY

  reload_system_reg(idt, idtr);
}

bool		idt_add_entry(int *gate_id, uint32_t type,
			      selector_t code_segment,
			      uint32_t priv_lvl,
			      void (*handler)())
{
  idtr_t	idtr;
  int		i;

  __asm__ volatile ("sidt %0": "=m"(idtr));
  for (i = 0; i < (idtr.limit+1)/8; i++)
    {
      if ((gl_idt[i][1] & SEGMENT_PRESENT))
	{
	  make_generic_gate(gl_idt[i], handler, 0, priv_lvl, type);
	  if (gate_id)
	    *gate_id = i;
	  return (true);
	}
    }
  return (false);
}

void		idt_dump(void)
{
  int		i;

  for (i = IDT_BASE_SYSCALL; i < IDT_BASE_SYSCALL+SYS_num_syscalls/* (idtr.limit+1)/8 */; i++)
    info("[IDT]%x: function: %p %x %x\n",
	 i, examour_do_irq_0,
	 gl_idt[i][0], gl_idt[i][1]);
/*     info("[IDT]%d: present: %b type: %p handler: %p " */
/* 	 "cs: %p privilege level: %d\n", i, */
/* 	 gl_idt[i].present, gl_idt[i].type, get_gate_handler(gl_idt[i]), */
/* 	 gl_idt[i]/\* .selector *\/, gl_idt[i].dpl); */
}
