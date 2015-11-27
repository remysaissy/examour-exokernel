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
  queue_t	queue;

}				list_test_t;

void Testqueue_init(CuTest *tc)
{
  list_test_t   root;

  root.queue.next = (void *)42;
  queue_init(&root, queue);
  CuAssertPtrEquals(tc, &root, root.queue.next);
}

void Testqueue_add(CuTest *tc)
{
  list_test_t   *root = NULL;
  list_test_t   new;
  list_test_t   new2;

  queue_add(root, &new, queue);
  CuAssertPtrEquals(tc, &new, root);
  queue_add(root, &new2, queue);
  CuAssertPtrEquals(tc, &new2, new.queue.next);
  CuAssertPtrEquals(tc, &new2, new.queue.prev);
}

void Testqueue_add_with_null_before(CuTest *tc)
{
  list_test_t   *root = NULL;
  list_test_t   new;

  queue_add(root, &new, queue);
  CuAssertPtrEquals(tc, root, &new);
  queue_add(root, NULL, queue);
  CuAssertPtrEquals(tc, root, &new);
}

void Testqueue_add_with_not_null_before(CuTest *tc)
{
  list_test_t   *root = NULL;
  list_test_t   new;
  list_test_t   new2;

  queue_add(root, &new, queue);
  CuAssertPtrEquals(tc, root, &new);
  queue_add(root, &new2, queue);
  CuAssertPtrEquals(tc, &new2, new.queue.next);
  CuAssertPtrEquals(tc, &new2, new.queue.prev);
}

void Testqueue_add_with_invalid_new(CuTest *tc)
{
  list_test_t   *root = NULL;

  queue_add(root, NULL, queue);
  CuAssertPtrEquals(tc, NULL, root);
}

void Testqueue_remove(CuTest *tc)
{
  list_test_t   *root = NULL;
  list_test_t   new;
  list_test_t   new2;
  list_test_t   *elem;

  queue_add(root, &new, queue);
  CuAssertPtrEquals(tc, root, &new);
  queue_add(root, &new2, queue);
  CuAssertPtrEquals(tc, &new2, new.queue.next);
  CuAssertPtrEquals(tc, &new2, new.queue.prev);
  elem = queue_remove(root, queue);
  CuAssertPtrEquals(tc, &new, elem);
  elem = queue_remove(root, queue);
  CuAssertPtrEquals(tc, &new2, elem);
}

void Testqueue_remove_with_invalid_item(CuTest *tc)
{
  list_test_t   *root = NULL;
  list_test_t   new;
  list_test_t   *elem;

  queue_add(root, &new, queue);
  CuAssertPtrEquals(tc, root, &new);
  elem = queue_remove(root, queue);
  CuAssertPtrEquals(tc, &new, elem);
}
