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

#include	<examour/event/exception_types.h>
#include	<examour/event/event_types.h>
#include	<examour_api.h>
#include	<vga.h>

/**
 * \warning	The arg pointer is ok but the code must force a ss:offset
 *		access since the generated code rely on data/stack overlapping
 *		which is not the case here.
 */

void		prologue(kevent_cpu_context_t *arg)
{
  puts("Prologue called!\n");
}

void		epilogue(kevent_cpu_context_t *arg)
{
  puts("Epilogue called!\n");
}

void		zerodiv(kevent_cpu_context_t *arg)
{
  printf("division by zero catched!\n");
  while (1);
}

void		segment_outofbound(kevent_cpu_context_t *arg)
{
  puts("Segment out of bounds, buffer overflow exploitation attempt?!\n");
  while (1);
}
