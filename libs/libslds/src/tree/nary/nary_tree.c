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

#include  <libslds/tree.h>

bool _ntree_init(void *tree,
		 unsigned int m)
{
  if (tree)
  {
    GET_FIELD(tree, m, ntree_t)->sibling.next = NULL;
    GET_FIELD(tree, m, ntree_t)->child = NULL;
    return (true);
  }
  return (false);
}

bool _ntree_insert(void **tree,
       char *path,
		   void *new,
		   unsigned int m,
		   ntree_compare_p compare_func,
		   ntree_add_node_p add_node_func,
		   void *data)
{
  void *it;
  int ret;
  void *tmp;
  int cnt;

  if (tree == NULL
      || new == NULL
      || compare_func == NULL
      || add_node_func == NULL)
  return (false);
  cnt = 0;
  if (*tree == NULL)
    {
      tmp = add_node_func(path, cnt, data);
      if (tmp == NULL)
      {
        slist_init(GET_FIELD(new, m, ntree_t), sibling);
    	  GET_FIELD(new, m, ntree_t)->child = NULL;
    	  *tree = new;
    	  return (true);
      }
      else
      {
        slist_init(GET_FIELD(tmp, m, ntree_t), sibling);
    	  GET_FIELD(tmp, m, ntree_t)->child = NULL;
    	  *tree = tmp;
      }
    }
    it = *tree;
    while (it)
    {
      ret = compare_func(it, path, &cnt, data);
      if (ret)
      {
        if (GET_FIELD(it, m, ntree_t)->child == NULL)
        {
          tmp = add_node_func(path, cnt, data);
          if (tmp == NULL)
          {
            slist_init(GET_FIELD(new, m, ntree_t), sibling);
            GET_FIELD(new, m, ntree_t)->child = NULL;
            GET_FIELD(it, m, ntree_t)->child = new;
            return (true);
          }
          else
          {
            slist_init(GET_FIELD(tmp, m, ntree_t), sibling);
            GET_FIELD(tmp, m, ntree_t)->child = NULL;
            GET_FIELD(it, m, ntree_t)->child = tmp;
          }
        }
        it = GET_FIELD(it, m, ntree_t)->child;
      }
      else
      {
        if (GET_FIELD(it, m, ntree_t)->sibling.next == NULL)
        {
          tmp = add_node_func(path, cnt, data);
          if (tmp == NULL)
          {
            slist_init(GET_FIELD(new, m, ntree_t), sibling);
            GET_FIELD(new, m, ntree_t)->child = NULL;
            _slist_add_after(tree, it, new, m);
            return (true);
          }
          else
          {
            slist_init(GET_FIELD(tmp, m, ntree_t), sibling);
            GET_FIELD(tmp, m, ntree_t)->child = NULL;
            _slist_add_after(tree, it, tmp, m);

          }
        }
        it = GET_FIELD(it, m, ntree_t)->sibling.next;
      }
    }
  return (false);
}

static void	__deep_remove(void *node, ntree_remove_node_p remove_node_func, void *data, unsigned int m)
{
	if (node)
	{
		__deep_remove(GET_FIELD(node, m, ntree_t)->child, remove_node_func, data, m);
		__deep_remove(GET_FIELD(node, m, ntree_t)->sibling.next, remove_node_func, data, m);
		remove_node_func(node, data);
	}
}

void *_ntree_remove(void **tree,
                    void *key,
                    unsigned int m,
                    ntree_compare_p compare_func,
                    ntree_remove_node_p	remove_node_func,
                    void *data)
{
  void *it;
  void	*parent;
  void  *prev_sibling;
  int ret;
  int cnt;

  if (tree == NULL
		  || *tree == NULL
		  || compare_func == NULL
		  || key == NULL)
	    return (NULL);
    cnt = 0;
	  it = *tree;
	  parent = NULL;
	  prev_sibling = NULL;
	  while (it)
	  {
	    ret = compare_func(it, key, &cnt, data);
	    if (ret == 1)
	    {
	          parent = it;
	          prev_sibling = NULL;
	          it = GET_FIELD(it, m, ntree_t)->child;
	    }
	    else if (ret == 0)
	    {
	      prev_sibling = it;
	      it = GET_FIELD(it, m, ntree_t)->sibling.next;
	    }
	    else
	    {
        if (prev_sibling == NULL)
        {
          // That node is the first of its sibling list.
          if (parent != NULL)
            GET_FIELD(parent, m, ntree_t)->child = GET_FIELD(it, m, ntree_t)->sibling.next;
          GET_FIELD(it, m, ntree_t)->sibling.next = NULL;
        }
        else
        {
          // That node is not the first of its sibling list.
          GET_FIELD(prev_sibling, m, ntree_t)->sibling.next = GET_FIELD(it, m, ntree_t)->sibling.next;
          GET_FIELD(it, m, ntree_t)->sibling.next = NULL;
        }
        if (remove_node_func != NULL)
        {
          __deep_remove(GET_FIELD(it, m, ntree_t)->child, remove_node_func, data, m);
          GET_FIELD(it, m, ntree_t)->child = NULL;
        }
        return (it);
	    }
	  }
	  return (NULL);
}

bool _ntree_graft(void **tree,
      char *path,
		  void *subtree,
		  unsigned int m,
		  ntree_compare_p compare_func,
		  ntree_add_node_p add_node_func,
		  void *data)
{
	  void *it;
	  int ret;
	  void *tmp;
	  int  cnt;

	  if (tree == NULL
		  || *tree == NULL
	      || subtree == NULL
	      || compare_func == NULL
	      || add_node_func == NULL)
		  return (false);
	  it = *tree;
	  cnt = 0;
	  while (it)
	    {
	      ret = compare_func(it, path, &cnt, data);
	      if (ret == 0)
	      {
		        if (GET_FIELD(it, m, ntree_t)->sibling.next == NULL)
		        {
		          tmp = add_node_func(path, cnt, data);
		          if (tmp == NULL)
		          {
		        	  _slist_add_after(tree, it, subtree, m);
			          return (true);
		          }
		          else
		          {
		            slist_init(GET_FIELD(tmp, m, ntree_t), sibling);
			            GET_FIELD(tmp, m, ntree_t)->child = NULL;
			        	_slist_add_after(tree, it, tmp, m);
		          }
		        }
		        it = GET_FIELD(it, m, ntree_t)->sibling.next;
	      }
	      else if (ret == 1)
	      {
		        if (GET_FIELD(it, m, ntree_t)->child == NULL)
		        {
		          tmp = add_node_func(path, cnt, data);
		          if (tmp == NULL)
		          {
			          GET_FIELD(it, m, ntree_t)->child = subtree;
			          return (true);
		          }
		          else
		          {
		            slist_init(GET_FIELD(tmp, m, ntree_t), sibling);
			          GET_FIELD(tmp, m, ntree_t)->child = NULL;
			          GET_FIELD(it, m, ntree_t)->child = tmp;
		          }
		        }
	        	it = GET_FIELD(it, m, ntree_t)->child;
	      }
	      else
	        return (false);
	    }
	  return (false);
}

void *_ntree_prune(void **tree,
                   void *key,
                   unsigned int m,
                   ntree_compare_p compare_func,
                   void *data)
{
	  void *it;
	  void	*parent;
	  void  *prev_sibling;
	  int   ret;
	  int    cnt;

	  if (tree == NULL
			  || *tree == NULL
			  || compare_func == NULL
			  || key == NULL)
		    return (NULL);
		  it = *tree;
		  cnt = 0;
		  parent = NULL;
		  prev_sibling = NULL;
		  while (it)
		  {
		    ret = compare_func(it, key, &cnt, data);
		    if (ret == 0)
		    {
		      prev_sibling = it;
		      it = GET_FIELD(it, m, ntree_t)->sibling.next;
		    }
		    else if (ret == 1)
		    {
		    	  parent = it;
		    	  prev_sibling = NULL;
		        it = GET_FIELD(it, m, ntree_t)->child;
		    }
		    else
		      {
            if (prev_sibling == NULL)
            {
              // That node is the first of its sibling list.
              if (parent != NULL)
                GET_FIELD(parent, m, ntree_t)->child = GET_FIELD(it, m, ntree_t)->sibling.next;
              GET_FIELD(it, m, ntree_t)->sibling.next = NULL;
            }
            else
            {
              // That node is not the first of its sibling list.
              GET_FIELD(prev_sibling, m, ntree_t)->sibling.next = GET_FIELD(it, m, ntree_t)->sibling.next;
              GET_FIELD(it, m, ntree_t)->sibling.next = NULL;
            }
            return (it);
		      }
		    }
		  return (NULL);
}

void  _ntree_walk_preorder(void **tree,
              unsigned int m,
              ntree_walk_p walk_func,
              void *data)
{
  if (tree == NULL
    || *tree == NULL
    || walk_func == NULL)
    return;
	walk_func(*tree, data);
	_ntree_walk_preorder(&GET_FIELD(*tree, m, ntree_t)->child, m, walk_func, data);
	_ntree_walk_preorder(&GET_FIELD(*tree, m, ntree_t)->sibling.next, m, walk_func, data);
}

void  _ntree_walk_inorder(void **tree,
              unsigned int m,
              ntree_walk_p walk_func,
              void *data)
{
  if (tree == NULL
    || *tree == NULL
    || walk_func == NULL)
    return;
	_ntree_walk_inorder(&GET_FIELD(*tree, m, ntree_t)->child, m, walk_func, data);
	walk_func(*tree, data);
	_ntree_walk_inorder(&GET_FIELD(*tree, m, ntree_t)->sibling.next, m, walk_func, data);
}

void  _ntree_walk_postorder(void **tree,
              unsigned int m,
              ntree_walk_p walk_func,
              void *data)
{
  if (tree == NULL
    || *tree == NULL
    || walk_func == NULL)
    return;
	_ntree_walk_postorder(&GET_FIELD(*tree, m, ntree_t)->child, m, walk_func, data);
	_ntree_walk_postorder(&GET_FIELD(*tree, m, ntree_t)->sibling.next, m, walk_func, data);
	walk_func(*tree, data);
}

void *_ntree_lookup(void **tree,
                    void *key,
                    unsigned int m,
                    ntree_compare_p compare_func,
                    void *data)
{
  void *it;
  int ret;
  int cnt;

  if (tree == NULL || *tree == NULL || compare_func == NULL)
    return (NULL);
  it = *tree;
  cnt = 0;
  while (it)
  {
    ret = compare_func(it, key, &cnt, data);
    if (ret == 0)
    {
      it = GET_FIELD(it, m, ntree_t)->sibling.next;
    }
    else if (ret == 1)
    {
      it = GET_FIELD(it, m, ntree_t)->child;
    }
    else
      return (it);
  }
  return (NULL);
}
