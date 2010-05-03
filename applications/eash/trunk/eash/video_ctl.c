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

#include	"commands.h"
#include	"video_ctl.h"

const command_t	const video_subcommands[] =
  {
    {"help", "?", "Help of the video subcommands.", NULL, do_video_help},
    {"list_fg_colors", "lfgc", "List available foreground colors", NULL, do_video_list_fg_colors},
    {"set_fg_color", "sfgc", "  Set a font color", NULL, do_video_set_fg_color},
    {"list_bg_colors", "lbgc", "List available background colors", NULL, do_video_list_bg_colors},
    {"set_bg_color", "sbgc", "  Set a background color", NULL, do_video_set_bg_color},
    {NULL, NULL, NULL, NULL, NULL},
  };

int		do_video_help(void)
{
  puts("Video commands:\n");
  list_commands(video_subcommands);
  return (0);
}

int		do_video_set_bg_color(void)
{
  char		*arg;

  arg = parse_next_arg();
  set_background_color(arg);
  return (0);
}

int		do_video_list_bg_colors(void)
{
  list_bg_colors();
  return (0);
}

int		do_video_set_fg_color(void)
{
  char		*arg;

  arg = parse_next_arg();
  set_foreground_color(arg);
  return (0);
}

int		do_video_list_fg_colors(void)
{
  list_fg_colors();
  return (0);
}
