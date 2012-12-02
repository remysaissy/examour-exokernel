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

#include	"parser.h"

static char	*unparsed_string = NULL;
static char	*current_begin = NULL;
static char	*current_end = NULL;

void	begin_parse(char *arg)
{
  unparsed_string = arg;
  current_begin = NULL;
  current_end = arg;
}

void	end_parse(void)
{
  unparsed_string = NULL;
  current_begin = NULL;
  current_end = NULL;
}

char	*parse_next_arg(void)
{
  char	*s;

  s = NULL;
  current_begin = current_end;
  if (current_begin != NULL && *current_begin)
    {
      while (*current_begin &&
	     (*current_begin == ' ' ||
	     *current_begin == '\t' ||
	     *current_begin == '\n'))
	current_begin++;
      if (current_begin)
	{
	  s = current_begin;
	  current_end = current_begin;
	  while (*current_end &&
		 *current_end != ' '
		 && *current_end != '\t'
		 && *current_end != '\n')
	    current_end++;
	  if (*current_end)
	    *current_end++ = '\0';
	}
    }
  return (s);
}

void		list_commands(const command_t const *_commands)
{
  int		j;

  for (j = 0; _commands[j].id != NULL; j++)
    {
      if (_commands[j].id != NULL)
	puts(_commands[j].id);
      if (_commands[j].alias != NULL)
	{
	  puts(" (");
	  puts(_commands[j].alias);
	  puts("):\t");
	}
      if (_commands[j].desc != NULL)
	{
	  puts(":\t");
	  puts(_commands[j].desc);
	}
      putchar('\n');
    }
}
