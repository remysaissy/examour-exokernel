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

#include	<libslds/hash.h>

/* Hashtable implementation. */

bool	_hashtable_init(void **hash, unsigned int n)
{
  unsigned int	it;

  if (hash && n > 0)
    {
      for (it = 0; it < n; it++)
	hash[it] = 0;
      return (true);
    }
  return (false);
}

bool	_hashtable_insert(void **hash,
			  void *key,
			  void *content,
			  unsigned int m,
			  hashing_function_p hash_func)
{
  uint64_t	hki;

  if (!hash || !key || !content || !hash_func)
    return (false);
  hki = hash_func(key);
  _slist_add_head(hash + hki, content, m);
  return (true);
}

void	*_hashtable_lookup(void **hash,
			   void *key,
			   unsigned int m,
			   hashing_function_p hash_func,
			   hashing_compare_p hash_comp)
{
  uint64_t   hki;
  void	*it;

  if (!hash || !key || !hash_func || !hash_comp)
    return (NULL);
  hki = hash_func(key);
  it = hash[hki];
  while (it)
    {
      if ((hash_comp(key, it)) == 0)
	break;
      it = GET_FIELD(it, m, hashtable_t)->next;
    }
  return (it);
}

bool	_hashtable_remove(void **hash,
			  void *key,
			  void *entry,
			  unsigned int m,
			  hashing_function_p hash_func)
{
  uint64_t	hki;
  void		*prev_it;
  void		*it;

  if (!hash || !key || !entry || !hash_func)
    return (false);
  hki = hash_func(key);
  prev_it = NULL;
  it = hash[hki];
  while (it)
    {
      if (it == entry)
	{
	  _slist_fast_remove(hash + hki, prev_it, entry, m);
	  return (true);
	}
      prev_it = it;
      it = GET_FIELD(it, m, hashtable_t)->next;
    }
  return (false);
}
