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

/* exAmour's environnement manager layer 1 */
/* Scheduler */

#include	<examour/env/sched.h>
#include	<examour/env/timer.h>
#include	<examour/env/timeslice.h>
#include	<examour/env/env.h>
#include	<examour/core/globals.h>
#include	<examour/mm/mem.h>
#include	<examour/support/log.h>
#include	<examour/event/event_types.h>

void		far_jump(int offset, int cs, kevent_cpu_context_t *arg);

void		sched_init(void)
{
  timer_set(0xffff);
}

int		sched_next(void)
{
  /* check if an env is running. */
  if (gl_current_env != gl_envs.idle)
    {
      if (timeslice_update(gl_timeslices) == false)
	{
	  /* time remains for this env. */
	  return (0);
	}
      else
	{
	  /* __switch_to updates the gl_current_env pointer. */
	  if (!gl_timeslices)
	    {
	      __switch_to(gl_envs.idle);
	      return (1);
	    }
	}
    }
  if (gl_timeslices != NULL)
    {
      __switch_to(gl_timeslices->env);
      /* syscall.c doesn't use it... I should agree on one method ! */
      return (1);
    }
  return (0);
}


void	      timed_sched(examour_env_t *env, selector_t cs, paddr_t offset, kevent_cpu_context_t *arg)
{
  ldt_t		*ldt;
  int		i;

  if (offset != PADDR_ERROR)
    {
      ldt = (ldt_t *)env->ldtr.base_addr;
      i = cs >> 3;
      if (i < (env->ldtr.limit + 1) / sizeof(ldt_t))
	{
	  gl_gdt[GDT_SEG_UCODE][0] = ldt[i][0];
	  gl_gdt[GDT_SEG_UCODE][1] = ldt[i][1];
	  set_segment_dpl(gl_gdt[GDT_SEG_UCODE], SEGMENT_PRIV_0);
	  __asm__ volatile ("movl %%eax, %%ds; movl %%ebx, %%es" :: "a"(arg->ds), "b"(arg->es));
	  far_jump(offset, GDT_GET_SELECTOR(GDT_SEG_UCODE), arg);
	  __asm__ volatile ("movl %%eax, %%ds; movl %%eax, %%es" :: "a"(GDT_GET_OFFSET(GDT_SEG_KDATA)));
	}
    }
}

