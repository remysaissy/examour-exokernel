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
/* #include        <tgfs.h> */

#include	"commands.h"
#include	"fs_ctl.h"

const command_t	const fs_subcommands[] = 
  {
    {"help", "?", "Help of the filesystems subcommands.", NULL, do_fs_help},
/*     {"tgfs_testsuite", "tgfs", "Run the tgfs test suite.", NULL, do_tgfs}, */
    {NULL, NULL, NULL, NULL, NULL}
  };

int	do_fs_help(void)
{
  puts("Filesystems commands list:\n");
  list_commands(fs_subcommands);
  return (0);
}

int		do_tgfs(void)
{
  puts("Not compiled in.\n");
/*   tgfs_test_suite(); */
  return (0);
}
