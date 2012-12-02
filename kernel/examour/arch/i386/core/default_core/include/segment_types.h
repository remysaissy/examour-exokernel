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
** Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef	__SEGMENT_TYPES_H__
#define	__SEGMENT_TYPES_H__

#include	"reg_types.h"
#include	"segment_enum.h"
#include	<examour/attributes.h>
#include	<examour/mm/mem_types.h>

/* Segments of the gdt */

/**
 * \brief	Index of the gdt's null descriptor
 */
#define	GDT_SEG_NULL		0

/**
 * \brief	Index of the gdt's kernel code descriptor
 */
#define	GDT_SEG_KCODE		1

/**
 * \brief	Index of the gdt's kernel data descriptor
 */
#define	GDT_SEG_KDATA		2

/**
 * \brief	List of the dead envs.
 */
#define	GDT_SEG_DEAD_ENVS	3

/**
 * \brief	Index of the gdt's kernel ldt descriptor
 */
#define	GDT_SEG_LDT		4

/**
 * \brief	Index of the gdt's kernel tss descriptor
 */
#define	GDT_SEG_TSS		5

/**
 * \brief	Index of the gdt's env's upcall code descriptor
 */
#define	GDT_SEG_UCODE		6

/**
 * \brief	The number of gdt entries
 */
#define	GDT_NR_ENTRIES		8

/* base address and limit definitions. */

/**
 * \brief	The kernel code segment base address.
 */
#define	GDT_KCODE_BASE	0

/**
 * \brief	The kernel code segment length.
 */
#define	GDT_KCODE_LIMIT	0xffffffff

/**
 * \brief	The kernel data segment base address.
 */
#define	GDT_KDATA_BASE	0

/**
 * \brief	The kernel data segment length.
 */
#define	GDT_KDATA_LIMIT	0xffffffff


/**
 * \brief	Filled later during the env init call.
 */
#define	GDT_DEAD_ENVS_BASE	0

/**
 * \brief	Filled later during the env init call.
 */
#define	GDT_DEAD_ENVS_LIMIT	0

/**
 * \brief	Filled later during the env init call.
 */
#define	GDT_LDT_BASE	0

/**
 * \brief	Filled later during the env init call.
 */
#define	GDT_LDT_LIMIT	0

/**
 * \brief	Filled later during the env init call.
 */
#define	GDT_TSS_BASE	0

/**
 * \brief	Filled later during the env init call.
 */
#define	GDT_TSS_LIMIT	0

/**
 * \brief	The size of the IO bitmap in bytes.
 */
#define	IO_BITMAP_SIZE	8196


#ifndef	__ASM__

#include	<stdint.h>

/**
 * \brief       Segment selector.
 */
typedef uint16_t	selector_t;

#pragma pack(push,1)

/**
 * \brief	Segment table register. Generic structure.
 */
typedef struct  PACKED	dtr_s
{
  uint16_t		limit;	   /** Size of the segment in bytes - 1. */
  paddr_t		base_addr; /** Base address of the segment. */

}			dtr_t;

#pragma pack(pop)

/**
 * \brief	Global descriptor table register.
 */
typedef dtr_t	gdtr_t;

/**
 * \brief	Local descriptor table register.
 */
typedef	dtr_t	ldtr_t;

/**
 * \brief	Interrupt descriptor table register.
 */
typedef dtr_t	idtr_t;

/**
 * \brief	Descriptor table.
 */
typedef uint32_t	dt_t[2];

/**
 * \brief	Interrupt gate.
 */
typedef dt_t		gate_t;

/**
 * \brief	Local descriptor table.
 */
typedef dt_t		ldt_t;

/**
 * \brief	Global descriptor table.
 */
typedef dt_t		gdt_t;


#pragma pack(push,1)

/**
 * \brief	The tss (Task segment selector).
 */
typedef struct PACKED	tss_s
{
  selector_t		prev;		/** link to the previous task. */
  uint16_t		reserved0;
  paddr_t		esp0;		/** Top of the ring0 stack. */
  selector_t		ss0;		/** Ring0's stack segment selector. */
  uint16_t		reserved1;
  paddr_t		esp1;		/** Ring1 stack top. */
  selector_t		ss1;		/** Ring1 stack segment selector. */
  uint16_t		reserved2;
  paddr_t		esp2;		/** Ring2 stack top. */
  selector_t		ss2;		/** Ring2 stack segment selector. */
  uint16_t		reserved3;
  cr3_t			cr3;		/** Paged memory register. */
  paddr_t		eip;		/** Program counter. */
  eflags_t		eflags;		/** Task's eflags. */
  gp_regs_t		gpregs;		/** Task's general registers.  */
  selector_t		es;		/** ES data segment selector. */
  uint16_t		reserved4;
  selector_t		cs;		/** CS code segment selector. */
  uint16_t		reserved5;
  selector_t		ss;		/** SS stack segment selector. */
  uint16_t		reserved6;
  selector_t		ds;		/** DS data segment selector. */
  uint16_t		reserved7;
  selector_t		fs;		/** FS data segment selector. */
  uint16_t		reserved8;
  selector_t		gs;		/** GS data segment selector. */
  uint16_t		reserved9;
  selector_t		ldtsel;		/** Task's LDT selector. */
  uint16_t		reserved10;
  bool			t : 1;		/** Debug. */
  uint16_t		reserved11 : 15;
  uint16_t		iobase;		/** Offset of the iomap in the tss. */
  /** \todo	Add and use the iomap for ioperms. */
/*   uint8_t		iomap[IO_BITMAP_SIZE]; /\** The iomap. 8KB bitfield. *\/ */

}			tss_t;

#pragma pack(pop)

#endif /* __ASM__ */

#endif /* __SEGMENT_TYPES_H__ */
