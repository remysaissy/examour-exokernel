/*
** This file is part of ExAmour

** Copyright (C) Remy Saissy <remy.saissy@gmail.com>
** ExAmour is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 2 of the License, or
** (at your option) any later version.

** ExAmour is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.

** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#ifndef TSS_H_
#define TSS_H_

/**
 * This file contains declarations and types for Task Segment Selector.
 */

#include    <stdint.h>

/**
 * \brief   The size of the IO bitmap in bytes.
 */
#define IO_BITMAP_SIZE  8196


/**
 * \brief   The tss (Task segment selector).
 */
typedef struct  tss_s
{
  selector_t    prev;       /** link to the previous task. */
  uint16_t      reserved0;
  uint32_t       esp0;       /** Top of the ring0 stack. */
  selector_t    ss0;        /** Ring0's stack segment selector. */
  uint16_t      reserved1;
  uint32_t       esp1;       /** Ring1 stack top. */
  selector_t    ss1;        /** Ring1 stack segment selector. */
  uint16_t      reserved2;
  uint32_t       esp2;       /** Ring2 stack top. */
  selector_t    ss2;        /** Ring2 stack segment selector. */
  uint16_t      reserved3;
  cr3_t         cr3;        /** Paged memory register. */
  uint32_t       eip;        /** Program counter. */
  eflags_t      eflags;     /** Task's eflags. */
  gp_regs_t     gpregs;     /** Task's general registers.  */
  selector_t    es;     /** ES data segment selector. */
  uint16_t      reserved4;
  selector_t    cs;     /** CS code segment selector. */
  uint16_t      reserved5;
  selector_t    ss;     /** SS stack segment selector. */
  uint16_t      reserved6;
  selector_t    ds;     /** DS data segment selector. */
  uint16_t      reserved7;
  selector_t    fs;     /** FS data segment selector. */
  uint16_t      reserved8;
  selector_t    gs;     /** GS data segment selector. */
  uint16_t      reserved9;
  selector_t    ldtsel;     /** Task's LDT selector. */
  uint16_t      reserved10;
  bool          t : 1;      /** Debug. */
  uint16_t      reserved11 : 15;
  uint16_t      iobase;     /** Offset of the iomap in the tss. */
  uint8_t       iomap[IO_BITMAP_SIZE]; /** The iomap. 8KB bitfield. */

}         __attribute__((packed))       tss_t;


#endif /* TSS_H_ */
