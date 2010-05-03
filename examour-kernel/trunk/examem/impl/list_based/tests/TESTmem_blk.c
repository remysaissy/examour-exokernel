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
#include    "../include/hdr_mem_blk.h"
#include    "../include/mem_blk.h"

#include	<CuTest.h>

/** @note Tests contained in that file require a sequential execution. */

extern paddr_t     gl_examem_base_addr;

void    Testexamem_mem_blk_ref_by_size(CuTest* tc)
{
  bool      ret;
  paddr_t   addr;

  ret = mem_blk_ref_by_size(&addr, 4096, EXAMEM_TYPE_REGULAR);
  CuAssertTrue(tc, ret);
}

void    Testexamem_mem_blk_ref_by_size_with_invalid_size(CuTest* tc)
{
  bool      ret;
  paddr_t   addr;

  ret = mem_blk_ref_by_size(&addr, 0, EXAMEM_TYPE_REGULAR);
  CuAssertTrue(tc, !ret);
}

void    Testexamem_mem_blk_ref_by_size_with_invalid_flags(CuTest* tc)
{
  bool      ret;
  paddr_t   addr;

  ret = mem_blk_ref_by_size(&addr, 32, EXAMEM_TYPE_DMA);
  CuAssertTrue(tc, !ret);
}

void    Testexamem_mem_blk_ref_by_size_with_8b_alignment(CuTest* tc)
{
  bool      ret;
  paddr_t   addr;

  ret = mem_blk_ref_by_size(&addr, 32, EXAMEM_TYPE_REGULAR | EXAMEM_ALIGNED_8B);
  CuAssertTrue(tc, ret);
  CuAssertTrue(tc, !(addr & 0x7));
}

void    Testexamem_mem_blk_ref_by_size_with_16b_alignment(CuTest* tc)
{
  bool      ret;
  paddr_t   addr;

  ret = mem_blk_ref_by_size(&addr, 32, EXAMEM_TYPE_REGULAR | EXAMEM_ALIGNED_16B);
  CuAssertTrue(tc, ret);
  CuAssertTrue(tc, !(addr & 0xf));
}

void    Testexamem_mem_blk_ref_by_size_with_4kb_alignment(CuTest* tc)
{
  bool      ret;
  paddr_t   addr;

  ret = mem_blk_ref_by_size(&addr, 32, EXAMEM_TYPE_REGULAR | EXAMEM_ALIGNED_4KB);
  CuAssertTrue(tc, ret);
  CuAssertTrue(tc, !(addr & 0xfff));
}

void    Testexamem_mem_blk_ref_by_size_with_4mb_alignment(CuTest* tc)
{
  bool      ret;
  paddr_t  addr;

  ret = mem_blk_ref_by_size(&addr, 32, EXAMEM_TYPE_REGULAR | EXAMEM_ALIGNED_4MB);
  CuAssertTrue(tc, ret);
  CuAssertTrue(tc, !(addr & 0x3fffff));
}

void    Testexamem_mem_blk_ref_by_address(CuTest* tc)
{
  bool  ret;
  paddr_t   addr;

  ret = mem_blk_ref_by_size(&addr, 32, EXAMEM_TYPE_REGULAR);
  CuAssertTrue(tc, ret);
  ret = mem_blk_ref_by_addr(addr, 32, EXAMEM_TYPE_REGULAR);
  CuAssertTrue(tc, ret);
  mem_blk_unref(addr);
  ret = mem_blk_ref_by_addr(addr, 32, EXAMEM_TYPE_REGULAR);
  CuAssertTrue(tc, ret);
  mem_blk_unref(addr);
}

void    Testexamem_mem_blk_ref_by_address_with_invalid_addr(CuTest* tc)
{
  bool  ret;

  ret = mem_blk_ref_by_addr(8, 32, EXAMEM_TYPE_REGULAR);
  CuAssertTrue(tc, !ret);
}

void    Testexamem_mem_blk_ref_by_address_with_invalid_size(CuTest* tc)
{
  bool  ret;

  ret = mem_blk_ref_by_addr(gl_examem_base_addr + 11000, 0, EXAMEM_TYPE_REGULAR);
  CuAssertTrue(tc, !ret);
  ret = mem_blk_ref_by_addr(gl_examem_base_addr + 11000, (size_t)-1, EXAMEM_TYPE_REGULAR);
  CuAssertTrue(tc, !ret);
}

void    Testexamem_mem_blk_ref_by_address_with_invalid_flags(CuTest* tc)
{
  bool  ret;

  ret = mem_blk_ref_by_addr(gl_examem_base_addr + 11000, 32, EXAMEM_TYPE_ACPI);
  CuAssertTrue(tc, !ret);
}

void    Testexamem_mem_blk_unref(CuTest* tc)
{
  bool      ret;
  paddr_t  addr;
  unsigned int  counter;

  ret = mem_blk_ref_by_size(&addr, 32, EXAMEM_TYPE_REGULAR);
  CuAssertTrue(tc, ret);
  counter = hdr_mem_blk_get_counter();
  mem_blk_unref(addr);
  CuAssertTrue(tc, (counter < hdr_mem_blk_get_counter()));
}

void    Testexamem_mem_blk_unref_with_invalid_value(CuTest* tc)
{
  unsigned int  counter;

  counter = hdr_mem_blk_get_counter();
  mem_blk_unref(gl_examem_base_addr + 42);
  CuAssertTrue(tc, (counter == hdr_mem_blk_get_counter()));
}
