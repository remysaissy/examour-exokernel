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
#include	<examour/core/segment.h>
#include	<examour/mm/ldt.h>
#include	<kbd.h>

#include	"commands.h"
#include	"input_ctl.h"

const command_t	const input_subcommands[] =
  {
    {"help", "?", "Help of the input subcommands.", NULL, do_input_help},
    {"list_keymap", "lkmap", "  Print the available keyboard maps.", NULL, do_input_list_keymap},
    {"set_keymap", "skmap", "   Set a keyboard map", NULL, do_input_set_keymap},
    {NULL, NULL, NULL, NULL}
  };

int		do_input_help(void)
{
  puts("Input commands list:\n");
  list_commands(input_subcommands);
  return (0);
}

int		do_input_list_keymap(void)
{
  kbd_list_keymap();
  return (0);
}

int		do_input_set_keymap(void)
{
  char		*arg;

  arg = parse_next_arg();
  kbd_set_kbd_map(arg);
  return (0);
}
