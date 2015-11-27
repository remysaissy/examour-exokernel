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

typedef struct test_redblack_tree_s
  {
    int key;
    redblack_tree_t redblack_tree;

  } test_redblack_tree_t;

static bst_tree_compare_e BTREE_COMPARE(void *n1, void *n2)
  {
    test_redblack_tree_t *bt1 = (test_redblack_tree_t *)n1;
    test_redblack_tree_t *bt2 = (test_redblack_tree_t *)n2;

    if (bt2->key < bt1->key)
      return (BST_TREE_LEFT);
    if (bt2->key > bt1->key)
      return (BST_TREE_RIGHT);
    return (BST_TREE_MATCH);
  }

static bst_tree_compare_e BTREE_COMPARE_KEY(void *n1, void *key)
  {
    int k = (int)key;
    test_redblack_tree_t *bt1 = (test_redblack_tree_t *)n1;

    if (k < bt1->key)
      return (BST_TREE_LEFT);
    if (k > bt1->key)
      return (BST_TREE_RIGHT);
    return (BST_TREE_MATCH);
  }

void Testredblack_tree_init(CuTest *tc)
  {
    test_redblack_tree_t test;
    bool ret;

    ret = _bst_tree_init(NULL, 0);
    CuAssertTrue(tc, !ret);
    ret = redblack_tree_init(&test, redblack_tree);
    CuAssertTrue(tc, ret);
  }

void Testredblack_tree_insert(CuTest *tc)
  {
    test_redblack_tree_t *root;
    test_redblack_tree_t *elem;
    bool ret;

    root = NULL;
    elem = NULL;
    ret = _redblack_tree_insert(NULL, elem, 0, BTREE_COMPARE);
    CuAssertTrue(tc, !ret);
    ret = redblack_tree_insert(root, NULL, redblack_tree, BTREE_COMPARE);
    CuAssertTrue(tc, !ret);
    ret = redblack_tree_insert(root, elem, redblack_tree, NULL);
    CuAssertTrue(tc, !ret);
    elem = malloc(sizeof(*elem));
    elem->key = 2;
    ret = redblack_tree_insert(root, elem, redblack_tree, BTREE_COMPARE);
    CuAssertTrue(tc, ret);
    elem = malloc(sizeof(*elem));
    elem->key = 1;
    ret = redblack_tree_insert(root, elem, redblack_tree, BTREE_COMPARE);
    CuAssertTrue(tc, ret);
    elem = malloc(sizeof(*elem));
    elem->key = 1;
    ret = redblack_tree_insert(root, elem, redblack_tree, BTREE_COMPARE);
    CuAssertTrue(tc, !ret);
    elem = malloc(sizeof(*elem));
    elem->key = 3;
    ret = redblack_tree_insert(root, elem, redblack_tree, BTREE_COMPARE);
    CuAssertTrue(tc, ret);
    elem = root;
    CuAssertIntEquals(tc, 2, elem->key);
    CuAssertIntEquals(tc, 1, ((test_redblack_tree_t *)elem->redblack_tree.left)->key);
    CuAssertIntEquals(tc, 3, ((test_redblack_tree_t *)elem->redblack_tree.right)->key);
  }

void Testredblack_tree_insert_case1(CuTest *tc)
  {
    test_redblack_tree_t *root;
    test_redblack_tree_t *elem;
    bool ret;

    root = NULL;
    elem = malloc(sizeof(*elem));
    elem->key = 2;
    ret = redblack_tree_insert(root, elem, redblack_tree, BTREE_COMPARE);
    CuAssertTrue(tc, ret);
    CuAssertIntEquals(tc, black, root->redblack_tree.colour);
  }

void Testredblack_tree_insert_case2(CuTest *tc)
  {
    test_redblack_tree_t *root;
    test_redblack_tree_t *elem;
    bool ret;

    root = NULL;
    elem = malloc(sizeof(*elem));
    elem->key = 2;
    ret = redblack_tree_insert(root, elem, redblack_tree, BTREE_COMPARE);
    CuAssertTrue(tc, ret);
    elem = malloc(sizeof(*elem));
    elem->key = 1;
    ret = redblack_tree_insert(root, elem, redblack_tree, BTREE_COMPARE);
    CuAssertTrue(tc, ret);
    CuAssertIntEquals(tc, black, root->redblack_tree.colour);
    CuAssertIntEquals(tc, red, ((test_redblack_tree_t *)root->redblack_tree.left)->redblack_tree.colour);
  }

void Testredblack_tree_insert_case3(CuTest *tc)
  {
    test_redblack_tree_t *root;
    test_redblack_tree_t *elem;
    bool ret;

    root = NULL;
    elem = malloc(sizeof(*elem));
    elem->key = 3;
    ret = redblack_tree_insert(root, elem, redblack_tree, BTREE_COMPARE);
    CuAssertTrue(tc, ret);
    elem = malloc(sizeof(*elem));
    elem->key = 4;
    ret = redblack_tree_insert(root, elem, redblack_tree, BTREE_COMPARE);
    CuAssertTrue(tc, ret);
    elem = malloc(sizeof(*elem));
    elem->key = 2;
    ret = redblack_tree_insert(root, elem, redblack_tree, BTREE_COMPARE);
    CuAssertTrue(tc, ret);
    CuAssertIntEquals(tc, black, root->redblack_tree.colour);
    CuAssertIntEquals(tc, red, ((test_redblack_tree_t *)root->redblack_tree.left)->redblack_tree.colour);
    CuAssertIntEquals(tc, red, ((test_redblack_tree_t *)root->redblack_tree.right)->redblack_tree.colour);
    elem = malloc(sizeof(*elem));
    elem->key = 1;
    ret = redblack_tree_insert(root, elem, redblack_tree, BTREE_COMPARE);
    CuAssertTrue(tc, ret);
    CuAssertIntEquals(tc, black, root->redblack_tree.colour);
    CuAssertIntEquals(tc, black, ((test_redblack_tree_t *)root->redblack_tree.left)->redblack_tree.colour);
    CuAssertIntEquals(tc, black, ((test_redblack_tree_t *)root->redblack_tree.right)->redblack_tree.colour);
    CuAssertIntEquals(tc, red, ((test_redblack_tree_t *)((test_redblack_tree_t *)root->redblack_tree.left)->redblack_tree.left)->redblack_tree.colour);
  }

void Testredblack_tree_insert_case4(CuTest *tc)
{
  test_redblack_tree_t *root;
  test_redblack_tree_t *elem;
  test_redblack_tree_t  *keep;
  bool ret;

  root = NULL;
  elem = malloc(sizeof(*elem));
  elem->key = 3;
  ret = redblack_tree_insert(root, elem, redblack_tree, BTREE_COMPARE);
  CuAssertTrue(tc, ret);
  elem = malloc(sizeof(*elem));
  elem->key = 4;
  keep = elem;
  ret = redblack_tree_insert(root, elem, redblack_tree, BTREE_COMPARE);
  CuAssertTrue(tc, ret);
  elem = malloc(sizeof(*elem));
  elem->key = 1;
  ret = redblack_tree_insert(root, elem, redblack_tree, BTREE_COMPARE);
  CuAssertTrue(tc, ret);
  keep->redblack_tree.colour = black;
  CuAssertIntEquals(tc, black, root->redblack_tree.colour);
  CuAssertIntEquals(tc, red, ((test_redblack_tree_t *)root->redblack_tree.left)->redblack_tree.colour);
  CuAssertIntEquals(tc, black, ((test_redblack_tree_t *)root->redblack_tree.right)->redblack_tree.colour);
  elem = malloc(sizeof(*elem));
  elem->key = 2;
  ret = redblack_tree_insert(root, elem, redblack_tree, BTREE_COMPARE);
  CuAssertTrue(tc, ret);
  CuAssertIntEquals(tc, black, root->redblack_tree.colour);
  CuAssertIntEquals(tc, black, ((test_redblack_tree_t *)root->redblack_tree.right)->redblack_tree.colour);
  CuAssertIntEquals(tc, red, ((test_redblack_tree_t *)root->redblack_tree.left)->redblack_tree.colour);
  CuAssertIntEquals(tc, red, ((test_redblack_tree_t *)((test_redblack_tree_t *)root->redblack_tree.left)->redblack_tree.left)->redblack_tree.colour);
  CuAssertIntEquals(tc, 2, ((test_redblack_tree_t *)root->redblack_tree.left)->key);
  CuAssertIntEquals(tc, 1, ((test_redblack_tree_t *)((test_redblack_tree_t *)root->redblack_tree.left)->redblack_tree.left)->key);
}

void Testredblack_tree_insert_case5(CuTest *tc)
  {
    test_redblack_tree_t *root;
    test_redblack_tree_t *elem;
    test_redblack_tree_t    *keep;
    bool ret;

    root = NULL;
    elem = malloc(sizeof(*elem));
    elem->key = 3;
    ret = redblack_tree_insert(root, elem, redblack_tree, BTREE_COMPARE);
    CuAssertTrue(tc, ret);
    elem = malloc(sizeof(*elem));
    elem->key = 4;
    keep = elem;
    ret = redblack_tree_insert(root, elem, redblack_tree, BTREE_COMPARE);
    CuAssertTrue(tc, ret);
    elem = malloc(sizeof(*elem));
    elem->key = 2;
    ret = redblack_tree_insert(root, elem, redblack_tree, BTREE_COMPARE);
    CuAssertTrue(tc, ret);
    keep->redblack_tree.colour = black;
    elem = malloc(sizeof(*elem));
    elem->key = 1;
    ret = redblack_tree_insert(root, elem, redblack_tree, BTREE_COMPARE);
    CuAssertTrue(tc, ret);
    CuAssertIntEquals(tc, black, root->redblack_tree.colour);
    CuAssertIntEquals(tc, 2, root->key);
    CuAssertIntEquals(tc, red, ((test_redblack_tree_t *)root->redblack_tree.left)->redblack_tree.colour);
    CuAssertIntEquals(tc, 1, ((test_redblack_tree_t *)root->redblack_tree.left)->key);
    CuAssertIntEquals(tc, red, ((test_redblack_tree_t *)root->redblack_tree.right)->redblack_tree.colour);
    CuAssertIntEquals(tc, 3, ((test_redblack_tree_t *)root->redblack_tree.right)->key);
    CuAssertIntEquals(tc, black, ((test_redblack_tree_t *)((test_redblack_tree_t *)root->redblack_tree.right)->redblack_tree.right)->redblack_tree.colour);
    CuAssertIntEquals(tc, 4, ((test_redblack_tree_t *)((test_redblack_tree_t *)root->redblack_tree.right)->redblack_tree.right)->key);
  }


void Testredblack_tree_lookup(CuTest *tc)
  {
    test_redblack_tree_t *root;
    test_redblack_tree_t *elem;
    int i;
    int j;
    bool ret;
    void *pret;

    root = NULL;
    for (i = 0, j = 30; i < j; i++, j--)
      {
        elem = malloc(sizeof(*elem));
        elem->key = i;
        ret = redblack_tree_insert(root, elem, redblack_tree, BTREE_COMPARE);
        CuAssertTrue(tc, ret);
        elem = malloc(sizeof(*elem));
        elem->key = j;
        ret = redblack_tree_insert(root, elem, redblack_tree, BTREE_COMPARE);
        CuAssertTrue(tc, ret);
      }
    CuAssertPtrNotNull(tc, root);
    for (i = 0, j = 30; i < j; i++, j--)
      {
        pret = redblack_tree_lookup(root, i, redblack_tree, BTREE_COMPARE_KEY);
        CuAssertPtrNotNull(tc, pret);
        pret = redblack_tree_lookup(root, j, redblack_tree, BTREE_COMPARE_KEY);
        CuAssertPtrNotNull(tc, pret);
      }
  }

void Testredblack_tree_remove(CuTest *tc)
  {
    test_redblack_tree_t *root;
    test_redblack_tree_t *elem;
    int i;
    int j;
    bool ret;
    void        *pret;

    root = NULL;
    for (i = 0, j = 6; i < j; i++, j--)
      {
        elem = malloc(sizeof(*elem));
        elem->key = i;
        ret = redblack_tree_insert(root, elem, redblack_tree, BTREE_COMPARE);
        CuAssertTrue(tc, ret);
        elem = malloc(sizeof(*elem));
        elem->key = j;
        ret = redblack_tree_insert(root, elem, redblack_tree, BTREE_COMPARE);
        CuAssertTrue(tc, ret);
      }
    for (i = 0, j = 6; i < j; i++, j--)
      {
        pret = redblack_tree_remove(root, i, redblack_tree, BTREE_COMPARE, BTREE_COMPARE_KEY);
        CuAssertPtrNotNull(tc, pret);
        pret = redblack_tree_remove(root, j, redblack_tree, BTREE_COMPARE, BTREE_COMPARE_KEY);
        CuAssertPtrNotNull(tc, pret);
      }
    CuAssertPtrEquals(tc, NULL, root);
  }

static bool	walk_state;
static int prev_value;

static void	redblack_tree_walk_preorder_cb(void *node, void *data)
{
	test_redblack_tree_t	*elem;
	int			prev;

	prev = prev_value;
	elem = (test_redblack_tree_t *)node;
	prev_value = elem->key;
	switch (prev)
	{
	case -1:
		if (elem->key != 8)
			walk_state = false;
		break;
	case 8:
		if (elem->key != 7)
			walk_state = false;
		break;
	case 7:
		if (elem->key != 6)
			walk_state = false;
		break;
	case 6:
		if (elem->key != 5)
			walk_state = false;
		break;
	case 5:
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

void Testredblack_tree_walk_preorder(CuTest *tc)
  {
 	test_redblack_tree_t *root;
    test_redblack_tree_t *elem;
    void		*pret;
    bool		ret;

	root = NULL;
    elem = malloc(sizeof(*elem));
    elem->key = 8;
    ret = redblack_tree_insert(root, elem, redblack_tree, BTREE_COMPARE);
    CuAssertTrue(tc, ret);

    elem = malloc(sizeof(*elem));
    elem->key = 6;
    ret = redblack_tree_insert(root, elem, redblack_tree, BTREE_COMPARE);
    CuAssertTrue(tc, ret);

    elem = malloc(sizeof(*elem));
    elem->key = 5;
    ret = redblack_tree_insert(root, elem, redblack_tree, BTREE_COMPARE);
    CuAssertTrue(tc, ret);

    elem = malloc(sizeof(*elem));
    elem->key = 7;
    ret = redblack_tree_insert(root, elem, redblack_tree, BTREE_COMPARE);
    CuAssertTrue(tc, ret);

    elem = malloc(sizeof(*elem));
    elem->key = 10;
    ret = redblack_tree_insert(root, elem, redblack_tree, BTREE_COMPARE);
    CuAssertTrue(tc, ret);

    elem = malloc(sizeof(*elem));
    elem->key = 9;
    ret = redblack_tree_insert(root, elem, redblack_tree, BTREE_COMPARE);
    CuAssertTrue(tc, ret);

    elem = malloc(sizeof(*elem));
    elem->key = 11;
    ret = redblack_tree_insert(root, elem, redblack_tree, BTREE_COMPARE);
    CuAssertTrue(tc, ret);

    walk_state = true;
	prev_value = -1;
	redblack_tree_walk_preorder(root, redblack_tree, redblack_tree_walk_preorder_cb, NULL);
	CuAssertIntEquals(tc, true, walk_state);

    pret = redblack_tree_remove(root, 8, redblack_tree, BTREE_COMPARE, BTREE_COMPARE_KEY);
    CuAssertPtrNotNull(tc, pret);

    pret = redblack_tree_remove(root, 6, redblack_tree, BTREE_COMPARE, BTREE_COMPARE_KEY);
    CuAssertPtrNotNull(tc, pret);

    pret = redblack_tree_remove(root, 5, redblack_tree, BTREE_COMPARE, BTREE_COMPARE_KEY);
    CuAssertPtrNotNull(tc, pret);

    pret = redblack_tree_remove(root, 7, redblack_tree, BTREE_COMPARE, BTREE_COMPARE_KEY);
    CuAssertPtrNotNull(tc, pret);

    pret = redblack_tree_remove(root, 10, redblack_tree, BTREE_COMPARE, BTREE_COMPARE_KEY);
    CuAssertPtrNotNull(tc, pret);

    pret = redblack_tree_remove(root, 9, redblack_tree, BTREE_COMPARE, BTREE_COMPARE_KEY);
    CuAssertPtrNotNull(tc, pret);

    pret = redblack_tree_remove(root, 11, redblack_tree, BTREE_COMPARE, BTREE_COMPARE_KEY);
    CuAssertPtrNotNull(tc, pret);

    CuAssertPtrEquals(tc, NULL, root);
  }

static void	redblack_tree_walk_inorder_cb(void *node, void *data)
{
	test_redblack_tree_t	*elem;
	int			prev;

	prev = prev_value;
	elem = (test_redblack_tree_t *)node;
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

void Testredblack_tree_walk_inorder(CuTest *tc)
  {
 	test_redblack_tree_t *root;
    test_redblack_tree_t *elem;
    void		*pret;
    bool		ret;

	root = NULL;
    elem = malloc(sizeof(*elem));
    elem->key = 8;
    ret = redblack_tree_insert(root, elem, redblack_tree, BTREE_COMPARE);
    CuAssertTrue(tc, ret);

    elem = malloc(sizeof(*elem));
    elem->key = 6;
    ret = redblack_tree_insert(root, elem, redblack_tree, BTREE_COMPARE);
    CuAssertTrue(tc, ret);

    elem = malloc(sizeof(*elem));
    elem->key = 5;
    ret = redblack_tree_insert(root, elem, redblack_tree, BTREE_COMPARE);
    CuAssertTrue(tc, ret);

    elem = malloc(sizeof(*elem));
    elem->key = 7;
    ret = redblack_tree_insert(root, elem, redblack_tree, BTREE_COMPARE);
    CuAssertTrue(tc, ret);

    elem = malloc(sizeof(*elem));
    elem->key = 10;
    ret = redblack_tree_insert(root, elem, redblack_tree, BTREE_COMPARE);
    CuAssertTrue(tc, ret);

    elem = malloc(sizeof(*elem));
    elem->key = 9;
    ret = redblack_tree_insert(root, elem, redblack_tree, BTREE_COMPARE);
    CuAssertTrue(tc, ret);

    elem = malloc(sizeof(*elem));
    elem->key = 11;
    ret = redblack_tree_insert(root, elem, redblack_tree, BTREE_COMPARE);
    CuAssertTrue(tc, ret);

    walk_state = true;
	prev_value = -1;
	redblack_tree_walk_inorder(root, redblack_tree, redblack_tree_walk_inorder_cb, NULL);
	CuAssertIntEquals(tc, true, walk_state);

    pret = redblack_tree_remove(root, 8, redblack_tree, BTREE_COMPARE, BTREE_COMPARE_KEY);
    CuAssertPtrNotNull(tc, pret);

    pret = redblack_tree_remove(root, 6, redblack_tree, BTREE_COMPARE, BTREE_COMPARE_KEY);
    CuAssertPtrNotNull(tc, pret);

    pret = redblack_tree_remove(root, 5, redblack_tree, BTREE_COMPARE, BTREE_COMPARE_KEY);
    CuAssertPtrNotNull(tc, pret);

    pret = redblack_tree_remove(root, 7, redblack_tree, BTREE_COMPARE, BTREE_COMPARE_KEY);
    CuAssertPtrNotNull(tc, pret);

    pret = redblack_tree_remove(root, 10, redblack_tree, BTREE_COMPARE, BTREE_COMPARE_KEY);
    CuAssertPtrNotNull(tc, pret);

    pret = redblack_tree_remove(root, 9, redblack_tree, BTREE_COMPARE, BTREE_COMPARE_KEY);
    CuAssertPtrNotNull(tc, pret);

    pret = redblack_tree_remove(root, 11, redblack_tree, BTREE_COMPARE, BTREE_COMPARE_KEY);
    CuAssertPtrNotNull(tc, pret);

    CuAssertPtrEquals(tc, NULL, root);
  }

static void	redblack_tree_walk_postorder_cb(void *node, void *data)
{
	test_redblack_tree_t	*elem;
	int			prev;

	prev = prev_value;
	elem = (test_redblack_tree_t *)node;
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

void Testredblack_tree_walk_postorder(CuTest *tc)
  {
 	test_redblack_tree_t *root;
    test_redblack_tree_t *elem;
    void		*pret;
    bool		ret;

	root = NULL;
    elem = malloc(sizeof(*elem));
    elem->key = 8;
    ret = redblack_tree_insert(root, elem, redblack_tree, BTREE_COMPARE);
    CuAssertTrue(tc, ret);

    elem = malloc(sizeof(*elem));
    elem->key = 6;
    ret = redblack_tree_insert(root, elem, redblack_tree, BTREE_COMPARE);
    CuAssertTrue(tc, ret);

    elem = malloc(sizeof(*elem));
    elem->key = 5;
    ret = redblack_tree_insert(root, elem, redblack_tree, BTREE_COMPARE);
    CuAssertTrue(tc, ret);

    elem = malloc(sizeof(*elem));
    elem->key = 7;
    ret = redblack_tree_insert(root, elem, redblack_tree, BTREE_COMPARE);
    CuAssertTrue(tc, ret);

    elem = malloc(sizeof(*elem));
    elem->key = 10;
    ret = redblack_tree_insert(root, elem, redblack_tree, BTREE_COMPARE);
    CuAssertTrue(tc, ret);

    elem = malloc(sizeof(*elem));
    elem->key = 9;
    ret = redblack_tree_insert(root, elem, redblack_tree, BTREE_COMPARE);
    CuAssertTrue(tc, ret);

    elem = malloc(sizeof(*elem));
    elem->key = 11;
    ret = redblack_tree_insert(root, elem, redblack_tree, BTREE_COMPARE);
    CuAssertTrue(tc, ret);

    walk_state = true;
	prev_value = -1;
	redblack_tree_walk_postorder(root, redblack_tree, redblack_tree_walk_postorder_cb, NULL);
	CuAssertIntEquals(tc,true, walk_state);

    pret = redblack_tree_remove(root, 8, redblack_tree, BTREE_COMPARE, BTREE_COMPARE_KEY);
    CuAssertPtrNotNull(tc, pret);

    pret = redblack_tree_remove(root, 6, redblack_tree, BTREE_COMPARE, BTREE_COMPARE_KEY);
    CuAssertPtrNotNull(tc, pret);

    pret = redblack_tree_remove(root, 5, redblack_tree, BTREE_COMPARE, BTREE_COMPARE_KEY);
    CuAssertPtrNotNull(tc, pret);

    pret = redblack_tree_remove(root, 7, redblack_tree, BTREE_COMPARE, BTREE_COMPARE_KEY);
    CuAssertPtrNotNull(tc, pret);

    pret = redblack_tree_remove(root, 10, redblack_tree, BTREE_COMPARE, BTREE_COMPARE_KEY);
    CuAssertPtrNotNull(tc, pret);

    pret = redblack_tree_remove(root, 9, redblack_tree, BTREE_COMPARE, BTREE_COMPARE_KEY);
    CuAssertPtrNotNull(tc, pret);

    pret = redblack_tree_remove(root, 11, redblack_tree, BTREE_COMPARE, BTREE_COMPARE_KEY);
    CuAssertPtrNotNull(tc, pret);

    CuAssertPtrEquals(tc, NULL, root);
  }


void Testredblack_tree_graft(CuTest *tc)
  {
    test_redblack_tree_t *root1;
    test_redblack_tree_t *root2;
    test_redblack_tree_t *elem;
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
        ret = redblack_tree_insert(root1, elem, redblack_tree, BTREE_COMPARE);
        CuAssertTrue(tc, ret);
        elem = malloc(sizeof(*elem));
        elem->key = j;
        ret = redblack_tree_insert(root2, elem, redblack_tree, BTREE_COMPARE);
        CuAssertTrue(tc, ret);
      }
    pret = redblack_tree_lookup(root1, i + 1, redblack_tree, BTREE_COMPARE_KEY);
    CuAssertPtrEquals(tc, NULL, pret);
    ret = redblack_tree_graft(root1, NULL, redblack_tree, BTREE_COMPARE);
    CuAssertTrue(tc, !ret);
    ret = redblack_tree_graft(root1, root2, redblack_tree, BTREE_COMPARE);
    CuAssertTrue(tc, ret);
    pret = redblack_tree_lookup(root1, j + 1, redblack_tree, BTREE_COMPARE_KEY);
    CuAssertPtrNotNull(tc, pret);
    for (i = 0, j = 6; i < j; i++, j--)
      {
        pret = redblack_tree_remove(root1, i, redblack_tree, BTREE_COMPARE, BTREE_COMPARE_KEY);
        CuAssertPtrNotNull(tc, pret);
        pret = redblack_tree_remove(root1, j, redblack_tree, BTREE_COMPARE, BTREE_COMPARE_KEY);
        CuAssertPtrNotNull(tc, pret);
      }
  }

void Testredblack_tree_prune(CuTest *tc)
  {
    test_redblack_tree_t *root;
    test_redblack_tree_t *grafted;
    test_redblack_tree_t *elem;
    int i;
    int j;
    bool ret;
    void *pret;

    root = NULL;
    for (i = 0, j = 6; i < j; i++, j--)
      {
        elem = malloc(sizeof(*elem));
        elem->key = i;
        ret = redblack_tree_insert(root, elem, redblack_tree, BTREE_COMPARE);
        CuAssertTrue(tc, ret);
        elem = malloc(sizeof(*elem));
        elem->key = j;
        ret = redblack_tree_insert(root, elem, redblack_tree, BTREE_COMPARE);
        CuAssertTrue(tc, ret);
      }
    grafted = redblack_tree_prune(root, j, redblack_tree, BTREE_COMPARE_KEY);
    CuAssertPtrEquals(tc, NULL, grafted);
    grafted = redblack_tree_prune(root, 5, redblack_tree, BTREE_COMPARE_KEY);
    CuAssertPtrNotNull(tc, grafted);
    pret = redblack_tree_lookup(grafted, 1, redblack_tree, BTREE_COMPARE_KEY);
    CuAssertPtrEquals(tc, NULL, pret);
    pret = redblack_tree_lookup(grafted, 5, redblack_tree, BTREE_COMPARE_KEY);
    CuAssertPtrNotNull(tc, pret);
    ret = redblack_tree_graft(root, grafted, redblack_tree, BTREE_COMPARE_KEY);
    CuAssertTrue(tc, ret);
    for (i = 0, j = 6; i < j; i++, j--)
      {
        pret = redblack_tree_remove(root, i, redblack_tree, BTREE_COMPARE, BTREE_COMPARE_KEY);
        CuAssertPtrNotNull(tc, pret);
        ret = redblack_tree_remove(root, j, redblack_tree, BTREE_COMPARE, BTREE_COMPARE_KEY);
        CuAssertPtrNotNull(tc, pret);
      }
    CuAssertPtrEquals(tc, NULL, root);
  }
