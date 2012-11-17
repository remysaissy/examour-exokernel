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

/* This is the maximum possible hdr_mem_blk_get with 4kb of memory. */
#define HDR_MEM_BLK_N_ITERATIONS 1024

/* Populated by Testexamem_hdr_mem_blk_get and freed by Testexamem_hdr_mem_blk_free. */
static   mem_blk_t  *sgl_hdr_mem_blk_tab[HDR_MEM_BLK_N_ITERATIONS] = {NULL,};

void Testexamem_hdr_mem_blk_get(CuTest* tc)
{
  bool  ret;
  int   i;
  void    *p;

  for (i = 0; i < HDR_MEM_BLK_N_ITERATIONS; i++)
  {

    ret = hdr_mem_blk_get(&p);
    sgl_hdr_mem_blk_tab[i] = p;
    CuAssertTrue(tc, ret);
  }
}

void Testexamem_hdr_mem_blk_get_with_invalid_pointer(CuTest* tc)
{
  bool  ret;

  ret = hdr_mem_blk_get(NULL);
  CuAssertTrue(tc, !ret);
}

void Testexamem_hdr_mem_blk_free(CuTest* tc)
{
  uint32_t  count;
  int   i;

   count = hdr_mem_blk_get_counter();
  for (i = 0; i < HDR_MEM_BLK_N_ITERATIONS; i++)
    hdr_mem_blk_free(sgl_hdr_mem_blk_tab[i]);
  CuAssertTrue(tc, (count == hdr_mem_blk_get_counter() - HDR_MEM_BLK_N_ITERATIONS));

}

void Testexamem_hdr_mem_blk_rationalize(CuTest *tc)
{
  uint32_t  count;

  count = hdr_mem_blk_get_counter();
  hdr_mem_blk_rationalize();
  CuAssertTrue(tc, (count > hdr_mem_blk_get_counter()));
}

void Testexamem_hdr_mem_blk_free_with_invalid_pointer(CuTest* tc)
{
  uint32_t  count;

  count = hdr_mem_blk_get_counter();
  hdr_mem_blk_free(NULL);
  CuAssertTrue(tc, (count == hdr_mem_blk_get_counter()));
}
