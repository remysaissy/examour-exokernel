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

#include	<stddef.h>
#include	<vga.h>
#include	<examour_api.h>
#include	<kbd.h>

#include	"commands.h"
#include	"shell.h"

static const command_t	const commands[] =
  {
    {"help", "?", "\t\t\t The command list.", NULL, do_help},
    {"version", "v", "\t\t  Print the version.", NULL, do_version},
    {"os", NULL, "Operating system features control.", os_subcommands, NULL},
    {"terminal", "term", "Terminal control.", terminal_subcommands, NULL},
    {"env", NULL, "Environment control.", env_subcommands, NULL},
    {"performance", "perf", "Performance control.", performance_subcommands, NULL},
    {NULL, NULL, NULL, NULL, NULL}
  };

static char		buff[255];

int		do_version(void)
{
  puts("eash, the ExAmour Shell. v0.1.\n");
  return (0);
}

int		do_help(void)
{
  puts("Command list:\n");
  list_commands(commands);
  return (0);
}

int		command_exec(char *cmd)
{
  int		i;
  char		*arg;
  const command_t	const *current_commands;
  
  begin_parse(cmd);
  current_commands = commands;
  is_negation = false;
  while (1)
    {
      arg = parse_next_arg();
      if (arg == NULL)
	break;
      if (!strcmp("no", arg))
	{
	  /* This is a negation of the command. */
	  is_negation = true;
	  continue;
	}
      for (i = 0; current_commands[i].id != NULL; i++)
	{
	  if ((current_commands[i].id != NULL && !strcmp(current_commands[i].id, arg)) ||
	      (current_commands[i].alias != NULL && !strcmp(current_commands[i].alias, arg)))
	    {
	      if ((void *)current_commands[i].command != NULL)
		return (current_commands[i].command());
	      else
		current_commands = current_commands[i].subcommands;
	      break;
	    }
	}
    }
  return (-1);
}

void		run_shell(void)
{
  int		cnt;

  while (1)
    {
      puts("eash$> ");
      while ((cnt = kbd_read(buff, 254)) <= 0)
	;
      buff[--cnt] = 0;
      if (*buff)
	if (command_exec(buff) == -1)
	  puts("Command not found.\n");
    }
}
