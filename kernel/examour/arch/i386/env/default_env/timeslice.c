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

/* exAmour's environnement manager layer 0 */
/* Timeslice manager */

#include	<examour/env/timeslice.h>
#include	<examour/core/globals.h>
#include	<examour/mm/mem.h>
#include	<examour/support/log.h>

void		timeslice_init(void)
{
  gl_timeslices = NULL;
}

bool		_timeslice_add(uint32_t ms, uint32_t flags, examour_env_t **env)
{
  examour_timeslice_t	*new;

  if (env == NULL || *env == NULL)
    return (false);
  if ((new = kmalloc(sizeof(*new))) == NULL)
    return (false);
  new->env = *env;
  new->ms_cnt = ms;
  (*env)->total_cputime += ms;
  clist_add_before(gl_timeslices, new, timeslices_list);
  return (true);
}

/* SYSCALL */
bool		timeslice_add(uint32_t ms, uint32_t flags)
{
  return (_timeslice_add(ms, flags, &gl_current_env));
}

/** \todo	Code this function. */
bool		timeslice_remove(uint32_t ms)
{
  return (false);
}

bool		timeslice_update(examour_timeslice_t *entry)
{
  entry->ms_cnt--;
  ((examour_env_t *)entry->env)->total_cputime--;
  if (entry->ms_cnt == 0)
    {
      clist_remove(gl_timeslices, entry, timeslices_list);
      /* FIXME: without code download for prologue/epilogue, */
      /* reset the tick_cnt to 1000 and reinject it at the tail */
      /* of the list. Therefore we have someting close to a */
      /* standard round-robin algorithm. */
      entry->ms_cnt = 50;
      clist_add_before(gl_timeslices, entry, timeslices_list);
      kfree(entry);
      return (true);
    }
  return (false);
}

void			timeslice_flush(eid_t eid)
{
  examour_timeslice_t	*p;
  void			*old;

  p = gl_timeslices;
  if (!p)
    return;
  do
    {
      if (eid == p->env->eid)
	{
	  clist_remove(gl_timeslices, p, timeslices_list);
	  old = p;
	  p = p->timeslices_list.next;
	  kfree(old);
	}
      else
	p = p->timeslices_list.next;
    } while (p != gl_timeslices);
}

void			timeslice_dump(void)
{
  examour_timeslice_t	*p;

  p = gl_timeslices;
  if (!p)
    return;
  do
    {
      info("timeslice: eid: %p milliseconds: %d\n",
	   p->env->eid, p->ms_cnt);
      p = p->timeslices_list.next;
    } while (p != gl_timeslices);
}
