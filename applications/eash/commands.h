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

#ifndef	__COMMANDS_H__
#define	__COMMANDS_H__

#include	<stdbool.h>

#include	"parser.h"

extern const command_t	const drivers_subcommands[];

extern const command_t	const env_subcommands[];

extern const command_t	const fs_subcommands[];

extern const command_t	const input_subcommands[];

extern const command_t	const mm_subcommands[];

extern const command_t	const os_subcommands[];

extern const command_t	const performance_subcommands[];

extern const command_t	const segments_subcommands[];

extern const command_t	const terminal_subcommands[];

extern const command_t	const	upcalls_subcommands[];

extern const command_t	const video_subcommands[];

/* Useful command flags. */
/* Any command prefixed by the keyword 'no' negate the command. */
bool		is_negation;


#endif /* __COMMANDS_H__ */
