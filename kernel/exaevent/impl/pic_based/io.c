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

#include    <exaevent.h>
#include    <examem.h>
#include    <exaprocess.h>

#include    <string.h>

#include    "include/internal.h"


/** Array of I/O. 0 means not granted, any other value is the pid of the process granted. */
static pid_t   *sgl_io_array = NULL;
static uint16_t sgl_nb_io = 0;

bool    _exaevent_io_init(void)
{
  /* TODO: retrieving it from MSR. */
  sgl_nb_io = 256;
  sgl_io_array = examem_ref_new(sgl_nb_io * sizeof(*sgl_io_array), EXAMEM_TYPE_REGULAR);
  if (sgl_io_array == NULL)
    return (false);
  memset(sgl_io_array, 0, sgl_nb_io * sizeof(*sgl_io_array));
  return (true);
}

bool    exaevent_iogrant(uint16_t ioport)
{
  pid_t current_pid;

  if (ioport >= sgl_nb_io)
    return (false);
  current_pid = exaprocess_get_current_pid();
  if (sgl_io_array[ioport] != 0)
    return (false);
  exaprocess_grant_io(ioport);
  sgl_io_array[ioport] = current_pid;
  return (true);
}

bool    exaevent_iorevoke(uint16_t ioport)
{
  pid_t current_pid;

  if (ioport >= sgl_nb_io)
    return (false);
  current_pid = exaprocess_get_current_pid();
  if (sgl_io_array[ioport] != current_pid)
    return (false);
  exaprocess_revoke_io(ioport);
  sgl_io_array[ioport] = 0;
  return (true);
}
