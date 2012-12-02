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

#ifndef	__PARSER_H__
#define	__PARSER_H__

typedef struct			command_s
{
  const char			*id;
  const char			*alias;
  const char			*desc;
  const struct command_s	const *subcommands;
  int				(*command)(void);

}				command_t;

void	begin_parse(char *arg);

void	end_parse(void);

char	*parse_next_arg(void);

void	list_commands(const command_t const *_command);


#endif /* __PARSER_H__ */
