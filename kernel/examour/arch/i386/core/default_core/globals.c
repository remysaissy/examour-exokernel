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

#include	<examour/core/globals.h>

/* gdt of the system. macros used are from segment.h. */
/* The gdt is setup in base/asm/bootstrap.S */
gdt_t	gl_gdt[GDT_NR_ENTRIES] __ALIGNED__(4096) =
{
    [GDT_SEG_NULL] = _set_null_segment,
    [GDT_SEG_KCODE] =_set_segment(SEGMENT_TYPE_CODE_EXEC,
				  GDT_KCODE_BASE,
				  GDT_KCODE_LIMIT,
				  SEGMENT_PRIV_0,
				  SEGMENT_GRANULARITY_4KB,
				  SEGMENT_32BITS),
    [GDT_SEG_KDATA] = _set_segment(SEGMENT_TYPE_DATA_RW,
				   GDT_KDATA_BASE,
				   GDT_KDATA_LIMIT,
				   SEGMENT_PRIV_0,
				   SEGMENT_GRANULARITY_4KB,
				   SEGMENT_32BITS),
    [GDT_SEG_DEAD_ENVS] = _set_segment(SEGMENT_TYPE_DATA_RD,
				       GDT_DEAD_ENVS_BASE,
				       GDT_DEAD_ENVS_LIMIT,
				       SEGMENT_PRIV_3,
				       SEGMENT_GRANULARITY_BYTE,
				       SEGMENT_32BITS),
    [GDT_SEG_LDT] = _set_segment(SEGMENT_TYPE_LDT,
				 GDT_LDT_BASE,
				 GDT_LDT_LIMIT,
				 SEGMENT_PRIV_3,
				 SEGMENT_GRANULARITY_BYTE,
				 SEGMENT_32BITS),
    [GDT_SEG_TSS] = _set_segment(SEGMENT_TYPE_TSS_32BITS,
				 GDT_TSS_BASE,
				 GDT_TSS_LIMIT,
				 SEGMENT_PRIV_0,
				 SEGMENT_GRANULARITY_BYTE,
				 SEGMENT_32BITS),
    [GDT_SEG_UCODE] =_set_segment(SEGMENT_TYPE_CODE_EXEC,
				  GDT_KCODE_BASE,
				  GDT_KCODE_LIMIT,
				  SEGMENT_PRIV_0,
				  SEGMENT_GRANULARITY_4KB,
				  SEGMENT_32BITS),
  };

/* assume that IDT_BASE_EXCEPTION < IDT_BASE_INTR < IDT_BASE_SYSCALL */
gate_t				*gl_idt = NULL;

examour_env_t			*gl_current_env = NULL;

examour_env_informations_t	gl_envs = {0, };

examour_timeslice_t		*gl_timeslices = NULL;

multiboot_info_t		*mbi = NULL;

tss_t				gl_tss = {0, };
