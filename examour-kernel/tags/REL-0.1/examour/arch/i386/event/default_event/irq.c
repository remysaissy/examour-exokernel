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

/* exAmour's event manager layer 1 */
/* IRQ manager */

#include	<examour/event/irq.h>
#include	<examour/event/8259a.h>

void	irq_init(void)
{
  _8259a_init();
}

void	irq_shutdown(void)
{
  _8259a_shutdown();
}

void	irq_ack(unsigned int irq)
{
  _8259a_ack(irq);
}

void	irq_enable(unsigned int irq)
{
  _8259a_enable_irq(irq);
}

void	irq_disable(unsigned int irq)
{
  _8259a_disable_irq(irq);
}
