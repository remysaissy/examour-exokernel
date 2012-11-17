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

#include	"commands.h"
#include	"terminal_ctl.h"

extern const char	const *examour_banner;

const command_t	const terminal_subcommands[] =
  {
    {"help", "?", "Help of the terminal subcommands.", NULL, do_terminal_help},
    {"clear_screen", "cls", "   Clear the screen", NULL, do_terminal_cls},
    {"echo", "e", "             Print a string on the screen.", NULL, do_terminal_print},
    {"banner", "b", "           Print the banner of the project.", NULL, do_terminal_banner},
    {NULL, NULL, NULL, NULL, NULL},
  };

int	do_terminal_help(void)
{
  puts("Terminal subcommands list:\n");
  list_commands(terminal_subcommands);
  return (0);
}

int		do_terminal_banner(void)
{
  char		*arg;

  arg = parse_next_arg();
  puts(examour_banner);
  return (0);
}

int		do_terminal_print(void)
{
  char		*arg;

  while ((arg = parse_next_arg()))
    printf("%s \n", arg);
  return (0);
}

int		do_terminal_cls(void)
{
  cls();
  return (0);
}
