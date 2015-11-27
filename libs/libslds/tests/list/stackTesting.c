/*
 * This file is part of libslds

 * Copyright (C) Remy Saissy <remy.saissy@gmail.com>
 * libslds is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.

 * libslds is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include	<stdlib.h>
#include	<string.h>

#include	<CuTest.h>

#include	<list.h>

typedef struct	list_test_s
{
  stack_t	stack;

}				list_test_t;

void Teststack_init(CuTest *tc)
{
  list_test_t   root;

  root.stack.next = (void *)42;
  stack_init(&root, stack);
  CuAssertPtrEquals(tc, NULL, root.stack.next);
}

void Teststack_push(CuTest *tc)
{
  list_test_t   *root = NULL;
  list_test_t   new;
  list_test_t   new2;

  stack_push(root, &new, stack);
  CuAssertPtrEquals(tc, &new, root);
  stack_push(root, &new2, stack);
  CuAssertPtrEquals(tc, &new2, root);
}

void Teststack_push_with_invalid_new(CuTest *tc)
{
  list_test_t   *root = NULL;

  stack_push(root, NULL, stack);
  CuAssertPtrEquals(tc, NULL, root);
}

void Teststack_pop(CuTest *tc)
{
  list_test_t   *root = NULL;
  list_test_t   new;
  list_test_t   new2;

  stack_push(root, &new, stack);
  CuAssertPtrEquals(tc, root, &new);
  stack_push(root, &new2, stack);
  CuAssertPtrEquals(tc, root, &new2);
  stack_pop(root, stack);
  CuAssertPtrEquals(tc, &new, root);
  stack_pop(root, stack);
  CuAssertPtrEquals(tc, NULL, root);
}

void Teststack_pop_with_invalid_item(CuTest *tc)
{
  list_test_t   *root = NULL;

  stack_pop(root, stack);
  CuAssertPtrEquals(tc, NULL, root);
}
