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

#ifndef __LIBSLDS_TREE_H__
#error  "Direct inclusion not allowed. Please include tree.h instead."
#endif

#ifndef __LIBSLDS_NARY_TREE_H__
#define __LIBSLDS_NARY_TREE_H__

/**
 * This header implements nary search trees.
 * In order to be flexible, the key lookup line is
 * left to the caller through a macro so it can be
 * set and unset at will.
 */

#include  <libslds/list.h>

/* Data type. */

/**
 * Comparison callback. This callback is used to compare a node with a key.
 * @param tree_node The node of the tree. Typically, this node is different from one call to another.
 * @param path The path to compare with tree_node.
 * @param iterator The position in the path.
 * @param data variable and optional parameter that can be used by the callback content. Typically used to locate the comparison state.
 * @return Where the caller must go next: 0==sibling, 1==match (go child), 2==match (end of path reached).
 */
typedef int (*ntree_compare_p)(void *tree_node, void *path, int *iterator, void *data);

/**
 * Walk along the tree callback. It is used like an iterator.
 * @param node The node of the tree.
 * @param data variable and optional parameter that can be used by the callback content. Typically used to locate the comparison state.
 */
typedef void            (*ntree_walk_p)(void *node, void *data);

/**
 * Add a new node callback. Used when it is needed to insert missing nodes before reaching the end of the path.
 * @param node The node we want to insert in the tree.
 * @param data variable and optional parameter that can be used by the callback content. Typically used to locate the comparison state.
 * @return The new node to add. If a NULL pointer is returned, it means that the caller can add node to the tree and ends.
 */
typedef void            *(*ntree_add_node_p)(void *path, int iterator, void *data);

/**
 * Remove a node callback. Used when it is needed to remove children nodes in an ntree_remove. It is an optional parameter.
 * @param node The node we want to remove from the tree.
 * @param data variable and optional parameter that can be used by the callback content. Typically used to locate the comparison state.
 */
typedef void			(*ntree_remove_node_p)(void *node, void *data);


/**
 * The ntree datastructure.
 */
typedef struct  ntree_s
{
  slist_t sibling;
  void  *child;

}   ntree_t;


/* Implementation. */

/**
 * Initialize an ntree node.
 * @param tree The root of the tree.
 * @param m The name of the ntree datastructure in tree.
 * @return true on success, false on error.
 */
#define ntree_init(tree, m)           \
  _ntree_init((void **)(tree),            \
       (unsigned int)offsetof(typeof(*(tree)), m))

/**
 * Insert an ntree node.
 * @param tree The root of the tree.
 * @param new The node to be added.
 * @param m The name of the ntree datastructure in tree.
 * @param compare_func callback for comparison.
 * @param add_node_func callback for adding new nodes along the way.
 * @param data arbitrary data for callbacks.
 * @return true on success, false on error.
 */
#define ntree_insert(tree, path, new, m, compare_func, add_node_func, data)      \
  _ntree_insert((void **)(tree),            \
          (void *)(path), \
      (void *)(new),            \
         (unsigned int)offsetof(typeof(**(tree)), m), \
         compare_func, \
         add_node_func, \
  		(void *)data)

/**
 * Remove an ntree node.
 * @param tree The root of the tree.
 * @param key Key to the node to be removed.
 * @param m The name of the ntree datastructure in tree.
 * @param compare_func callback for comparison.
 * @param remove_node_func callback for removing children nodes once key has been found.
 * @param data arbitrary data for callbacks.
 * @return The node removed on success, NULL on error.
 */
#define ntree_remove(tree, key, m, compare_func, remove_node_func, data)  \
     _ntree_remove((void **)(tree),           \
         (void *)(key),           \
      (unsigned int)offsetof(typeof(**(tree)), m),    \
      compare_func, \
      remove_node_func, \
	(void *)(data))

/**
 * Look for a node in an ntree.
 * @param tree The root of the tree.
 * @param key Key to the node to look for.
 * @param m The name of the ntree datastructure in tree.
 * @param compare_func callback for comparison.
 * @param data arbitrary data for callbacks.
 * @return The node looked up on success, NULL on error.
 */
#define ntree_lookup(tree, key, m, compare_func, data)      \
  _ntree_lookup((void **)(tree),            \
      (void *)(key),            \
         (unsigned int)offsetof(typeof(**(tree)), m), \
         compare_func, \
	(void *)(data))

/**
 * Graft a subtree in an ntree.
 * @param tree The root of the tree.
 * @param subtree subtree to be graft.
 * @param m The name of the ntree datastructure in tree.
 * @param compare_func callback for comparison.
 * @param add_node_func callback for adding nodes.
 * @param data arbitrary data for callbacks.
 * @return true on success, false on error.
 * @note A subtree that has nodes which are also in tree can be grafted.
 * this preliminary control is left to the caller.
 */
#define ntree_graft(tree, path, subtree, m, compare_func, add_node_func, data)     \
  _ntree_graft((void **)(tree),           \
               (void *)(path), \
      (void *)(subtree),            \
         (unsigned int)offsetof(typeof(**(tree)), m), \
         compare_func, \
         add_node_func, \
	(void *)(data))

/**
 * Prune an ntree.
 * @param tree The root of the tree.
 * @param key key of the part of the tree to be pruned.
 * @param m The name of the ntree datastructure in tree.
 * @param compare_func callback for comparison.
 * @param data arbitrary data for callbacks.
 * @return The subtree on success, NULL on error.
 */
#define ntree_prune(tree, key, m, compare_func, data)     \
  _ntree_prune((void **)(tree),           \
      (void *)(key),            \
         (unsigned int)offsetof(typeof(**(tree)), m), \
         compare_func, \
	(void *)(data))

/**
 * Step along the tree in a preorder fashion.
 * @param tree The root of the tree.
 * @param m The name of the ntree datastructure in tree.
 * @param walk_func Callback used like an iterator. Called for every nodes.
 * @param data arbitrary data for callbacks.
 */
#define ntree_walk_preorder(tree, m, walk_func, data)           \
    _ntree_walk_preorder((void **)(tree),               \
              (unsigned int)offsetof(typeof(**(tree)), m),  \
              walk_func,                    \
              (void *)(data))

/**
 * Step along the tree in a inorder fashion.
 * @param tree The root of the tree.
 * @param m The name of the ntree datastructure in tree.
 * @param walk_func Callback used like an iterator. Called for every nodes.
 * @param data arbitrary data for callbacks.
 */
#define ntree_walk_inorder(tree, m, walk_func, data)            \
    _ntree_walk_inorder((void **)(tree),                \
              (unsigned int)offsetof(typeof(**(tree)), m),  \
              walk_func,                    \
              (void *)(data))

/**
 * Step along the tree in a postorder fashion.
 * @param tree The root of the tree.
 * @param m The name of the ntree datastructure in tree.
 * @param walk_func Callback used like an iterator. Called for every nodes.
 * @param data arbitrary data for callbacks.
 */
#define ntree_walk_postorder(tree, m, walk_func, data)            \
    _ntree_walk_postorder((void **)(tree),            \
              (unsigned int)offsetof(typeof(**(tree)), m),  \
              walk_func,                    \
              (void *)(data))


/* tree implementation. */

/**
 * Initialize an ntree node.
 * @param tree The root of the tree.
 * @param m The offset of the ntree datastructure in tree.
 * @return true on success, false on error.
 */
bool  _ntree_init(void *tree,
        unsigned int m);

/**
 * Insert an ntree node.
 * @param tree The root of the tree.
 * @param new The node to be added.
 * @param m The offset of the ntree datastructure in tree.
 * @param compare_func callback for comparison.
 * @param add_node_func callback for adding new nodes along the way.
 * @param data arbitrary data for callbacks.
 * @return true on success, false on error.
 */
bool  _ntree_insert(void **tree,
          char *path,
          void *new,
          unsigned int m,
          ntree_compare_p compare_func,
          ntree_add_node_p add_node_func,
          void *data);

/**
 * Remove an ntree node.
 * @param tree The root of the tree.
 * @param key Key to the node to be removed.
 * @param m The offset of the ntree datastructure in tree.
 * @param compare_func callback for comparison.
 * @param remove_node_func callback for removing children nodes once key has been found.
 * @param data arbitrary data for callbacks.
 * @return The node removed on success, NULL on error.
 */
void  *_ntree_remove(void **tree,
          void *key,
          unsigned int m,
          ntree_compare_p compare_func,
          ntree_remove_node_p remove_node_func,
          void *data);

/**
 * Look for a node in an ntree.
 * @param tree The root of the tree.
 * @param key Key to the node to look for.
 * @param m The offset of the ntree datastructure in tree.
 * @param compare_func callback for comparison.
 * @param data arbitrary data for callbacks.
 * @return The node looked up on success, NULL on error.
 */
void  *_ntree_lookup(void **tree,
			 void *key,
			 unsigned int m,
			 ntree_compare_p compare_func,
			 void *data);

/**
 * Graft a subtree in an ntree.
 * @param tree The root of the tree.
 * @param subtree subtree to be graft.
 * @param m The offset of the ntree datastructure in tree.
 * @param compare_func callback for comparison.
 * @param add_node_func callback for adding nodes.
 * @param data arbitrary data for callbacks.
 * @return true on success, false on error.
 * @note A subtree that has nodes which are also in tree can be grafted.
 * this preliminary control is left to the caller.
 */
bool  _ntree_graft(void **tree,
         char *path,
         void *subtree,
         unsigned int m,
         ntree_compare_p compare_func,
         ntree_add_node_p add_node_func,
         void *data);

/**
 * Prune an ntree.
 * @param tree The root of the tree.
 * @param key key of the part of the tree to be pruned.
 * @param m The offset of the ntree datastructure in tree.
 * @param compare_func callback for comparison.
 * @param data arbitrary data for callbacks.
 * @return The subtree on success, NULL on error.
 */
void  *_ntree_prune(void **tree,
         void *key,
         unsigned int m,
         ntree_compare_p compare_func,
         void *data);

/**
 * Step along the tree in a preorder fashion.
 * @param tree The root of the tree.
 * @param m The offset of the ntree datastructure in tree.
 * @param walk_func Callback used like an iterator. Called for every nodes.
 * @param data arbitrary data for callbacks.
 */
void  _ntree_walk_preorder(void **tree,
			       unsigned int m,
			       ntree_walk_p walk_func,
			       void *data);

/**
 * Step along the tree in an inorder fashion.
 * @param tree The root of the tree.
 * @param m The offset of the ntree datastructure in tree.
 * @param walk_func Callback used like an iterator. Called for every nodes.
 * @param data arbitrary data for callbacks.
 */
void  _ntree_walk_inorder(void **tree,
			      unsigned int m,
			      ntree_walk_p walk_func,
			      void *data);

/**
 * Step along the tree in a postorder fashion.
 * @param tree The root of the tree.
 * @param m The offset of the ntree datastructure in tree.
 * @param walk_func Callback used like an iterator. Called for every nodes.
 * @param data arbitrary data for callbacks.
 */
void  _ntree_walk_postorder(void **tree,
				unsigned int m,
				ntree_walk_p walk_func,
				void *data);

#endif /* __LIBSLDS_NARY_TREE_H__ */
