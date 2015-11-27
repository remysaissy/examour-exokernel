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

#include    <stdio.h>
#include    <stdlib.h>

#include    <CuTest.h>
#include    <tree.h>

#include    "../tree/binary/include/avl_rotation.h"

typedef struct test_bst_tree_s
  {
    int key;
    bst_tree_t btree;
    ebst_tree_t ebtree;

  } test_bst_tree_t;

static bst_tree_compare_e BTREE_COMPARE(void *n1, void *n2)
  {
    test_bst_tree_t *bt1 = (test_bst_tree_t *)n1;
    test_bst_tree_t *bt2 = (test_bst_tree_t *)n2;

    if (bt2->key < bt1->key)
      return (BST_TREE_LEFT);
    if (bt2->key > bt1->key)
      return (BST_TREE_RIGHT);
    return (BST_TREE_MATCH);
  }

void Testavl_rotation_bst_left(CuTest *tc)
  {
    test_bst_tree_t *root;
    test_bst_tree_t *elem;
    bool ret;

    root = NULL;
    elem = NULL;
    elem = malloc(sizeof(*elem));
    elem->key = 2;
    ret = bst_tree_insert(root, elem, btree, BTREE_COMPARE);
    CuAssertTrue(tc, ret);
    elem = malloc(sizeof(*elem));
    elem->key = 1;
    ret = bst_tree_insert(root, elem, btree, BTREE_COMPARE);
    CuAssertTrue(tc, ret);
    elem = malloc(sizeof(*elem));
    elem->key = 4;
    ret = bst_tree_insert(root, elem, btree, BTREE_COMPARE);
    CuAssertTrue(tc, ret);
    elem = malloc(sizeof(*elem));
    elem->key = 3;
    ret = bst_tree_insert(root, elem, btree, BTREE_COMPARE);
    CuAssertTrue(tc, ret);
    elem = malloc(sizeof(*elem));
    elem->key = 5;
    ret = bst_tree_insert(root, elem, btree, BTREE_COMPARE);
    CuAssertTrue(tc, ret);
    root = avl_single_rotate_with_left(root, (unsigned int)offsetof(typeof(*root), btree));
    CuAssertIntEquals(tc, 4, root->key);
    CuAssertIntEquals(tc, 2, ((test_bst_tree_t *)root->btree.left)->key);
    CuAssertIntEquals(tc, 5, ((test_bst_tree_t *)root->btree.right)->key);
    CuAssertIntEquals(tc, 1, ((test_bst_tree_t *)((test_bst_tree_t *)root->btree.left)->btree.left)->key);
    CuAssertIntEquals(tc, 3, ((test_bst_tree_t *)((test_bst_tree_t *)root->btree.left)->btree.right)->key);
  }

void Testavl_rotation_bst_right(CuTest *tc)
  {
    test_bst_tree_t *root;
    test_bst_tree_t *elem;
    bool ret;

    root = NULL;
    elem = NULL;
    elem = malloc(sizeof(*elem));
    elem->key = 4;
    ret = bst_tree_insert(root, elem, btree, BTREE_COMPARE);
    CuAssertTrue(tc, ret);
    elem = malloc(sizeof(*elem));
    elem->key = 5;
    ret = bst_tree_insert(root, elem, btree, BTREE_COMPARE);
    CuAssertTrue(tc, ret);
    elem = malloc(sizeof(*elem));
    elem->key = 2;
    ret = bst_tree_insert(root, elem, btree, BTREE_COMPARE);
    CuAssertTrue(tc, ret);
    elem = malloc(sizeof(*elem));
    elem->key = 1;
    ret = bst_tree_insert(root, elem, btree, BTREE_COMPARE);
    CuAssertTrue(tc, ret);
    elem = malloc(sizeof(*elem));
    elem->key = 3;
    ret = bst_tree_insert(root, elem, btree, BTREE_COMPARE);
    CuAssertTrue(tc, ret);
    root = avl_single_rotate_with_right(root, (unsigned int)offsetof(typeof(*root), btree));
    CuAssertIntEquals(tc, 2, root->key);
    CuAssertIntEquals(tc, 1, ((test_bst_tree_t *)root->btree.left)->key);
    CuAssertIntEquals(tc, 4, ((test_bst_tree_t *)root->btree.right)->key);
    CuAssertIntEquals(tc, 5, ((test_bst_tree_t *)((test_bst_tree_t *)root->btree.right)->btree.right)->key);
    CuAssertIntEquals(tc, 3, ((test_bst_tree_t *)((test_bst_tree_t *)root->btree.right)->btree.left)->key);
  }


void Testavl_rotation_ebst_left(CuTest *tc)
  {
    test_bst_tree_t *root;
    test_bst_tree_t *elem;
    bool ret;

    root = NULL;
    elem = NULL;
    elem = malloc(sizeof(*elem));
    elem->key = 2;
    ret = ebst_tree_insert(root, elem, ebtree, BTREE_COMPARE);
    CuAssertTrue(tc, ret);
    elem = malloc(sizeof(*elem));
    elem->key = 1;
    ret = ebst_tree_insert(root, elem, ebtree, BTREE_COMPARE);
    CuAssertTrue(tc, ret);
    elem = malloc(sizeof(*elem));
    elem->key = 4;
    ret = ebst_tree_insert(root, elem, ebtree, BTREE_COMPARE);
    CuAssertTrue(tc, ret);
    elem = malloc(sizeof(*elem));
    elem->key = 3;
    ret = ebst_tree_insert(root, elem, ebtree, BTREE_COMPARE);
    CuAssertTrue(tc, ret);
    elem = malloc(sizeof(*elem));
    elem->key = 5;
    ret = ebst_tree_insert(root, elem, ebtree, BTREE_COMPARE);
    CuAssertTrue(tc, ret);
    root = avl_parent_rotate_with_left(root, (unsigned int)offsetof(typeof(*root), ebtree));
    CuAssertIntEquals(tc, 4, root->key);
    CuAssertIntEquals(tc, 2, ((test_bst_tree_t *)root->ebtree.left)->key);
    CuAssertIntEquals(tc, 5, ((test_bst_tree_t *)root->ebtree.right)->key);
    CuAssertIntEquals(tc, 1, ((test_bst_tree_t *)((test_bst_tree_t *)root->ebtree.left)->ebtree.left)->key);
    CuAssertIntEquals(tc, 3, ((test_bst_tree_t *)((test_bst_tree_t *)root->ebtree.left)->ebtree.right)->key);
  }

void Testavl_rotation_ebst_right(CuTest *tc)
  {
    test_bst_tree_t *root;
    test_bst_tree_t *elem;
    bool ret;

    root = NULL;
    elem = NULL;
    elem = malloc(sizeof(*elem));
    elem->key = 4;
    ret = ebst_tree_insert(root, elem, ebtree, BTREE_COMPARE);
    CuAssertTrue(tc, ret);
    elem = malloc(sizeof(*elem));
    elem->key = 5;
    ret = ebst_tree_insert(root, elem, ebtree, BTREE_COMPARE);
    CuAssertTrue(tc, ret);
    elem = malloc(sizeof(*elem));
    elem->key = 2;
    ret = ebst_tree_insert(root, elem, ebtree, BTREE_COMPARE);
    CuAssertTrue(tc, ret);
    elem = malloc(sizeof(*elem));
    elem->key = 1;
    ret = ebst_tree_insert(root, elem, ebtree, BTREE_COMPARE);
    CuAssertTrue(tc, ret);
    elem = malloc(sizeof(*elem));
    elem->key = 3;
    ret = ebst_tree_insert(root, elem, ebtree, BTREE_COMPARE);
    CuAssertTrue(tc, ret);
    root = avl_parent_rotate_with_right(root, (unsigned int)offsetof(typeof(*root), ebtree));
    CuAssertIntEquals(tc, 2, root->key);
    CuAssertIntEquals(tc, 1, ((test_bst_tree_t *)root->ebtree.left)->key);
    CuAssertIntEquals(tc, 4, ((test_bst_tree_t *)root->ebtree.right)->key);
    CuAssertIntEquals(tc, 5, ((test_bst_tree_t *)((test_bst_tree_t *)root->ebtree.right)->ebtree.right)->key);
    CuAssertIntEquals(tc, 3, ((test_bst_tree_t *)((test_bst_tree_t *)root->ebtree.right)->ebtree.left)->key);
  }
