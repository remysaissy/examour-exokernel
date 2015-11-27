/*
 * This file is part of ExAmour

 * Copyright (C) Remy Saissy <remy.saissy@gmail.com>
 * ExAmour is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.

 * ExAmour is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/* ExAmour's event manager layer 1. */
/* Capability allocator. */

#include	<examour/event/io.h>
#include	<examour/mm/mem.h>
#include	<examour/mm/ldt.h>
#include	<examour/support/log.h>
#include	<examour/support/string.h>
#include	<examour/core/globals.h>

static iocap_t	*system_iocaps = NULL;

/* Helper functions. */

static iocap_t	*_iocap_lookup(uint16_t ioport)
{
  iocap_t	*p;

  p = system_iocaps;
  while (p)
    {
      if (ioport == p->ioport)
	break;
      p = p->iocaps_list.next;
    }
  return (p);
}

static examour_env_t	*_iocap_check_env(iocap_t *iocap, eid_t eid)
{
  examour_env_t		*p;

  p = iocap->envs;
  while (p)
    {
      if (p->eid == eid)
	break;
      p = p->iocaps_list.next;
    }
  return (p);
}


/* Public functions. */

void		io_init(void)
{
  system_iocaps = NULL;
  info("I/O subsystem initialized.\n");
}

/* SYSCALL */
bool		io_grant(uint16_t ioport, bool exclusive)
{
  iocap_t	*iocap;

  iocap = _iocap_lookup(ioport);
  if (iocap == NULL)
    {
      if ((iocap = kcalloc(sizeof(*iocap))) == NULL)
	return (false);
      iocap->ioport = ioport;
      iocap->ref_cnt = 0;
      iocap->exclusive = exclusive;
      dlist_add_head(system_iocaps, iocap, iocaps_list);
    }
  else
    {
      if (exclusive == true)
	return (false);
      if (iocap->exclusive == true)
	return (false);
      if (_iocap_check_env(iocap, gl_current_env->eid) != NULL)
	return (false);
    }
  /** \todo find a better way to establish a bidirectionnal link. */
  /* register the env in the iocap structure. */
  dlist_add_head(iocap->envs, gl_current_env, iocaps_list);
  /* register the iocap in the env structure. */
  dlist_add_head(gl_current_env->iocaps, iocap, envs_list);
  iocap->ref_cnt++;
  /* setup the ioport in the env iocaps. */
/*   gl_current_env->tss.iomap[ioport/sizeof(gl_current_env->tss.iomap)] |= */
/*     (1 << ioport%sizeof(gl_current_env->tss.iomap)); */
  return (true);
}

/* SYSCALL */
bool		io_revoke(uint16_t ioport)
{
  iocap_t		*iocap;

  iocap = _iocap_lookup(ioport);
  if (iocap == NULL)
    return (false);
  /* check if the env has the iocap. */
  if (_iocap_check_env(iocap, gl_current_env->eid) == NULL)
    return (false);
  /* unlink the  iocapability. */
  /* unregister the env in the iocap structure. */
  dlist_remove(iocap->envs, gl_current_env, iocaps_list);
  /* unregister the iocap in the env structure. */
  dlist_remove(gl_current_env->iocaps, iocap, envs_list);
  /* setup the ioport in the env iocaps. */
/*   gl_current_env->tss.iomap[ioport/sizeof(gl_current_env->tss.iomap)] &= */
/*     ~((1 << ioport%sizeof(gl_current_env->tss.iomap))); */
  iocap->ref_cnt--;
  /* The iocap is empty. */
  if (iocap->ref_cnt == 0)
    {
      dlist_remove(system_iocaps, iocap, iocaps_list);
      kfree(iocap);
    }
  return (true);
}

void		io_flush(eid_t eid)
{
  info("[STUB]: iocap_flush().");
}
