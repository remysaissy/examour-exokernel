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

#include    "include/ldt.h"

bool    ldt_create(ldt_t *context)
{
  if (context == NULL)
    return (false);
  memset(context, 0, LDT_TABLE_SIZE * sizeof(*context));
  return (true);
}

/* NOTE: We assume that the context passed is not the current ldt context. */
bool    ldt_destroy(ldt_t *context)
{
  int   i;

  if (context == NULL)
    return (false);
  for (i = 0; i < LDT_TABLE_SIZE; i++)
    ldt_remove_entry(context, i);
  return (true);
}

bool     ldt_add_entry(ldt_t *context, uint32_t base, size_t limit, uint32_t flags, uint16_t *index)
{
  int   i;

  if (context == NULL || index == NULL || limit == 0)
    return (false);
  for (i = 0; i < LDT_TABLE_SIZE; i++)
  {
    if (context[i].hi == 0)
    {
      context[i].lo = limit & 0xffff;
      context[i].lo |= (base << 16) & 0xffff0000;
      context[i].hi = (base >> 16) & 0xff;
      context[i].hi |= base & 0xff000000;
      flags &= 0x00f0ff00;
      flags |= SEGMENT_PRESENT | SEGMENT_TYPE_LDT;
      context[i].hi |= flags | (limit & 0x000f0000);
      *index = i;
      return (true);
    }
  }
  return (false);
}

bool     ldt_add_entry_at(ldt_t *context, uint16_t index, uint32_t base, size_t limit, uint32_t flags)
{
  if (context == NULL || limit == 0)
     return (false);
   if (context[index].hi != 0)
     return (false);
   context[index].lo = limit & 0xffff;
   context[index].lo |= (base << 16) & 0xffff0000;
   context[index].hi = (base >> 16) & 0xff;
   context[index].hi |= base & 0xff000000;
   flags &= 0x00f0ff00;
   flags |= SEGMENT_PRESENT | SEGMENT_TYPE_LDT;
   context[index].hi |= flags | (limit & 0x000f0000);
   return (true);
}

bool    ldt_remove_entry(ldt_t *context, uint16_t index)
{
  if (context == NULL || context[index].hi == 0)
     return (false);
  context[index].lo = 0;
  context[index].hi = 0;
   return (true);
}
