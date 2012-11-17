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

#ifndef SEGMENTS_H_
#define SEGMENTS_H_

#include    <stdint.h>
#include    <stddef.h>

/**
 * This file contains segment descriptions and declarations
 * for the i386 architecture.
 */

/* Intel vol3 System programming. Section 3.10: protected mode mm. */
/* 0x1000 is implied. */
/* 0x1f00 */

/**
 * \brief   Read only segment.
 */
#define SEGMENT_TYPE_DATA_RD        0x1000

/**
 * \brief   Read write segment.
 */
#define SEGMENT_TYPE_DATA_RW        0x1200

/**
 * \brief   Expdown segment.
 */
#define SEGMENT_EXPDOWN         0x400

/**
 * \brief   Code execute only segment.
 */
#define SEGMENT_TYPE_CODE_EXEC      0x1800

/**
 * \brief   Code execute and readonly segment.
 */
#define SEGMENT_TYPE_CODE_EXEC_RD   0x1a00

/**
 * \brief   Conforming segment.
 */
#define SEGMENT_CONFORMING      0x400

/**
 * \brief   Privilege level 0 segment.
 */
#define SEGMENT_PRIV_0          0

/**
 * \brief   Privilege level 1 segment.
 */
#define SEGMENT_PRIV_1          0x2000

/**
 * \brief   Privilege level 2 segment.
 */
#define SEGMENT_PRIV_2          0x4000

/**
 * \brief   Privilege level 3 segment.
 */
#define SEGMENT_PRIV_3          0x6000

/**
 * \brief   Mask with all the privileges bits.
 */
#define SEGMENT_PRIV_LEVELS     SEGMENT_PRIV_3

/**
 * \brief   Shift of the privileges bits.
 */
#define SEGMENT_PRIV_SHIFT      13

/**
 * \param x the flag, typically an uint32_t.
 * \brief   Retrieve the privilege level from a flag.
 */
#define GET_SEGMENT_PRIV_LEVEL(x)           \
(((x) & SEGMENT_PRIV_LEVELS) >> SEGMENT_PRIV_SHIFT)

/*
 * \brief   16bits segment.
 */
#define SEGMENT_16BITS          0

/**
 * \brief   32bits segment.
 */
#define SEGMENT_32BITS          0x400000

/**
 * \brief   64bits segment.
 */
#define SEGMENT_64BITS          0x200000

/* no system type segment for now. */

/* Don't use these macros in ldt_add_entry(). */

/**
 * \brief   code or data segment.
 */
#define SEGMENT_NOT_SYSTEM      0x1000

/**
 * \brief   flag the segment as present.
 */
#define SEGMENT_PRESENT         0x8000

/**
 * \brief   flag the segment as not present.
 */
#define SEGMENT_NO_PRESENT      0

/**
 * \brief   4kb segment's granularity limit (mandatory from 1mb).
 */
#define SEGMENT_GRANULARITY_4KB     0x800000

/**
 * \brief   1b segment's granularity limit (segments up to 1mb).
 */
#define SEGMENT_GRANULARITY_BYTE    0

/**
 * \brief   ldt system segment.
 */
#define SEGMENT_TYPE_LDT        0x200

/**
 * \brief   32 bits tss system segment.
 */
#define SEGMENT_TYPE_TSS_32BITS     0x900


/* Note: present is the 15th bit, */

/* segment selectors */

/**
 * \brief       gdt segment selector.
 */
#define SELECTOR_GDT    0

/**
 * \brief       ldt segment selector.
 */
#define SELECTOR_LDT    0x4

/**
 * \brief       privilege level 0's segment selector.
 */
#define SELECTOR_PRIV_0 0

/**
 * \brief       privilege level 1's segment selector.
 */
#define SELECTOR_PRIV_1 1

/**
 * \brief       privilege level 2's segment selector.
 */
#define SELECTOR_PRIV_2 2

/**
 * \brief       privilege level 3's segment selector.
 */
#define SELECTOR_PRIV_3 3


/* idt gates */

/**
 * \brief   Task gate segment.
 */
#define GATE_TASK_GATE      0x500

/**
 * \brief   16bits interrupt gate segment.
 */
#define GATE_INTR_GATE_16BITS   0x600

/**
 * \brief   32bits interrupt gate segment.
 */
#define GATE_INTR_GATE_32BITS   0xe00

/**
 * \brief   16bits trap gate segment.
 */
#define GATE_TRAP_GATE_16BITS   0x700

/**
 * \brief   32bits trap gate segment.
 */
#define GATE_TRAP_GATE_32BITS   0xf00


/**
 * \brief       Segment selector.
 */
typedef uint16_t    selector_t;

/**
 * \brief   Segment table register. Generic structure.
 */
typedef struct  dtr_s
{
  uint16_t      limit;     /** Size of the segment in bytes - 1. */
  uint32_t      base_addr; /** Base address of the segment. */

}  __attribute__((packed))               dtr_t;

/**
 * \brief   Global descriptor table register.
 */
typedef dtr_t   gdtr_t;

/**
 * \brief   Local descriptor table register.
 */
typedef dtr_t   ldtr_t;

/**
 * \brief   Interrupt descriptor table register.
 */
typedef dtr_t   idtr_t;

/**
 * Description of a descriptor table.
 */
typedef struct  dt_s
{
  uint32_t      lo;
  uint32_t      hi;

}  __attribute__((packed))  dt_t;

/**
 * The idt is a collection of gates.
 */
typedef dt_t   idt_t;

/**
 * \brief   Global descriptor table.
 */
typedef dt_t    gdt_t;

/**
 * \brief   Local descriptor table.
 */
typedef gdt_t        ldt_t;


/**
 * \param idx   The GDT's descriptor index
 * \return  The corresponding segment selector assuming
 *      a privilege level of 0
 * \brief   Retrieve a ring0 gdt segment selector from its
 *      index
 */
#define GDT_GET_OFFSET(idx) (idx << 3)

/**
 * \param idx   The gdt index of the descriptor
 * \return  The corresponding segment selector assuming
 *      the descriptor privilege level
 * \brief   Retrieve a gdt segment selector from its
 *      index. Unlike GDT_GET_OFFSET the selector returned
 *      is a selector_t type and the privilege level is the
 *      one of the descriptor
 */
#define GDT_GET_SELECTOR(idx)               \
 (GDT_GET_OFFSET(idx) | get_segment_dpl(gl_gdt[idx]))

/**
 * \param idx   The gdt index of the descriptor
 * \return  The corresponding segment selector assuming
 *      a privilege level of 0
 * \brief   Retrieve a ring0 gdt segment selector from its
 *      index. Unlike GDT_GET_OFFSET the selector returned
 *      is a selector_t type
 */
#define GDT_GET_SELECTOR0(idx)  (GDT_GET_OFFSET(idx))

/**
 * \param sys_reg   The name of the system register
 * \param value     Where to store the current sys_reg.
 * \brief       Gets the value of a system register.
 *          Examples are: gdt,tr,ldt,idt
 */
#define get_system_reg(sys_reg, value)   \
do                      \
{                       \
  __asm__ volatile ("s"#sys_reg " %0\n\t"   \
        :: "m" (value));        \
} while (0)

/**
 * \param sys_reg   The name of the system register
 * \param value     The value to be loaded
 * \brief       sets a new value in a system register.
 *          Examples are: gdt,tr,ldt,idt
 */
#define set_system_reg(sys_reg, value)   \
do                      \
{                       \
  __asm__ volatile ("l"#sys_reg " %0\n\t"   \
        :: "m" (value));        \
} while (0)

/**
 * \param selector  The selector of the segment selector.
 * \brief       Gets the value of the segment selector.
 *              Examples are: cs,ss,ds,es,fs,gs
 */
#define get_segment(seg, selector)  \
do                      \
{                       \
  __asm__ volatile ("movw %%"#seg",%%ax"      \
        :"=a"(selector));      \
} while (0)

/**
 * \param seg       The name of the segment
 * \param selector  The selector to be loaded
 * \brief       Loads a new selector in a given segment.
 *          Examples are: ds,es,fs,gs
 */
#define set_data_segment(seg, selector)  \
do                      \
{                       \
  __asm__ volatile ("movw %%ax,%%"#seg      \
        :: "a"(selector));      \
} while (0)

#endif /* SEGMENTS_H_ */
