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

#include	<libslds/list.h>

/* Circular linked list implementation. */

void		_clist_init(void *clist, unsigned int m)
{
  if (clist)
    {
      GET_FIELD(clist, m, clist_t)->prev = clist;
      GET_FIELD(clist, m, clist_t)->next = clist;
    }
}

void		_clist_add_after(void **clist, void *new, unsigned int m)
{
  if (!clist || !new)
    return;
  if (*clist)
    {
      GET_FIELD(new, m,clist_t)->next = GET_FIELD(*clist, m, clist_t)->next;
      GET_FIELD(new, m, clist_t)->prev = *clist;
      GET_FIELD(GET_FIELD(*clist, m, clist_t)->next, m, clist_t)->prev = new;
      GET_FIELD(*clist, m, clist_t)->next = new;
    }
  else
    {
      GET_FIELD(new, m, clist_t)->next = new;
      GET_FIELD(new, m, clist_t)->prev = new;
      *clist = new;
    }
}

void		_clist_add_before(void **clist, void *new, unsigned int m)
{
  if (!clist || !new)
    return;
  if (*clist)
    {
      GET_FIELD(new, m, clist_t)->prev = GET_FIELD(*clist, m, clist_t)->prev;
      GET_FIELD(new, m, clist_t)->next = *clist;
      GET_FIELD(GET_FIELD(*clist, m, clist_t)->prev, m, clist_t)->next = new;
      GET_FIELD(*clist, m, clist_t)->prev = new;
    }
  else
    {
      GET_FIELD(new, m, clist_t)->next = new;
      GET_FIELD(new, m, clist_t)->prev = new;
      *clist = new;
    }
}

void	       _clist_remove(void **clist, void *elem, unsigned int m)
{
  if (!clist || !elem)
    return;
  if (*clist)
    {
      if (GET_FIELD(*clist, m, clist_t)->prev != *clist)
	{
	  GET_FIELD(GET_FIELD(elem, m, clist_t)->next, m, clist_t)->prev =
	    GET_FIELD(elem, m, clist_t)->prev;
	  GET_FIELD(GET_FIELD(elem, m, clist_t)->prev, m, clist_t)->next =
	    GET_FIELD(elem, m, clist_t)->next;
	  if (*clist == elem)
	    *clist = GET_FIELD(*clist, m, clist_t)->next;
	}
      else
	*clist = 0;
    }
}


/* queue implementation. */

void		*_queue_remove(void **queue, unsigned int m)
{
  void		*ret;

  if (!queue)
    return (0);
  ret = 0;
  if (*queue)
    {
      ret = *queue;
      _clist_remove(queue, ret, m);
    }
  return (ret);
}
