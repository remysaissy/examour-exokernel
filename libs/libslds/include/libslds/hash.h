/*
** This file is part of libslds

** Copyright (C) Remy Saissy <remy.saissy@epitech.net>
** libslds is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 2 of the License, or
** (at your option) any later version.

** libslds is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.

** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#ifndef	__LIBSLDS_HASH_H__
#define	__LIBSLDS_HASH_H__

#include	<stddef.h>
#include	<stdint.h>
#include	<stdbool.h>

#include	"common.h"
#include	"list.h"

/**
 * Hashtable data structure:
 *  - hashtable_t
 *
 * How to use the hashtables:
 * Every data structure has an optional macro parameter: the hash parameter.
 * This parameter allows your implementation to use several hashtables in the
 * same host data structure but if you leave it empty, the macro simply
 * assume that the hash data structure is located at the very beginning of
 * the data structure.
 * @note For now, the parameter is mandatory because I don't know how to
 * check for an empty parameter with cpp.
 */

/* Data structures */

/**
 * \brief	A basic data type to be included in every data structure that
 *		that expect to be used in a hashtable.
 */
typedef slist_t	hashtable_t;

/**
 * Hashing callback.
 * @param key The key value to be hashed.
 * @return The hashed value.
 */
typedef uint64_t (*hashing_function_p)(void *key);

/**
 * Comparison callback.
 * @param key The key to be compared.
 * @param it The node to compare the key with.
 * @return 0 if it matchs, another value otherwise.
 */
typedef uint64_t (*hashing_compare_p)(void *key, void *it);

/* Implementation */

/* Hashing functions. */

/* Integer hashing. */

/**
 * @param key The key, a 32 bit integer.
 * @returns The hash of the key, a 32 bit integer.
 * @todo Unit test.
 */
uint64_t  hashing_integer_knuth_multiplicative(void *key);

/**
 * @param key The key, an array of 3 32 bit integers.
 * @returns The hash of the key, a 32 bit integer.
 * @todo Unit test.
 */
uint64_t  hashing_integer_jenkins_96bit_mix(void *key);

/**
 * @param key The key, a 32 bit integer.
 * @returns The hash of the key, a 32 bit integer.
 * @todo Unit test.
 */
uint64_t  hashing_integer_jenkins_32bit(void *key);

/**
 * @param key The key, a 32 bit integer.
 * @returns The hash of the key, a 32 bit integer.
 * @todo Unit test.
 */
uint64_t  hashing_integer_32bit_multiplication(void *key);

/**
 * @param key The key, a 64 bit integer.
 * @returns The hash of the key, a 64 bit integer.
 * @todo Unit test.
 */
uint64_t  hashing_integer_64bit_multiplication(void *key);

/**
 * @param key The key, a 64 bit integer.
 * @returns The hash of the key, a 32 bit integer.
 * @todo Unit test.
 */
uint64_t  hashing_integer_64_to_32bit(void *key);


/* String Hashing. */

/**
 * @param key The key, a null terminated string.
 * @returns The hash of the key, a 64 bit integer.
 * @todo unit test.
 */
uint64_t  hashing_string_djb2(void *key);

/**
 * @param key The key, a null terminated string.
 * @returns The hash of the key, a 64 bit integer.
 * @todo unit test.
 */
uint64_t  hashing_string_sdbm(void *key);

/**
 * @param key The key, a null terminated string.
 * @returns The hash of the key, a 64 bit integer.
 * @todo unit test.
 */
uint64_t  hashing_string_lose_lose(void *key);

/* TODO: add string hashing functions. */

/* Library routines. */

/**
 * Initialize an hashtable.
 * @param hash The hashtable.
 * @param n The name of the hash datastructure in hash.
 * @return true on success, false on error.
 */
#define	hashtable_init(hash, n)					\
 _hashtable_init((void **)(hash), (n))

/**
 * Insert a new node in an hashtable.
 * @param hash The hashtable.
 * @param key The key for insertion.
 * @param content the content of be inserted.
 * @param m The name of the hashtable datastructure in hash.
 * @param hash_func The Hashing callback.
 * @return true on success, false on error.
 */
#define	hashtable_insert(hash, key, content, m, hash_func)	\
 _hashtable_insert((void **)(hash),				\
		   (void *)(key),				\
		   (void *)(content),				\
		   (unsigned int)offsetof(typeof(**(hash)), m),		\
		   (hash_func))

/**
 * Lookup for a node in an hashtable.
 * @param hash The hashtable.
 * @param key The key for lookup.
 * @param m The name of the hashtable datastructure in hash.
 * @param hash_func The Hashing callback.
 * @param hash_comp The comparision callback.
 * @return The node on success, NULL on error.
 */
#define	hashtable_lookup(hash, key, m, hash_func, hash_comp)	\
 _hashtable_lookup((void **)(hash),				\
		   (void *)(key),				\
		   (unsigned int)offsetof(typeof(**(hash)), m),		\
		   (hash_func),					\
		   (hash_comp))

/**
 * Remove a node from an hashtable.
 * @param hash The hashtable.
 * @param key The key to remove.
 * @param entry The node to remove (retrieved through a lookup).
 * @param m The name of the hashtable datastructure in hash.
 * @param hash_func The Hashing callback.
 * @return true on success, false on error.
 */
#define	hashtable_remove(hash, key, entry, m, hash_func)	\
 _hashtable_remove((void **)(hash),				\
		   (void *)(key),				\
		   (void *)(entry),				\
		   (unsigned int)offsetof(typeof(**(hash)), m),		\
		   (hash_func))

/**
 * Initialize an hashtable.
 * @param hash The hashtable.
 * @param n The size of the hashtable.
 * @return true on success, false on error.
 */
bool	_hashtable_init(void **hash, unsigned int n);

/**
 * Insert a new node in an hashtable.
 * @param hash The hashtable.
 * @param key The key for insertion.
 * @param content the content of be inserted.
 * @param m The offset of the hashtable datastructure in hash.
 * @param hash_func The Hashing callback.
 * @return true on success, false on error.
 */
bool	_hashtable_insert(void **hash,
			  void *key,
			  void *content,
			  unsigned int m,
			  hashing_function_p hash_func);

/**
 * Lookup for a node in an hashtable.
 * @param hash The hashtable.
 * @param key The key for lookup.
 * @param m The offset of the hashtable datastructure in hash.
 * @param hash_func The Hashing callback.
 * @param hash_comp The comparision callback.
 * @return The node on success, NULL on error.
 */
void	*_hashtable_lookup(void **hash,
			   void *key,
			   unsigned int m,
			   hashing_function_p hash_func,
			   hashing_compare_p hash_comp);

/**
 * Remove a node from an hashtable.
 * @param hash The hashtable.
 * @param key The key to remove.
 * @param entry The node to remove (retrieved through a lookup).
 * @param m The offset of the hashtable datastructure in hash.
 * @param hash_func The Hashing callback.
 * @return true on success, false on error.
 */
bool	_hashtable_remove(void **hash,
			  void *key,
			  void *entry,
			  unsigned int m,
			  hashing_function_p hash_func);

#endif /* __LIBSLDS_HASH_H__ */
