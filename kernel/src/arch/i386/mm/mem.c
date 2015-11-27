/*
** This file is part of exAmour

** Copyright (C) Remy Saissy <remy.saissy@epitech.net>
** exAmour is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 2 of the License, or
** (at your option) any later version.

** exAmour is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.

** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

/* exAmour's memory manager layer 1/2 */
/* Kernel memory allocator */

#include	<examour/mm/mem.h>
#include	<examour/support/string.h>
#include	<examour/mm/phymem.h>
#include	<examour/mm/ldt.h>

void	mem_init(paddr_t *first_env, int first_env_size)
{
  phymem_init(first_env, first_env_size);
  ldt_init();
}

void	*kmalloc(size_t size)
{
  paddr_t	paddr;

  phymem_ref_new(&paddr, size, REGULAR_ZONE|EXCLUSIVE);
  return ((void *)paddr);
}

void	*kcalloc(size_t size)
{
  paddr_t	paddr;

  if (phymem_ref_new(&paddr, size, REGULAR_ZONE|EXCLUSIVE) == false)
    return (NULL);
  memset((void *)paddr, size, 0);
  return ((void *)paddr);
}

void	kfree(void *p)
{
  phymem_unref((paddr_t)p);
}
