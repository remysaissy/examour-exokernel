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
  dlist_t	dlist;

}				list_test_t;

void Testdlist_init(CuTest *tc)
{
  list_test_t   root;

  root.dlist.next = (void *)42;
  dlist_init(&root, dlist);
  CuAssertPtrEquals(tc, NULL, root.dlist.next);
}

void Testdlist_init_with_null_pointer(CuTest *tc)
{
  _dlist_init(NULL, 0);
}

void Testdlist_add_head(CuTest *tc)
{
  list_test_t   *root = NULL;
  list_test_t   new;
  list_test_t   new2;

  dlist_add_head(root, &new, dlist);
  CuAssertPtrEquals(tc, &new, root);
  dlist_add_head(root, &new2, dlist);
  CuAssertPtrEquals(tc, &new2, root);
}

void Testdlist_add_head_with_invalid_root(CuTest *tc)
{
  list_test_t   new;

  _dlist_add_head(NULL, &new, 0);
}

void Testdlist_add_head_with_invalid_new(CuTest *tc)
{
  list_test_t   *root = NULL;

  dlist_add_head(root, NULL, dlist);
  CuAssertPtrEquals(tc, NULL, root);
}

void Testdlist_insert_after(CuTest *tc)
{
  list_test_t   *root = NULL;
  list_test_t   new;
  list_test_t   new2;

  dlist_add_head(root, &new, dlist);
  CuAssertPtrEquals(tc, &new, root);
  dlist_add_after(root, &new, &new2, dlist);
  CuAssertPtrEquals(tc, &new2, new.dlist.next);
}

void Testdlist_insert_after_with_null_after(CuTest *tc)
{
  list_test_t   *root = NULL;
  list_test_t   new;
  list_test_t   new2;

  dlist_add_after(root, NULL, &new, dlist);
  CuAssertPtrEquals(tc, root, &new);
  dlist_add_after(root, NULL, &new2, dlist);
  CuAssertPtrEquals(tc, root, &new);
}

void Testdlist_insert_after_with_not_null_after(CuTest *tc)
{
  list_test_t   *root = NULL;
  list_test_t   new;
  list_test_t   new2;

  dlist_add_after(root, NULL, &new, dlist);
  CuAssertPtrEquals(tc, root, &new);
  dlist_add_after(root, &new, &new2, dlist);
  CuAssertPtrEquals(tc, root, &new);
}

void Testdlist_insert_after_with_invalid_root(CuTest *tc)
{
  list_test_t   new;

  _dlist_add_after(NULL, NULL, &new, 0);
}

void Testdlist_insert_after_with_invalid_new(CuTest *tc)
{
  list_test_t   *root = NULL;

  dlist_add_after(root, NULL, NULL, dlist);
  CuAssertPtrEquals(tc, NULL, root);
}

void Testdlist_insert_before(CuTest *tc)
{
  list_test_t   *root = NULL;
  list_test_t   new;
  list_test_t   new2;

  dlist_add_head(root, &new, dlist);
  CuAssertPtrEquals(tc, &new, root);
  dlist_add_before(root, &new, &new2, dlist);
  CuAssertPtrEquals(tc, NULL, new.dlist.next);
  CuAssertPtrEquals(tc, &new2, new.dlist.prev);
  CuAssertPtrEquals(tc, root, &new2);
}

void Testdlist_insert_before_with_null_before(CuTest *tc)
{
  list_test_t   *root = NULL;
  list_test_t   new;
  list_test_t   new2;

  dlist_add_before(root, NULL, &new, dlist);
  CuAssertPtrEquals(tc, root, &new);
  dlist_add_before(root, NULL, &new2, dlist);
  CuAssertPtrEquals(tc, root, &new2);
}

void Testdlist_insert_before_with_not_null_before(CuTest *tc)
{
  list_test_t   *root = NULL;
  list_test_t   new;
  list_test_t   new2;

  dlist_add_before(root, NULL, &new, dlist);
  CuAssertPtrEquals(tc, root, &new);
  dlist_add_before(root, &new, &new2, dlist);
  CuAssertPtrEquals(tc, NULL, new.dlist.next);
  CuAssertPtrEquals(tc, &new2, new.dlist.prev);
  CuAssertPtrEquals(tc, root, &new2);
}

void Testdlist_insert_before_with_invalid_root(CuTest *tc)
{
  list_test_t   new;

  _dlist_add_before(NULL, NULL, &new, 0);
}

void Testdlist_insert_before_with_invalid_new(CuTest *tc)
{
  list_test_t   *root = NULL;

  dlist_add_before(root, NULL, NULL, dlist);
  CuAssertPtrEquals(tc, NULL, root);
}

void Testdlist_remove(CuTest *tc)
{
  list_test_t   *root = NULL;
  list_test_t   new;
  list_test_t   new2;

  dlist_add_head(root, &new, dlist);
  CuAssertPtrEquals(tc, root, &new);
  dlist_add_head(root, &new2, dlist);
  CuAssertPtrEquals(tc, root, &new2);
  dlist_remove(root, &new2, dlist);
  CuAssertPtrEquals(tc, &new, root);
  dlist_remove(root, &new, dlist);
  CuAssertPtrEquals(tc, NULL, root);
}

void Testdlist_remove_with_invalid_root(CuTest *tc)
{
  list_test_t   new;

  _dlist_remove(NULL, &new, 0);
}

void Testdlist_remove_with_invalid_item(CuTest *tc)
{
  list_test_t   *root = NULL;
  list_test_t   new;

  dlist_add_head(root, &new, dlist);
  CuAssertPtrEquals(tc, root, &new);
  dlist_remove(root, NULL, dlist);
  CuAssertPtrEquals(tc, &new, root);
}
