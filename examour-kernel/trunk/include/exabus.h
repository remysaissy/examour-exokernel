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

#ifndef EXABUS_H_
#define EXABUS_H_

#include        <stddef.h>
#include		<stdint.h>
#include        <stdbool.h>
#include        <string.h>
#include        <tree.h>
#include		<list.h>

#include		"exaboot.h"
#include        "examem.h"
#include		"exaprocess.h"


/* Public datatypes. */

/**
 * Types of a symbols.
 */
typedef enum	_exabus_symbol_type_e
{
    EXABUS_SYMBOL_NONE = -1,
	EXABUS_SYMBOL_METHOD,
	EXABUS_SYMBOL_SIGNAL,

}				exabus_symbol_type_e;

/**
 * A symbol of an interface.
 * Parameters can be one of the following types:
 *   - i -> signed integer
 *   - I -> unsigned integer
 *   - s -> signed short integer
 *   - S -> unsigned short integer
 *   - l -> signed long integer
 *   - L -> unsigned long integer
 *   - c -> signed character
 *   - C -> unsigned character
 *   - f -> floating point number
 *   - d -> high precision floating point number
 *   - p -> untyped pointer.
 *   - b -> boolean.
 *   - \0 -> zero is no argument.
 */
typedef struct	exabus_symbol_s
{
	uint32_t			max_execution_time; /** maximum allocated time for execution in milliseconds. Overrides the interface level value. */
	char					*id; /** Identifier of the symbols. */
	exabus_symbol_type_e	type; /** Type of symbols. */
	char					in[6]; /** Input parameters. */
	char					out[6]; /** Output parameters. Unused with signals. */
	paddr_t                 cb; /** Callback function. */

}				exabus_symbol_t;

/**
 * An interface of the service tree.
 */
typedef struct  exabus_interface_s
{
	uint32_t	max_execution_time; /** maximum allocated time for execution in milliseconds. */
	exabus_symbol_t	*symbols; /** Interface's symbols. */
	uint32_t	n_symbols; /* Number of symbols. */

}       exabus_interface_t;

typedef union exabus_argument_u
{
	signed int		i;
	unsigned int	I;
	signed short	s;
	unsigned short	S;
	signed long		l;
	unsigned long	L;
	signed char		c;
	unsigned char	C;
	float			f;
	double			d;
	void			*p;
	bool            b;
}			exabus_argument_t[6];

typedef	void	(*exabus_method_callback_p)(bool executed, exabus_argument_t out);

/***** Kernel internal data structure ************/

/**
 * A node of the service tree.
 */
typedef struct  exabus_node_s
{
  ntree_t       		entries; /** Service tree entries. */
  char          		*id; /** identifier of the node. */
  exabus_interface_t	*interface; /* If NULL, the node is a namespace. */

}       exabus_node_t;


/* Kernel internals. */

/**
 * Initialize exabus.
 * @param	inf	The information data structure.
 */
bool  _exabus_init(const exaboot_t * const inf);

/* Public API. It is bounded to syscalls. */

/**
 * Publish a new interface on the service tree.
 * @param path				Path to the interface.
 * @param interface_name	Name of the interface.
 * @param interface			The interface.
 * @return True on success, false otherwise.
 * @note	A path is a set of namespaces each separated by a dot.
 */
bool	exabus_publish(const char *path, const char *interface_name, exabus_interface_t *interface);

/**
 * Unpublish an existing interface.
 * @param fullpath			The path to the interface with the interface name at the end.
 * @return True on success, false otherwise.
 * @note	A path is a set of namespaces each separated by a dot.
 */
bool	exabus_unpublish(const char *fullpath);

/**
 * Suscribe to a signal.
 * @param	fullpath	The full path to the interface.
 * @param	signal		The name of the signal to suscribe to.
 * @return	True on success, false otherwise.
 * @TODO	Implement it.
 */
bool	exabus_subscribe(const char *fullpath, const char *signal);

/**
 * Unsuscribe from a signal.
 * @param	fullpath	The full path to the interface.
 * @param	signal		The name of the signal to unsuscribe from.
 * @return	True on success, false otherwise.
 * @TODO	Implement it.
 */
bool	exabus_unsubscribe(const char *fullpath, const char *signal);

/**
 * Look for an interface an optionally a symbol within.
 * @param fullpath	The path of the namespace or interface to look for.
 * @param symbol	The smybol to look for within the interface.
 * @param type      The type of the symbol to look for.
 * @return True if found, false otherwise.
 */
bool	exabus_find(const char *fullpath, const char *symbol, exabus_symbol_type_e type);

/**
 * Raise a signal.
 * @param	fullpath	The path of the interface of the signal to be raised.
 * @param	signal		The identifier of the signal to be raised.
 * @param	in			Pointer to input arguments.
 * @note Raises are asynchronous.
 * @todo	To be implemented.
 */
bool	exabus_raise(const char *fullpath, const char *signal, exabus_argument_t in);

/**
 * Calls a method.
 * @param	fullpath	The path of the interface of method to be called.
 * @param	method		The method to be called.
 * @param	in			Pointer to input arguments.
 * @param	method_callback	Callback to get output of the method call.
 * @note	Calls are asynchronous.
 * @todo	To be implemented.
 */
bool	exabus_call(const char *fullpath, const char *method, exabus_argument_t in, exabus_method_callback_p method_callback);

/**
 * Flushes pending requests made to exabus.
 */
void    exabus_flush_pending_requests(void);

#endif /*EXABUS_H_*/
