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
#include	"os_ctl.h"

const command_t	const os_subcommands[] =
  {
    {"help", "?", "Help of the operating system subcommands.", NULL, do_os_help},
    {"drivers", NULL, "Operating system's drivers control.", drivers_subcommands, NULL},
    {"mm", NULL, "Memory commands.", mm_subcommands, NULL},
    {"segment", NULL, "Memory segments and registers.", segments_subcommands, NULL},
    {"upcalls", NULL, "Upcall functionalities.", upcalls_subcommands, NULL},
    {"heap_buffer_overflow", "hbof", "Attempt to exploit a heap buffer overflow", NULL, do_os_hbof},
    {"stack_buffer_overflow", "sbof", "Attempt to exploit a stack buffer overflow", NULL, do_os_sbof},
    {NULL, NULL, NULL, NULL, NULL}
  };

static char	shellcode[2] = "\xeb\xfe";

void		segment_outofbound(kevent_cpu_context_t *arg);

int		do_os_help(void)
{
  puts("OS commands list:\n");
  list_commands(os_subcommands);
  return (0);
}

int		do_os_hbof(void)
{
  void		(*f)();

  puts("Atempt to exploit a data buffer overflow...\n");
  f = (void *)shellcode;
  f();
  puts("Exploitation failed!\n");
  return (0);
}

int		do_os_sbof(void)
{
  char		sbof[2] = "\xeb\xfe";
  void		(*f)();

  puts("Attempt to exploit a stack buffer overflow...\n");
  set_exception_handler(5, (paddr_t)_segment_outofbound);
  f = (void *)sbof;
  f();
  unset_exception_handler(5);
  puts("Exploitation failed!\n");
  return (0);
}
