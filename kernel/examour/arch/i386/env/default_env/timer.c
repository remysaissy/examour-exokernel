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

/* exAmour's environnement manager layer 0 */
/* i8253  manager */

#include	<examour/env/timer.h>
#include	<examour/core/asm.h>

/* TODO: use macros instead of hardcoded hexa codes */
/* TODO: it doesn't seems to work correctly... */
void		timer_set(uint32_t ms)
{
  if (ms == 0)
    ms = 0xffff;
/*   ms = MS_TO_HZ(ms); */
/*    ms = LATCH(ms); */

  outb(I8254_CONTROL, I8254_MODE2|I8254_RD_LSB_MSB);
  outb(I8254_TIMER0, (ms & 0xff));
  outb(I8254_TIMER0, (ms >> 8) & 0xff);
}

uint32_t	timer_get(void)
{
  uint32_t	counter;

  outbp(I8254_CONTROL, 0);
  counter = inb(I8254_TIMER0);
  /* TODO: convert counter in ms */
  return (counter);
}
