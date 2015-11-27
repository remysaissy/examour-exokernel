/*
** This file is part of exAmour

** Copyright (C) Remy Saissy <remy.saissy@epitech.net>
** exAmour is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 2 of the License, or
** (at your option) any later version.

** exAmour is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.

** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/



/**
 * \file tgfs.c
 * \brief TGFS (Tres Gore File Sytem)
 * \brief   main file, it contains some helper functions and all tgfs functions
 * \brief - helper functions:
 * \brief	memcpy, memset, strdup, ....
 * \brief
 * \brief - tgfs functions:
 * \brief 	-# tg_create_hash: create hash value from name
 * \brief 	-# tg_create_path_str: append 2 string to create a path
 * \brief 	-# tg_add_node_in_list: add a node to a list
 * \brief 	-# tg_add_node: general function to add a node
 * \brief 	-# tg_find_son: find a node with a known name in a list
 * \brief 	-# tg_name_from_path: find a file name from a path
 * \brief 	-# tg_find_node_in_hash: find a node in a hash table with
 * \brief 	-# its name and path
 * \brief 	-# tg_find_node_by_name: find a node in a nodes list with
 * \brief 	-# its name and path
 * \brief 	-# tg_find_node: find a node with its path, parent and/or type
 * \brief 	-# tg_del_in_node_list: delete a node from a node list
 * \brief 	-# tg_del_in_parent: delte a node in its parent list
 * \brief 	-# tg_del_node_from_list: delete all the nodes in a
 * \brief 	list (directory, ...)
 * \brief 	-# tg_del_son_from_list: delete a subnode
 * \brief 	-# tg_del_file_from_list: delete a file node
 * \brief 	-# tg_free_dir: clean a directory datas (clean all subdir/file)
 * \brief 	-# tg_del_node: delete a node
 * \brief 	-# tg_mknode: create a node
 * \brief 	-# tg_del_dir: delete a directory
 * \brief 	-# tg_del_file: delete a file
 * \brief 	-# tg_mkdir: create a directory
 * \brief 	-# tg_mkfile: create a file
 * \brief 	-# tg_mklnk: create a link
 *
 *
 * \brief  - tgfs is a file system where :
 * \brief 	-# all files are in a hash table
 * \brief 	-# all directories are in a hash table
 * \brief 	-# directories separate of file in references
 * \brief 	-# files are "virtualy" in directories.
 * \brief  - due to it structure tgfs need very few operations to get a
 * \brief file/directory (at most 2 hashs keys entries to check: 1 for the file,
 * \brief 1 for it's directory)
 * \brief
 * \brief  - a directory have a reference on it's files/subdirs
 * \brief  - a file have a reference on it's direct parent
 * \brief  - to delete a file, the system only has to delete 2 references
 * \brief (1 in hash 1 in the parent directory)
 * \brief  - to move, the system has to change 1 reference, delete 1, create 1
 * \brief (change parent in the node, delete in the old parent,
 * \brief  creat in the new one)
 */


#include <examour/support/support.h>
#include <examour/mm/mem.h>
#include <stddef.h>
#include "../../video/vga/vga.h"
#include "../../mm/segment/segmentmm.h"
#include <examour/support/string.h>

#include <queue.h>

#include "include/tgfs.h"


#if (TG_HASH_SIZE > 0)
/*
** TODO: find a way to use sizeof(unsigned) and not 4
*/
# if (TG_HASH_SIZE > 4)
#  undef TG_HASH_SIZE
#  define TG_HASH_SIZE 4
# endif
# define TG_HASH_TAB_SIZE (TG_HASH_SIZE * 255)
#else
# define TG_HASH_TAB_SIZE 1
#endif

_tgfs_t		*gl_tgfs_files = 0;
_tgfs_t		*gl_tgfs_dirs = 0;
_tg_node_list_t	gl_tgfs_dirs_hash[TG_HASH_TAB_SIZE] = {{0, }};

raw_spinlock_t	gl_tgfs_lock_dirs_hash = __RAW_SPIN_LOCK_UNLOCKED;
raw_spinlock_t	gl_tgfs_lock_dirs = __RAW_SPIN_LOCK_UNLOCKED;
raw_spinlock_t	gl_tgfs_lock_files = __RAW_SPIN_LOCK_UNLOCKED;

int	ufind(const char *s, char c)
{
  int i = -1;

  if (s)
    while(s[i] && s[i] != c)
      ++i;
  if (!s[i])
    i = -1;
  return (i);
}

int	urfind(const char *s, char c)
{
  int i = -1;
  if (s)
    {
      i = strlen(s);
      
      while(i >= 0 && s[i] != c)
	--i;
    }
  return (i);
}

/**
 * \fn		unsigned tg_create_hash(const char *name)
 * \brief	create hash value from name
 * \param name	string Use this to create the hash
 * \return	hash value
 */
unsigned	tg_create_hash(const char *name)
{
  if (TG_HASH_SIZE)
    {
      unsigned	hash = 0;
      unsigned i = 0;

      for (i = 0; name[i]; i++)
	{
	  unsigned offset = ((i % TG_HASH_SIZE) * 8);

	  hash &= ((name[i] >> offset) & (0xff << offset));
	}
      return (hash);
    }
  return(0);
}

/**
 * \fn		char *tg_create_path_str(const char *s1, const char *s2)
 * \brief	append 2 string to create a path
 * \param s1	1st string
 * \param s2	2nd string
 * \return	The full path (or NULL on error)
 */
char	*tg_create_path_str(const char *s1, const char *s2)
{

  char	*str = NULL;
  unsigned len = 0;
  unsigned len2 = 0;

  if (s1)
    len = strlen(s1);
  if (s2)
    len2 = strlen(s2);
    str = malloc(len + len2 + 2);
  if (s1)
    memcpy(str, s1, len);
  str[len++] = '/';
  if (s2)
    memcpy(str + len, s2, len2);
  str[len + len2 + 1] = 0;
  return (str);
}

/**
 * \fn		static void *tg_add_node_in_list(_tgfs_t *elem,
 				_tg_node_list_t **list_head,
				raw_spinlock_t *lock)
 * \brief	add a node to a list
 * \param elem	node to add
 * \param list	add to this list
 * \param lock	locking system of the list
 * \return	The new node (or NULL on error)
 */
static void	*tg_add_node_in_list(_tgfs_t *elem,
				     _tg_node_list_t **list_head,
				     raw_spinlock_t *lock)
{
  _tg_node_list_t	*new = NULL;

  new = malloc(sizeof(*new));
  if (new)
    {
      new->node = elem;
      __raw_spin_unlock_wait(lock);
      __raw_spin_lock(lock);
      _slist_add_head((void **)list_head, new, 0);
      __raw_spin_unlock(lock);
    }
  return (new);
}
/**
 * \fn		static _tgfs_t *tg_add_node(_tgfs_infos_t *infos, void *datas)
 * \brief	general function to add a node
 * \param infos	node's infos (perm, type, ....)
 * \param datas	node's datas (raw or node list)
 * \return	The new node (or NULL on error)
 */
static _tgfs_t	*tg_add_node(_tgfs_infos_t *infos, void *datas)
{
  _tgfs_t	*new = NULL;

  new = malloc(sizeof(*new));
  if (new)
    {
      new->u_d.datas = datas;
      memcpy(&(new->infos), infos, sizeof(*infos));
      if (IS_FILE(new))
	{
	  __raw_spin_unlock_wait(&gl_tgfs_lock_files);
	  __raw_spin_lock(&gl_tgfs_lock_files);
	  _clist_add_before((void **)&gl_tgfs_files, new, 0);
	  __raw_spin_unlock(&gl_tgfs_lock_files);
	}
      else
	if (IS_DIR(new))
	  {
	    _tg_node_list_t *list_head =
	      &(gl_tgfs_dirs_hash[tg_create_hash(infos->name)]);

	    __raw_spin_unlock_wait(&gl_tgfs_lock_dirs);
	    __raw_spin_lock(&gl_tgfs_lock_dirs);
	    _clist_add_before((void **)&gl_tgfs_dirs, new, 0);
	    __raw_spin_unlock(&gl_tgfs_lock_dirs);
	    tg_add_node_in_list(new,
				&list_head,
				&gl_tgfs_lock_dirs_hash);
	    /*
	    ** TODO: print an error :
	    ** node isn't added to dir hash
	    */
	  }
      if (infos->parent)
	if (!tg_add_node_in_list(new,(_tg_node_list_t **)
				 &(((_tgfs_t*)(new->infos.parent))->u_d.sons),
				 &(((_tgfs_t*)(new->infos.parent))->infos.lock)))
	  {
	    /*
	    ** TODO: print a critical error :
	    ** node isn't added to dir list
	    */
	    free(new);
	    return (0);
	  }
    }
  return(new);
}

/**
 * \fn			static _tgfs_t *tg_find_son(_tg_node_list_t *son_list,
 							const char *name)
 * \brief		find a node with a known name in a list
 * \param son_list	list of node
 * \param name		node to find's name
 * \return		The node (or 0 on error)
 */
static _tgfs_t	*tg_find_son(_tg_node_list_t *son_list, const char *name)
{
  if (son_list)
    {
      _tg_node_list_t *list = son_list;
      char found = 0;

      do
	{
	  if (CHECK_NAME(((_tgfs_t *)(list->node)), name))
	    {
	      found = 1;
	      break;
	    }
	  list = list->next;
	} while (list != son_list);
      if (!found)
	return (0);
      return(son_list->node);
    }
  return (0);
}

/**
 * \fn			char *tg_name_from_path(const char *p,
						char **parent_path)
 * \brief		find a file name from a path
 * \param p		the all path
 * \param parent_path	the path of the parent (if known)
 * \return		The node name (or 0 on error)
 */
char		*tg_name_from_path(const char *p,
				   char **parent_path)
{
  char		*name = 0;
  int		i = -1;

  if (p)
    {
      char	*path = strdup(p);

      if (!path)
	return (0);
      i = urfind(path, '/');
      if (i == strlen(path))
	{
	  /* we delete the last char ('/') and retry */
	  path[i - 1] = 0;
	  i = urfind(path, '/');
	}
      name = strdup(path + i + 1);	// this is ok any time because
					// urfind return -1 if not found
      if (parent_path)
	{
	  char *s;

	  *parent_path = 0;
	  if (i >= 0)
	    {
	      s = strdup(path);
	      if (s)
		{
		  s[i] = 0;
		      *parent_path = strdup(s);
		      if (*parent_path)
			parent_path[0][i] = 0;
		      free(s);
		}
	    }
	}
      free(path);
    }
  return (name);
}


/**
 * \fn		static int check_path(_tgfs_t *node, char *p)
 * \brief	check if the node's path and a given path are the same
 * \param node	the node
 * \param p	the given path
 * \return	1 if root, 0 otherwise
 */
static int	check_path(_tgfs_t *node, char *p)
{
  char *parent_name;
  char *parent_path;

  if (!node || (!p && !HAS_PARENT(node)))
      return (1); //we are on the root
  if (p && HAS_PARENT(node))
    {
      parent_name = tg_name_from_path(p, &parent_path);
      if (!strcmp(parent_name, HAS_NAME((_tgfs_t *)(HAS_PARENT(node)))))
	{
	  if (strlen(parent_path))
	    return (check_path(HAS_PARENT(node), parent_path));
	  else
	    return (1); // we are on the root
	}
    }
  return (0);
}

/**
 * \fn		tg_find_node_in_hash(char *name, char *path,
					      _tg_node_list_t *list)
 * \brief	find a node in a hash table with its name and path
 * \param name	node's name
 * \param path	node's path
 * \param list	hash-list
 * \return	The node (or 0 on error)
 */
static inline _tgfs_t	*tg_find_node_in_hash(char *name, char *path,
					      _tg_node_list_t *list)
{
  _tg_node_list_t *node_list = &(list[tg_create_hash(name)]);


  if (path && !path[0])
    path = 0;
  if (node_list && node_list->node)
    {
      do
	{
	  if (CHECK_NAME(((_tgfs_t *)(node_list->node)), name)
	      && check_path(((_tgfs_t *)(node_list->node)), path) == 1)
	    return ((_tgfs_t *)(node_list->node));
	  node_list = node_list->next;
	} while (node_list != list);
    }
  return(0);
}

/**
 * \fn		static inline _tgfs_t	*tg_find_node_by_name(char *name,
								char *path,
								_tgfs_t *list)
 * \brief	find a node in a nodes list with its name and path
 * \param name	node's name
 * \param path	node's path
 * \param list	nodes-list
 * \return	The node (or 0 on error)
 */
static inline _tgfs_t	*tg_find_node_by_name(char *name, char *path,
					      _tgfs_t *list)
{
  _tgfs_t *node = list;

  if (path && !path[0])
    path = 0;
  do
  {
    if (CHECK_NAME(node, name) && check_path(node, path) == 1)
      return (node);
    node = node->next;
  } while (node != list);
  return(0);
}

/**
 * \fn			_tgfs_t	*tg_find_node(_tgfs_t *parent,const char *p,
						unsigned char type)
 * \brief		find a node with its path, parent and/or type
 * \param parent	node's parent
 * \param p		node's path
 * \param type		node's type
 * \return		The node (or 0 on error)
 */
_tgfs_t		*tg_find_node(_tgfs_t *parent, const char *p,
			      unsigned char type)
{
  char		*path = 0;
  char		*name = tg_name_from_path(p, &path);
  _tgfs_t	*elem = 0;

  if (!name)
    return (elem);
  if (!type)
    type = 255; // all bits set to 1
  if ((type & TG_TYPE_FIL) && gl_tgfs_files)
    {
      if (!parent)
	{
	  if (path && path[0])
	    elem = tg_find_son(GET_SONS_LIST(tg_find_node(0, path, TG_TYPE_DIR)),
			       name);
	  else /* file is on root */
	    elem = tg_find_node_by_name(name, path, gl_tgfs_files);
	}
      else
	elem = tg_find_son(GET_SONS_LIST(parent), name);
    }
  if ((type & TG_TYPE_DIR) && !elem && gl_tgfs_dirs)
    {
      if (!parent)
	{
	  elem = tg_find_node_in_hash(name, path, gl_tgfs_dirs_hash);
	  if (!elem)
	    elem = tg_find_node_by_name(name, path, gl_tgfs_dirs);
	}
      else
	elem = tg_find_son(GET_SONS_LIST(parent), name);
    }
  return (elem);
}

/**
 * \fn		static void *tg_free_file(_tgfs_t *elem)
 * \brief	free the file's datas
 * \param elem	file's node
 * \return	Nothing
 */
static void	*tg_free_file(_tgfs_t *elem)
{
  if (elem->u_d.datas)
    free(elem->u_d.datas);
  return ((void *)1);
}

/**
 * \fn		static void change_parent_size(_tgfs_t *node,
						unsigned long size)
 * \brief	update parent size (when add/del a sub/file)
 * \param node	node to update
 * \param size	size to add
 * \return	Nothing
 */
static void	change_parent_size(_tgfs_t *node, unsigned long size)
{
  __raw_spin_unlock_wait(&(node->infos.lock));
  __raw_spin_lock(&(node->infos.lock));
  HAS_SIZE(node) = HAS_SIZE(node) + size;
  if (HAS_PARENT(node))
    change_parent_size(HAS_PARENT(node), size);
  __raw_spin_unlock(&(node->infos.lock));
}

/**
 * \fn		static unsigned char tg_del_in_node_list(_tgfs_t *elem,
					    _tg_node_list_t **list_head,
					    raw_spinlock_t *lock)
 * \brief	delete a node from a node list
 * \param elem	node to delete
 * \param list	nodes' list
 * \param lock	list's locking system
 * \return	1 on success 0 on error
 */
static unsigned char	tg_del_in_node_list(_tgfs_t *elem,
					    _tg_node_list_t **list_head,
					    raw_spinlock_t *lock)
{
  if (list_head && *list_head)
    {
      _tg_node_list_t *node_list = *list_head;
      _tg_node_list_t *list = *list_head;
      char found = 0;

      do
	{
	  if (list->node == elem)
	    {
	      found = 1;
	      break;
	    }
	  list = list->next;
	} while (list != node_list);
      if (found)
	{
	  __raw_spin_unlock_wait(lock);
	  __raw_spin_lock(lock);
	  _slist_remove((void **)list_head, list, 0);
	  __raw_spin_unlock(lock);
	  free(list);
	  return (1);
	}
    }
  return (0);
}

/**
 * \fn		static unsigned char tg_del_in_parent(_tgfs_t *elem)
 * \brief	delte a node in its parent list
 * \param elem	node
 * \return	1 on success 0 on error
 */
static unsigned char	tg_del_in_parent(_tgfs_t *elem)
{
  _tgfs_t		*parent = 0;

  if (elem)
    {
      parent = HAS_PARENT(elem);
      if (parent)
	{
/* 	  _tg_node_list_t *son_list = GET_SONS_LIST(parent); */
	return(tg_del_in_node_list(elem,
				   ((_tg_node_list_t **)
				    &(((_tgfs_t *)
				       (elem->infos.parent))->u_d.sons)),
				   &(((_tgfs_t *)
				      (elem->infos.parent))->infos.lock)));
	}
    }
  return (0);
}

/**
 * \fn			static unsigned char tg_del_node_from_list(
						_tgfs_t *elem, char is_rec)
 * \brief		delete all the nodes in a list (directory, ...)
 * \param elem		node
 * \param is_rec	a recursion test's flag
 * \return		1 on success 0 on error
 */
static unsigned char	tg_del_node_from_list(_tgfs_t *elem, char is_rec)
{
  if (!(is_rec & TG_REC_DEL))
    {
      __raw_spin_unlock_wait(&(elem->infos.lock));
      __raw_spin_lock(&(elem->infos.lock));
    }
  if (!(elem->infos.free_me(elem)))
    return (0);
  if (HAS_PARENT(elem))
    {
      change_parent_size(HAS_PARENT(elem), -HAS_SIZE(elem));
      if (!tg_del_in_parent(elem))
	{
	  __raw_spin_unlock(&(elem->infos.lock));
	  return (0);
	}
      if (tg_find_son(GET_SONS_LIST(elem->infos.parent), elem->infos.name))
	return (0);
    }
  if (IS_FILE(elem))
    {
      __raw_spin_unlock_wait(&gl_tgfs_lock_files);
      __raw_spin_lock(&gl_tgfs_lock_files);
      _clist_remove((void **)&gl_tgfs_files, elem, 0);
      __raw_spin_unlock(&gl_tgfs_lock_files);
    }
  else
    if (IS_DIR(elem))
      {
	_tg_node_list_t *tmp = gl_tgfs_dirs_hash;

	tg_del_in_node_list(elem, ((_tg_node_list_t **) &tmp),
			    &gl_tgfs_lock_dirs_hash);
	__raw_spin_unlock_wait(&gl_tgfs_lock_dirs);
	__raw_spin_lock(&gl_tgfs_lock_dirs);
	_clist_remove((void **)&gl_tgfs_dirs, elem, 0);
	__raw_spin_unlock(&gl_tgfs_lock_dirs);
      }
  if (elem && elem->infos.name)
    free(elem->infos.name);
  if (elem)
    free(elem);
  return (1);
}

/**
 * \fn		char tg_del_son_from_list(_tgfs_t *elem)
 * \brief	delete a subnode
 * \param elem	node
 * \return	1 on success 0 on error
 */
char tg_del_son_from_list(_tgfs_t *elem)
{
  return (tg_del_node_from_list(elem, TG_REC_DEL));
}

/**
 * \fn		char tg_del_file_from_list(_tgfs_t *elem)
 * \brief	delete a file node
 * \param elem	node
 * \return	1 on success 0 on error
 */
char tg_del_file_from_list(_tgfs_t *elem)
{
  return (tg_del_node_from_list(elem, TG_NO_REC_DEL));
}

/**
 * \fn		static void *tg_free_dir(_tgfs_t *elem)
 * \brief	clean a directory datas (clean all subdirs/files)
 * \param elem	node
 * \return	Nothing
 */
static void	*tg_free_dir(_tgfs_t *elem)
{
  _tg_node_list_t	*son_list = GET_SONS_LIST(elem);

  while (son_list)
    {
      _tg_node_list_t	*to_del = son_list;

      if (son_list->next == 0
	  && tg_del_node_from_list(to_del->node, TG_REC_DEL))
	{
	  free(to_del);
	  son_list = 0;
	  break;
	}
      if (tg_del_node_from_list(to_del->node, TG_REC_DEL))
	free(to_del);
      else
	break;
      son_list = son_list->next;
    }
  if (son_list)
    return ((void *)0);
  return ((void *)1);
}

/**
 * \fn		static unsigned char tg_del_node(const char *p, char type)
 * \brief	delete a node
 * \param p	node's path
 * \param type	node's type (file, directory, ...)
 * \return	1 on success 0 on error
 */
static unsigned char	tg_del_node(const char *p, char type)
{
  char			*path;
  char			*name;
  _tgfs_t		*elem;

  name = tg_name_from_path(p, &path);

  if (gl_tgfs_files && (type & TG_TYPE_FIL))
    {
      elem = gl_tgfs_files;
      do
	{
	  if (CHECK_NAME(elem, name))
	    if (check_path(elem, path))
	      return(tg_del_node_from_list(elem, TG_NO_REC_DEL));
	  elem = elem->next;
	} while (elem != gl_tgfs_files);
    }
  if (gl_tgfs_dirs && (type & TG_TYPE_DIR))
    {
      elem = gl_tgfs_dirs;
      do
	{
	  if (CHECK_NAME(elem, name))
	    if (check_path(elem, path))
	      return(tg_del_node_from_list(elem, TG_NO_REC_DEL));
	  elem = elem->next;
	} while (elem != gl_tgfs_dirs);
    }
  return (0);
}

/**
 * \fn			static _tgfs_t *tg_mknode(const char *p,
						const char *name, char perm,
						char type, void *(*free_fct)(),
						void *datas,
						unsigned long datas_size)
 * \brief		create a node
 * \param p		node's path
 * \param name		node's name
 * \param perm		node's perms (RWX)
 * \param type		node's type (file, directory, ...)
 * \param free_fct	node's cleanning function (most of time depend of type)
 * \param datas		node's datas (if any)
 * \param datas_size	node's datas size (0 if directory)
 * \return		Pointer on created node or 0 on error
 */
static _tgfs_t	*tg_mknode(const char *p, const char *name, char perm,
			   char type, void *(*free_fct)(), void *datas,
			   unsigned long datas_size)
{
  char		*path;
  _tgfs_t	*new_node = 0;
  _tgfs_infos_t	infos;

  infos.name = strdup(name);
  infos.lock.slock = 0;/*  __RAW_SPIN_LOCK_LOCKED, */
  infos.perm = perm;
  infos.type = type;
  infos.free_me = free_fct;
  infos.datas_size = datas_size;
  infos.links = 0;

  if (!p || !p[0])
    path = 0;
  else
    path = (char *)p;
  if (infos.name)
    {
      if (path)
	{
	  char	*parent_name;
	  char	*parent_path;

	  parent_name = tg_name_from_path(path, &parent_path);
	  infos.parent = tg_find_node(0, path, TG_TYPE_DIR);
	}
      else
	infos.parent = 0;
      if ((!infos.parent && !path && !tg_find_node(0, name, 0))
	  || (infos.parent && path
	      && !tg_find_son(GET_SONS_LIST(infos.parent), name)))
	new_node = tg_add_node(&infos, datas);
      if (new_node)
	{
	  __raw_spin_unlock(&(new_node->infos.lock));
	  if (infos.parent)
	    change_parent_size(HAS_PARENT(new_node), datas_size);
	}
    }
  return (new_node);
}

/**
 * \fn		unsigned char tg_del_dir(const char *path)
 * \brief	delete a directory
 * \param path	node's path
 * \return	1 on success 0 on error
 */
unsigned char	tg_del_dir(const char *path)
{
  if (!path)
    return(0);
  return(tg_del_node(path, TG_TYPE_DIR));
}

/**
 * \fn		unsigned char tg_del_file(const char *path)
 * \brief	delete a file
 * \param path	node's path
 * \return	1 on success 0 on error
 */
unsigned char	tg_del_file(const char *path)
{
  if (!path)
    return(0);
  return(tg_del_node(path, TG_TYPE_FIL));
}

/**
 * \fn		_tgfs_t	*tg_mkdir(const char *path, const char *name, char perm)
 * \brief	create a directory
 * \param path	directory's path
 * \return	Pointer on created node or 0 on error
 */
_tgfs_t		*tg_mkdir(const char *path, const char *name, char perm)
{
/* prohibit names with '/' */
  if (!name || ufind(name, '/') != -1)
    return((_tgfs_t *) 0);
  return (tg_mknode(path, name, perm, TG_TYPE_DIR, tg_free_dir, 0, 0));
}

/**
 * \fn		_tgfs_t *tg_mkfile(const char *path, const char *name,
					char perm, void *datas,
					unsigned long datas_size)
 * \brief	create a file
 * \param path	file's path
 * \param name	file's name
 * \param perm	file's perms
 * \param datas	file's datas
 * \param datas_size	file's datas size
 * \return	Pointer on created node or 0 on error
 */
_tgfs_t		*tg_mkfile(const char *path, const char *name, char perm,
			   void *datas, unsigned long datas_size)
{
/* prohibit names with '/' */
  if (!name || ufind(name, '/') != -1)
    return((_tgfs_t *) 0);

  return (tg_mknode(path, name, perm, TG_TYPE_FIL, tg_free_file,
		    datas, datas_size));
}

/**
 * \fn		_tgfs_t *tg_mklnk(const char *path, const char *name, char perm,
					char *orig, unsigned lnk_type)
 * \brief	create a link
 * \param path	link's path
 * \param name	link's name
 * \param perm	link's perms
 * \param orig	links orignal/source node
 * \param lnk_type	link type
 * \return	Pointer on created node or 0 on error
 */
_tgfs_t		*tg_mklnk(const char *path, const char *name, char perm,
			  char *orig, unsigned lnk_type)
{
  if (!lnk_type)
    lnk_type = TG_TYPE_LNK_P;
/* prohibit names with '/' */
  if (!name || ufind(name, '/') != -1)
    name = tg_name_from_path(orig, 0);
  if (path && orig && name)
    {
      _tgfs_t	*orig_node = tg_find_node(0, orig, 0);

      if (orig_node)
	return (tg_mknode(path, name, perm,
			  lnk_type | HAS_TYPE(orig_node), tg_free_file,
			  ((lnk_type & TG_TYPE_LNK_P) ? (void *)orig
			   : (void *)orig_node),
			  1));
    }
  return ((_tgfs_t *) 0);
}

/*
** TODO: le tg_mv_node()
**
** reflechir au devenir des liens lors d'un move :
** - le lien est lie au node -> il reste lie
** - le lien est lie au path -> il pointe dans le vide
**
** pour le moment les 2 types : (TG_TYPE_LNK_N, TG_TYPE_LNK_P)
*/
