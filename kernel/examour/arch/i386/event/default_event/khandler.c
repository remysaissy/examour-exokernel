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

/* exAmour's event manager layer 0 */
/* Kernel specific handlers */

#include	<examour/core/globals.h>
#include	<examour/support/log.h>
#include	<examour/event/exception_types.h>
#include	<examour/event/event_types.h>
#include	<examour/core/segment.h>
#include        <examour/core/globals.h>
#include	<examour/env/sched.h>

/**
 * \todo	Relocate the handlers code in the assembly part of
 *		the kernel to achieve a greater level of optimization.
 */

void		do_unhandled(kevent_cpu_context_t *arg)
{
  cls();
  panic("Unhandled exception #%d at %p:%p.\n"
	"context dump:\n"
	"\teax:%p  ebx:%p  ecx:%p  edx:%p\n"
	"\tesi:%p  edi:%p  ebp:%p  esp:%p\n"
	"\teflags:%p  cs:%p  ss:%p\n"
	"\tds:%p  es:%p  fs:%p  gs:%p\n",
	arg->ev_id, arg->cs, arg->eip,
	arg->eax, arg->ebx, arg->ecx, arg->edx,
	arg->esi, arg->edi, arg->ebp, arg->esp,
	arg->eflags, arg->cs, arg->ss, arg->ds,
	arg->es, arg->fs, arg->gs);
}

void		do_epilogue(kevent_cpu_context_t arg)
{
  if (gl_current_env->epilogue.offset != PADDR_ERROR)
    {
      timed_sched(gl_current_env, 
		  gl_current_env->epilogue.cs,
		  gl_current_env->epilogue.offset,
		  &arg);
    }
}

void		do_prologue(kevent_cpu_context_t arg)
{
  if (gl_current_env->prologue.offset != PADDR_ERROR)
    {
      timed_sched(gl_current_env, 
		  gl_current_env->prologue.cs,
		  gl_current_env->prologue.offset,
		  &arg);
    }
}

void		do_exception(kevent_cpu_context_t arg)
{
  if (gl_current_env->exceptions[arg.ev_id].offset != (paddr_t)PADDR_ERROR)
    {
      timed_sched(gl_current_env, 
		  gl_current_env->exceptions[arg.ev_id].cs,
		  gl_current_env->exceptions[arg.ev_id].offset,
		  &arg);
    }
  else
    do_unhandled(&arg);
}
