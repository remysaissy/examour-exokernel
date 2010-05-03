/*
** This file is part of ExAmour

** Copyright (C) Remy Saissy <remy.saissy@gmail.com>
** examour is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 2 of the License, or
** (at your option) any later version.

** examour is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.

** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#include    <string.h>

#include    "include/idt.h"

bool    idt_create(idt_t *context)
{
  if (context == NULL)
    return (false);
  memset(context, 0, IDT_TABLE_SIZE * sizeof(*context));
  return (true);
}

/* NOTE: We assume that the context passed is not the current idt context. */
bool    idt_destroy(idt_t *context)
{
  int   i;

  if (context == NULL)
    return (false);
  for (i = 0; i < IDT_TABLE_SIZE; i++)
    idt_remove_entry(context, i);
  return (true);
}


bool    idt_add_entry(idt_t *context, selector_t code_segment, uint32_t flags, exception_raised_p handler, uint16_t *index)
{
  uint16_t   i;

  if (context == NULL || index == NULL || handler == NULL)
    return (false);
  for (i = 0; i < IDT_TABLE_SIZE; i++)
  {
    if (context[i].hi == 0)
    {
      context[i].lo = *((uint32_t *)&handler) & 0xffff;
      context[i].hi = *((uint32_t *)&handler) & 0xffff0000;
      context[i].lo |= ((code_segment << 16) & 0xffff0000);
      flags |= SEGMENT_PRESENT;
      context[i].hi |= flags & 0xffff;
      *index = i;
      return (true);
    }
  }
  return (false);
}

bool    idt_add_entry_at(idt_t *context, uint16_t index, selector_t code_segment, uint32_t flags, exception_raised_p handler)
{
  if (context == NULL || handler == NULL)
    return (false);
  if (context[index].hi != 0)
    return (false);
  context[index].lo = *((uint32_t *)&handler) & 0xffff;
  context[index].hi = *((uint32_t *)&handler) & 0xffff0000;
  context[index].lo |= ((code_segment << 16) & 0xffff0000);
  flags |= SEGMENT_PRESENT;
  context[index].hi |= flags & 0xffff;
  return (true);
}

bool    idt_remove_entry(idt_t *context, uint16_t index)
{
  if (context == NULL || context[index].hi == 0)
    return (false);
  context[index].lo = 0;
  context[index].hi = 0;
  return (true);
}
