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

/* Single linked list implementation. */

void		_slist_init(void *head,
              unsigned int m)
{
  if (head)
    GET_FIELD(head, m, slist_t)->next = 0;
}

void		_slist_add_head(void **head,
				void *new,
				unsigned int m)
{
  if (head && new)
    {
      GET_FIELD(new, m, slist_t)->next = *head;
      *head = new;
    }
}

void		_slist_add_after(void **head,
				 void *slist,
				 void *new,
				 unsigned int m)
{
  if (!head || !new)
    return;
  if (slist)
    {
      GET_FIELD(new, m, slist_t)->next = GET_FIELD(slist, m, slist_t)->next;
      GET_FIELD(slist, m, slist_t)->next = new;
    }
  else
    {
      if (*head)
	{
	  GET_FIELD(new, m, slist_t)->next =
	    GET_FIELD(*head, m, slist_t)->next;
	  GET_FIELD(*head, m, slist_t)->next = new;
	}
      else
	{
	  GET_FIELD(new, m, slist_t)->next = 0;
	  *head = new;
	}
    }
}

void		_slist_remove(void **head,
			      void *slist,
			      unsigned int m)
{
  if (!head || !slist)
    return;
  if (*head && slist)
    {
      if (slist == *head)
	*head = GET_FIELD(slist, m, slist_t)->next;
      else
	{
	  while (*head && GET_FIELD(*head, m, slist_t)->next != slist)
	    *head = GET_FIELD(*head, m, slist_t)->next;
	  GET_FIELD(*head, m, slist_t)->next =
	    GET_FIELD(slist, m, slist_t)->next;
	  GET_FIELD(slist, m, slist_t)->next = 0;
	}
    }
}

void		_slist_fast_remove(void **head,
				   void *pslist,
				   void *slist,
				   unsigned int m)
{
  if (!head || !slist)
    return;
  if (!pslist || GET_FIELD(pslist, m, slist_t)->next != slist)
    _slist_remove(head, slist, m);
  else
    {
      if (*head && slist)
	{
	  if (slist == *head)
	    *head = GET_FIELD(slist, m, slist_t)->next;
	  else
	    {
	      GET_FIELD(pslist, m, slist_t)->next =
		GET_FIELD(slist, m, slist_t)->next;
	      GET_FIELD(slist, m, slist_t)->next = 0;
	    }
	}
    }
}

