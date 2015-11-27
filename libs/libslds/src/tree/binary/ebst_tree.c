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


bool _ebst_tree_init(void *tree,
    unsigned int m)
{
  if (tree)
  {
    GET_FIELD(tree, m, ebst_tree_t)->left = NULL;
    GET_FIELD(tree, m, ebst_tree_t)->right = NULL;
    GET_FIELD(tree, m, ebst_tree_t)->parent = NULL;
    return (true);
  }
  return (false);
}

bool _ebst_tree_insert(void **tree,
    void *new,
    unsigned int m,
    bst_tree_compare_p compare_func)
{
  void *it;
  int ret;

  if (tree == NULL
      || new == NULL
      || compare_func == NULL)
  return (false);
  GET_FIELD(new, m, ebst_tree_t)->left = NULL;
  GET_FIELD(new, m, ebst_tree_t)->right = NULL;
  GET_FIELD(new, m, ebst_tree_t)->parent = NULL;
  if (*tree == NULL)
  {
    *tree = new;
  }
  else
  {
    it = *tree;
    while (1)
    {
      ret = compare_func(it, new);
      switch (ret)
      {
        case BST_TREE_LEFT:
          if (GET_FIELD(it, m, ebst_tree_t)->left == NULL)
          {
            GET_FIELD(it, m, ebst_tree_t)->left = new;
            GET_FIELD(new, m, ebst_tree_t)->parent = it;
            return (true);
          }
          else
            it = GET_FIELD(it, m, ebst_tree_t)->left;
          break;
        case BST_TREE_RIGHT:
          if (GET_FIELD(it, m, ebst_tree_t)->right == NULL)
          {
            GET_FIELD(it, m, ebst_tree_t)->right = new;
            GET_FIELD(new, m, ebst_tree_t)->parent = it;
            return (true);
          }
          else
            it = GET_FIELD(it, m, ebst_tree_t)->right;
          break;
        case BST_TREE_MATCH:
          return (false);
      }
    }
  }
  return (true);
}

void *_ebst_tree_remove(void **tree,
                    void *key,
                    unsigned int m,
                    bst_tree_compare_p compare_func,
                    bst_tree_compare_key_p compare_key_func)
{
  return (_internal_ebst_tree_remove(tree, key, m, compare_func, compare_key_func, NULL));
}


void *_internal_ebst_tree_remove(void **tree,
                    void *key,
                    unsigned int m,
                    bst_tree_compare_p compare_func,
                    bst_tree_compare_key_p compare_key_func,
                    void **replacing_node)
{
  void *left_prev;
  void *right_prev;
  void *it;
  void *parent;
  void *node;
  int ret;

  if (tree == NULL
      || *tree == NULL
      || compare_func == NULL
      || compare_key_func == NULL)
    return (NULL);
  it = *tree;
  left_prev = NULL;
  right_prev = NULL;
  while (it)
  {
    ret = compare_key_func(it, key);
    switch (ret)
    {
      case BST_TREE_LEFT:
        left_prev = it;
        right_prev = NULL;
        it = GET_FIELD(it, m, ebst_tree_t)->left;
        break;
      case BST_TREE_RIGHT:
        left_prev = NULL;
        right_prev = it;
        it = GET_FIELD(it, m, ebst_tree_t)->right;
        break;
      case BST_TREE_MATCH:
        node = NULL;
        if (GET_FIELD(it, m, ebst_tree_t)->left == NULL
            && GET_FIELD(it, m, ebst_tree_t)->right == NULL
            && GET_FIELD(it, m, ebst_tree_t)->parent == NULL)
          *tree = NULL;
        else
        {
          if (GET_FIELD(it, m, ebst_tree_t)->right != NULL)
          {
            /* Get the deepest node on the left of the right child. */

            node = GET_FIELD(it, m, ebst_tree_t)->right;
            while (GET_FIELD(node, m, ebst_tree_t)->left != NULL)
              node = GET_FIELD(node, m, ebst_tree_t)->left;
            if (GET_FIELD(node, m, ebst_tree_t)->parent != it)
            {
              parent = GET_FIELD(node, m, ebst_tree_t)->parent;
              GET_FIELD(parent, m, ebst_tree_t)->left = GET_FIELD(node, m, ebst_tree_t)->right;
              if (GET_FIELD(node, m, ebst_tree_t)->right != NULL)
                GET_FIELD(GET_FIELD(node, m, ebst_tree_t)->right, m, ebst_tree_t)->parent = parent;
              GET_FIELD(node, m, ebst_tree_t)->right = GET_FIELD(it, m, ebst_tree_t)->right;
              GET_FIELD(GET_FIELD(it, m, ebst_tree_t)->right, m, ebst_tree_t)->parent = node;
            }
            GET_FIELD(node, m, ebst_tree_t)->left = GET_FIELD(it, m, ebst_tree_t)->left;
            if (GET_FIELD(it, m, ebst_tree_t)->left != NULL)
              GET_FIELD(GET_FIELD(it, m, ebst_tree_t)->left, m, ebst_tree_t)->parent = node;
          }
          else
          {
            if (GET_FIELD(it, m, ebst_tree_t)->left != NULL)
            {
              /* Get the deepest node on the right of the left child. */

              node = GET_FIELD(it, m, ebst_tree_t)->left;
              while (GET_FIELD(node, m, ebst_tree_t)->right != NULL)
                node = GET_FIELD(node, m, ebst_tree_t)->right;
              if (GET_FIELD(node, m, ebst_tree_t)->parent != it)
              {
                parent = GET_FIELD(node, m, ebst_tree_t)->parent;
                GET_FIELD(parent, m, ebst_tree_t)->right = GET_FIELD(node, m, ebst_tree_t)->left;
                if (GET_FIELD(node, m, ebst_tree_t)->left != NULL)
                  GET_FIELD(GET_FIELD(node, m, ebst_tree_t)->left, m, ebst_tree_t)->parent = parent;
                GET_FIELD(node, m, ebst_tree_t)->left = GET_FIELD(it, m, ebst_tree_t)->left;
                GET_FIELD(GET_FIELD(it, m, ebst_tree_t)->left, m, ebst_tree_t)->parent = node;
              }
              GET_FIELD(node, m, ebst_tree_t)->right = GET_FIELD(it, m, ebst_tree_t)->right;
              if (GET_FIELD(it, m, ebst_tree_t)->right != NULL)
                GET_FIELD(GET_FIELD(it, m, ebst_tree_t)->right, m, ebst_tree_t)->parent = node;
            }
          }
          if (left_prev != NULL)
          {
            GET_FIELD(left_prev, m, ebst_tree_t)->left = node;
            if (node != NULL)
              GET_FIELD(node, m, ebst_tree_t)->parent = left_prev;
          }
          else
          {
            if (right_prev != NULL)
            {
              GET_FIELD(right_prev, m, ebst_tree_t)->right = node;
              if (node != NULL)
                GET_FIELD(node, m, ebst_tree_t)->parent = right_prev;
            }
            else
              *tree = node;
          }
        }
        if (replacing_node != NULL)
          *replacing_node = node;
        return (it);
    }
  }
  return (NULL);
}

bool _ebst_tree_graft(void **tree,
    void *subtree,
    unsigned int m,
    bst_tree_compare_p compare_func)
{
  void *it;
  int ret;
  void *left_prev;
  void *right_prev;

  if (tree == NULL
      || *tree == NULL
      || subtree == NULL
      || compare_func == NULL)
  return (false);

  it = *tree;
  left_prev = NULL;
  right_prev = NULL;
  while (it)
  {
    ret = compare_func(it, subtree);
    switch (ret)
    {
      case BST_TREE_LEFT:
      left_prev = it;
      right_prev = NULL;
      it = GET_FIELD(it, m, ebst_tree_t)->left;
      break;
      case BST_TREE_RIGHT:
      left_prev = NULL;
      right_prev = it;
      it = GET_FIELD(it, m, ebst_tree_t)->right;
      break;
      case BST_TREE_MATCH:
      return (false);
    }
  }
  if (left_prev != NULL)
  {
    GET_FIELD(left_prev, m, ebst_tree_t)->left = subtree;
    GET_FIELD(subtree, m, ebst_tree_t)->parent = left_prev;
  }
  else
  {
    if (right_prev != NULL)
    {
      GET_FIELD(right_prev, m, ebst_tree_t)->right = subtree;
      GET_FIELD(subtree, m, ebst_tree_t)->parent = right_prev;
    }
    else
    *tree = subtree;
  }
  return (true);
}

void *_ebst_tree_prune(void **tree,
                   void *key,
                   unsigned int m,
                   bst_tree_compare_key_p compare_key_func)
{
  void *it;
  void *left_prev;
  void *right_prev;
  int ret;

  if (tree == NULL || *tree == NULL || compare_key_func == NULL)
    return (NULL);
  it = *tree;
  left_prev = NULL;
  right_prev = NULL;
  while (it)
  {
    ret = compare_key_func(it, key);
    switch (ret)
    {
      case BST_TREE_LEFT:
        left_prev = it;
        right_prev = NULL;
        it = GET_FIELD(it, m, ebst_tree_t)->left;
        break;
      case BST_TREE_RIGHT:
        left_prev = NULL;
        right_prev = it;
        it = GET_FIELD(it, m, ebst_tree_t)->right;
        break;
      case BST_TREE_MATCH:
        if (left_prev != NULL)
          GET_FIELD(left_prev, m, ebst_tree_t)->left = NULL;
        else
        {
          if (right_prev != NULL)
            GET_FIELD(right_prev, m, ebst_tree_t)->right = NULL;
          else
            *tree = NULL;
        }
        GET_FIELD(it, m, ebst_tree_t)->parent = NULL;
        return (it);
    }
  }
  return (NULL);
}
