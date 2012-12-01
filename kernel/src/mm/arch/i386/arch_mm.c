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
#include    <segments.h>
#include    <gdt.h>

#include    "include/arch_examem.h"

bool        _examem_arch_specific_init(const exaboot_t const *inf)
{
  gdtr_t    gdtr;
  gdt_t     *context;

  context = examem_ref_new(GDT_TABLE_SIZE * sizeof(*context), EXAMEM_ALIGNED_4KB);
  if (context == NULL)
    return (false);
  if (gdt_create(context) == false)
    return (false);
  if (gdt_add_entry_at(context, 1, 0, 0xffffffff, SEGMENT_32BITS | SEGMENT_GRANULARITY_4KB | SEGMENT_PRIV_0 | SEGMENT_TYPE_CODE_EXEC) == false)
    return (false);
  if (gdt_add_entry_at(context, 2, 0, 0xffffffff, SEGMENT_32BITS | SEGMENT_GRANULARITY_4KB | SEGMENT_PRIV_0 | SEGMENT_TYPE_DATA_RW) == false)
    return (false);
  gdtr.limit = GDT_TABLE_SIZE * sizeof(*context) - 1;
  gdtr.base_addr = (uint32_t)context;
  gdt_flush(&gdtr, GDT_GET_OFFSET(2), GDT_GET_OFFSET(2), GDT_GET_OFFSET(2), GDT_GET_OFFSET(2), GDT_GET_OFFSET(2), GDT_GET_OFFSET(1));
  return (true);
}
