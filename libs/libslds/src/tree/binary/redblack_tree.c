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

#include    <libslds/tree.h>

#include    "include/avl_rotation.h"

/* Helpers. */

static void *__grandparent(void *node, unsigned int m)
{
    if ((node != NULL) && (GET_FIELD(node, m, redblack_tree_t)->parent != NULL))
        return (GET_FIELD(GET_FIELD(node, m, redblack_tree_t)->parent, m, redblack_tree_t)->parent);
    else
        return (NULL);
}

static void *__uncle(void *node, unsigned int m)
{
    void    *grandpa = __grandparent(node, m);

    if (grandpa == NULL)
      return (NULL);
    if (GET_FIELD(node, m, redblack_tree_t)->parent == GET_FIELD(grandpa, m, redblack_tree_t)->left)
        return GET_FIELD(grandpa, m, redblack_tree_t)->right;
    else
        return GET_FIELD(grandpa, m, redblack_tree_t)->left;
}
//
//static void *__sibling(void *node, unsigned int m)
//{
//  if (node == NULL)
//    return (NULL);
//    if (node == GET_FIELD(GET_FIELD(node, m, redblack_tree_t)->parent, m, redblack_tree_t)->left)
//        return (GET_FIELD(GET_FIELD(node, m, redblack_tree_t)->parent, m, redblack_tree_t)->right);
//    else
//      return (GET_FIELD(GET_FIELD(node, m, redblack_tree_t)->parent, m, redblack_tree_t)->left);
//}

static void __insert_case5(void *node, unsigned int m)
{
  void      *grandpa;
  void      *uncle;
  void      *parent;

  if (node == NULL)
    return;
  grandpa = __grandparent(node, m);
  uncle = __uncle(node, m);
  parent = GET_FIELD(node, m, redblack_tree_t)->parent;
  if (grandpa == NULL || uncle == NULL || parent == NULL)
    return;
  if (GET_FIELD(parent, m, redblack_tree_t)->colour == red
      && GET_FIELD(uncle, m, redblack_tree_t)->colour == black)
  {
    if (node == GET_FIELD(parent, m, redblack_tree_t)->left
        && parent == GET_FIELD(grandpa, m, redblack_tree_t)->left)
    {
      avl_parent_rotate_with_right(grandpa, m);
      GET_FIELD(parent, m, redblack_tree_t)->colour = GET_FIELD(grandpa, m, redblack_tree_t)->colour;
      GET_FIELD(grandpa, m, redblack_tree_t)->colour = red;
    }
    else
    {
      if (node == GET_FIELD(parent, m, redblack_tree_t)->right
          && parent == GET_FIELD(grandpa, m, redblack_tree_t)->right)
      {
        avl_parent_rotate_with_left(grandpa, m);
        GET_FIELD(parent, m, redblack_tree_t)->colour = GET_FIELD(grandpa, m, redblack_tree_t)->colour;
        GET_FIELD(grandpa, m, redblack_tree_t)->colour = red;
      }
    }
  }
}

static void __insert_case4(void *node, unsigned int m)
{
  void  *grandpa;

  if (node == NULL)
    return;
  grandpa = __grandparent(node, m);
  if (grandpa == NULL)
    return;
  if ((node == GET_FIELD(GET_FIELD(node, m, redblack_tree_t)->parent, m, redblack_tree_t)->right)
      && (GET_FIELD(node, m, redblack_tree_t)->parent == GET_FIELD(grandpa, m, redblack_tree_t)->left))
  {
    avl_parent_rotate_with_left(GET_FIELD(node, m, redblack_tree_t)->parent, m);
    node = GET_FIELD(node, m, redblack_tree_t)->left;
  }
  else
  {
    if ((node == GET_FIELD(GET_FIELD(node, m, redblack_tree_t)->parent, m, redblack_tree_t)->left)
        && (GET_FIELD(node, m, redblack_tree_t)->parent == GET_FIELD(grandpa, m, redblack_tree_t)->right))
    {
      avl_parent_rotate_with_right(GET_FIELD(node, m, redblack_tree_t)->parent, m);
      node = GET_FIELD(node, m, redblack_tree_t)->right;
    }
  else
    __insert_case5(node, m);
  }
}

static void __insert_case1(void *node, unsigned int m);

static void __insert_case3(void *node, unsigned int m)
{
    void    *uncle;
    void    *grandpa;

    if (node == NULL)
      return;
    uncle = __uncle(node, m);
    grandpa = NULL;
    if ((uncle != NULL) && (GET_FIELD(uncle, m, redblack_tree_t)->colour == red))
    {
        GET_FIELD(GET_FIELD(node, m, redblack_tree_t)->parent, m, redblack_tree_t)->colour = black;
        GET_FIELD(uncle, m, redblack_tree_t)->colour = black;
        grandpa = __grandparent(node, m);
        GET_FIELD(grandpa, m, redblack_tree_t)->colour = red;
        __insert_case1(grandpa, m);
    }
    else
    {
        __insert_case4(node, m);
    }
}

static void __insert_case2(void *node, unsigned int m)
{
  if (node == NULL)
    return;
    if (GET_FIELD(GET_FIELD(node, m, redblack_tree_t)->parent, m, redblack_tree_t)->colour == black)
        return; /* Tree is still valid */
    else
        __insert_case3(node, m);
}

static void __insert_case1(void *node, unsigned int m)
{
  if (node == NULL)
      return;
    if (GET_FIELD(node, m, redblack_tree_t)->parent == NULL)
      GET_FIELD(node, m, redblack_tree_t)->colour = black;
    else
        __insert_case2(node, m);
}

static void __recolor_tree(void **tree, void *node, unsigned int m)
{
  if (tree == NULL || *tree == NULL || node == NULL)
      return;
  GET_FIELD(node, m, redblack_tree_t)->colour = red;
  __insert_case1(node, m);
  while (node != NULL && GET_FIELD(node, m, redblack_tree_t)->parent != NULL)
    node = GET_FIELD(node, m, redblack_tree_t)->parent;
  *tree = node;
}

/* Implementation. */

bool _redblack_tree_insert(void **tree,
                          void *new,
                          unsigned int m,
                          bst_tree_compare_p compare_func)
{
  bool  ret;

  ret = _ebst_tree_insert(tree, new, m, compare_func);
  if (ret == true)
    __recolor_tree(tree, new, m);
  return (ret);
}

void *_redblack_tree_remove(void **tree,
                    void *key,
                    unsigned int m,
                    bst_tree_compare_p compare_func,
                    bst_tree_compare_key_p compare_key_func)
{
  void  *node;
  void  *child;

  /* TODO: We have to check the removal of the redblack tree. I am not convinced that this implementation is right. */
  node = _internal_ebst_tree_remove(tree, key, m, compare_func, compare_key_func, &child);
  if (node != NULL && child != NULL)
    GET_FIELD(child, m, redblack_tree_t)->colour = GET_FIELD(node, m, redblack_tree_t)->colour;
  return (node);
}

bool _redblack_tree_graft(void **tree,
    void *subtree,
    unsigned int m,
    bst_tree_compare_p compare_func)
{
  bool  ret;
  ret = _ebst_tree_graft(tree, subtree, m, compare_func);
  if (ret == true)
    __recolor_tree(tree, subtree, m);
  return (ret);
}

void *_redblack_tree_prune(void **tree,
                   void *key,
                   unsigned int m,
                   bst_tree_compare_key_p compare_key_func)
{
  void  *subtree;

  subtree = _ebst_tree_prune(tree, key, m, compare_key_func);
  if (subtree != NULL)
    GET_FIELD(subtree, m, redblack_tree_t)->colour = black;
  return (subtree);
}
