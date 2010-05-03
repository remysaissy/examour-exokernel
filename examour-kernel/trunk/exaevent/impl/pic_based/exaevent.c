/*
** This file is part of ExAmour

** Copyright (C) Remy Saissy <remy.saissy@gmail.com>
** examour is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 2 of the License, or
** (at your option) any later version.

** examour is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.

** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#include	<exaevent.h>

#include    "include/internal.h"
#include    "arch/i386/include/pic.h"

#include	"../debugging/log.h"

bool    _exaevent_init(const exaboot_t * const inf)
{
	if (_exaevent_io_init() == false)
	  return (false);
    if (exavent_initialize_intr() == false)
      return (false);
    message("exaevent initialization completed.\n");
    return (true);
}
