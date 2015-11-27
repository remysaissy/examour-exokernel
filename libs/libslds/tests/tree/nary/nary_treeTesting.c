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
#include	<string.h>

#include	<CuTest.h>

#include	<tree.h>

typedef struct test_nary_tree_s
  {
    char  *key;
    ntree_t ntree;

  } test_nary_tree_t;

static int NTREE_COMPARE(void *tree_node, void *path, int *iterator, void *data)
  {
    test_nary_tree_t *current_node = (test_nary_tree_t *)tree_node;
    char		      *key = (char *)path;
    int           end_position;
    char          *p;
    int           ret;

    p = strchr(key + *iterator, '.');
    if (p != NULL)
      end_position = (int)p - (int)(key + *iterator);
    else
      end_position = strlen(key + *iterator);
    ret = strncmp(key + *iterator, current_node->key, end_position);
    if (!ret)
    {
      *iterator += end_position + 1;
      if (*iterator >= strlen(key))
        return (2);
      return (1);
    }
    return (0);
}

static void            *NTREE_ADD_NEW_NODE(void *path, int iterator, void *data)
{
  char          *key = (char *)path;
  int           end_position;
  char          *p;
  test_nary_tree_t   *elem;

  if (iterator >= strlen(path))
    return (NULL);
  p = strchr(key + iterator, '.');
  if (p != NULL)
    end_position = (int)p - (int)(key + iterator);
  else
    end_position = strlen(key + iterator);
  elem = calloc(sizeof(*elem), 1);
  if (elem == NULL)
    return (NULL);
  elem->key = calloc(end_position + 1, 1);
  if (elem->key == NULL)
    return (NULL);
  strncpy(elem->key, key + iterator, end_position);
  return (elem);
}

static void				NTREE_REMOVE_NODE(void *node, void *data)
{
	test_nary_tree_t			*n = (test_nary_tree_t *)node;

	free(n->key);
	free(n);
}

void Testnary_tree_init(CuTest *tc)
  {
    test_nary_tree_t test;
    bool ret;

    ret = _ntree_init(NULL, 0);
    CuAssertTrue(tc, !ret);
    ret = ntree_init(&test, ntree);
    CuAssertTrue(tc, ret);
  }

void Testnary_tree_insert(CuTest *tc)
  {
  test_nary_tree_t *root;
  test_nary_tree_t *elem;
  bool        ret;

  root = NULL;
  ntree_init(root, ntree);
  elem = malloc(sizeof(*elem));
  CuAssertPtrNotNull(tc, elem);
  elem->key = strdup("desk");
  ret = ntree_insert(&root, "office", elem, ntree, NTREE_COMPARE, NTREE_ADD_NEW_NODE, NULL);
  CuAssertTrue(tc, ret);
  elem = malloc(sizeof(*elem));
  CuAssertPtrNotNull(tc, elem);
  elem->key = strdup("coffee");
  ret = ntree_insert(&root, "office.hall", elem, ntree, NTREE_COMPARE, NTREE_ADD_NEW_NODE, NULL);
  CuAssertTrue(tc, ret);
  elem = malloc(sizeof(*elem));
  CuAssertPtrNotNull(tc, elem);
  elem->key = strdup("bed");
  ret = ntree_insert(&root, "home.room", elem, ntree, NTREE_COMPARE, NTREE_ADD_NEW_NODE, NULL);
  CuAssertTrue(tc, ret);
  }

void Testnary_tree_lookup(CuTest *tc)
  {
	  test_nary_tree_t *root;
	  test_nary_tree_t *elem;
	  bool        ret;

	  root = NULL;
	  ntree_init(root, ntree);
	  elem = malloc(sizeof(*elem));
	  CuAssertPtrNotNull(tc, elem);
	  elem->key = strdup("desk");
	  ret = ntree_insert(&root, "office", elem, ntree, NTREE_COMPARE, NTREE_ADD_NEW_NODE, NULL);
	  CuAssertTrue(tc, ret);
	  elem = malloc(sizeof(*elem));
	  CuAssertPtrNotNull(tc, elem);
	  elem->key = strdup("coffee");
	  ret = ntree_insert(&root, "office.hall", elem, ntree, NTREE_COMPARE, NTREE_ADD_NEW_NODE, NULL);
	  CuAssertTrue(tc, ret);
	  elem = malloc(sizeof(*elem));
	  CuAssertPtrNotNull(tc, elem);
	  elem->key = strdup("bed");
	  ret = ntree_insert(&root, "home.room", elem, ntree, NTREE_COMPARE, NTREE_ADD_NEW_NODE, NULL);
	  CuAssertTrue(tc, ret);
	  elem = ntree_lookup(&root, "office.hall.coffee", ntree, NTREE_COMPARE, NULL);
	  CuAssertPtrNotNull(tc, elem);
	  elem = ntree_lookup(&root, "office.hall", ntree, NTREE_COMPARE, NULL);
	  CuAssertPtrNotNull(tc, elem);
	  elem = ntree_lookup(&root, "home.room", ntree, NTREE_COMPARE, NULL);
	  CuAssertPtrNotNull(tc, elem);
	  elem = ntree_lookup(&root, "home.kitchen", ntree, NTREE_COMPARE, NULL);
	  CuAssertPtrEquals(tc, NULL, elem);
  }

void Testnary_tree_remove(CuTest *tc)
  {
	  test_nary_tree_t *root;
	  test_nary_tree_t *elem;
	  bool        ret;

	  root = NULL;
	  ntree_init(root, ntree);
	  elem = malloc(sizeof(*elem));
	  CuAssertPtrNotNull(tc, elem);
	  elem->key = strdup("desk");
	  ret = ntree_insert(&root, "office", elem, ntree, NTREE_COMPARE, NTREE_ADD_NEW_NODE, NULL);
	  CuAssertTrue(tc, ret);
	  elem = malloc(sizeof(*elem));
	  CuAssertPtrNotNull(tc, elem);
	  elem->key = strdup("short");
	  ret = ntree_insert(&root, "office.hall.coffee", elem, ntree, NTREE_COMPARE, NTREE_ADD_NEW_NODE, NULL);
	  CuAssertTrue(tc, ret);
	  elem = malloc(sizeof(*elem));
	  CuAssertPtrNotNull(tc, elem);
	  elem->key = strdup("long");
	  ret = ntree_insert(&root, "office.hall.coffee", elem, ntree, NTREE_COMPARE, NTREE_ADD_NEW_NODE, NULL);
	  CuAssertTrue(tc, ret);
	  elem = malloc(sizeof(*elem));
	  CuAssertPtrNotNull(tc, elem);
	  elem->key = strdup("tea");
	  ret = ntree_insert(&root, "office.hall", elem, ntree, NTREE_COMPARE, NTREE_ADD_NEW_NODE, NULL);
	  CuAssertTrue(tc, ret);
	  elem = malloc(sizeof(*elem));
	  CuAssertPtrNotNull(tc, elem);
	  elem->key = strdup("kro");
	  ret = ntree_insert(&root, "office.hall.beer", elem, ntree, NTREE_COMPARE, NTREE_ADD_NEW_NODE, NULL);
	  CuAssertTrue(tc, ret);
	  elem = malloc(sizeof(*elem));
	  CuAssertPtrNotNull(tc, elem);
	  elem->key = strdup("bed");
	  ret = ntree_insert(&root, "home.room", elem, ntree, NTREE_COMPARE, NTREE_ADD_NEW_NODE, NULL);
	  CuAssertTrue(tc, ret);
	  elem = ntree_remove(&root, "office.hall", ntree, NTREE_COMPARE, NTREE_REMOVE_NODE, NULL);
	  CuAssertPtrNotNull(tc, elem);
	  elem = ntree_lookup(&root, "home.room", ntree, NTREE_COMPARE, NULL);
	  CuAssertPtrNotNull(tc, elem);
	  elem = ntree_lookup(&root, "office.hall", ntree, NTREE_COMPARE, NULL);
	  CuAssertPtrEquals(tc, NULL, elem);
	  elem = ntree_lookup(&root, "office.hall.coffee", ntree, NTREE_COMPARE, NULL);
	  CuAssertPtrEquals(tc, NULL, elem);
	  elem = ntree_lookup(&root, "office.desk", ntree, NTREE_COMPARE, NULL);
	  CuAssertPtrNotNull(tc, elem);
  }

static bool	walk_state;
static int prev_value;

static void	ntree_walk_preorder_cb(void *node, void *data)
{
	test_nary_tree_t	*n = (test_nary_tree_t *)node;

	switch (prev_value)
	{
	case -1:
	if (!strcmp(n->key, "office"))
		prev_value++;
	else
		walk_state = false;
	break;

	case 0:
		if (!strcmp(n->key, "desk"))
			prev_value++;
		else
			walk_state = false;
	break;

	case 1:
		if (!strcmp(n->key, "hall"))
			prev_value++;
		else
			walk_state = false;
	break;

	case 2:
		if (!strcmp(n->key, "coffee"))
			prev_value++;
		else
			walk_state = false;
	break;

	case 3:
		if (!strcmp(n->key, "short"))
			prev_value++;
		else
			walk_state = false;
	break;

	case 4:
		if (!strcmp(n->key, "long"))
			prev_value++;
		else
			walk_state = false;
	break;

	case 5:
		if (!strcmp(n->key, "tea"))
			prev_value++;
		else
			walk_state = false;
	break;
	}

}

void Testnary_tree_walk_preorder(CuTest *tc)
  {
	  test_nary_tree_t *root;
	  test_nary_tree_t *elem;
	  bool        ret;

	  root = NULL;
	  ntree_init(root, ntree);
	  elem = malloc(sizeof(*elem));
	  CuAssertPtrNotNull(tc, elem);
	  elem->key = strdup("desk");
	  ret = ntree_insert(&root,"office", elem, ntree, NTREE_COMPARE, NTREE_ADD_NEW_NODE, NULL);
	  CuAssertTrue(tc, ret);
	  elem = malloc(sizeof(*elem));
	  CuAssertPtrNotNull(tc, elem);
	  elem->key = strdup("short");
	  ret = ntree_insert(&root, "office.hall.coffee", elem, ntree, NTREE_COMPARE, NTREE_ADD_NEW_NODE, NULL);
	  CuAssertTrue(tc, ret);
	  elem = malloc(sizeof(*elem));
	  CuAssertPtrNotNull(tc, elem);
	  elem->key = strdup("long");
	  ret = ntree_insert(&root, "office.hall.coffee", elem, ntree, NTREE_COMPARE, NTREE_ADD_NEW_NODE, NULL);
	  CuAssertTrue(tc, ret);
	  elem = malloc(sizeof(*elem));
	  CuAssertPtrNotNull(tc, elem);
	  elem->key = strdup("tea");
	  ret = ntree_insert(&root, "office.hall", elem, ntree, NTREE_COMPARE, NTREE_ADD_NEW_NODE, NULL);
	  CuAssertTrue(tc, ret);
	  prev_value = -1;
	  walk_state = true;
	  ntree_walk_preorder(&root, ntree, ntree_walk_preorder_cb, NULL);
	  CuAssertTrue(tc, walk_state);
  }

static void	ntree_walk_inorder_cb(void *node, void *data)
{
	test_nary_tree_t	*n = (test_nary_tree_t *)node;

	switch (prev_value)
	{
	case -1:
	if (!strcmp(n->key, "desk"))
		prev_value++;
	else
		walk_state = false;
	break;

	case 0:
		if (!strcmp(n->key, "short"))
			prev_value++;
		else
			walk_state = false;
	break;

	case 1:
		if (!strcmp(n->key, "long"))
			prev_value++;
		else
			walk_state = false;
	break;

	case 2:
		if (!strcmp(n->key, "coffee"))
			prev_value++;
		else
			walk_state = false;
	break;

	case 3:
		if (!strcmp(n->key, "tea"))
			prev_value++;
		else
			walk_state = false;
	break;

	case 4:
		if (!strcmp(n->key, "hall"))
			prev_value++;
		else
			walk_state = false;
	break;

	case 5:
		if (!strcmp(n->key, "office"))
			prev_value++;
		else
			walk_state = false;
	break;
	}

}

void Testnary_tree_walk_inorder(CuTest *tc)
  {
	  test_nary_tree_t *root;
	  test_nary_tree_t *elem;
	  bool        ret;

	  root = NULL;
	  ntree_init(root, ntree);
	  elem = malloc(sizeof(*elem));
	  CuAssertPtrNotNull(tc, elem);
	  elem->key = strdup("desk");
	  ret = ntree_insert(&root, "office", elem, ntree, NTREE_COMPARE, NTREE_ADD_NEW_NODE, NULL);
	  CuAssertTrue(tc, ret);
	  elem = malloc(sizeof(*elem));
	  CuAssertPtrNotNull(tc, elem);
	  elem->key = strdup("short");
	  ret = ntree_insert(&root, "office.hall.coffee", elem, ntree, NTREE_COMPARE, NTREE_ADD_NEW_NODE, NULL);
	  CuAssertTrue(tc, ret);
	  elem = malloc(sizeof(*elem));
	  CuAssertPtrNotNull(tc, elem);
	  elem->key = strdup("long");
	  ret = ntree_insert(&root, "office.hall.coffee", elem, ntree, NTREE_COMPARE, NTREE_ADD_NEW_NODE, NULL);
	  CuAssertTrue(tc, ret);
	  elem = malloc(sizeof(*elem));
	  CuAssertPtrNotNull(tc, elem);
	  elem->key = strdup("tea");
	  ret = ntree_insert(&root, "office.hall", elem, ntree, NTREE_COMPARE, NTREE_ADD_NEW_NODE, NULL);
	  CuAssertTrue(tc, ret);
	  prev_value = -1;
	  walk_state = true;
	  ntree_walk_inorder(&root, ntree, ntree_walk_inorder_cb, NULL);
	  CuAssertTrue(tc, walk_state);
  }

static void	ntree_walk_postorder_cb(void *node, void *data)
{
	test_nary_tree_t	*n = (test_nary_tree_t *)node;

	switch (prev_value)
	{
	case -1:
	if (!strcmp(n->key, "long"))
		prev_value++;
	else
		walk_state = false;
	break;

	case 0:
		if (!strcmp(n->key, "short"))
			prev_value++;
		else
			walk_state = false;
	break;

	case 1:
		if (!strcmp(n->key, "tea"))
			prev_value++;
		else
			walk_state = false;
	break;

	case 2:
		if (!strcmp(n->key, "coffee"))
			prev_value++;
		else
			walk_state = false;
	break;

	case 3:
		if (!strcmp(n->key, "hall"))
			prev_value++;
		else
			walk_state = false;
	break;

	case 4:
		if (!strcmp(n->key, "desk"))
			prev_value++;
		else
			walk_state = false;
	break;

	case 5:
		if (!strcmp(n->key, "office"))
			prev_value++;
		else
			walk_state = false;
	break;
	}

}

void Testnary_tree_walk_postorder(CuTest *tc)
  {
	  test_nary_tree_t *root;
	  test_nary_tree_t *elem;
	  bool        ret;

	  root = NULL;
	  ntree_init(root, ntree);
	  elem = malloc(sizeof(*elem));
	  CuAssertPtrNotNull(tc, elem);
	  elem->key = strdup("desk");
	  ret = ntree_insert(&root, "office", elem, ntree, NTREE_COMPARE, NTREE_ADD_NEW_NODE, NULL);
	  CuAssertTrue(tc, ret);
	  elem = malloc(sizeof(*elem));
	  CuAssertPtrNotNull(tc, elem);
	  elem->key = strdup("short");
	  ret = ntree_insert(&root, "office.hall.coffee", elem, ntree, NTREE_COMPARE, NTREE_ADD_NEW_NODE, NULL);
	  CuAssertTrue(tc, ret);
	  elem = malloc(sizeof(*elem));
	  CuAssertPtrNotNull(tc, elem);
	  elem->key = strdup("long");
	  ret = ntree_insert(&root, "office.hall.coffee", elem, ntree, NTREE_COMPARE, NTREE_ADD_NEW_NODE, NULL);
	  CuAssertTrue(tc, ret);
	  elem = malloc(sizeof(*elem));
	  CuAssertPtrNotNull(tc, elem);
	  elem->key = strdup("tea");
	  ret = ntree_insert(&root, "office.hall", elem, ntree, NTREE_COMPARE, NTREE_ADD_NEW_NODE, NULL);
	  CuAssertTrue(tc, ret);
	  prev_value = -1;
	  walk_state = true;
	  ntree_walk_postorder(&root, ntree, ntree_walk_postorder_cb, NULL);
	  CuAssertTrue(tc, walk_state);
  }

void Testnary_tree_graft(CuTest *tc)
  {
	  test_nary_tree_t 	*root1;
	  test_nary_tree_t	*root2;
	  test_nary_tree_t 	*elem;
	  bool        	ret;

	  root1 = NULL;
	  root2 = NULL;
	  elem = malloc(sizeof(*elem));
	  CuAssertPtrNotNull(tc, elem);
	  elem->key = strdup("desk");
	  ret = ntree_insert(&root1, "office", elem, ntree, NTREE_COMPARE, NTREE_ADD_NEW_NODE, NULL);
	  CuAssertTrue(tc, ret);
	  elem = malloc(sizeof(*elem));
	  CuAssertPtrNotNull(tc, elem);
	  elem->key = strdup("coffee");
	  ret = ntree_insert(&root1, "office.hall", elem, ntree, NTREE_COMPARE, NTREE_ADD_NEW_NODE, NULL);
	  CuAssertTrue(tc, ret);
	  elem = malloc(sizeof(*elem));
	  CuAssertPtrNotNull(tc, elem);
	  elem->key = strdup("bed");
	  ret = ntree_insert(&root2, "home.room", elem, ntree, NTREE_COMPARE, NTREE_ADD_NEW_NODE, NULL);
	  CuAssertTrue(tc, ret);
	  elem = ntree_lookup(&root1, "home.room.bed", ntree, NTREE_COMPARE, NULL);
	  CuAssertPtrEquals(tc, NULL, elem);
  }

void Testnary_tree_prune(CuTest *tc)
  {
	  test_nary_tree_t 	*root1;
	  test_nary_tree_t	*root2;
	  test_nary_tree_t 	*elem;
	  bool        	ret;

	  root1 = NULL;
	  root2 = NULL;
	  elem = malloc(sizeof(*elem));
	  CuAssertPtrNotNull(tc, elem);
	  elem->key = strdup("desk");
	  ret = ntree_insert(&root1, "office", elem, ntree, NTREE_COMPARE, NTREE_ADD_NEW_NODE, NULL);
	  CuAssertTrue(tc, ret);
	  elem = malloc(sizeof(*elem));
	  CuAssertPtrNotNull(tc, elem);
	  elem->key = strdup("coffee");
	  ret = ntree_insert(&root1, "office.hall", elem, ntree, NTREE_COMPARE, NTREE_ADD_NEW_NODE, NULL);
	  CuAssertTrue(tc, ret);
	  elem = malloc(sizeof(*elem));
	  CuAssertPtrNotNull(tc, elem);
	  elem->key = strdup("bed");
	  ret = ntree_insert(&root1, "home.room", elem, ntree, NTREE_COMPARE, NTREE_ADD_NEW_NODE, NULL);
	  CuAssertTrue(tc, ret);
	  root2 = ntree_prune(&root1, "home.room", ntree, NTREE_COMPARE, NULL);
	  CuAssertPtrNotNull(tc, root2);
	  elem = ntree_lookup(&root1, "home.room.bed", ntree, NTREE_COMPARE, NULL);
	  CuAssertPtrEquals(tc, NULL, elem);
	  elem = ntree_lookup(&root2, "home.room.bed", ntree, NTREE_COMPARE, NULL);
	  CuAssertPtrEquals(tc, NULL, elem);
	  elem = ntree_lookup(&root2, "room.bed", ntree, NTREE_COMPARE, NULL);
	  CuAssertPtrNotNull(tc, elem);
	  elem = ntree_lookup(&root2, "room", ntree, NTREE_COMPARE, NULL);
	  CuAssertPtrNotNull(tc, elem);
  }
