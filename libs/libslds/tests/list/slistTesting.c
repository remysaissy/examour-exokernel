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
  slist_t	slist;

}				list_test_t;

void Testslist_init(CuTest *tc)
{
  list_test_t   root;

  root.slist.next = (void *)42;
  slist_init(&root, slist);
  CuAssertPtrEquals(tc, NULL, root.slist.next);
}

void Testslist_init_with_null_pointer(CuTest *tc)
{
  _slist_init(NULL, 0);
}

void Testslist_add_head(CuTest *tc)
{
  list_test_t   *root = NULL;
  list_test_t   new;
  list_test_t   new2;

  slist_add_head(root, &new, slist);
  CuAssertPtrEquals(tc, &new, root);
  slist_add_head(root, &new2, slist);
  CuAssertPtrEquals(tc, &new2, root);
}

void Testslist_add_head_with_invalid_root(CuTest *tc)
{
  list_test_t   new;

  _slist_add_head(NULL, &new, 0);
}

void Testslist_add_head_with_invalid_new(CuTest *tc)
{
  list_test_t   *root = NULL;

  slist_add_head(root, NULL, slist);
  CuAssertPtrEquals(tc, NULL, root);
}

void Testslist_insert_after(CuTest *tc)
{
  list_test_t   *root = NULL;
  list_test_t   new;
  list_test_t   new2;

  slist_add_head(root, &new, slist);
  CuAssertPtrEquals(tc, &new, root);
  slist_add_after(root, &new, &new2, slist);
  CuAssertPtrEquals(tc, &new2, new.slist.next);
}

void Testslist_insert_after_with_null_after(CuTest *tc)
{
  list_test_t   *root = NULL;
  list_test_t   new;
  list_test_t   new2;

  slist_add_after(root, NULL, &new, slist);
  CuAssertPtrEquals(tc, root, &new);
  slist_add_after(root, NULL, &new2, slist);
  CuAssertPtrEquals(tc, root, &new);
}

void Testslist_insert_after_with_not_null_after(CuTest *tc)
{
  list_test_t   *root = NULL;
  list_test_t   new;
  list_test_t   new2;

  slist_add_after(root, NULL, &new, slist);
  CuAssertPtrEquals(tc, root, &new);
  slist_add_after(root, &new, &new2, slist);
  CuAssertPtrEquals(tc, root, &new);
}

void Testslist_insert_after_with_invalid_root(CuTest *tc)
{
  list_test_t   new;

  _slist_add_after(NULL, NULL, &new, 0);
}

void Testslist_insert_after_with_invalid_new(CuTest *tc)
{
  list_test_t   *root = NULL;

  slist_add_after(root, NULL, NULL, slist);
  CuAssertPtrEquals(tc, NULL, root);
}

void Testslist_remove(CuTest *tc)
{
  list_test_t   *root = NULL;
  list_test_t   new;
  list_test_t   new2;

  slist_add_head(root, &new, slist);
  CuAssertPtrEquals(tc, root, &new);
  slist_add_head(root, &new2, slist);
  CuAssertPtrEquals(tc, root, &new2);
  slist_remove(root, &new2, slist);
  CuAssertPtrEquals(tc, &new, root);
  slist_remove(root, &new, slist);
  CuAssertPtrEquals(tc, NULL, root);
}

void Testslist_remove_with_invalid_root(CuTest *tc)
{
  list_test_t   new;

  _slist_remove(NULL, &new, 0);
}

void Testslist_remove_with_invalid_item(CuTest *tc)
{
  list_test_t   *root = NULL;
  list_test_t   new;

  slist_add_head(root, &new, slist);
  CuAssertPtrEquals(tc, root, &new);
  slist_remove(root, NULL, slist);
  CuAssertPtrEquals(tc, &new, root);
}

void Testslist_fast_remove(CuTest *tc)
{
  list_test_t   *root = NULL;
  list_test_t   new;
  list_test_t   new2;

  slist_add_head(root, &new, slist);
  CuAssertPtrEquals(tc, root, &new);
  slist_add_head(root, &new2, slist);
  CuAssertPtrEquals(tc, root, &new2);
  slist_fast_remove(root, &new, &new2, slist);
  CuAssertPtrEquals(tc, &new, root);
}

void Testslist_fast_remove_with_null_plist(CuTest *tc)
{
  list_test_t   *root = NULL;
  list_test_t   new;
  list_test_t   new2;

  slist_add_head(root, &new, slist);
  CuAssertPtrEquals(tc, root, &new);
  slist_add_head(root, &new2, slist);
  CuAssertPtrEquals(tc, root, &new2);
  slist_fast_remove(root, NULL, &new2, slist);
  CuAssertPtrEquals(tc, &new, root);
}

void Testslist_fast_remove_with_invalid_root(CuTest *tc)
{
  list_test_t   new;

  _slist_fast_remove(NULL, NULL, &new, 0);
}

void Testslist_fast_remove_with_invalid_slist(CuTest *tc)
{
  list_test_t   *root = NULL;
  list_test_t   new;
  list_test_t   new2;

  slist_add_head(root, &new, slist);
  CuAssertPtrEquals(tc, root, &new);
  slist_add_head(root, &new2, slist);
  CuAssertPtrEquals(tc, root, &new2);
  slist_fast_remove(root, NULL, NULL, slist);
  CuAssertPtrEquals(tc, &new2, root);
}
