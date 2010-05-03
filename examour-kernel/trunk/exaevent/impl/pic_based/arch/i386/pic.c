/*
** This file is part of ExAmour

** Copyright (C) Remy Saissy <remy.saissy@gmail.com>
** ExAmour is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 2 of the License, or
** (at your option) any later version.

** ExAmour is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.

** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#include    <examem.h>
#include    <8259a.h>
#include    <idt.h>

#include    "include/pic.h"

#include    "../debugging/log.h"

void    isr0(cpu_context_t *args);
void    isr1(cpu_context_t *args);
void    isr2(cpu_context_t *args);
void    isr3(cpu_context_t *args);
void    isr4(cpu_context_t *args);
void    isr5(cpu_context_t *args);
void    isr6(cpu_context_t *args);
void    isr7(cpu_context_t *args);
void    isr8(cpu_context_t *args);
void    isr9(cpu_context_t *args);
void    isr10(cpu_context_t *args);
void    isr11(cpu_context_t *args);
void    isr12(cpu_context_t *args);
void    isr13(cpu_context_t *args);
void    isr14(cpu_context_t *args);
void    isr15(cpu_context_t *args);
void    isr16(cpu_context_t *args);
void    isr17(cpu_context_t *args);
void    isr18(cpu_context_t *args);
void    isr19(cpu_context_t *args);
void    isr20(cpu_context_t *args);
void    isr21(cpu_context_t *args);
void    isr22(cpu_context_t *args);
void    isr23(cpu_context_t *args);
void    isr24(cpu_context_t *args);
void    isr25(cpu_context_t *args);
void    isr26(cpu_context_t *args);
void    isr27(cpu_context_t *args);
void    isr28(cpu_context_t *args);
void    isr29(cpu_context_t *args);
void    isr30(cpu_context_t *args);
void    isr31(cpu_context_t *args);

/* The exabus syscall interface. */
/* TODO: the exabus syscall interface should be only one call. */
void    isr80_exabus_publish(cpu_context_t *args);
void    isr81_exabus_unpublish(cpu_context_t *args);
void    isr82_exabus_subscribe(cpu_context_t *args);
void    isr83_exabus_unsubscribe(cpu_context_t *args);
void    isr84_exabus_find(cpu_context_t *args);
void    isr85_exabus_raise(cpu_context_t *args);
void    isr86_exabus_call(cpu_context_t *args);

/* TODO: remove that isr. */
void    isr_handler(void)
{
  message("Salut!\n");
}

bool    exavent_initialize_intr(void)
{
  idt_t         *context;
  idtr_t        idtr;
  selector_t    seg;

  context = examem_ref_new(IDT_TABLE_SIZE * sizeof(*context), EXAMEM_ALIGNED_4KB);
  if (context == NULL)
    return (false);
  get_segment(cs, seg);
  if (idt_create(context) == false)
    return (false);
  if (idt_add_entry_at(context, 0, seg, SEGMENT_PRIV_0 | GATE_INTR_GATE_32BITS, isr0) == false)
    return (false);
  if (idt_add_entry_at(context, 1, seg, SEGMENT_PRIV_0 | GATE_INTR_GATE_32BITS, isr1) == false)
    return (false);
  if (idt_add_entry_at(context, 2, seg, SEGMENT_PRIV_0 | GATE_INTR_GATE_32BITS, isr2) == false)
    return (false);
  if (idt_add_entry_at(context, 3, seg, SEGMENT_PRIV_0 | GATE_INTR_GATE_32BITS, isr3) == false)
    return (false);
  if (idt_add_entry_at(context, 4, seg, SEGMENT_PRIV_0 | GATE_INTR_GATE_32BITS, isr4) == false)
    return (false);
  if (idt_add_entry_at(context, 5, seg, SEGMENT_PRIV_0 | GATE_INTR_GATE_32BITS, isr5) == false)
    return (false);
  if (idt_add_entry_at(context, 6, seg, SEGMENT_PRIV_0 | GATE_INTR_GATE_32BITS, isr6) == false)
    return (false);
  if (idt_add_entry_at(context, 7, seg, SEGMENT_PRIV_0 | GATE_INTR_GATE_32BITS, isr7) == false)
    return (false);
  if (idt_add_entry_at(context, 8, seg, SEGMENT_PRIV_0 | GATE_INTR_GATE_32BITS, isr8) == false)
    return (false);
  if (idt_add_entry_at(context, 9, seg, SEGMENT_PRIV_0 | GATE_INTR_GATE_32BITS, isr9) == false)
    return (false);
  if (idt_add_entry_at(context, 10, seg, SEGMENT_PRIV_0 | GATE_INTR_GATE_32BITS, isr10) == false)
    return (false);
  if (idt_add_entry_at(context, 11, seg, SEGMENT_PRIV_0 | GATE_INTR_GATE_32BITS, isr11) == false)
    return (false);
  if (idt_add_entry_at(context, 12, seg, SEGMENT_PRIV_0 | GATE_INTR_GATE_32BITS, isr12) == false)
    return (false);
  if (idt_add_entry_at(context, 13, seg, SEGMENT_PRIV_0 | GATE_INTR_GATE_32BITS, isr13) == false)
    return (false);
  if (idt_add_entry_at(context, 14, seg, SEGMENT_PRIV_0 | GATE_INTR_GATE_32BITS, isr14) == false)
    return (false);
  if (idt_add_entry_at(context, 15, seg, SEGMENT_PRIV_0 | GATE_INTR_GATE_32BITS, isr15) == false)
    return (false);
  if (idt_add_entry_at(context, 16, seg, SEGMENT_PRIV_0 | GATE_INTR_GATE_32BITS, isr16) == false)
    return (false);
  if (idt_add_entry_at(context, 17, seg, SEGMENT_PRIV_0 | GATE_INTR_GATE_32BITS, isr17) == false)
    return (false);
  if (idt_add_entry_at(context, 18, seg, SEGMENT_PRIV_0 | GATE_INTR_GATE_32BITS, isr18) == false)
    return (false);
  if (idt_add_entry_at(context, 19, seg, SEGMENT_PRIV_0 | GATE_INTR_GATE_32BITS, isr19) == false)
    return (false);
  if (idt_add_entry_at(context, 20, seg, SEGMENT_PRIV_0 | GATE_INTR_GATE_32BITS, isr20) == false)
    return (false);
  if (idt_add_entry_at(context, 21, seg, SEGMENT_PRIV_0 | GATE_INTR_GATE_32BITS, isr21) == false)
    return (false);
  if (idt_add_entry_at(context, 22, seg, SEGMENT_PRIV_0 | GATE_INTR_GATE_32BITS, isr22) == false)
    return (false);
  if (idt_add_entry_at(context, 23, seg, SEGMENT_PRIV_0 | GATE_INTR_GATE_32BITS, isr23) == false)
    return (false);
  if (idt_add_entry_at(context, 24, seg, SEGMENT_PRIV_0 | GATE_INTR_GATE_32BITS, isr24) == false)
    return (false);
  if (idt_add_entry_at(context, 25, seg, SEGMENT_PRIV_0 | GATE_INTR_GATE_32BITS, isr25) == false)
    return (false);
  if (idt_add_entry_at(context, 26, seg, SEGMENT_PRIV_0 | GATE_INTR_GATE_32BITS, isr26) == false)
    return (false);
  if (idt_add_entry_at(context, 27, seg, SEGMENT_PRIV_0 | GATE_INTR_GATE_32BITS, isr27) == false)
    return (false);
  if (idt_add_entry_at(context, 28, seg, SEGMENT_PRIV_0 | GATE_INTR_GATE_32BITS, isr28) == false)
    return (false);
  if (idt_add_entry_at(context, 29, seg, SEGMENT_PRIV_0 | GATE_INTR_GATE_32BITS, isr29) == false)
    return (false);
  if (idt_add_entry_at(context, 30, seg, SEGMENT_PRIV_0 | GATE_INTR_GATE_32BITS, isr30) == false)
    return (false);
  if (idt_add_entry_at(context, 31, seg, SEGMENT_PRIV_0 | GATE_INTR_GATE_32BITS, isr31) == false)
    return (false);
  /* Exabus syscalls. */
  /* TODO: use ring3 instead. */
  if (idt_add_entry_at(context, 80, seg, SEGMENT_PRIV_0 | GATE_INTR_GATE_32BITS, isr80_exabus_publish) == false)
    return (false);
  if (idt_add_entry_at(context, 81, seg, SEGMENT_PRIV_0 | GATE_INTR_GATE_32BITS, isr81_exabus_unpublish) == false)
    return (false);
  if (idt_add_entry_at(context, 82, seg, SEGMENT_PRIV_0 | GATE_INTR_GATE_32BITS, isr82_exabus_subscribe) == false)
    return (false);
  if (idt_add_entry_at(context, 83, seg, SEGMENT_PRIV_0 | GATE_INTR_GATE_32BITS, isr83_exabus_unsubscribe) == false)
    return (false);
  if (idt_add_entry_at(context, 84, seg, SEGMENT_PRIV_0 | GATE_INTR_GATE_32BITS, isr84_exabus_find) == false)
    return (false);
  if (idt_add_entry_at(context, 85, seg, SEGMENT_PRIV_0 | GATE_INTR_GATE_32BITS, isr85_exabus_raise) == false)
    return (false);
  if (idt_add_entry_at(context, 86, seg, SEGMENT_PRIV_0 | GATE_INTR_GATE_32BITS, isr86_exabus_call) == false)
    return (false);
  idtr.limit = IDT_TABLE_SIZE * sizeof(*context) - 1;
  idtr.base_addr = (uint32_t)context;
  idt_flush(&idtr);
//  get_system_reg(idt, idtr);
//  message("base_addr: %p limit: %p\n", idtr.base_addr, idtr.limit);
//  message("segment selector: %p handler: %p\n", seg, isr3);
//  message("hi: %p lo:%p\n", context[3].hi, context[3].lo);
//  __asm__ volatile ("int $0x3");
//  _8259a_init();
  return (true);
}
