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
#include	"performance_ctl.h"

const command_t	const performance_subcommands[] =
  {
    {"help", "?", "Help of the performance monitoring subcommands.", NULL, do_performance_help},
    {"timestamp", "ts", "Get the timestamp.", NULL, do_performance_get_timestamp},
    {NULL, NULL, NULL, NULL, NULL},
  };

int	do_performance_help(void)
{
  puts("Performance commands list:\n");
  list_commands(performance_subcommands);
  return (0);
}

int	do_performance_get_timestamp(void)
{
  uint64_t	ts;

  ts = 0;
  read_timestamp(&ts);
  printf("Timestamp: %u\n", ts);
  return (0);
}
