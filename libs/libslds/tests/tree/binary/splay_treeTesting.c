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

#include	<stdio.h>
#include	<stdlib.h>

#include	<CuTest.h>

#include	<tree.h>

typedef struct test_splay_tree_s
  {
    int key;
    splay_tree_t splay_tree;

  } test_splay_tree_t;

static bst_tree_compare_e BTREE_COMPARE(void *n1, void *n2)
  {
    test_splay_tree_t *bt1 = (test_splay_tree_t *)n1;
    test_splay_tree_t *bt2 = (test_splay_tree_t *)n2;

    if (bt2->key < bt1->key)
      return (BST_TREE_LEFT);
    if (bt2->key > bt1->key)
      return (BST_TREE_RIGHT);
    return (BST_TREE_MATCH);
  }

static bst_tree_compare_e BTREE_COMPARE_KEY(void *n1, void *key)
  {
    int k = (int)key;
    test_splay_tree_t *bt1 = (test_splay_tree_t *)n1;

//    printf("k: %p bt: %p\n", key, n1);
//    if (n1 == NULL)
//      __asm__ volatile ("int $0x3");
    if (k < bt1->key)
      return (BST_TREE_LEFT);
    if (k > bt1->key)
      return (BST_TREE_RIGHT);
    return (BST_TREE_MATCH);
  }

void Testsplay_tree_init(CuTest *tc)
  {
    test_splay_tree_t test;
    bool ret;

    ret = _bst_tree_init(NULL, 0);
    CuAssertTrue(tc, !ret);
    ret = bst_tree_init(&test, splay_tree);
    CuAssertTrue(tc, ret);
  }

void Testsplay_tree_insert(CuTest *tc)
  {
    test_splay_tree_t *root;
    test_splay_tree_t *elem;
    bool ret;

    root = NULL;
    elem = NULL;
    /* Basically, a splay tree differs from a binary tree through the lookup, not the insert. */
    ret = _bst_tree_insert(NULL, elem, 0, BTREE_COMPARE);
    CuAssertTrue(tc, !ret);
    ret = splay_tree_insert(root, NULL, splay_tree, BTREE_COMPARE);
    CuAssertTrue(tc, !ret);
    ret = splay_tree_insert(root, elem, splay_tree, NULL);
    CuAssertTrue(tc, !ret);
    elem = malloc(sizeof(*elem));
    elem->key = 2;
    ret = splay_tree_insert(root, elem, splay_tree, BTREE_COMPARE);
    CuAssertTrue(tc, ret);
    elem = malloc(sizeof(*elem));
    elem->key = 1;
    ret = splay_tree_insert(root, elem, splay_tree, BTREE_COMPARE);
    CuAssertTrue(tc, ret);
    elem = malloc(sizeof(*elem));
    elem->key = 1;
    ret = splay_tree_insert(root, elem, splay_tree, BTREE_COMPARE);
    CuAssertTrue(tc, !ret);
    elem = malloc(sizeof(*elem));
    elem->key = 3;
    ret = splay_tree_insert(root, elem, splay_tree, BTREE_COMPARE);
    CuAssertTrue(tc, ret);
    elem = root;
    CuAssertIntEquals(tc, 2, elem->key);
    CuAssertIntEquals(tc, 1, ((test_splay_tree_t *)elem->splay_tree.left)->key);
    CuAssertIntEquals(tc, 3, ((test_splay_tree_t *)elem->splay_tree.right)->key);
  }

void Testsplay_tree_left_zig_step_lookup(CuTest *tc)
  {
    test_splay_tree_t *root;
    test_splay_tree_t *elem;
    int i;
    bool ret;

    root = NULL;
    elem = malloc(sizeof(*elem));
    elem->key = 4;
    ret = splay_tree_insert(root, elem, splay_tree, BTREE_COMPARE);
    CuAssertTrue(tc, ret);
    elem = malloc(sizeof(*elem));
    elem->key = 5;
    ret = splay_tree_insert(root, elem, splay_tree, BTREE_COMPARE);
    CuAssertTrue(tc, ret);
    elem = malloc(sizeof(*elem));
    elem->key = 2;
    ret = splay_tree_insert(root, elem, splay_tree, BTREE_COMPARE);
    CuAssertTrue(tc, ret);
    elem = malloc(sizeof(*elem));
    elem->key = 1;
    ret = splay_tree_insert(root, elem, splay_tree, BTREE_COMPARE);
    CuAssertTrue(tc, ret);
    elem = malloc(sizeof(*elem));
    elem->key = 3;
    ret = splay_tree_insert(root, elem, splay_tree, BTREE_COMPARE);
    CuAssertTrue(tc, ret);
    CuAssertPtrNotNull(tc, root);
    CuAssertIntEquals(tc, 4, root->key);
    CuAssertIntEquals(tc, 5, ((test_splay_tree_t *)root->splay_tree.right)->key);
    CuAssertIntEquals(tc, 2, ((test_splay_tree_t *)root->splay_tree.left)->key);
    CuAssertIntEquals(tc, 1, ((test_splay_tree_t *)((test_splay_tree_t *)root->splay_tree.left)->splay_tree.left)->key);
    CuAssertIntEquals(tc, 3, ((test_splay_tree_t *)((test_splay_tree_t *)root->splay_tree.left)->splay_tree.right)->key);
    elem = splay_tree_lookup(root, 2, splay_tree, BTREE_COMPARE_KEY);
    CuAssertPtrNotNull(tc, elem);
    CuAssertIntEquals(tc, 2, root->key);
    CuAssertIntEquals(tc, 1, ((test_splay_tree_t *)root->splay_tree.left)->key);
    CuAssertIntEquals(tc, 4, ((test_splay_tree_t *)root->splay_tree.right)->key);
    CuAssertIntEquals(tc, 3, ((test_splay_tree_t *)((test_splay_tree_t *)root->splay_tree.right)->splay_tree.left)->key);
    CuAssertIntEquals(tc, 5, ((test_splay_tree_t *)((test_splay_tree_t *)root->splay_tree.right)->splay_tree.right)->key);
    for (i = 1; i < 6; i++)
      {
        elem = splay_tree_remove(root, i, splay_tree, BTREE_COMPARE, BTREE_COMPARE_KEY);
        free(elem);
      }
  }

void Testsplay_tree_right_zig_step_lookup(CuTest *tc)
{
  test_splay_tree_t *root;
  test_splay_tree_t *elem;
  int i;
  bool ret;

  root = NULL;
  elem = malloc(sizeof(*elem));
  elem->key = 2;
  ret = splay_tree_insert(root, elem, splay_tree, BTREE_COMPARE);
  CuAssertTrue(tc, ret);
  elem = malloc(sizeof(*elem));
  elem->key = 1;
  ret = splay_tree_insert(root, elem, splay_tree, BTREE_COMPARE);
  CuAssertTrue(tc, ret);
  elem = malloc(sizeof(*elem));
  elem->key = 4;
  ret = splay_tree_insert(root, elem, splay_tree, BTREE_COMPARE);
  CuAssertTrue(tc, ret);
  elem = malloc(sizeof(*elem));
  elem->key = 3;
  ret = splay_tree_insert(root, elem, splay_tree, BTREE_COMPARE);
  CuAssertTrue(tc, ret);
  elem = malloc(sizeof(*elem));
  elem->key = 5;
  ret = splay_tree_insert(root, elem, splay_tree, BTREE_COMPARE);
  CuAssertTrue(tc, ret);
  CuAssertPtrNotNull(tc, root);
  CuAssertIntEquals(tc, 2, root->key);
  CuAssertIntEquals(tc, 1, ((test_splay_tree_t *)root->splay_tree.left)->key);
  CuAssertIntEquals(tc, 4, ((test_splay_tree_t *)root->splay_tree.right)->key);
  CuAssertIntEquals(tc, 3, ((test_splay_tree_t *)((test_splay_tree_t *)root->splay_tree.right)->splay_tree.left)->key);
  CuAssertIntEquals(tc, 5, ((test_splay_tree_t *)((test_splay_tree_t *)root->splay_tree.right)->splay_tree.right)->key);
  elem = splay_tree_lookup(root, 4, splay_tree, BTREE_COMPARE_KEY);
  CuAssertPtrNotNull(tc, elem);
  CuAssertIntEquals(tc, 4, root->key);
  CuAssertIntEquals(tc, 5, ((test_splay_tree_t *)root->splay_tree.right)->key);
  CuAssertIntEquals(tc, 2, ((test_splay_tree_t *)root->splay_tree.left)->key);
  CuAssertIntEquals(tc, 1, ((test_splay_tree_t *)((test_splay_tree_t *)root->splay_tree.left)->splay_tree.left)->key);
  CuAssertIntEquals(tc, 3, ((test_splay_tree_t *)((test_splay_tree_t *)root->splay_tree.left)->splay_tree.right)->key);
  for (i = 1; i < 6; i++)
  {
    elem = splay_tree_remove(root, i, splay_tree, BTREE_COMPARE, BTREE_COMPARE_KEY);
    free(elem);
  }
}

void Testsplay_tree_left_zig_zig_step_lookup(CuTest *tc)
{
  test_splay_tree_t *root;
  test_splay_tree_t *elem;
  int i;
  bool ret;

  root = NULL;
  elem = malloc(sizeof(*elem));
  elem->key = 6;
  ret = splay_tree_insert(root, elem, splay_tree, BTREE_COMPARE);
  CuAssertTrue(tc, ret);
  elem = malloc(sizeof(*elem));
  elem->key = 7;
  ret = splay_tree_insert(root, elem, splay_tree, BTREE_COMPARE);
  CuAssertTrue(tc, ret);
  elem = malloc(sizeof(*elem));
  elem->key = 4;
  ret = splay_tree_insert(root, elem, splay_tree, BTREE_COMPARE);
  CuAssertTrue(tc, ret);
  elem = malloc(sizeof(*elem));
  elem->key = 5;
  ret = splay_tree_insert(root, elem, splay_tree, BTREE_COMPARE);
  CuAssertTrue(tc, ret);
  elem = malloc(sizeof(*elem));
  elem->key = 2;
  ret = splay_tree_insert(root, elem, splay_tree, BTREE_COMPARE);
  CuAssertTrue(tc, ret);
  elem = malloc(sizeof(*elem));
  elem->key = 3;
  ret = splay_tree_insert(root, elem, splay_tree, BTREE_COMPARE);
  CuAssertTrue(tc, ret);
  elem = malloc(sizeof(*elem));
  elem->key = 1;
  ret = splay_tree_insert(root, elem, splay_tree, BTREE_COMPARE);
  CuAssertTrue(tc, ret);
  CuAssertPtrNotNull(tc, root);
  CuAssertIntEquals(tc, 6, root->key);
  CuAssertIntEquals(tc, 7, ((test_splay_tree_t *)root->splay_tree.right)->key);
  CuAssertIntEquals(tc, 4, ((test_splay_tree_t *)root->splay_tree.left)->key);
  CuAssertIntEquals(tc, 5, ((test_splay_tree_t *)((test_splay_tree_t *)root->splay_tree.left)->splay_tree.right)->key);
  CuAssertIntEquals(tc, 2, ((test_splay_tree_t *)((test_splay_tree_t *)root->splay_tree.left)->splay_tree.left)->key);
  CuAssertIntEquals(tc, 3, ((test_splay_tree_t *)((test_splay_tree_t *)((test_splay_tree_t *)root->splay_tree.left)->splay_tree.left)->splay_tree.right)->key);
  CuAssertIntEquals(tc, 1, ((test_splay_tree_t *)((test_splay_tree_t *)((test_splay_tree_t *)root->splay_tree.left)->splay_tree.left)->splay_tree.left)->key);
  elem = splay_tree_lookup(root, 2, splay_tree, BTREE_COMPARE_KEY);
  CuAssertPtrNotNull(tc, elem);
  CuAssertIntEquals(tc, 2, root->key);
  CuAssertIntEquals(tc, 1, ((test_splay_tree_t *)root->splay_tree.left)->key);
  CuAssertIntEquals(tc, 4, ((test_splay_tree_t *)root->splay_tree.right)->key);
  CuAssertIntEquals(tc, 3, ((test_splay_tree_t *)((test_splay_tree_t *)root->splay_tree.right)->splay_tree.left)->key);
  CuAssertIntEquals(tc, 6, ((test_splay_tree_t *)((test_splay_tree_t *)root->splay_tree.right)->splay_tree.right)->key);
  CuAssertIntEquals(tc, 5, ((test_splay_tree_t *)((test_splay_tree_t *)((test_splay_tree_t *)root->splay_tree.right)->splay_tree.right)->splay_tree.left)->key);
  CuAssertIntEquals(tc, 7, ((test_splay_tree_t *)((test_splay_tree_t *)((test_splay_tree_t *)root->splay_tree.right)->splay_tree.right)->splay_tree.right)->key);
  for (i = 1; i < 8; i++)
  {
    elem = splay_tree_remove(root, i, splay_tree, BTREE_COMPARE, BTREE_COMPARE_KEY);
    free(elem);
  }
}

void Testsplay_tree_right_zig_zig_step_lookup(CuTest *tc)
{
  test_splay_tree_t *root;
  test_splay_tree_t *elem;
  int i;
  bool ret;

  root = NULL;
  elem = malloc(sizeof(*elem));
  elem->key = 2;
  ret = splay_tree_insert(root, elem, splay_tree, BTREE_COMPARE);
  CuAssertTrue(tc, ret);
  elem = malloc(sizeof(*elem));
  elem->key = 1;
  ret = splay_tree_insert(root, elem, splay_tree, BTREE_COMPARE);
  CuAssertTrue(tc, ret);
  elem = malloc(sizeof(*elem));
  elem->key = 4;
  ret = splay_tree_insert(root, elem, splay_tree, BTREE_COMPARE);
  CuAssertTrue(tc, ret);
  elem = malloc(sizeof(*elem));
  elem->key = 3;
  ret = splay_tree_insert(root, elem, splay_tree, BTREE_COMPARE);
  CuAssertTrue(tc, ret);
  elem = malloc(sizeof(*elem));
  elem->key = 6;
  ret = splay_tree_insert(root, elem, splay_tree, BTREE_COMPARE);
  CuAssertTrue(tc, ret);
  elem = malloc(sizeof(*elem));
  elem->key = 5;
  ret = splay_tree_insert(root, elem, splay_tree, BTREE_COMPARE);
  CuAssertTrue(tc, ret);
  elem = malloc(sizeof(*elem));
  elem->key = 7;
  ret = splay_tree_insert(root, elem, splay_tree, BTREE_COMPARE);
  CuAssertTrue(tc, ret);
  CuAssertPtrNotNull(tc, root);
  CuAssertIntEquals(tc, 2, root->key);
  CuAssertIntEquals(tc, 1, ((test_splay_tree_t *)root->splay_tree.left)->key);
  CuAssertIntEquals(tc, 4, ((test_splay_tree_t *)root->splay_tree.right)->key);
  CuAssertIntEquals(tc, 3, ((test_splay_tree_t *)((test_splay_tree_t *)root->splay_tree.right)->splay_tree.left)->key);
  CuAssertIntEquals(tc, 6, ((test_splay_tree_t *)((test_splay_tree_t *)root->splay_tree.right)->splay_tree.right)->key);
  CuAssertIntEquals(tc, 5, ((test_splay_tree_t *)((test_splay_tree_t *)((test_splay_tree_t *)root->splay_tree.right)->splay_tree.right)->splay_tree.left)->key);
  CuAssertIntEquals(tc, 7, ((test_splay_tree_t *)((test_splay_tree_t *)((test_splay_tree_t *)root->splay_tree.right)->splay_tree.right)->splay_tree.right)->key);
  elem = splay_tree_lookup(root, 6, splay_tree, BTREE_COMPARE_KEY);
  CuAssertPtrNotNull(tc, elem);
  CuAssertIntEquals(tc, 6, root->key);
  CuAssertIntEquals(tc, 7, ((test_splay_tree_t *)root->splay_tree.right)->key);
  CuAssertIntEquals(tc, 4, ((test_splay_tree_t *)root->splay_tree.left)->key);
  CuAssertIntEquals(tc, 5, ((test_splay_tree_t *)((test_splay_tree_t *)root->splay_tree.left)->splay_tree.right)->key);
  CuAssertIntEquals(tc, 2, ((test_splay_tree_t *)((test_splay_tree_t *)root->splay_tree.left)->splay_tree.left)->key);
  CuAssertIntEquals(tc, 3, ((test_splay_tree_t *)((test_splay_tree_t *)((test_splay_tree_t *)root->splay_tree.left)->splay_tree.left)->splay_tree.right)->key);
  CuAssertIntEquals(tc, 1, ((test_splay_tree_t *)((test_splay_tree_t *)((test_splay_tree_t *)root->splay_tree.left)->splay_tree.left)->splay_tree.left)->key);
  for (i = 1; i < 8; i++)
  {
    elem = splay_tree_remove(root, i, splay_tree, BTREE_COMPARE, BTREE_COMPARE_KEY);
    free(elem);
  }
}

void Testsplay_tree_left_zig_zag_step_lookup(CuTest *tc)
{
  test_splay_tree_t *root;
  test_splay_tree_t *elem;
  int i;
  bool ret;

  root = NULL;
  elem = malloc(sizeof(*elem));
  elem->key = 6;
  ret = splay_tree_insert(root, elem, splay_tree, BTREE_COMPARE);
  CuAssertTrue(tc, ret);
  elem = malloc(sizeof(*elem));
  elem->key = 7;
  ret = splay_tree_insert(root, elem, splay_tree, BTREE_COMPARE);
  CuAssertTrue(tc, ret);
  elem = malloc(sizeof(*elem));
  elem->key = 2;
  ret = splay_tree_insert(root, elem, splay_tree, BTREE_COMPARE);
  CuAssertTrue(tc, ret);
  elem = malloc(sizeof(*elem));
  elem->key = 1;
  ret = splay_tree_insert(root, elem, splay_tree, BTREE_COMPARE);
  CuAssertTrue(tc, ret);
  elem = malloc(sizeof(*elem));
  elem->key = 4;
  ret = splay_tree_insert(root, elem, splay_tree, BTREE_COMPARE);
  CuAssertTrue(tc, ret);
  elem = malloc(sizeof(*elem));
  elem->key = 3;
  ret = splay_tree_insert(root, elem, splay_tree, BTREE_COMPARE);
  CuAssertTrue(tc, ret);
  elem = malloc(sizeof(*elem));
  elem->key = 5;
  ret = splay_tree_insert(root, elem, splay_tree, BTREE_COMPARE);
  CuAssertTrue(tc, ret);
  CuAssertPtrNotNull(tc, root);
  CuAssertIntEquals(tc, 6, root->key);
  CuAssertIntEquals(tc, 7, ((test_splay_tree_t *)root->splay_tree.right)->key);
  CuAssertIntEquals(tc, 2, ((test_splay_tree_t *)root->splay_tree.left)->key);
  CuAssertIntEquals(tc, 1, ((test_splay_tree_t *)((test_splay_tree_t *)root->splay_tree.left)->splay_tree.left)->key);
  CuAssertIntEquals(tc, 4, ((test_splay_tree_t *)((test_splay_tree_t *)root->splay_tree.left)->splay_tree.right)->key);
  CuAssertIntEquals(tc, 3, ((test_splay_tree_t *)((test_splay_tree_t *)((test_splay_tree_t *)root->splay_tree.left)->splay_tree.right)->splay_tree.left)->key);
  CuAssertIntEquals(tc, 5, ((test_splay_tree_t *)((test_splay_tree_t *)((test_splay_tree_t *)root->splay_tree.left)->splay_tree.right)->splay_tree.right)->key);
  elem = splay_tree_lookup(root, 4, splay_tree, BTREE_COMPARE_KEY);
  CuAssertPtrNotNull(tc, elem);
  CuAssertIntEquals(tc, 4, root->key);
  CuAssertIntEquals(tc, 2, ((test_splay_tree_t *)root->splay_tree.left)->key);
  CuAssertIntEquals(tc, 1, ((test_splay_tree_t *)((test_splay_tree_t *)root->splay_tree.left)->splay_tree.left)->key);
  CuAssertIntEquals(tc, 3, ((test_splay_tree_t *)((test_splay_tree_t *)root->splay_tree.left)->splay_tree.right)->key);
  CuAssertIntEquals(tc, 6, ((test_splay_tree_t *)root->splay_tree.right)->key);
  CuAssertIntEquals(tc, 5, ((test_splay_tree_t *)((test_splay_tree_t *)root->splay_tree.right)->splay_tree.left)->key);
  CuAssertIntEquals(tc, 7, ((test_splay_tree_t *)((test_splay_tree_t *)root->splay_tree.right)->splay_tree.right)->key);
  for (i = 1; i < 8; i++)
  {
    elem = splay_tree_remove(root, i, splay_tree, BTREE_COMPARE, BTREE_COMPARE_KEY);
    free(elem);
  }
}

void Testsplay_tree_right_zig_zag_step_lookup(CuTest *tc)
{
  test_splay_tree_t *root;
  test_splay_tree_t *elem;
  int i;
  bool ret;

  root = NULL;
  elem = malloc(sizeof(*elem));
  elem->key = 2;
  ret = splay_tree_insert(root, elem, splay_tree, BTREE_COMPARE);
  CuAssertTrue(tc, ret);
  elem = malloc(sizeof(*elem));
  elem->key = 1;
  ret = splay_tree_insert(root, elem, splay_tree, BTREE_COMPARE);
  CuAssertTrue(tc, ret);
  elem = malloc(sizeof(*elem));
  elem->key = 6;
  ret = splay_tree_insert(root, elem, splay_tree, BTREE_COMPARE);
  CuAssertTrue(tc, ret);
  elem = malloc(sizeof(*elem));
  elem->key = 7;
  ret = splay_tree_insert(root, elem, splay_tree, BTREE_COMPARE);
  CuAssertTrue(tc, ret);
  elem = malloc(sizeof(*elem));
  elem->key = 4;
  ret = splay_tree_insert(root, elem, splay_tree, BTREE_COMPARE);
  CuAssertTrue(tc, ret);
  elem = malloc(sizeof(*elem));
  elem->key = 3;
  ret = splay_tree_insert(root, elem, splay_tree, BTREE_COMPARE);
  CuAssertTrue(tc, ret);
  elem = malloc(sizeof(*elem));
  elem->key = 5;
  ret = splay_tree_insert(root, elem, splay_tree, BTREE_COMPARE);
  CuAssertTrue(tc, ret);
  CuAssertPtrNotNull(tc, root);
  CuAssertIntEquals(tc, 2, root->key);
  CuAssertIntEquals(tc, 1, ((test_splay_tree_t *)root->splay_tree.left)->key);;
  CuAssertIntEquals(tc, 6, ((test_splay_tree_t *)root->splay_tree.right)->key);
  CuAssertIntEquals(tc, 7, ((test_splay_tree_t *)((test_splay_tree_t *)root->splay_tree.right)->splay_tree.right)->key);
  CuAssertIntEquals(tc, 4, ((test_splay_tree_t *)((test_splay_tree_t *)root->splay_tree.right)->splay_tree.left)->key);
  CuAssertIntEquals(tc, 3, ((test_splay_tree_t *)((test_splay_tree_t *)((test_splay_tree_t *)root->splay_tree.right)->splay_tree.left)->splay_tree.left)->key);
  CuAssertIntEquals(tc, 5, ((test_splay_tree_t *)((test_splay_tree_t *)((test_splay_tree_t *)root->splay_tree.right)->splay_tree.left)->splay_tree.right)->key);
  elem = splay_tree_lookup(root, 4, splay_tree, BTREE_COMPARE_KEY);
  CuAssertPtrNotNull(tc, elem);
  CuAssertIntEquals(tc, 4, root->key);
  CuAssertIntEquals(tc, 2, ((test_splay_tree_t *)root->splay_tree.left)->key);
  CuAssertIntEquals(tc, 1, ((test_splay_tree_t *)((test_splay_tree_t *)root->splay_tree.left)->splay_tree.left)->key);
  CuAssertIntEquals(tc, 3, ((test_splay_tree_t *)((test_splay_tree_t *)root->splay_tree.left)->splay_tree.right)->key);
  CuAssertIntEquals(tc, 6, ((test_splay_tree_t *)root->splay_tree.right)->key);
  CuAssertIntEquals(tc, 5, ((test_splay_tree_t *)((test_splay_tree_t *)root->splay_tree.right)->splay_tree.left)->key);
  CuAssertIntEquals(tc, 7, ((test_splay_tree_t *)((test_splay_tree_t *)root->splay_tree.right)->splay_tree.right)->key);
  for (i = 1; i < 8; i++)
  {
    elem = splay_tree_remove(root, i, splay_tree, BTREE_COMPARE, BTREE_COMPARE_KEY);
    free(elem);
  }
}

void Testsplay_tree_remove(CuTest *tc)
  {
    test_splay_tree_t *root;
    test_splay_tree_t *elem;
    int i;
    int j;
    bool ret;
    void        *pret;

    root = NULL;
    for (i = 0, j = 6; i < j; i++, j--)
      {
        elem = malloc(sizeof(*elem));
        elem->key = i;
        ret = splay_tree_insert(root, elem, splay_tree, BTREE_COMPARE);
        CuAssertTrue(tc, ret);
        elem = malloc(sizeof(*elem));
        elem->key = j;
        ret = splay_tree_insert(root, elem, splay_tree, BTREE_COMPARE);
        CuAssertTrue(tc, ret);
      }
    for (i = 0, j = 6; i < j; i++, j--)
      {
        pret = splay_tree_remove(root, i, splay_tree, BTREE_COMPARE, BTREE_COMPARE_KEY);
        CuAssertPtrNotNull(tc, pret);
        pret = splay_tree_remove(root, j, splay_tree, BTREE_COMPARE, BTREE_COMPARE_KEY);
        CuAssertPtrNotNull(tc, pret);
      }
    CuAssertPtrEquals(tc, NULL, root);
  }

static bool walk_state;
static int prev_value;

static void splay_tree_walk_preorder_cb(void *node, void *data)
{
    test_splay_tree_t *elem;
    int         prev;

    prev = prev_value;
    elem = (test_splay_tree_t *)node;
    prev_value = elem->key;
    switch (prev)
    {
    case -1:
        if (elem->key != 8)
            walk_state = false;
        break;
    case 8:
        if (elem->key != 6)
            walk_state = false;
        break;
    case 6:
        if (elem->key != 5)
            walk_state = false;
        break;
    case 5:
        if (elem->key != 7)
            walk_state = false;
        break;
    case 7:
        if (elem->key != 10)
            walk_state = false;
        break;
    case 10:
        if (elem->key != 9)
            walk_state = false;
        break;
    case 9:
        if (elem->key != 11)
            walk_state = false;
        break;
    case 11:
        walk_state = false;
        break;
    }
}

void Testsplay_tree_walk_preorder(CuTest *tc)
  {
    test_splay_tree_t *root;
    test_splay_tree_t *elem;
    void        *pret;
    bool        ret;

    root = NULL;
    elem = malloc(sizeof(*elem));
    elem->key = 8;
    ret = splay_tree_insert(root, elem, splay_tree, BTREE_COMPARE);
    CuAssertTrue(tc, ret);

    elem = malloc(sizeof(*elem));
    elem->key = 6;
    ret = splay_tree_insert(root, elem, splay_tree, BTREE_COMPARE);
    CuAssertTrue(tc, ret);

    elem = malloc(sizeof(*elem));
    elem->key = 5;
    ret = splay_tree_insert(root, elem, splay_tree, BTREE_COMPARE);
    CuAssertTrue(tc, ret);

    elem = malloc(sizeof(*elem));
    elem->key = 7;
    ret = splay_tree_insert(root, elem, splay_tree, BTREE_COMPARE);
    CuAssertTrue(tc, ret);

    elem = malloc(sizeof(*elem));
    elem->key = 10;
    ret = splay_tree_insert(root, elem, splay_tree, BTREE_COMPARE);
    CuAssertTrue(tc, ret);

    elem = malloc(sizeof(*elem));
    elem->key = 9;
    ret = splay_tree_insert(root, elem, splay_tree, BTREE_COMPARE);
    CuAssertTrue(tc, ret);

    elem = malloc(sizeof(*elem));
    elem->key = 11;
    ret = splay_tree_insert(root, elem, splay_tree, BTREE_COMPARE);
    CuAssertTrue(tc, ret);

    walk_state = true;
    prev_value = -1;
    splay_tree_walk_preorder(root, splay_tree, splay_tree_walk_preorder_cb, NULL);
    CuAssertIntEquals(tc, true, walk_state);

    pret = splay_tree_remove(root, 8, splay_tree, BTREE_COMPARE, BTREE_COMPARE_KEY);
    CuAssertPtrNotNull(tc, pret);

    pret = splay_tree_remove(root, 6, splay_tree, BTREE_COMPARE, BTREE_COMPARE_KEY);
    CuAssertPtrNotNull(tc, pret);

    pret = splay_tree_remove(root, 5, splay_tree, BTREE_COMPARE, BTREE_COMPARE_KEY);
    CuAssertPtrNotNull(tc, pret);

    pret = splay_tree_remove(root, 7, splay_tree, BTREE_COMPARE, BTREE_COMPARE_KEY);
    CuAssertPtrNotNull(tc, pret);

    pret = splay_tree_remove(root, 10, splay_tree, BTREE_COMPARE, BTREE_COMPARE_KEY);
    CuAssertPtrNotNull(tc, pret);

    pret = splay_tree_remove(root, 9, splay_tree, BTREE_COMPARE, BTREE_COMPARE_KEY);
    CuAssertPtrNotNull(tc, pret);

    pret = splay_tree_remove(root, 11, splay_tree, BTREE_COMPARE, BTREE_COMPARE_KEY);
    CuAssertPtrNotNull(tc, pret);

    CuAssertPtrEquals(tc, NULL, root);
  }

static void splay_tree_walk_inorder_cb(void *node, void *data)
{
    test_splay_tree_t *elem;
    int         prev;

    prev = prev_value;
    elem = (test_splay_tree_t *)node;
    prev_value = elem->key;
    switch (prev)
    {
    case -1:
        if (elem->key != 5)
            walk_state = false;
        break;
    case 5:
        if (elem->key != 6)
            walk_state = false;
        break;
    case 6:
        if (elem->key != 7)
            walk_state = false;
        break;
    case 7:
        if (elem->key != 8)
            walk_state = false;
        break;
    case 8:
        if (elem->key != 9)
            walk_state = false;
        break;
    case 9:
        if (elem->key != 10)
            walk_state = false;
        break;
    case 10:
        if (elem->key != 11)
            walk_state = false;
        break;
    case 11:
        walk_state = false;
        break;
    }
}

void Testsplay_tree_walk_inorder(CuTest *tc)
  {
    test_splay_tree_t *root;
    test_splay_tree_t *elem;
    void        *pret;
    bool        ret;

    root = NULL;
    elem = malloc(sizeof(*elem));
    elem->key = 8;
    ret = splay_tree_insert(root, elem, splay_tree, BTREE_COMPARE);
    CuAssertTrue(tc, ret);

    elem = malloc(sizeof(*elem));
    elem->key = 6;
    ret = splay_tree_insert(root, elem, splay_tree, BTREE_COMPARE);
    CuAssertTrue(tc, ret);

    elem = malloc(sizeof(*elem));
    elem->key = 5;
    ret = splay_tree_insert(root, elem, splay_tree, BTREE_COMPARE);
    CuAssertTrue(tc, ret);

    elem = malloc(sizeof(*elem));
    elem->key = 7;
    ret = splay_tree_insert(root, elem, splay_tree, BTREE_COMPARE);
    CuAssertTrue(tc, ret);

    elem = malloc(sizeof(*elem));
    elem->key = 10;
    ret = splay_tree_insert(root, elem, splay_tree, BTREE_COMPARE);
    CuAssertTrue(tc, ret);

    elem = malloc(sizeof(*elem));
    elem->key = 9;
    ret = splay_tree_insert(root, elem, splay_tree, BTREE_COMPARE);
    CuAssertTrue(tc, ret);

    elem = malloc(sizeof(*elem));
    elem->key = 11;
    ret = splay_tree_insert(root, elem, splay_tree, BTREE_COMPARE);
    CuAssertTrue(tc, ret);

    walk_state = true;
    prev_value = -1;
    splay_tree_walk_inorder(root, splay_tree, splay_tree_walk_inorder_cb, NULL);
    CuAssertIntEquals(tc, true, walk_state);

    pret = splay_tree_remove(root, 8, splay_tree, BTREE_COMPARE, BTREE_COMPARE_KEY);
    CuAssertPtrNotNull(tc, pret);

    pret = splay_tree_remove(root, 6, splay_tree, BTREE_COMPARE, BTREE_COMPARE_KEY);
    CuAssertPtrNotNull(tc, pret);

    pret = splay_tree_remove(root, 5, splay_tree, BTREE_COMPARE, BTREE_COMPARE_KEY);
    CuAssertPtrNotNull(tc, pret);

    pret = splay_tree_remove(root, 7, splay_tree, BTREE_COMPARE, BTREE_COMPARE_KEY);
    CuAssertPtrNotNull(tc, pret);

    pret = splay_tree_remove(root, 10, splay_tree, BTREE_COMPARE, BTREE_COMPARE_KEY);
    CuAssertPtrNotNull(tc, pret);

    pret = splay_tree_remove(root, 9, splay_tree, BTREE_COMPARE, BTREE_COMPARE_KEY);
    CuAssertPtrNotNull(tc, pret);

    pret = splay_tree_remove(root, 11, splay_tree, BTREE_COMPARE, BTREE_COMPARE_KEY);
    CuAssertPtrNotNull(tc, pret);

    CuAssertPtrEquals(tc, NULL, root);
  }

static void splay_tree_walk_postorder_cb(void *node, void *data)
{
    test_splay_tree_t *elem;
    int         prev;

    prev = prev_value;
    elem = (test_splay_tree_t *)node;
    prev_value = elem->key;
    switch (prev)
    {
    case -1:
        if (elem->key != 5)
            walk_state = false;
        break;
    case 5:
        if (elem->key != 7)
            walk_state = false;
        break;
    case 7:
        if (elem->key != 6)
            walk_state = false;
        break;
    case 6:
        if (elem->key != 9)
            walk_state = false;
        break;
    case 9:
        if (elem->key != 11)
            walk_state = false;
        break;
    case 11:
        if (elem->key != 10)
            walk_state = false;
        break;
    case 10:
        if (elem->key != 8)
            walk_state = false;
        break;
    case 8:
        walk_state = false;
        break;
    }
}

void Testsplay_tree_walk_postorder(CuTest *tc)
  {
    test_splay_tree_t *root;
    test_splay_tree_t *elem;
    void        *pret;
    bool        ret;

    root = NULL;
    elem = malloc(sizeof(*elem));
    elem->key = 8;
    ret = splay_tree_insert(root, elem, splay_tree, BTREE_COMPARE);
    CuAssertTrue(tc, ret);

    elem = malloc(sizeof(*elem));
    elem->key = 6;
    ret = splay_tree_insert(root, elem, splay_tree, BTREE_COMPARE);
    CuAssertTrue(tc, ret);

    elem = malloc(sizeof(*elem));
    elem->key = 5;
    ret = splay_tree_insert(root, elem, splay_tree, BTREE_COMPARE);
    CuAssertTrue(tc, ret);

    elem = malloc(sizeof(*elem));
    elem->key = 7;
    ret = splay_tree_insert(root, elem, splay_tree, BTREE_COMPARE);
    CuAssertTrue(tc, ret);

    elem = malloc(sizeof(*elem));
    elem->key = 10;
    ret = splay_tree_insert(root, elem, splay_tree, BTREE_COMPARE);
    CuAssertTrue(tc, ret);

    elem = malloc(sizeof(*elem));
    elem->key = 9;
    ret = splay_tree_insert(root, elem, splay_tree, BTREE_COMPARE);
    CuAssertTrue(tc, ret);

    elem = malloc(sizeof(*elem));
    elem->key = 11;
    ret = splay_tree_insert(root, elem, splay_tree, BTREE_COMPARE);
    CuAssertTrue(tc, ret);

    walk_state = true;
    prev_value = -1;
    splay_tree_walk_postorder(root, splay_tree, splay_tree_walk_postorder_cb, NULL);
    CuAssertIntEquals(tc,true, walk_state);

    pret = splay_tree_remove(root, 8, splay_tree, BTREE_COMPARE, BTREE_COMPARE_KEY);
    CuAssertPtrNotNull(tc, pret);

    pret = splay_tree_remove(root, 6, splay_tree, BTREE_COMPARE, BTREE_COMPARE_KEY);
    CuAssertPtrNotNull(tc, pret);

    pret = splay_tree_remove(root, 5, splay_tree, BTREE_COMPARE, BTREE_COMPARE_KEY);
    CuAssertPtrNotNull(tc, pret);

    pret = splay_tree_remove(root, 7, splay_tree, BTREE_COMPARE, BTREE_COMPARE_KEY);
    CuAssertPtrNotNull(tc, pret);

    pret = splay_tree_remove(root, 10, splay_tree, BTREE_COMPARE, BTREE_COMPARE_KEY);
    CuAssertPtrNotNull(tc, pret);

    pret = splay_tree_remove(root, 9, splay_tree, BTREE_COMPARE, BTREE_COMPARE_KEY);
    CuAssertPtrNotNull(tc, pret);

    pret = splay_tree_remove(root, 11, splay_tree, BTREE_COMPARE, BTREE_COMPARE_KEY);
    CuAssertPtrNotNull(tc, pret);

    CuAssertPtrEquals(tc, NULL, root);
  }

void Testsplay_tree_graft(CuTest *tc)
  {
    test_splay_tree_t *root1;
    test_splay_tree_t *root2;
    test_splay_tree_t *elem;
    int i;
    int j;
    bool ret;
    void *pret;

    root1 = NULL;
    root2 = NULL;
    for (i = 0, j = 6; i < j; i++, j--)
      {
        elem = malloc(sizeof(*elem));
        elem->key = i;
        ret = splay_tree_insert(root1, elem, splay_tree, BTREE_COMPARE);
        CuAssertTrue(tc, ret);
        elem = malloc(sizeof(*elem));
        elem->key = j;
        ret = splay_tree_insert(root2, elem, splay_tree, BTREE_COMPARE);
        CuAssertTrue(tc, ret);
      }
    pret = splay_tree_lookup(root1, i + 1, splay_tree, BTREE_COMPARE_KEY);
    CuAssertPtrEquals(tc, NULL, pret);
    ret = splay_tree_graft(root1, NULL, splay_tree, BTREE_COMPARE);
    CuAssertTrue(tc, !ret);
    ret = splay_tree_graft(root1, root2, splay_tree, BTREE_COMPARE);
    CuAssertTrue(tc, ret);
    pret = splay_tree_lookup(root1, j + 1, splay_tree, BTREE_COMPARE_KEY);
    CuAssertPtrNotNull(tc, pret);
    for (i = 0, j = 6; i < j; i++, j--)
      {
        pret = splay_tree_remove(root1, i, splay_tree, BTREE_COMPARE, BTREE_COMPARE_KEY);
        CuAssertPtrNotNull(tc, pret);
        pret = splay_tree_remove(root1, j, splay_tree, BTREE_COMPARE, BTREE_COMPARE_KEY);
        CuAssertPtrNotNull(tc, pret);
      }
  }

void Testsplay_tree_prune(CuTest *tc)
  {
    test_splay_tree_t *root;
    test_splay_tree_t *grafted;
    test_splay_tree_t *elem;
    int i;
    int j;
    bool ret;
    void *pret;

    root = NULL;
    for (i = 0, j = 6; i < j; i++, j--)
      {
        elem = malloc(sizeof(*elem));
        elem->key = i;
        ret = splay_tree_insert(root, elem, splay_tree, BTREE_COMPARE);
        CuAssertTrue(tc, ret);
        elem = malloc(sizeof(*elem));
        elem->key = j;
        ret = splay_tree_insert(root, elem, splay_tree, BTREE_COMPARE);
        CuAssertTrue(tc, ret);
      }
    grafted = splay_tree_prune(root, j, splay_tree, BTREE_COMPARE_KEY);
    CuAssertPtrEquals(tc, NULL, grafted);
    grafted = splay_tree_prune(root, 5, splay_tree, BTREE_COMPARE_KEY);
    CuAssertPtrNotNull(tc, grafted);
    pret = splay_tree_lookup(grafted, 1, splay_tree, BTREE_COMPARE_KEY);
    CuAssertPtrEquals(tc, NULL, pret);
    pret = splay_tree_lookup(grafted, 5, splay_tree, BTREE_COMPARE_KEY);
    CuAssertPtrNotNull(tc, pret);
    ret = splay_tree_graft(root, grafted, splay_tree, BTREE_COMPARE_KEY);
    CuAssertTrue(tc, ret);
    for (i = 0, j = 6; i < j; i++, j--)
      {
        pret = splay_tree_remove(root, i, splay_tree, BTREE_COMPARE, BTREE_COMPARE_KEY);
        CuAssertPtrNotNull(tc, pret);
        ret = splay_tree_remove(root, j, splay_tree, BTREE_COMPARE, BTREE_COMPARE_KEY);
        CuAssertPtrNotNull(tc, pret);
      }
    CuAssertPtrEquals(tc, NULL, root);
  }
