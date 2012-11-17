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

#ifndef _8259A_H_
#define _8259A_H_

#define PIC_MASTER      0x20
#define PIC_SLAVE       0xA0
#define PIC_MASTER_CMD  PIC_MASTER
#define PIC_MASTER_IMR  (PIC_MASTER+1)
#define PIC_SLAVE_CMD   PIC_SLAVE
#define PIC_SLAVE_IMR   (PIC_SLAVE+1)
#define PIC_EOI         0x20

#define ICW1_ICW4       0x01    /* icw4 needed */
#define ICW1_SINGLE     0x02    /* single mode */
#define ICW1_INTERVAL4  0x04    /* call address interval 4 */
#define ICW1_LEVEL      0x08    /* level triggered mode */
#define ICW1_INIT       0x10    /* initialization -- required ! */

#define ICW4_8086       0x01    /* 8086/88 mode */
#define ICW4_AUTO       0x02    /* auto eoi */
#define ICW4_BUF_SLAVE  0x08    /* buffered mode for slave */
#define ICW4_BUF_MASTER 0x0c    /* buffer mode for master */
#define ICW4_SFNM       0x10    /* special fully nested */

#define PIC_CASCADE_IR  2   /* IR2 is connected to the slave PIC */

#include    <stdint.h>

/**
 * \brief   Initialize the PIC.
 */
void        _8259a_init(void);

/**
 * \brief   Shutdown the PIC.
 */
void        _8259a_shutdown(void);

/**
 * \param irq   The irq line to enable.
 * \brief   Enables a PIC's irq line.
 */
void        _8259a_enable_irq(uint32_t irq);

/**
 * \param irq   The irq line to disable.
 * \brief   Disables a PIC's irq line.
 */
void        _8259a_disable_irq(uint32_t irq);

/**
 * \param irq   The irq line to acknowldge.
 * \brief   Acknowledge a PIC's irq line.
 */
void        _8259a_ack(uint32_t irq);

#endif /* _8259A_H_ */
