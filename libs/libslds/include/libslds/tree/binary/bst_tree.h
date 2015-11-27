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

#ifndef	__LIBSLDS_TREE_H__
#error	"Direct inclusion not allowed. Please include tree.h instead."
#endif

#ifndef	__LIBSLDS_BINARY_BTREE_H__
#define	__LIBSLDS_BINARY_BTREE_H__

/**
 * This header implements binary search trees.
 * In order to be flexible, the key lookup line is
 * left to the caller through a macro so it can be
 * set and unset at will.
 */

/* Data type. */

/**
 * Enumerator of return values of comparison functions.
 * When evaluating a binary tree node, the result can be
 * to go to the left or to the right child. the comparison
 * also match and, in that case, match is returned.
 */
typedef enum    _bst_tree_compare_e
{
    BST_TREE_LEFT = -1,
    BST_TREE_MATCH,
    BST_TREE_RIGHT

}               bst_tree_compare_e;

/**
 * Comparison callback. This callback is used to compare two nodes.
 * @param tree_node The node of the tree. Typically, this node is different from one call to another.
 * @param node The node used for comparison.
 * @return Where the caller must go next: left or right child or match if the comparison matched.
 */
typedef bst_tree_compare_e (*bst_tree_compare_p)(void *tree_node, void *node);

/**
 * Comparison callback. This callback is used to compare a node and a key.
 * @param tree_node The node of the tree. Typically, this node is different from one call to another.
 * @param key The key to compare with tree_node.
 * @return Where the caller must go next: left or right child or match if the comparison matched.
 */
typedef bst_tree_compare_e (*bst_tree_compare_key_p)(void *tree_node, void *key);

/**
 * Walk along the tree callback. It is used like an iterator.
 * @param node The node of the tree.
 * @param data variable and optional parameter that can be used by the callback content. Typically used to locate the comparison state.
 */
typedef void            (*bst_tree_walk_p)(void *node, void *data);

/**
 * The data structure which represents a binary tree.
 */
typedef struct	bst_tree_s
{
  void          *left;
  void          *right;

}		         bst_tree_t;

/* Implementation. */

/**
 * Initialize a binary tree node.
 * @param tree The root of the tree.
 * @param m The name of the binary tree data structure in tree.
 * @return true on success, false on error.
 */
#define	bst_tree_init(tree, m)						\
	_bst_tree_init((void *)(tree),						\
		   (unsigned int)offsetof(typeof(*(tree)), m))

/**
 * Look for a node in a binary tree.
 * @param tree The root of the tree.
 * @param key Key to the node to look for.
 * @param m The name of the binary tree data structure in tree.
 * @param compare_key_func callback for comparison.
 * @return The node looked up on success, NULL on error.
 */
#define	bst_tree_lookup(tree, key, m, compare_key_func)			\
	_bst_tree_lookup((void **)&(tree),						\
	    (void *)(key),						\
		     (unsigned int)offsetof(typeof(*(tree)), m),	\
		     compare_key_func)

/**
 * Insert a binary tree node.
 * @param tree The root of the tree.
 * @param new The node to be added.
 * @param m The name of the binary tree data structure in tree.
 * @param compare_func callback for comparison.
 * @return true on success, false on error.
 */
#define	bst_tree_insert(tree, new, m, compare_func)			\
	_bst_tree_insert((void **)&(tree),						\
              (void *)(new),						\
		     (unsigned int)offsetof(typeof(*(tree)), m),	\
		     compare_func)

/**
 * Remove a binary tree node.
 * @param tree The root of the tree.
 * @param key Key to the node to be removed.
 * @param m The name of the binary tree data structure in tree.
 * @param compare_func callback for comparison.
 * @param compare_key_func callback for comparison.
 * @return The node removed on success, NULL on error.
 */
#define	bst_tree_remove(tree, key, m, compare_func, compare_key_func)	\
     _bst_tree_remove((void **)&(tree),						\
         (void *)(key),						\
		  (unsigned int)offsetof(typeof(*(tree)), m),		\
		  compare_func,						\
		  compare_key_func)

/**
 * Graft a subtree in a binary tree.
 * @param tree The root of the tree.
 * @param subtree subtree to be graft.
 * @param m The name of the binary tree data structure in tree.
 * @param compare_func callback for comparison.
 * @return true on success, false on error.
 * @note A subtree that has nodes which are also in tree can be grafted.
 * this preliminary control is left to the caller.
 */
#define	bst_tree_graft(tree, subtree, m, compare_func)			\
	_bst_tree_graft((void **)&(tree),						\
	    (void *)(subtree),						\
		     (unsigned int)offsetof(typeof(*(tree)), m),	\
		     compare_func)

/**
 * Prune a binary tree.
 * @param tree The root of the tree.
 * @param key key of the part of the tree to be pruned.
 * @param m The name of the binary tree data structure in tree.
 * @param compare_key_func callback for comparison.
 * @return The subtree on success, NULL on error.
 */
#define	bst_tree_prune(tree, key, m, compare_key_func)			\
	_bst_tree_prune((void **)&(tree),						\
	    (void *)(key),						\
		     (unsigned int)offsetof(typeof(*(tree)), m),	\
		     compare_key_func)

/**
 * Step along the tree in a pre-order fashion.
 * @param tree The root of the tree.
 * @param m The name of the binary tree data structure in tree.
 * @param walk_func Callback used like an iterator. Called for every nodes.
 * @param data arbitrary data for callbacks.
 */
#define	bst_tree_walk_preorder(tree, m, walk_func, data)						\
		_bst_tree_walk_preorder((void **)&(tree),								\
							(unsigned int)offsetof(typeof(*(tree)), m),	\
							walk_func,										\
							(void *)(data))

/**
 * Step along the tree in a in-order fashion.
 * @param tree The root of the tree.
 * @param m The name of the binary tree data structure in tree.
 * @param walk_func Callback used like an iterator. Called for every nodes.
 * @param data arbitrary data for callbacks.
 */
#define	bst_tree_walk_inorder(tree, m, walk_func, data)						\
		_bst_tree_walk_inorder((void **)&(tree),								\
							(unsigned int)offsetof(typeof(*(tree)), m),	\
							walk_func,										\
							(void *)(data))

/**
 * Step along the tree in a post-order fashion.
 * @param tree The root of the tree.
 * @param m The name of the binary tree data structure in tree.
 * @param walk_func Callback used like an iterator. Called for every nodes.
 * @param data arbitrary data for callbacks.
 */
#define	bst_tree_walk_postorder(tree, m, walk_func, data)						\
		_bst_tree_walk_postorder((void **)&(tree),						\
							(unsigned int)offsetof(typeof(*(tree)), m),	\
							walk_func,										\
							(void *)(data))

/* Implementation. */


/**
 * Initialize a binary tree node.
 * @param tree The root of the tree.
 * @param m The offset of the binary tree data structure in tree.
 * @return true on success, false on error.
 */
bool    _bst_tree_init(void *tree,
            unsigned int m);
/**
 * Insert a binary tree node.
 * @param tree The root of the tree.
 * @param new The node to be added.
 * @param m The offset of the binary tree data structure in tree.
 * @param compare_func callback for comparison.
 * @return true on success, false on error.
 */
bool    _bst_tree_insert(void **tree,
              void *new,
              unsigned int m,
              bst_tree_compare_p compare_func);

/**
 * Remove a binary tree node.
 * @param tree The root of the tree.
 * @param key Key to the node to be removed.
 * @param m The offset of the binary tree data structure in tree.
 * @param compare_func callback for comparison.
 * @param compare_key_func callback for comparison.
 * @return The node removed on success, NULL on error.
 */
void    *_bst_tree_remove(void **tree,
              void *key,
              unsigned int m,
              bst_tree_compare_p compare_func,
              bst_tree_compare_key_p compare_key_func);

/**
 * Graft a subtree in a binary tree.
 * @param tree The root of the tree.
 * @param subtree subtree to be graft.
 * @param m The offset of the binary tree data structure in tree.
 * @param compare_func callback for comparison.
 * @return true on success, false on error.
 * @note A subtree that has nodes which are also in tree can be grafted.
 * this preliminary control is left to the caller.
 */
bool    _bst_tree_graft(void **tree,
             void *subtree,
             unsigned int m,
             bst_tree_compare_p compare_func);

/**
 * Prune a binary tree.
 * @param tree The root of the tree.
 * @param key key of the part of the tree to be pruned.
 * @param m The offset of the binary tree data structure in tree.
 * @param compare_key_func callback for comparison.
 * @return The subtree on success, NULL on error.
 */
void    *_bst_tree_prune(void **tree,
             void *key,
             unsigned int m,
             bst_tree_compare_key_p compare_key_func);

/**
 * Look for a node in a binary tree.
 * @param tree The root of the tree.
 * @param key Key to the node to look for.
 * @param m The offset of the binary tree data structure in tree.
 * @param compare_key_func callback for comparison.
 * @return The node looked up on success, NULL on error.
 */
void    *_bst_tree_lookup(void **tree,
               void *key,
               unsigned int m,
               bst_tree_compare_key_p compare_key_func);

/**
 * Step along the tree in a pre-order fashion.
 * @param tree The root of the tree.
 * @param m The offset of the binary tree data structure in tree.
 * @param walk_func Callback used like an iterator. Called for every nodes.
 * @param data arbitrary data for callbacks.
 */
void    _bst_tree_walk_preorder(void **tree,
                            unsigned int m,
                            bst_tree_walk_p walk_func,
                            void *data);

/**
 * Step along the tree in a in-order fashion.
 * @param tree The root of the tree.
 * @param m The offset of the binary tree data structure in tree.
 * @param walk_func Callback used like an iterator. Called for every nodes.
 * @param data arbitrary data for callbacks.
 */
void    _bst_tree_walk_inorder(void **tree,
                            unsigned int m,
                            bst_tree_walk_p walk_func,
                            void *data);

/**
 * Step along the tree in a post-order fashion.
 * @param tree The root of the tree.
 * @param m The offset of the binary tree data structure in tree.
 * @param walk_func Callback used like an iterator. Called for every nodes.
 * @param data arbitrary data for callbacks.
 */
void    _bst_tree_walk_postorder(void **tree,
                            unsigned int m,
                            bst_tree_walk_p walk_func,
                            void *data);

#endif /* __LIBSLDS_BINARY_BTREE_H__ */
