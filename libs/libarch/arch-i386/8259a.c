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

#include    <sys/io.h>

#include    "include/8259a.h"
#include    "include/irq.h"

/* This code is based on the linux 2.6 one. */
/* This code doesn't work (bad copy/paste...) */
/* It must be rewritten correctly so for now */
/* only ack works with two outb() ;) */

static uint32_t cached_irq_mask = 0;
/* static unsigned int  spurious_irq_mask = 0; */
/* static unsigned int  irq_err_cnt = 0; */

void        _8259a_init(void)
{
  /* mask all irqs. */
  outb(PIC_MASTER_IMR, 0xff);
  outb(PIC_SLAVE_IMR, 0xff);

  /* PIC_MASTER */

  /* ICW1: init. */
  outb(PIC_MASTER_CMD, ICW1_INIT | ICW1_ICW4);

  /* ICW2 */
  /* irqs in idt from IDT_BASE_IRQ to IDT_BASE_IRQ+15 */
  outb(PIC_MASTER_IMR, IRQ_BASE_IDX);
  while (1);
  /* ICW3 */
  /* slave is on IR2 */
  outb(PIC_MASTER_IMR, (1UL << PIC_CASCADE_IR));

  /* ICW4 */
  outb(PIC_MASTER_IMR, ICW4_8086);

  /* PIC SLAVE */

  /* ICW1 */
  outb(PIC_SLAVE_CMD, ICW1_INIT | ICW1_ICW4);

  /* intr in idt from 0x28 to 0x2f */
  outb(PIC_SLAVE_IMR, IRQ_BASE_IDX+8);

  /* ICW3 */
  /* PIC is slave on master's IR2.. */
  outb(PIC_SLAVE_IMR, PIC_CASCADE_IR);

  outb(PIC_SLAVE_IMR, ICW4_8086);

  /* set the default IRQ mask. */
  outb(PIC_MASTER_IMR, cached_irq_mask);    /* only the timer is 0xfe, timer+kbd is 0xfc */
  outb(PIC_SLAVE_IMR, cached_irq_mask >> 8);
}

void        _8259a_shutdown(void)
{
  outb(PIC_MASTER_IMR, 0xff);
  outb(PIC_SLAVE_IMR, 0xff);
}

void        _8259a_enable_irq(uint32_t irq)
{
  cached_irq_mask &= ~(1UL << irq);
  if (irq < 8)
    {
      /* master pic */
      outb(PIC_MASTER_IMR, cached_irq_mask);
    }
  else
    {
      /* slave pic */
      outb(PIC_SLAVE_IMR, cached_irq_mask >> 8);
    }
}

void        _8259a_disable_irq(uint32_t irq)
{
  cached_irq_mask |= (1UL << irq);
  if (irq < 8)
    {
      /* master pic */
      outb(PIC_MASTER_IMR, cached_irq_mask);
    }
  else
    {
      /* slave pic */
      outb(PIC_SLAVE_IMR, cached_irq_mask >> 8);
    }
}

void        _8259a_ack(uint32_t irq)
{
/*   register int   irq_mask = (1UL << irq); */

  if (irq >= 8)
    outb(PIC_EOI, PIC_SLAVE_CMD);
  outb(PIC_EOI, PIC_MASTER_CMD);


/*   if ((cached_irq_mask & irq_mask)) */
/*     { */
/*       int value; */

/*       /\* should not be masked. maybe a spurious irq. *\/ */
/*       if (irq < 8) */
/*  { */
/*    outb(0x0B,PIC_MASTER_CMD);      /\* ISR register *\/ */
/*    value = inb(PIC_MASTER_CMD) & irq_mask; */
/*    outb(0x0A,PIC_MASTER_CMD);      /\* back to the IRR register *\/ */
/*  } */
/*       else */
/*  { */
/*    outb(0x0B,PIC_SLAVE_CMD);       /\* ISR register *\/ */
/*    value = inb(PIC_SLAVE_CMD) & (irq_mask >> 8); */
/*    outb(0x0A,PIC_SLAVE_CMD);       /\* back to the IRR register *\/ */
/*  } */
/*       if (value == 0)        /\* this is a spurious irq. *\/ */
/*  { */
/*    if (!(spurious_irq_mask & irq_mask)) */
/*      { */
/*        klog(LOG_IRQ, "[Kernel] spurious irq: %d\n", irq); */
/*        spurious_irq_mask |= irq_mask; */
/*      } */
/*    irq_err_cnt++; */
/*  } */
/*     } */
/*   /\* normal processing. *\/ */
/*   cached_irq_mask |= irq_mask; */
/*   if (irq < 8) */
/*     { */
/*       /\* master pic *\/ */
/*       outb(PIC_MASTER_IMR, cached_irq_mask); */
/*       outb(PIC_MASTER_IMR, 0x60 + irq); */
/*     } */
/*   else */
/*     { */
/*       /\* slave pic *\/ */
/*       outb(PIC_SLAVE_IMR, cached_irq_mask); */
/*       outb(PIC_SLAVE_CMD, 0x60 + (irq & 7)); /\* specific EOI to slave. *\/ */
/*       outb(PIC_MASTER_CMD, 0x60 + PIC_CASCADE_IR); */
/*     } */
}
