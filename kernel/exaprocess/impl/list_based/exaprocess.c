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

#include    <stdbool.h>
#include    <stdint.h>

#include    <exaprocess.h>
#include    <examem.h>
#include    <exabus.h>

#include    "include/internal.h"

#include    "../debugging/log.h"

static  exaprocess_t    *sgl_current_process = NULL;

/* Kernel internal API. */

bool    _exaprocess_init(const exaboot_t * const inf)
{
	return (false);
}

pid_t       exaprocess_get_current_pid(void)
{
  if (sgl_current_process == NULL)
    return (0);
  return (sgl_current_process->pid);
}

void        exaprocess_grant_io(uint16_t ioport)
{

}

void        exaprocess_revoke_io(uint16_t ioport)
{

}

void        exaprocess_switch(void)
{
  message("Task Switch.\n");
//  exabus_flush_pending_requests();
//  examem_rationalize();
//  sgl_current_process = sgl_current_process->entries.next;
}

/* Exabus exports */

pid_t       exaprocess_create(exaprocess_section_t *sections,
                              uint32_t n_sections)
{
    exaprocess_t  *new_process;

    if (sections == NULL || n_sections == 0)
      return (0);
    new_process = examem_ref_new(sizeof(*new_process), EXAMEM_TYPE_REGULAR);
    if (new_process == NULL)
      return (0);
    new_process->pid = (paddr_t)new_process;
    clist_add_before(sgl_current_process, new_process, entries);
    return (new_process->pid);

    //  examour_env_t       *new_env;
    //  paddr_t       *stack0;
    //  kevent_cpu_context_t  *ctx;
    //  eid_t         eid = PADDR_ERROR;
    //  examour_env_section_t *code_section = NULL;
    //  int           defined = 0;
    //  int           i;
    //
    //  if (id == NULL)
    //    return (-1);
    //  /* All envs must provide those parameters. */
    //  if (sections == NULL || n_sections <= 0)
    //    return (-1);
    //
    //  /* This part of the code is shared by both dead and alive envs. */
    //
    //  /* Allocate the kernel stack. */
    //  /* The environnement is at the very bottom of the stack. */
    //  if ((stack0 = kmalloc(STACK0_SIZE)) == NULL)
    //    return (-1);
    //  *stack0 = (paddr_t)stack0 + STACK0_SIZE - sizeof(*ctx);
    //  /* setup the env pointer. */
    //  new_env = (examour_env_t *)(stack0 + 1);
    //  ctx = (kevent_cpu_context_t *)*stack0;
    //  /* clean up the env content */
    //  memset(new_env,
    //     PADDR_ERROR,
    //     EXAMOUR_ENV_RW_MAPPING_SIZE);
    //  memset((char *)new_env + EXAMOUR_ENV_RW_MAPPING_SIZE,
    //     0,
    //     sizeof(*new_env) - EXAMOUR_ENV_RW_MAPPING_SIZE);
    //  memset(ctx, 0, sizeof(*ctx));
    //  /* Create the memory context. */
    //  if (_ldt_create(&new_env->ldtr, (paddr_t)new_env) == false)
    //    {
    //      kfree(stack0);
    //      return (-1);
    //    }
    //  for (i = 0; i < n_sections; i++)
    //    {
    //      sections[i].ldt_idx = ldt_add_entry(&new_env->ldtr,
    //                      sections[i].flags,
    //                      sections[i].base_addr,
    //                      sections[i].size);
    //      if (sections[i].ldt_idx == -1)
    //    {
    //      ldt_destroy(&new_env->ldtr);
    //      kfree(new_env);
    //      return (-1);
    //    }
    //      else
    //    {
    //      if ((sections[i].hint & ENV_HINT_CODE))
    //        {
    //          ctx->cs = (sections[i].ldt_idx << 3) |
    //        GET_SEGMENT_PRIV_LEVEL(sections[i].flags) |
    //        SELECTOR_LDT;
    //          ctx->eip = sections[i].offset;
    //          if (eid == PADDR_ERROR)
    //        {
    //          ldt_t *ldt;
    //
    //          ldt = (ldt_t *)new_env->ldtr.base_addr;
    //          eid = (eid_t)get_segment_base_address(ldt[sections[i].ldt_idx]);
    //        }
    //          else
    //        {
    //          /* Only one code segment per env. */
    //          ldt_destroy(&new_env->ldtr);
    //          kfree(new_env);
    //          return (-1);
    //        }
    //          /* save the code section pointer. */
    //          code_section = sections + i;
    //        }
    //      if ((sections[i].hint & ENV_HINT_STACK))
    //        {
    //          if ((defined & ENV_HINT_STACK))
    //        {
    //          /* Only one stack segment can be installed per env. */
    //          ldt_destroy(&new_env->ldtr);
    //          kfree(new_env);
    //          return (-1);
    //        }
    //          defined |= ENV_HINT_STACK;
    //          ctx->ss = (sections[i].ldt_idx << 3) |
    //        GET_SEGMENT_PRIV_LEVEL(sections[i].flags) |
    //        SELECTOR_LDT;
    //          ctx->esp = sections[i].offset;
    //        }
    //      if ((sections[i].hint & ENV_HINT_DS))
    //        {
    //          if ((defined & ENV_HINT_DS))
    //        {
    //          /* Only one ds segment can be installed per env. */
    //          ldt_destroy(&new_env->ldtr);
    //          kfree(new_env);
    //          return (-1);
    //        }
    //          defined |= ENV_HINT_DS;
    //          ctx->ds = (sections[i].ldt_idx << 3) |
    //        GET_SEGMENT_PRIV_LEVEL(sections[i].flags) |
    //        SELECTOR_LDT;
    //          ctx->esi = sections[i].offset;
    //        }
    //      if ((sections[i].hint & ENV_HINT_ES))
    //        {
    //          if ((defined & ENV_HINT_ES))
    //        {
    //          /* Only one es segment can be installed per env. */
    //          ldt_destroy(&new_env->ldtr);
    //          kfree(new_env);
    //          return (-1);
    //        }
    //          defined |= ENV_HINT_ES;
    //          ctx->es = (sections[i].ldt_idx << 3) |
    //        GET_SEGMENT_PRIV_LEVEL(sections[i].flags) |
    //        SELECTOR_LDT;
    //          ctx->edi = sections[i].offset;
    //        }
    //      if ((sections[i].hint & ENV_HINT_FS))
    //        {
    //          if ((defined & ENV_HINT_FS))
    //        {
    //          /* Only one fs segment can be installed per env. */
    //          ldt_destroy(&new_env->ldtr);
    //          kfree(new_env);
    //          return (-1);
    //        }
    //          defined |= ENV_HINT_FS;
    //          ctx->fs = (sections[i].ldt_idx << 3) |
    //        GET_SEGMENT_PRIV_LEVEL(sections[i].flags) |
    //        SELECTOR_LDT;
    //        }
    //      if ((sections[i].hint & ENV_HINT_GS))
    //        {
    //          if ((defined & ENV_HINT_GS))
    //        {
    //          /* Only one gs segment can be installed per env. */
    //          ldt_destroy(&new_env->ldtr);
    //          kfree(new_env);
    //          return (-1);
    //        }
    //          defined |= ENV_HINT_GS;
    //          ctx->gs = (sections[i].ldt_idx << 3) |
    //        GET_SEGMENT_PRIV_LEVEL(sections[i].flags) |
    //        SELECTOR_LDT;
    //        }
    //    }
    //    }
    //
    //  /* Magic line to give full io access. temporary. */
    //  ctx->eflags = EFLAGS_IOPL3;
    //
    //  /* The eid is the base address of the code segment. */
    //  /* We do it because it allow an easy check of the caller */
    //  /* on an event or syscall and let us control more efficiently */
    //  /* the access to resources through the caps. */
    //  /* resources allocations are code segment oriented on ExAmour. */
    //  new_env->eid = eid;
    //
    //  /* eventually, set the state */
    //  new_env->state = env_stopped;
    //
    //  if ((basic_cap & CAP_ALIVE))
    //    {
    //      /* Running env. */
    //      /* Give it few time. */
    //      if (_timeslice_add(50, 0, &new_env) == false)
    //    {
    //      ldt_destroy(&new_env->ldtr);
    //      kfree(new_env);
    //      return (-1);
    //    }
    //
    //      /* Add the env to the alive envs list. */
    //      _register_new_alive_env(new_env);
    //      return (eid);
    //    }
    //  else
    //    {
    //      int       ret;
    //
    //      /* Dynamic library. */
    //      /* Now add the code entry of the dynamic library in the ldt of the */
    //      /* running env. */
    //      ret = ldt_add_entry(&gl_current_env->ldtr,
    //              code_section->flags,
    //              code_section->base_addr,
    //              code_section->size);
    //      if (ret == -1)
    //    {
    //      ldt_destroy(&new_env->ldtr);
    //      kfree(new_env);
    //      return (-1);
    //    }
    //      /* Add the env to the dead envs list. */
    //      _register_new_dead_env(new_env);
    //      return (ret);
    //    }
    //  return (-1);
}

bool        exaprocess_delete(pid_t pid)
{
  exaprocess_t  *process;

  process = sgl_current_process;
  while (process && process->pid != pid)
  {
    if (process->entries.next == sgl_current_process)
      return (false);
    process = process->entries.next;
  }
  clist_remove(sgl_current_process, process, entries);
  return (true);
}

bool        exaprocess_yield(pid_t pid)
{
  exaprocess_t  *process;

   process = sgl_current_process;
   while (process && process->pid != pid)
   {
     if (process->entries.next == sgl_current_process)
       return (false);
     process = process->entries.next;
   }
   /** TODO: we have found the process, yield it. */
  return (false);
}
