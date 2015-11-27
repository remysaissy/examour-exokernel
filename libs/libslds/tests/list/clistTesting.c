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
  clist_t	clist;

}				list_test_t;

void Testclist_init(CuTest *tc)
{
  list_test_t   root;

  root.clist.next = (void *)42;
  clist_init(&root, clist);
  CuAssertPtrEquals(tc, &root, root.clist.next);
}

void Testclist_init_with_null_pointer(CuTest *tc)
{
  _clist_init(NULL, 0);
}

void Testclist_insert_after(CuTest *tc)
{
  list_test_t   *root = NULL;
  list_test_t   new;
  list_test_t   new2;

  clist_add_after(root, &new, clist);
  CuAssertPtrEquals(tc, &new, root);
  clist_add_after(root, &new2, clist);
  CuAssertPtrEquals(tc, &new2, new.clist.next);
}

void Testclist_insert_after_with_invalid_root(CuTest *tc)
{
  list_test_t   new;

  _clist_add_after(NULL, &new, 0);
}

void Testclist_insert_after_with_invalid_new(CuTest *tc)
{
  list_test_t   *root = NULL;

  clist_add_after(root, NULL, clist);
  CuAssertPtrEquals(tc, NULL, root);
}

void Testclist_insert_before(CuTest *tc)
{
  list_test_t   *root = NULL;
  list_test_t   new;
  list_test_t   new2;

  clist_add_before(root, &new, clist);
  CuAssertPtrEquals(tc, &new, root);
  clist_add_before(root, &new2, clist);
  CuAssertPtrEquals(tc, &new2, new.clist.next);
  CuAssertPtrEquals(tc, &new2, new.clist.prev);
}

void Testclist_insert_before_with_null_before(CuTest *tc)
{
  list_test_t   *root = NULL;
  list_test_t   new;

  clist_add_before(root, &new, clist);
  CuAssertPtrEquals(tc, root, &new);
  clist_add_before(root, NULL, clist);
  CuAssertPtrEquals(tc, root, &new);
}

void Testclist_insert_before_with_not_null_before(CuTest *tc)
{
  list_test_t   *root = NULL;
  list_test_t   new;
  list_test_t   new2;

  clist_add_before(root, &new, clist);
  CuAssertPtrEquals(tc, root, &new);
  clist_add_before(root, &new2, clist);
  CuAssertPtrEquals(tc, &new2, new.clist.next);
  CuAssertPtrEquals(tc, &new2, new.clist.prev);
}

void Testclist_insert_before_with_invalid_root(CuTest *tc)
{
  list_test_t   new;

  _clist_add_before(NULL, &new, 0);
}

void Testclist_insert_before_with_invalid_new(CuTest *tc)
{
  list_test_t   *root = NULL;

  clist_add_before(root, NULL, clist);
  CuAssertPtrEquals(tc, NULL, root);
}

void Testclist_remove(CuTest *tc)
{
  list_test_t   *root = NULL;
  list_test_t   new;
  list_test_t   new2;

  clist_add_before(root, &new, clist);
  CuAssertPtrEquals(tc, root, &new);
  clist_add_after(root, &new2, clist);
  CuAssertPtrEquals(tc, &new2, new.clist.next);
  CuAssertPtrEquals(tc, &new2, new.clist.prev);
  clist_remove(root, &new2, clist);
  CuAssertPtrEquals(tc, &new, root);
  clist_remove(root, &new, clist);
  CuAssertPtrEquals(tc, NULL, root);
}

void Testclist_remove_with_invalid_root(CuTest *tc)
{
  list_test_t   new;

  _clist_remove(NULL, &new, 0);
}

void Testclist_remove_with_invalid_item(CuTest *tc)
{
  list_test_t   *root = NULL;
  list_test_t   new;

  clist_add_after(root, &new, clist);
  CuAssertPtrEquals(tc, root, &new);
  clist_remove(root, NULL, clist);
  CuAssertPtrEquals(tc, &new, root);
}
