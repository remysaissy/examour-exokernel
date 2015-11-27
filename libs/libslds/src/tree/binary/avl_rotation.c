/*
 * avl_rotation.c
 *
 *  Created on: 5 déc. 2008
 *      Author: remy
 */

#include <libslds/tree.h>
#include "include/avl_rotation.h"

//Let Q be P's right child.
//Set Q to be the new root.
//Set P's right child to be Q's left child.
//Set Q's left child to be P.

void    *avl_single_rotate_with_left(void *node,
                                     unsigned int m)
{
  void  *tmp;

  tmp = GET_FIELD(node, m, bst_tree_t)->right;
  GET_FIELD(node, m, bst_tree_t)->right = GET_FIELD(tmp, m, bst_tree_t)->left;
  GET_FIELD(tmp, m, bst_tree_t)->left = node;
  return (tmp);
}

void    *avl_single_rotate_with_right(void *node,
                                      unsigned int m)
{
  void  *tmp;

  tmp = GET_FIELD(node, m, bst_tree_t)->left;
  GET_FIELD(node, m, bst_tree_t)->left = GET_FIELD(tmp, m, bst_tree_t)->right;
  GET_FIELD(tmp, m, bst_tree_t)->right = node;
  return (tmp);
}


void    *avl_parent_rotate_with_left(void *node,
                                     unsigned int m)
{
  void  *tmp;
  void  *parent;

  tmp = GET_FIELD(node, m, ebst_tree_t)->right;
  GET_FIELD(node, m, ebst_tree_t)->right = GET_FIELD(tmp, m, ebst_tree_t)->left;
  if (GET_FIELD(tmp, m, ebst_tree_t)->left != NULL)
    GET_FIELD(GET_FIELD(tmp, m, ebst_tree_t)->left, m, ebst_tree_t)->parent = node;
  GET_FIELD(tmp, m, ebst_tree_t)->left = node;
  parent = GET_FIELD(node, m, ebst_tree_t)->parent;
  GET_FIELD(node, m, ebst_tree_t)->parent = tmp;
  if (parent != NULL)
  {
    if (node == GET_FIELD(parent, m, ebst_tree_t)->left)
    {
     GET_FIELD(parent, m, ebst_tree_t)->left = tmp;
    }
    else
    {
      GET_FIELD(parent, m, ebst_tree_t)->right = tmp;
    }
  }
  GET_FIELD(tmp, m, ebst_tree_t)->parent = parent;
  return (tmp);
}

void    *avl_parent_rotate_with_right(void *node,
                                      unsigned int m)
{
  void  *tmp;
  void  *parent;

  tmp = GET_FIELD(node, m, ebst_tree_t)->left;
  GET_FIELD(node, m, ebst_tree_t)->left = GET_FIELD(tmp, m, ebst_tree_t)->right;
  if (GET_FIELD(tmp, m, ebst_tree_t)->right != NULL)
    GET_FIELD(GET_FIELD(tmp, m, ebst_tree_t)->right, m, ebst_tree_t)->parent = node;
  GET_FIELD(tmp, m, ebst_tree_t)->right = node;
  parent = GET_FIELD(node, m, ebst_tree_t)->parent;
  GET_FIELD(node, m, ebst_tree_t)->parent = tmp;
  if (parent != NULL)
  {
    if (node == GET_FIELD(parent, m, ebst_tree_t)->left)
    {
     GET_FIELD(parent, m, ebst_tree_t)->left = tmp;
    }
    else
    {
      GET_FIELD(parent, m, ebst_tree_t)->right = tmp;
    }
  }
  GET_FIELD(tmp, m, ebst_tree_t)->parent = parent;
  return (tmp);
}
