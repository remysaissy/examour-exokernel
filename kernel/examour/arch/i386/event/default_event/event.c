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

/* exAmour's Event manager layer 0 */
/* generic event manager. */

#include	<examour/event/event.h>
#include	<examour/event/irq.h>
#include	<examour/event/idt.h>
#include	<examour/core/asm.h>
#include	<examour/env/sched.h>
#include	<examour/core/globals.h>
#include	<toolkit/list.h>

typedef struct event_s
{
  dlist_t	events;
  examour_env_t	*env;
  selector_t	cs;
  paddr_t	offset;
  uint32_t	flags;

}		event_t;

static event_t	*events[IRQ_MAX_NUM] = {0, };

void		event_init(void)
{
  /* setup the irqs. */
  irq_init();

  /* setup the idt. */
  idt_init();
}

/* SYSCALL */
bool		event_register(uint32_t		vector_id,
			       selector_t	cs,
			       paddr_t		offset,
			       uint32_t		flags)
{
  event_t	*new_event;

  if (vector_id > IRQ_MAX_NUM)
    return (false);
  /* \todo	Add the lookup for flags. */
  if ((new_event = kmalloc(sizeof(*new_event))) == NULL)
    return (false);
  new_event->cs = cs;
  new_event->offset = offset;
  new_event->flags = flags;
  new_event->env = gl_current_env;
  dlist_add_head(events[vector_id], new_event, events);
  return (true);
}

/* Internal function for unregister. */
static bool	_event_unregister(uint32_t vector_id, event_t **p)
{
  if (vector_id > IRQ_MAX_NUM)
    return (false);
  if (p == NULL || *p == NULL)
    return (false);
  if (((*p)->flags & EVENT_REGISTER_LOCKED) == EVENT_REGISTER_LOCKED)
    return (false);
  dlist_remove(events[vector_id], (*p), events);
  kfree(*p);
  return (true);
}

/* SYSCALL */
bool		event_unregister(uint32_t	vector_id,
				 selector_t	cs,
				 paddr_t	offset)
{
  event_t	*p;

  if (vector_id > IRQ_MAX_NUM)
    return (false);
  p = events[vector_id];
  while (p)
    {
      if (cs == p->cs && 
	  offset == p->offset && 
	  p->env == gl_current_env)
	return (_event_unregister(vector_id, &p));
      p = p->events.next;
    }
  return (false);
}

/* SYSCALL */
bool		event_forge(void *forgery, uint32_t *event_id)
{
  return (false);
}

/* SYSCALL */
bool		event_throw(uint32_t event_id, uint32_t flags)
{
  return (false);
}

void		event_flush(examour_env_t *env)
{
  event_t	*p;
  int		i;

  for (i = 0; i < IRQ_MAX_NUM; i++)
    {
      p = events[i];
      while (p)
	{
	  if (p->env == env)
	    {
	      dlist_remove(events[i], p, events);
	      kfree(p);
	      p = events[i];
	    }
	  else
	    p = p->events.next;
	}
    }
}

void		event_process_request(kevent_cpu_context_t args)
{
  event_t	*p;
  event_t	*ps;

  if (args.ev_id > IRQ_MAX_NUM)
    return;
  p = events[args.ev_id];
  while (p)
    {
      timed_sched(p->env, p->cs, p->offset, &args);
      if ((p->flags & EVENT_REGISTER_ONESHOT) == EVENT_REGISTER_ONESHOT)
	{
	  ps = p;
	  p = p->events.next;
	  _event_unregister(args.ev_id, &ps);
	}
      else
	p = p->events.next;
    }
}
