/* 
 * This file is part of eash

 * Copyright (C) Remy Saissy <remy.saissy@gmail.com>
 * eash is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.

 * eash is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#include	<vga.h>
#include	<examour_api.h>

#include	"upcalls.h"
#include	"commands.h"
#include	"upcalls_ctl.h"

const command_t	const	upcalls_subcommands[] =
  {
    {"help", "?", "Help of upcalls subcommands.", NULL, do_upcalls_help},
    {"epilogue_ctl", "ectl", "Control a basic epilogue.", NULL, do_upcalls_epilogue_ctl},
    {"prologue_ctl", "pctl", "Control a basic prologue.", NULL, do_upcalls_prologue_ctl},
    {"exception_ctl", "exctl", "Control exceptions. param: <vector number> [raise]", NULL, do_upcalls_exception_ctl},
    {NULL, NULL, NULL, NULL, NULL}
  };

/* static const	char		*exception_name[] = */
/*   { */
/*     "EXCEPTION_DIVIDE_ERROR", */
/*     "EXCEPTION_DEBUG", */
/*     "EXCEPTION_NMI_INTR", */
/*     "EXCEPTION_BREAKPOINT", */
/*     "EXCEPTION_OVERFLOW", */
/*     "EXCEPTION_BOUND_EXCEED", */
/*     "EXCEPTION_INVL_OPCODE", */
/*     "EXCEPTION_DEV_NOT_AVL", */
/*     "EXCEPTION_DOUBLE_FAULT", */
/*     "EXCEPTION_COP_SEG_OVERRUN", */
/*     "EXCEPTION_INVL_TSS", */
/*     "EXCEPTION_SEGMENT_NOT_PRESENT", */
/*     "EXCEPTION_STACK_FAULT", */
/*     "EXCEPTION_GENERAL_PROTECTION", */
/*     "EXCEPTION_PAGE_FAULT", */
/*     "EXCEPTION_UNUSED", */
/*     "EXCEPTION_FPU_ERROR", */
/*     "EXCEPTION_ALIGNMENT_CHECK", */
/*     "EXCEPTION_MACHINE_CHECK", */
/*     "EXCEPTION_SIMD_FPU" */
/*   }; */

int		do_upcalls_help(void)
{
  puts("Upcalls commands list:\n");
  list_commands(upcalls_subcommands);
  return (0);
}

int		do_upcalls_exception_ctl(void)
{
  if (is_negation == false)
    {
      set_exception_handler(EXCEPTION_INVL_OPCODE, (paddr_t)_segment_outofbound);
    }
  else
    {
      unset_exception_handler(EXCEPTION_INVL_OPCODE);
    }
  return (0);
}

int		do_upcalls_prologue_ctl(void)
{
  if (is_negation == false)
    set_prologue((paddr_t)_prologue);
  else
    unset_prologue();
  return (0);
}

int		do_upcalls_epilogue_ctl(void)
{
  if (is_negation == false)
    set_epilogue((paddr_t)_epilogue);
  else
    unset_epilogue();
  return (0);
}

/* int		do_upcalls_zerodiv(void) */
/* { */
/*   int		i; */
/*   int		y; */

/*   set_exception_handler(EXCEPTION_DIVIDE_ERROR, (paddr_t)_zerodiv); */
/*   i = 42; */
/*   y = 0; */
/*   y = i/y; */
/*   unset_exception_handler(EXCEPTION_DIVIDE_ERROR); */
/*   return (0); */
/* } */
