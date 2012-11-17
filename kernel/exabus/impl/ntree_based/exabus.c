/*
** This file is part of ExAmour

** Copyright (C) Remy Saissy <remy.saissy@gmail.com>
** examour is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 2 of the License, or
** (at your option) any later version.

** examour is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.

** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#include    <string.h>
#include	<examem.h>
#include	<exabus.h>

#include    "include/internal.h"

/** The service tree instance of exabus. */
/* TODO: protect it by a lock. Excepted use is many reads for few writes. */
static exabus_node_t	*sgl_service_tree = NULL;

static exabus_call_queue_t  *sgl_call_queue = NULL;

/*************************** Helpers **********************************************/

static inline void __cleanup_node(exabus_node_t *node)
{
	unsigned int		i;

  if (node != NULL)
  {
  if (node->interface != NULL)
  {
	  if (node->interface->symbols != NULL)
	  {
		  for (i = 0; i < node->interface->n_symbols; i++)
		  {
			  /* Content of a symbols. */
		    if (node->interface->symbols[i].id != NULL)
			  examem_unref(node->interface->symbols[i].id);
		  }
		  examem_unref(node->interface->symbols);
	  }
	  /* Content of an interface. */
    examem_unref(node->interface);
  }
  /* Content of a node. */
  if (node->id != NULL)
    examem_unref(node->id);
  examem_unref(node);
  }
}

static inline exabus_node_t *__create_ns_node(const char *node_name, int length)
{
  exabus_node_t *elem;

  if (node_name == NULL || length == 0)
    return (false);
  elem = examem_ref_new(sizeof(*elem), EXAMEM_TYPE_REGULAR);
  if (elem == NULL)
    return (NULL);
  memset(elem, 0, sizeof(*elem));
  elem->id = examem_ref_new(length + 1, EXAMEM_TYPE_REGULAR);
  if (elem->id == NULL)
  {
    examem_unref(elem);
    return (NULL);
  }
  strncpy(elem->id, node_name, length);
  elem->id[length] = 0;
  return (elem);
}

static inline exabus_node_t *__create_interface_node(const char *node_name, int length, exabus_interface_t *interface)
{
  exabus_node_t 	*node;
  unsigned int		i;
  int				len;

  if (node_name == NULL || length == 0 || interface == NULL || interface->n_symbols == 0 || interface->symbols == NULL)
    return (NULL);
  node = __create_ns_node(node_name, length);
  if (node == NULL)
    return (NULL);
  node->interface = examem_ref_new(sizeof(*interface), EXAMEM_TYPE_REGULAR);
  if (node->interface == NULL)
  {
    __cleanup_node(node);
    return (NULL);
  }
  memset(node->interface, 0, sizeof(*interface));
  /* BEGIN: Copy of source interface content to destination interface. */
  node->interface->symbols = examem_ref_new(interface->n_symbols * sizeof(*node->interface->symbols), EXAMEM_TYPE_REGULAR);
  if (node->interface->symbols == NULL)
  {
      __cleanup_node(node);
      return (NULL);
  }
  memset(node->interface->symbols, 0, interface->n_symbols * sizeof(*node->interface->symbols));
  node->interface->max_execution_time = interface->max_execution_time;
  node->interface->n_symbols = interface->n_symbols;
  memcpy(node->interface->symbols, interface->symbols, interface->n_symbols * sizeof(*interface->symbols));
  for (i = 0; i < node->interface->n_symbols; i++)
  {
      if (interface->symbols[i].id == NULL)
      {
        __cleanup_node(node);
        return (NULL);
      }
	  /* All dynamic pointer typed data must be copied here. Everything else is copied during the memcpy above. */
	  len = strlen(interface->symbols[i].id);
	  node->interface->symbols[i].id = examem_ref_new(len + 1, EXAMEM_TYPE_REGULAR);
	  if (node->interface->symbols[i].id == NULL)
	  {
		  __cleanup_node(node);
		  return (NULL);
	  }
	  strncpy(node->interface->symbols[i].id, interface->symbols[i].id, len);
	  node->interface->symbols[i].id[len] = 0;
  }
  /* END: Copy of source interface content to destination interface. */
  ntree_init(node, entries);
  return (node);
}

static int 			s_exabus_compare(void *tree_node, void *path, int *iterator, void *data)
  {
    exabus_node_t 	*current_node = (exabus_node_t *)tree_node;
    char          	*key = (char *)path;
    int           	end_position;
    char          	*p;
    int           	ret;

    p = strchr(key + *iterator, '.');
    if (p != NULL)
      end_position = (int)p - (int)(key + *iterator);
    else
      end_position = strlen(key + *iterator);
    ret = strncmp(key + *iterator, current_node->id, end_position);
    if (!ret)
    {
      *iterator += end_position + 1;
      if (*iterator >= strlen(key))
        return (2);
      return (1);
    }
    return (0);
  }

static void			*s_exabus_add_new_node(void *path, int iterator, void *data)
{
  char          	*key = (char *)path;
  int           	end_position;
  char          	*p;
  exabus_node_t   	*elem;

  if (iterator >= strlen(path))
    return (NULL);
  p = strchr(key + iterator, '.');
  if (p != NULL)
    end_position = (int)p - (int)(key + iterator);
  else
    end_position = strlen(key + iterator);
  elem = __create_ns_node(key + iterator, end_position);
  if (elem == NULL)
    return (NULL);
  return (elem);
}

static void			s_exabus_remove_node(void *node, void *data)
{
  __cleanup_node(node);
}


/******************************* Kernel internals ***************************************************/

bool	_exabus_init(const exaboot_t * const inf)
{
    if (inf == NULL)
      return (false);
	sgl_service_tree = NULL;
	sgl_call_queue = NULL;
	return (true);
}

/******************************* Public API *********************************************************/

bool	exabus_publish(const char *path, const char *interface_name, exabus_interface_t *interface)
{
	exabus_node_t	*node;

	if (path == NULL || interface_name == NULL || interface == NULL || interface->n_symbols == 0 || (interface->n_symbols > 0 && interface->symbols == NULL))
		return (false);
	node = ntree_lookup(&sgl_service_tree, path, entries, s_exabus_compare, NULL);
	if (node)
	{
		node = node->entries.child;
		if (ntree_lookup(&node, interface_name, entries, s_exabus_compare, NULL))
			return (false);
	}
	node = __create_interface_node(interface_name, strlen(interface_name), interface);
	if (node == NULL)
	  return (NULL);
	if (ntree_insert(&sgl_service_tree, path, node, entries, s_exabus_compare, s_exabus_add_new_node, NULL) == false)
	{
	  __cleanup_node(node);
		return (false);
	}
	return (true);
}

bool	exabus_unpublish(const char *fullpath)
{
	exabus_node_t	*node;

	if (fullpath == NULL)
		return (false);
	node = ntree_remove(&sgl_service_tree, fullpath, entries, s_exabus_compare, s_exabus_remove_node, NULL);
	if (node == NULL)
		return (false);
	__cleanup_node(node);
	return (true);
}

bool	exabus_subscribe(const char *fullpath, const char *signal)
{
	exabus_node_t	*node;
	unsigned int	i;

	if (fullpath == NULL || signal == NULL)
		return (false);
	node = ntree_lookup(&sgl_service_tree, fullpath, entries, s_exabus_compare, NULL);
	if (node == NULL || node->interface == NULL)
		return (false);
	for (i = 0; i < node->interface->n_symbols; i++)
	{
		if (!strcmp(node->interface->symbols[i].id, signal) && node->interface->symbols[i].type == EXABUS_SYMBOL_SIGNAL)
		{
			/* TODO: add to the subscribers list. */
			return (true);
		}
	}
	return (false);
}

bool	exabus_unsubscribe(const char *fullpath, const char *signal)
{
	exabus_node_t	*node;
	unsigned int	i;

	if (fullpath == NULL || signal == NULL)
		return (false);
	node = ntree_lookup(&sgl_service_tree, fullpath, entries, s_exabus_compare, NULL);
	if (node == NULL || node->interface == NULL)
		return (false);
	for (i = 0; i < node->interface->n_symbols; i++)
	{
		if (!strcmp(node->interface->symbols[i].id, signal) && node->interface->symbols[i].type == EXABUS_SYMBOL_SIGNAL)
		{
			/* TODO: remove subscribers list. */
			return (true);
		}
	}
	return (false);
}

bool	exabus_find(const char *fullpath, const char *symbol, exabus_symbol_type_e type)
{
	exabus_node_t	*node;
	unsigned int	i;

	if (fullpath == NULL)
		return (false);
	node = ntree_lookup(&sgl_service_tree, fullpath, entries, s_exabus_compare, NULL);
	if (node == NULL || node->interface == NULL)
		return (false);
	if (symbol == NULL)
		return (true);
	for (i = 0; i < node->interface->n_symbols; i++)
	{
		if (!strcmp(symbol, node->interface->symbols[i].id) && node->interface->symbols[i].type == type)
			return (true);
	}
	return (false);
}

bool	exabus_raise(const char *fullpath, const char *signal, exabus_argument_t in)
{
  if (fullpath == NULL || signal == NULL)
    return (false);
  return (false);
}

bool	exabus_call(const char *fullpath, const char *method, exabus_argument_t in, exabus_method_callback_p method_callback)
{
  exabus_call_queue_t   *elem;

  if (fullpath == NULL || method == NULL || (void *)method_callback == NULL)
     return (false);
  if (exabus_find(fullpath, method, EXABUS_SYMBOL_METHOD) == false)
    return (false);
  elem = examem_ref_new(sizeof(*elem), EXAMEM_TYPE_REGULAR);
  if (elem == NULL)
    return (false);
  elem->fullpath = examem_ref_new(strlen(fullpath) + 1, EXAMEM_ALIGNED_4KB | EXAMEM_TYPE_REGULAR);
  if (elem->fullpath == NULL)
  {
    examem_unref(elem);
    return (false);
  }
  strcpy(elem->fullpath, fullpath);
  elem->method = examem_ref_new(strlen(method) + 1, EXAMEM_ALIGNED_4KB | EXAMEM_TYPE_REGULAR);
  if (elem->method == NULL)
  {
    examem_unref(elem->fullpath);
    examem_unref(elem);
    return (false);
  }
  strcpy(elem->method, method);
  elem->caller = exaprocess_get_current_pid();
  elem->cb = method_callback;
  memcpy(elem->in, in, sizeof(in));
  queue_add(sgl_call_queue, elem, entries);
  return (true);
}

void    exabus_flush_pending_requests(void)
{
  exabus_node_t         *node;
  exabus_call_queue_t   *elem;
  exabus_argument_t     out;
  unsigned int          i;

  while (sgl_call_queue != NULL)
  {
    elem = queue_remove(sgl_call_queue, entries);
    memset(out, 0, sizeof(out));
    node = ntree_lookup(&sgl_service_tree, elem->fullpath, entries, s_exabus_compare, NULL);
    if (node == NULL || node->interface == NULL)
      elem->cb(false, out);
    else
    {
      for (i = 0; i < node->interface->n_symbols; i++)
      {
          if (!strcmp(elem->method, node->interface->symbols[i].id) && node->interface->symbols[i].type == EXABUS_SYMBOL_METHOD)
          {
            /* TODO: call the method from exabus (upcall). */
            elem->cb(true, out);
            break;
          }
      }
    }
    examem_unref(elem->method);
    examem_unref(elem->fullpath);
    examem_unref(elem);
  }
}
