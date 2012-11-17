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

#include    <stdbool.h>
#include    <stdlib.h>

#include    <CuTest.h>

#include    "../include/idt.h"

void    Testidt_create_with_null_pointer(CuTest *tc)
{
  bool  ret;

  ret = idt_create(NULL);
  CuAssertTrue(tc, !ret);
}

void    Testidt_create(CuTest *tc)
{
  idt_t *context;
  bool  ret;

  context = malloc(sizeof(*context) * IDT_TABLE_SIZE);
  ret = idt_create(context);
  CuAssertTrue(tc, ret);
  free(context);
}

void    Testidt_destroy_with_null_pointer(CuTest *tc)
{
  bool  ret;

  ret = idt_destroy(NULL);
  CuAssertTrue(tc, !ret);
}

void    Testidt_destroy(CuTest *tc)
{
  idt_t *context;
  bool  ret;

  context = malloc(sizeof(*context) * IDT_TABLE_SIZE);
  ret = idt_create(context);
  CuAssertTrue(tc, ret);
  ret = idt_destroy(context);
  CuAssertTrue(tc, ret);
  free(context);
}

static void _test_handler(cpu_context_t *args)
{

}

void    Testidt_add_entry_with_null_context(CuTest *tc)
{
  bool  ret;
  uint16_t  index;

  ret = idt_add_entry(NULL, 0, SEGMENT_PRIV_0 | GATE_INTR_GATE_32BITS, _test_handler, &index);
  CuAssertTrue(tc, !ret);
}

void    Testidt_add_entry_with_null_index(CuTest *tc)
{
  bool  ret;
  idt_t *context;

  context = malloc(sizeof(*context) * IDT_TABLE_SIZE);
  ret = idt_create(context);
  CuAssertTrue(tc, ret);
  ret = idt_add_entry(context, 0, SEGMENT_PRIV_0 | GATE_INTR_GATE_32BITS, _test_handler, NULL);
  CuAssertTrue(tc, !ret);
  free(context);
}

void    Testidt_add_entry_with_null_handler(CuTest *tc)
{
  bool  ret;
  idt_t *context;
  uint16_t  index;

  context = malloc(sizeof(*context) * IDT_TABLE_SIZE);
  ret = idt_create(context);
  CuAssertTrue(tc, ret);
  ret = idt_add_entry(context, 0, SEGMENT_PRIV_0 | GATE_INTR_GATE_32BITS, NULL, &index);
  CuAssertTrue(tc, !ret);
  free(context);
}

void    Testidt_add_entry(CuTest *tc)
{
  bool  ret;
  idt_t *context;
  uint16_t  index;

  context = malloc(sizeof(*context) * IDT_TABLE_SIZE);
  ret = idt_create(context);
  CuAssertTrue(tc, ret);
  ret = idt_add_entry(context, 0, SEGMENT_PRIV_0 | GATE_INTR_GATE_32BITS, _test_handler, &index);
  CuAssertTrue(tc, ret);
  free(context);
}

void    Testidt_add_entry_at_with_null_context(CuTest *tc)
{
  bool  ret;

  ret = idt_add_entry_at(NULL, 0, 0, SEGMENT_PRIV_0 | GATE_INTR_GATE_32BITS, _test_handler);
  CuAssertTrue(tc, !ret);
}

void    Testidt_add_entry_at_with_null_handler(CuTest *tc)
{
  bool  ret;
  idt_t *context;

  context = malloc(sizeof(*context) * IDT_TABLE_SIZE);
  ret = idt_create(context);
  CuAssertTrue(tc, ret);
  ret = idt_add_entry_at(context, 0, 0, SEGMENT_PRIV_0 | GATE_INTR_GATE_32BITS, NULL);
  CuAssertTrue(tc, !ret);
  free(context);
}

void    Testidt_add_entry_at(CuTest *tc)
{
  bool  ret;
  idt_t *context;

  context = malloc(sizeof(*context) * IDT_TABLE_SIZE);
  ret = idt_create(context);
  CuAssertTrue(tc, ret);
  ret = idt_add_entry_at(context, 0, 0, SEGMENT_PRIV_0 | GATE_INTR_GATE_32BITS, _test_handler);
  CuAssertTrue(tc, ret);
  free(context);
}

void    Testidt_add_entry_at_with_already_used_entry(CuTest *tc)
{
  bool  ret;
  idt_t *context;

  context = malloc(sizeof(*context) * IDT_TABLE_SIZE);
  ret = idt_create(context);
  CuAssertTrue(tc, ret);
  ret = idt_add_entry_at(context, 0, 0, SEGMENT_PRIV_0 | GATE_INTR_GATE_32BITS, _test_handler);
  CuAssertTrue(tc, ret);
  ret = idt_add_entry_at(context, 0, 0, SEGMENT_PRIV_1 | GATE_INTR_GATE_16BITS, _test_handler);
  CuAssertTrue(tc, !ret);
  free(context);
}

void    Testidt_remove_entry_with_null_context(CuTest *tc)
{
  bool  ret;

  ret = idt_remove_entry(NULL, 0);
  CuAssertTrue(tc, !ret);
}

void    Testidt_remove_entry_already_free(CuTest *tc)
{
  bool  ret;
  idt_t *context;

  context = malloc(sizeof(*context) * IDT_TABLE_SIZE);
  ret = idt_create(context);
  CuAssertTrue(tc, ret);
  ret = idt_remove_entry(context, 0);
  CuAssertTrue(tc, !ret);
  free(context);
}

void    Testidt_remove_entry(CuTest *tc)
{
  bool  ret;
  idt_t *context;

  context = malloc(sizeof(*context) * IDT_TABLE_SIZE);
  ret = idt_create(context);
  CuAssertTrue(tc, ret);
  ret = idt_add_entry_at(context, 0, 0, SEGMENT_PRIV_1 | GATE_INTR_GATE_16BITS, _test_handler);
  CuAssertTrue(tc, ret);
  ret = idt_remove_entry(context, 0);
  CuAssertTrue(tc, ret);
  free(context);
}
