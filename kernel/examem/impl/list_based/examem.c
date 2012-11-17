;/*
** This file is part of ExAmour

** Copyright (C) Rémy Saissy <remy.saissy@gmail.com>
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

#ifdef  __UNIT_TESTING__
#include    <stdlib.h>
#endif

#include    <string.h>
#include	<examem.h>
#include    <exabus.h>

#include "include/hdr_mem_blk.h"
#include	"include/mem_blk.h"
#include    "arch/i386/include/arch_examem.h"

#include    "../debugging/log.h"

void	hdr_mem_blk_dump_state(void);

bool    _examem_init(const exaboot_t const *inf)
{
  uint32_t  total_mem;
  int		i;
  exabus_interface_t    *interface;

	if (mem_blk_init() == false)
		return (false);
	total_mem = 0;
	for (i = 0; i < inf->n_exa_mmap / sizeof(inf->exa_mmap[0]); i++)
	  total_mem += inf->exa_mmap[i].length_low;
	#ifndef __UNIT_TESTING__
	if (total_mem <= 0x1000000)
	  return (false);
    if (mem_blk_populate(0, 0x100000, EXAMEM_TYPE_RESERVED) == false)
          return (false);
    if (mem_blk_populate(0x100000, 0xf00000,  EXAMEM_TYPE_DMA) == false)
              return (false);
    if (mem_blk_populate(0x1000000, total_mem - 0x1000000, EXAMEM_TYPE_REGULAR) == false)
              return (false);
    if (mem_blk_populate(0xfe000000, 0x1ffffff, EXAMEM_TYPE_REGULAR) == false)
                  return (false);
    // TODO: detect memory through E820 interruption.
    // TODO: Do not assume the computer has at least 32mb of RAM.
#else
    for (i = 0; i < inf->n_exa_mmap / sizeof(inf->exa_mmap[0]); i++)
    {
      if (mem_blk_populate(inf->exa_mmap[i].base_addr_low, inf->exa_mmap[i].length_low, inf->exa_mmap[i].type) == false)
        return (false);
    }
#endif
	if (examem_ref_at(inf->kernel_start,
							  inf->kernel_end - inf->kernel_start,
							  EXAMEM_TYPE_REGULAR | EXAMEM_MAP_EXCL_RD | EXAMEM_MAP_EXCL_EXEC | EXAMEM_MAP_EXCL_WR | EXAMEM_SCOPE_SYSTEM) == false)
		return (false);
#ifndef __UNIT_TESTING__
	if (_examem_arch_specific_init(inf) == false)
	  return (false);
#endif
	// TODO: reference the init program.
    interface = examem_ref_new(sizeof(*interface), EXAMEM_TYPE_REGULAR);
    if (interface == NULL)
      return (false);
//    memset(interface, 0, sizeof(*interface));
//    interface->n_symbols = 2;
//    interface->symbols = examem_ref_new(2 * sizeof(*interface->symbols), EXAMEM_TYPE_REGULAR);
//    if (interface->symbols == NULL)
//      return (false);
//    memset(interface->symbols, 0, sizeof(*interface->symbols));
//    interface->symbols[0].id = "ldt_add_entry";
//    interface->symbols[0].type = EXABUS_SYMBOL_METHOD;
//    strcpy(interface->symbols[0].in, "pII\0\0\0");
//    strcpy(interface->symbols[0].out, "i\0\0\0\0\0");
//    interface->symbols[0].cb = (paddr_t)examem_ldt_add_entry;
//    interface->symbols[1].id = "ldt_remove_entry";
//    interface->symbols[1].type = EXABUS_SYMBOL_METHOD;
//    strcpy(interface->symbols[1].in, "i\0\0\0\0\0");
//    strcpy(interface->symbols[1].out, "b\0\0\0\0\0");
//    interface->symbols[1].cb = (paddr_t)examem_ldt_remove_entry;
//    if (exabus_publish("kernel", "examem", interface) == false)
//      return (false);
//    examem_unref(interface->symbols);
//    examem_unref(interface);
    message("examem initialization completed.\n");
	return (true);
}

void *examem_ref_new(size_t size, int flags)
{
  paddr_t   addr;

  if (mem_blk_ref_by_size(&addr, size, flags) == false)
    return (NULL);
  return ((void *)addr);
}


bool    examem_ref_at(paddr_t addr, size_t size, int flags)
{
  return (mem_blk_ref_by_addr(addr, size, flags));
}

void examem_unref(void *addr)
{
  mem_blk_unref((paddr_t)addr);
}

void    examem_rationalize(void)
{
  hdr_mem_blk_rationalize();
}
