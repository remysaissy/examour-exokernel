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

#ifndef __LIBSLDS_BINARY_REDBLACK_TREE_H__
#define __LIBSLDS_BINARY_REDBLACK_TREE_H__

/* Splay trees. Bottom-up implementation. */

#include    <stdbool.h>
#include    <libslds/tree.h>

/*
 * Data structure.
 */
typedef struct          redblack_tree_s
{
  void                  *left;
  void                  *right;
  void                  *parent; /** The parent is put after left and right for btree compatible functions. */
  enum { black, red }   colour; /** The colour of the node. */

}                       redblack_tree_t;


/**
 * Initialize a redblack tree node.
 * @param tree The root of the tree.
 * @param m The name of the redblack tree data structure in tree.
 * @return true on success, false on error.
 */
#define redblack_tree_init(tree, m)                     \
    _ebst_tree_init((void *)(tree),                     \
           (unsigned int)offsetof(typeof(*(tree)), m))

/**
 * Look for a node in a redblack tree.
 * @param tree The root of the tree.
 * @param key Key to the node to look for.
 * @param m The name of the redblack tree data structure in tree.
 * @param compare_key_func callback for comparison.
 * @return The node looked up on success, NULL on error.
 */
#define redblack_tree_lookup(tree, key, m, compare_key_func)            \
    _bst_tree_lookup((void **)&(tree),                       \
        (void *)(key),                      \
             (unsigned int)offsetof(typeof(*(tree)), m),    \
             compare_key_func)

/**
 * Insert a redblack tree node.
 * @param tree The root of the tree.
 * @param new The node to be added.
 * @param m The name of the redblack tree data structure in tree.
 * @param compare_func callback for comparison.
 * @return true on success, false on error.
 */
#define redblack_tree_insert(tree, new, m, compare_func)            \
    _redblack_tree_insert((void **)&(tree),                     \
              (void *)(new),                        \
             (unsigned int)offsetof(typeof(*(tree)), m),    \
             compare_func)

/**
 * Remove a redblack tree node.
 * @param tree The root of the tree.
 * @param key Key to the node to be removed.
 * @param m The name of the redblack tree data structure in tree.
 * @param compare_func callback for comparison.
 * @param compare_key_func callback for comparison.
 * @return The node removed on success, NULL on error.
 */
#define redblack_tree_remove(tree, key, m, compare_func, compare_key_func)  \
     _redblack_tree_remove((void **)&(tree),                        \
         (void *)(key),                     \
          (unsigned int)offsetof(typeof(*(tree)), m),       \
          compare_func,                     \
          compare_key_func)

/**
 * Graft a suredblack_tree in a redblack tree.
 * @param tree The root of the tree.
 * @param suredblack_tree suredblack_tree to be graft.
 * @param m The name of the redblack tree data structure in tree.
 * @param compare_func callback for comparison.
 * @return true on success, false on error.
 * @note A suredblack_tree that has nodes which are also in tree can be grafted.
 * this preliminary control is left to the caller.
 */
#define redblack_tree_graft(tree, suredblack_tree, m, compare_func)         \
    _redblack_tree_graft((void **)&(tree),                      \
        (void *)(suredblack_tree),                      \
             (unsigned int)offsetof(typeof(*(tree)), m),    \
             compare_func)

/**
 * Prune a redblack tree.
 * @param tree The root of the tree.
 * @param key key of the part of the tree to be pruned.
 * @param m The name of the redblack tree data structure in tree.
 * @param compare_key_func callback for comparison.
 * @return The suredblack_tree on success, NULL on error.
 */
#define redblack_tree_prune(tree, key, m, compare_key_func)         \
    _redblack_tree_prune((void **)&(tree),                      \
        (void *)(key),                      \
             (unsigned int)offsetof(typeof(*(tree)), m),    \
             compare_key_func)

/**
 * Step along the tree in a pre-order fashion.
 * @param tree The root of the tree.
 * @param m The name of the redblack tree data structure in tree.
 * @param walk_func Callback used like an iterator. Called for every nodes.
 * @param data arbitrary data for callbacks.
 */
#define redblack_tree_walk_preorder(tree, m, walk_func, data)                       \
        _bst_tree_walk_preorder((void **)&(tree),                                \
                            (unsigned int)offsetof(typeof(*(tree)), m), \
                            walk_func,                                      \
                            (void *)(data))

/**
 * Step along the tree in a in-order fashion.
 * @param tree The root of the tree.
 * @param m The name of the redblack tree data structure in tree.
 * @param walk_func Callback used like an iterator. Called for every nodes.
 * @param data arbitrary data for callbacks.
 */
#define redblack_tree_walk_inorder(tree, m, walk_func, data)                        \
        _bst_tree_walk_inorder((void **)&(tree),                             \
                            (unsigned int)offsetof(typeof(*(tree)), m), \
                            walk_func,                                      \
                            (void *)(data))

/**
 * Step along the tree in a post-order fashion.
 * @param tree The root of the tree.
 * @param m The name of the redblack tree data structure in tree.
 * @param walk_func Callback used like an iterator. Called for every nodes.
 * @param data arbitrary data for callbacks.
 */
#define redblack_tree_walk_postorder(tree, m, walk_func, data)                      \
        _bst_tree_walk_postorder((void **)&(tree),                       \
                            (unsigned int)offsetof(typeof(*(tree)), m), \
                            walk_func,                                      \
                            (void *)(data))


/* tree implementation. */

/**
 * Insert a redblack_ tree node.
 * @param tree The root of the tree.
 * @param new The node to be added.
 * @param m The offset of the binary tree data structure in tree.
 * @param compare_func callback for comparison.
 * @return true on success, false on error.
 */
bool    _redblack_tree_insert(void **tree,
              void *new,
              unsigned int m,
              bst_tree_compare_p compare_func);

/**
 * Remove a redblack tree node.
 * @param tree The root of the tree.
 * @param key Key to the node to be removed.
 * @param m The offset of the binary tree data structure in tree.
 * @param compare_func callback for comparison.
 * @param compare_key_func callback for comparison.
 * @return The node removed on success, NULL on error.
 */
void    *_redblack_tree_remove(void **tree,
              void *key,
              unsigned int m,
              bst_tree_compare_p compare_func,
              bst_tree_compare_key_p compare_key_func);

/**
 * Graft a subtree in a redblack tree.
 * @param tree The root of the tree.
 * @param subtree subtree to be graft.
 * @param m The offset of the binary tree data structure in tree.
 * @param compare_func callback for comparison.
 * @return true on success, false on error.
 * @note A subtree that has nodes which are also in tree can be grafted.
 * this preliminary control is left to the caller.
 */
bool    _redblack_tree_graft(void **tree,
             void *subtree,
             unsigned int m,
             bst_tree_compare_p compare_func);

/**
 * Prune a redblack tree.
 * @param tree The root of the tree.
 * @param key key of the part of the tree to be pruned.
 * @param m The offset of the binary tree data structure in tree.
 * @param compare_key_func callback for comparison.
 * @return The subtree on success, NULL on error.
 */
void    *_redblack_tree_prune(void **tree,
             void *key,
             unsigned int m,
             bst_tree_compare_key_p compare_key_func);


#endif /* __LIBSLDS_BINARY_REDBLACK_TREE_H__ */
