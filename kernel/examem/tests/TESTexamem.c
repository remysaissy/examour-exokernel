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

#include	<stdlib.h>

#include	<examem.h>

#include	<CuTest.h>

/** @note Tests contained in that file require a sequential execution. */

/**
 * The memory used for unit testing.
 */
#define HDR_MEM_VMEM_SIZE       4096000

/**
 * Base adress of the memory allocated for tests.
 */
paddr_t     gl_examem_base_addr;

/** NOTE: This must be the very first test to be run!!! */
void    Testexamem_init(CuTest* tc)
{
  bool          ret;
  exaboot_t     inf;
  void          *p;

  p = malloc(HDR_MEM_VMEM_SIZE);
  CuAssertPtrNotNull(tc, p);
  inf.exa_mmap = malloc(sizeof(*inf.exa_mmap));
  CuAssertPtrNotNull(tc, inf.exa_mmap);
  gl_examem_base_addr = (paddr_t)p;
  inf.exa_mmap[0].base_addr_low = (unsigned long)p;
  inf.exa_mmap[0].base_addr_high = 0;
  inf.exa_mmap[0].length_low = HDR_MEM_VMEM_SIZE;
  inf.exa_mmap[0].length_high = 0;
  inf.exa_mmap[0].type = EXAMEM_TYPE_REGULAR;
  inf.n_exa_mmap = sizeof(inf.exa_mmap[0]);
  inf.init_start = (unsigned long)p;
  inf.init_end = (unsigned long)p + 100;
  inf.kernel_start = (unsigned long)p + 110;
  inf.kernel_end = (unsigned long)p + 200;
  ret = _examem_init(&inf);
  free(inf.exa_mmap);
  CuAssertTrue(tc, ret);
}
