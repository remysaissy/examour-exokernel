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

typedef struct test_ebst_tree_s
  {
    int key;
    ebst_tree_t btree;

  } test_ebst_tree_t;

static bst_tree_compare_e EBTREE_COMPARE(void *n1, void *n2)
  {
    test_ebst_tree_t *bt1 = (test_ebst_tree_t *)n1;
    test_ebst_tree_t *bt2 = (test_ebst_tree_t *)n2;

    if (bt2->key < bt1->key)
      return (BST_TREE_LEFT);
    if (bt2->key > bt1->key)
      return (BST_TREE_RIGHT);
    return (BST_TREE_MATCH);
  }

static bst_tree_compare_e EBTREE_COMPARE_KEY(void *n1, void *key)
  {
    int k = (int)key;
    test_ebst_tree_t *bt1 = (test_ebst_tree_t *)n1;

    if (k < bt1->key)
      return (BST_TREE_LEFT);
    if (k > bt1->key)
      return (BST_TREE_RIGHT);
    return (BST_TREE_MATCH);
  }

void Testebst_tree_init(CuTest *tc)
  {
    test_ebst_tree_t test;
    bool ret;

    ret = _ebst_tree_init(NULL, 0);
    CuAssertTrue(tc, !ret);
    ret = ebst_tree_init(&test, btree);
    CuAssertTrue(tc, ret);
  }

void Testebst_tree_insert(CuTest *tc)
  {
    test_ebst_tree_t *root;
    test_ebst_tree_t *elem;
    bool ret;

    root = NULL;
    elem = NULL;
    ret = _ebst_tree_insert(NULL, elem, 0, EBTREE_COMPARE);
    CuAssertTrue(tc, !ret);
    ret = ebst_tree_insert(root, NULL, btree, EBTREE_COMPARE);
    CuAssertTrue(tc, !ret);
    ret = ebst_tree_insert(root, elem, btree, NULL);
    CuAssertTrue(tc, !ret);
    elem = malloc(sizeof(*elem));
    elem->key = 2;
    ret = ebst_tree_insert(root, elem, btree, EBTREE_COMPARE);
    CuAssertTrue(tc, ret);
    elem = malloc(sizeof(*elem));
    elem->key = 1;
    ret = ebst_tree_insert(root, elem, btree, EBTREE_COMPARE);
    CuAssertTrue(tc, ret);
    elem = malloc(sizeof(*elem));
    elem->key = 1;
    ret = ebst_tree_insert(root, elem, btree, EBTREE_COMPARE);
    CuAssertTrue(tc, !ret);
    elem = malloc(sizeof(*elem));
    elem->key = 3;
    ret = ebst_tree_insert(root, elem, btree, EBTREE_COMPARE);
    CuAssertTrue(tc, ret);
    CuAssertIntEquals(tc, 2, root->key);
    CuAssertIntEquals(tc, 1, ((test_ebst_tree_t *)root->btree.left)->key);
    CuAssertIntEquals(tc, 3, ((test_ebst_tree_t *)root->btree.right)->key);
    CuAssertPtrEquals(tc, NULL, root->btree.parent);
    CuAssertPtrEquals(tc, root, ((test_ebst_tree_t *)root->btree.left)->btree.parent);
    CuAssertPtrEquals(tc, root, ((test_ebst_tree_t *)root->btree.right)->btree.parent);
  }

void Testebst_tree_lookup(CuTest *tc)
  {
    test_ebst_tree_t *root;
    test_ebst_tree_t *elem;
    int i;
    int j;
    bool ret;
    void *pret;

    root = NULL;
    for (i = 0, j = 30; i < j; i++, j--)
      {
        elem = malloc(sizeof(*elem));
        elem->key = i;
        ret = ebst_tree_insert(root, elem, btree, EBTREE_COMPARE);
        CuAssertTrue(tc, ret);
        elem = malloc(sizeof(*elem));
        elem->key = j;
        ret = ebst_tree_insert(root, elem, btree, EBTREE_COMPARE);
        CuAssertTrue(tc, ret);
      }
    CuAssertPtrNotNull(tc, root);
    for (i = 0, j = 30; i < j; i++, j--)
      {
        pret = ebst_tree_lookup(root, i, btree, EBTREE_COMPARE_KEY);
        CuAssertPtrNotNull(tc, pret);
        pret = ebst_tree_lookup(root, j, btree, EBTREE_COMPARE_KEY);
        CuAssertPtrNotNull(tc, pret);
      }
  }

void Testebst_tree_remove(CuTest *tc)
  {
    test_ebst_tree_t *root;
    test_ebst_tree_t *elem;
    void        *pret;
    bool        ret;

    root = NULL;

    elem = malloc(sizeof(*elem));
    elem->key = 4;
    ret = ebst_tree_insert(root, elem, btree, EBTREE_COMPARE);
    CuAssertTrue(tc, ret);

    elem = malloc(sizeof(*elem));
    elem->key = 5;
    ret = ebst_tree_insert(root, elem, btree, EBTREE_COMPARE);
    CuAssertTrue(tc, ret);

    elem = malloc(sizeof(*elem));
    elem->key = 2;
    ret = ebst_tree_insert(root, elem, btree, EBTREE_COMPARE);
    CuAssertTrue(tc, ret);

    elem = malloc(sizeof(*elem));
    elem->key = 3;
    ret = ebst_tree_insert(root, elem, btree, EBTREE_COMPARE);
    CuAssertTrue(tc, ret);

    elem = malloc(sizeof(*elem));
    elem->key = 1;
    ret = ebst_tree_insert(root, elem, btree, EBTREE_COMPARE);
    CuAssertTrue(tc, ret);

    pret = ebst_tree_remove(root, 2, btree, EBTREE_COMPARE, EBTREE_COMPARE_KEY);
    CuAssertPtrNotNull(tc, pret);
    CuAssertIntEquals(tc, 4, root->key);
    CuAssertIntEquals(tc, 5, ((test_ebst_tree_t *)root->btree.right)->key);
    CuAssertIntEquals(tc, 3, ((test_ebst_tree_t *)root->btree.left)->key);
    CuAssertIntEquals(tc, 1, ((test_ebst_tree_t *)((test_ebst_tree_t *)root->btree.left)->btree.left)->key);
    CuAssertPtrEquals(tc, NULL, root->btree.parent);
    CuAssertPtrEquals(tc, root, ((test_ebst_tree_t *)root->btree.right)->btree.parent);
    CuAssertPtrEquals(tc, root, ((test_ebst_tree_t *)root->btree.left)->btree.parent);
  }


static bool	walk_state;
static int prev_value;

static void	btree_walk_preorder_cb(void *node, void *data)
{
	test_ebst_tree_t	*elem;
	int			prev;

	prev = prev_value;
	elem = (test_ebst_tree_t *)node;
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

void Testebst_tree_walk_preorder(CuTest *tc)
  {
 	test_ebst_tree_t *root;
    test_ebst_tree_t *elem;
    void		*pret;
    bool		ret;

	root = NULL;
    elem = malloc(sizeof(*elem));
    elem->key = 8;
    ret = ebst_tree_insert(root, elem, btree, EBTREE_COMPARE);
    CuAssertTrue(tc, ret);

    elem = malloc(sizeof(*elem));
    elem->key = 6;
    ret = ebst_tree_insert(root, elem, btree, EBTREE_COMPARE);
    CuAssertTrue(tc, ret);

    elem = malloc(sizeof(*elem));
    elem->key = 5;
    ret = ebst_tree_insert(root, elem, btree, EBTREE_COMPARE);
    CuAssertTrue(tc, ret);

    elem = malloc(sizeof(*elem));
    elem->key = 7;
    ret = ebst_tree_insert(root, elem, btree, EBTREE_COMPARE);
    CuAssertTrue(tc, ret);

    elem = malloc(sizeof(*elem));
    elem->key = 10;
    ret = ebst_tree_insert(root, elem, btree, EBTREE_COMPARE);
    CuAssertTrue(tc, ret);

    elem = malloc(sizeof(*elem));
    elem->key = 9;
    ret = ebst_tree_insert(root, elem, btree, EBTREE_COMPARE);
    CuAssertTrue(tc, ret);

    elem = malloc(sizeof(*elem));
    elem->key = 11;
    ret = ebst_tree_insert(root, elem, btree, EBTREE_COMPARE);
    CuAssertTrue(tc, ret);

    walk_state = true;
	prev_value = -1;
	ebst_tree_walk_preorder(root, btree, btree_walk_preorder_cb, NULL);
	CuAssertIntEquals(tc, true, walk_state);

    pret = ebst_tree_remove(root, 8, btree, EBTREE_COMPARE, EBTREE_COMPARE_KEY);
    CuAssertPtrNotNull(tc, pret);

    pret = ebst_tree_remove(root, 6, btree, EBTREE_COMPARE, EBTREE_COMPARE_KEY);
    CuAssertPtrNotNull(tc, pret);

    pret = ebst_tree_remove(root, 5, btree, EBTREE_COMPARE, EBTREE_COMPARE_KEY);
    CuAssertPtrNotNull(tc, pret);

    pret = ebst_tree_remove(root, 7, btree, EBTREE_COMPARE, EBTREE_COMPARE_KEY);
    CuAssertPtrNotNull(tc, pret);

    pret = ebst_tree_remove(root, 10, btree, EBTREE_COMPARE, EBTREE_COMPARE_KEY);
    CuAssertPtrNotNull(tc, pret);

    pret = ebst_tree_remove(root, 9, btree, EBTREE_COMPARE, EBTREE_COMPARE_KEY);
    CuAssertPtrNotNull(tc, pret);

    pret = ebst_tree_remove(root, 11, btree, EBTREE_COMPARE, EBTREE_COMPARE_KEY);
    CuAssertPtrNotNull(tc, pret);

    CuAssertPtrEquals(tc, NULL, root);
  }

static void	btree_walk_inorder_cb(void *node, void *data)
{
	test_ebst_tree_t	*elem;
	int			prev;

	prev = prev_value;
	elem = (test_ebst_tree_t *)node;
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

void Testebst_tree_walk_inorder(CuTest *tc)
  {
 	test_ebst_tree_t *root;
    test_ebst_tree_t *elem;
    void		*pret;
    bool		ret;

	root = NULL;
    elem = malloc(sizeof(*elem));
    elem->key = 8;
    ret = ebst_tree_insert(root, elem, btree, EBTREE_COMPARE);
    CuAssertTrue(tc, ret);

    elem = malloc(sizeof(*elem));
    elem->key = 6;
    ret = ebst_tree_insert(root, elem, btree, EBTREE_COMPARE);
    CuAssertTrue(tc, ret);

    elem = malloc(sizeof(*elem));
    elem->key = 5;
    ret = ebst_tree_insert(root, elem, btree, EBTREE_COMPARE);
    CuAssertTrue(tc, ret);

    elem = malloc(sizeof(*elem));
    elem->key = 7;
    ret = ebst_tree_insert(root, elem, btree, EBTREE_COMPARE);
    CuAssertTrue(tc, ret);

    elem = malloc(sizeof(*elem));
    elem->key = 10;
    ret = ebst_tree_insert(root, elem, btree, EBTREE_COMPARE);
    CuAssertTrue(tc, ret);

    elem = malloc(sizeof(*elem));
    elem->key = 9;
    ret = ebst_tree_insert(root, elem, btree, EBTREE_COMPARE);
    CuAssertTrue(tc, ret);

    elem = malloc(sizeof(*elem));
    elem->key = 11;
    ret = ebst_tree_insert(root, elem, btree, EBTREE_COMPARE);
    CuAssertTrue(tc, ret);

    walk_state = true;
	prev_value = -1;
	ebst_tree_walk_inorder(root, btree, btree_walk_inorder_cb, NULL);
	CuAssertIntEquals(tc, true, walk_state);

    pret = ebst_tree_remove(root, 8, btree, EBTREE_COMPARE, EBTREE_COMPARE_KEY);
    CuAssertPtrNotNull(tc, pret);

    pret = ebst_tree_remove(root, 6, btree, EBTREE_COMPARE, EBTREE_COMPARE_KEY);
    CuAssertPtrNotNull(tc, pret);

    pret = ebst_tree_remove(root, 5, btree, EBTREE_COMPARE, EBTREE_COMPARE_KEY);
    CuAssertPtrNotNull(tc, pret);

    pret = ebst_tree_remove(root, 7, btree, EBTREE_COMPARE, EBTREE_COMPARE_KEY);
    CuAssertPtrNotNull(tc, pret);

    pret = ebst_tree_remove(root, 10, btree, EBTREE_COMPARE, EBTREE_COMPARE_KEY);
    CuAssertPtrNotNull(tc, pret);

    pret = ebst_tree_remove(root, 9, btree, EBTREE_COMPARE, EBTREE_COMPARE_KEY);
    CuAssertPtrNotNull(tc, pret);

    pret = ebst_tree_remove(root, 11, btree, EBTREE_COMPARE, EBTREE_COMPARE_KEY);
    CuAssertPtrNotNull(tc, pret);

    CuAssertPtrEquals(tc, NULL, root);
  }

static void	btree_walk_postorder_cb(void *node, void *data)
{
	test_ebst_tree_t	*elem;
	int			prev;

	prev = prev_value;
	elem = (test_ebst_tree_t *)node;
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

void Testebst_tree_walk_postorder(CuTest *tc)
  {
 	test_ebst_tree_t *root;
    test_ebst_tree_t *elem;
    void		*pret;
    bool		ret;

	root = NULL;
    elem = malloc(sizeof(*elem));
    elem->key = 8;
    ret = ebst_tree_insert(root, elem, btree, EBTREE_COMPARE);
    CuAssertTrue(tc, ret);

    elem = malloc(sizeof(*elem));
    elem->key = 6;
    ret = ebst_tree_insert(root, elem, btree, EBTREE_COMPARE);
    CuAssertTrue(tc, ret);

    elem = malloc(sizeof(*elem));
    elem->key = 5;
    ret = ebst_tree_insert(root, elem, btree, EBTREE_COMPARE);
    CuAssertTrue(tc, ret);

    elem = malloc(sizeof(*elem));
    elem->key = 7;
    ret = ebst_tree_insert(root, elem, btree, EBTREE_COMPARE);
    CuAssertTrue(tc, ret);

    elem = malloc(sizeof(*elem));
    elem->key = 10;
    ret = ebst_tree_insert(root, elem, btree, EBTREE_COMPARE);
    CuAssertTrue(tc, ret);

    elem = malloc(sizeof(*elem));
    elem->key = 9;
    ret = ebst_tree_insert(root, elem, btree, EBTREE_COMPARE);
    CuAssertTrue(tc, ret);

    elem = malloc(sizeof(*elem));
    elem->key = 11;
    ret = ebst_tree_insert(root, elem, btree, EBTREE_COMPARE);
    CuAssertTrue(tc, ret);

    walk_state = true;
	prev_value = -1;
	ebst_tree_walk_postorder(root, btree, btree_walk_postorder_cb, NULL);
	CuAssertIntEquals(tc,true, walk_state);

    pret = ebst_tree_remove(root, 8, btree, EBTREE_COMPARE, EBTREE_COMPARE_KEY);
    CuAssertPtrNotNull(tc, pret);

    pret = ebst_tree_remove(root, 6, btree, EBTREE_COMPARE, EBTREE_COMPARE_KEY);
    CuAssertPtrNotNull(tc, pret);

    pret = ebst_tree_remove(root, 5, btree, EBTREE_COMPARE, EBTREE_COMPARE_KEY);
    CuAssertPtrNotNull(tc, pret);

    pret = ebst_tree_remove(root, 7, btree, EBTREE_COMPARE, EBTREE_COMPARE_KEY);
    CuAssertPtrNotNull(tc, pret);

    pret = ebst_tree_remove(root, 10, btree, EBTREE_COMPARE, EBTREE_COMPARE_KEY);
    CuAssertPtrNotNull(tc, pret);

    pret = ebst_tree_remove(root, 9, btree, EBTREE_COMPARE, EBTREE_COMPARE_KEY);
    CuAssertPtrNotNull(tc, pret);

    pret = ebst_tree_remove(root, 11, btree, EBTREE_COMPARE, EBTREE_COMPARE_KEY);
    CuAssertPtrNotNull(tc, pret);

    CuAssertPtrEquals(tc, NULL, root);
  }


void Testebst_tree_graft(CuTest *tc)
  {
    test_ebst_tree_t *root1;
    test_ebst_tree_t *root2;
    test_ebst_tree_t *elem;
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
        ret = ebst_tree_insert(root1, elem, btree, EBTREE_COMPARE);
        CuAssertTrue(tc, ret);
        elem = malloc(sizeof(*elem));
        elem->key = j;
        ret = ebst_tree_insert(root2, elem, btree, EBTREE_COMPARE);
        CuAssertTrue(tc, ret);
      }
    pret = ebst_tree_lookup(root1, i + 1, btree, EBTREE_COMPARE_KEY);
    CuAssertPtrEquals(tc, NULL, pret);
    ret = ebst_tree_graft(root1, NULL, btree, EBTREE_COMPARE);
    CuAssertTrue(tc, !ret);
    ret = ebst_tree_graft(root1, root2, btree, EBTREE_COMPARE);
    CuAssertTrue(tc, ret);
    pret = ebst_tree_lookup(root1, j + 1, btree, EBTREE_COMPARE_KEY);
    CuAssertPtrNotNull(tc, pret);
    for (i = 0, j = 6; i < j; i++, j--)
      {
        pret = ebst_tree_remove(root1, i, btree, EBTREE_COMPARE, EBTREE_COMPARE_KEY);
        CuAssertPtrNotNull(tc, pret);
        pret = ebst_tree_remove(root1, j, btree, EBTREE_COMPARE, EBTREE_COMPARE_KEY);
        CuAssertPtrNotNull(tc, pret);
      }
  }

void Testebst_tree_prune(CuTest *tc)
  {
    test_ebst_tree_t *root;
    test_ebst_tree_t *grafted;
    test_ebst_tree_t *elem;
    int i;
    int j;
    bool ret;
    void *pret;

    root = NULL;
    for (i = 0, j = 6; i < j; i++, j--)
      {
        elem = malloc(sizeof(*elem));
        elem->key = i;
        ret = ebst_tree_insert(root, elem, btree, EBTREE_COMPARE);
        CuAssertTrue(tc, ret);
        elem = malloc(sizeof(*elem));
        elem->key = j;
        ret = ebst_tree_insert(root, elem, btree, EBTREE_COMPARE);
        CuAssertTrue(tc, ret);
      }
    grafted = ebst_tree_prune(root, j, btree, EBTREE_COMPARE_KEY);
    CuAssertPtrEquals(tc, NULL, grafted);
    grafted = ebst_tree_prune(root, 5, btree, EBTREE_COMPARE_KEY);
    CuAssertPtrNotNull(tc, grafted);
    pret = ebst_tree_lookup(grafted, 1, btree, EBTREE_COMPARE_KEY);
    CuAssertPtrEquals(tc, NULL, pret);
    pret = ebst_tree_lookup(grafted, 5, btree, EBTREE_COMPARE_KEY);
    CuAssertPtrNotNull(tc, pret);
    ret = ebst_tree_graft(root, grafted, btree, EBTREE_COMPARE_KEY);
    CuAssertTrue(tc, ret);
    for (i = 0, j = 6; i < j; i++, j--)
      {
        pret = ebst_tree_remove(root, i, btree, EBTREE_COMPARE, EBTREE_COMPARE_KEY);
        CuAssertPtrNotNull(tc, pret);
        ret = ebst_tree_remove(root, j, btree, EBTREE_COMPARE, EBTREE_COMPARE_KEY);
        CuAssertPtrNotNull(tc, pret);
      }
    CuAssertPtrEquals(tc, NULL, root);
  }
