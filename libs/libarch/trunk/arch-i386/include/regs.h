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

#ifndef REGS_H_
#define REGS_H_

/**
 * This file contains declarations and types of registers.
 */

#include    <stdbool.h>
#include    <stdint.h>

/**
 * \brief   CR0 register, protected mode flag.
 */
#define CR0_PE      0x1 /* (1 << 0) */

/**
 * \brief   CR0 register, monitor co-processor flag.
 */
#define CR0_MP      0x2 /* (1 << 1) */

/**
 * \brief   CR0 register, x87 emulation flag.
 */
#define CR0_EM      0x4 /* (1 << 2) */

/**
 * \brief   CR0 register, task switched flag.
 */
#define CR0_TS      0x8 /* (1 << 3) */

/**
 * \brief   CR0 register, extension type flag.
 */
#define CR0_ET      0x10    /* (1 << 4) */

/**
 * \brief   CR0 register, numeric error flag.
 */
#define CR0_NE      0x20    /* (1 << 5) */

/**
 * \brief   CR0 register, write protect flag.
 */
#define CR0_WP      0x10000 /* (1 << 16) */

/**
 * \brief   CR0 register, alignment mask flag.
 */
#define CR0_AM      0x40000 /* (1 << 18) */

/**
 * \brief   CR0 register, not write through flag.
 */
#define CR0_NW      0x20000000  /* (1 << 29) */

/**
 * \brief   CR0 register, cache disable flag.
 */
#define CR0_CD      0x40000000  /* (1 << 30) */

/**
 * \brief   CR0 register, paging mode flag.
 */
#define CR0_PG      0x80000000  /* (1 << 31) */

/**
 * \brief   CR3 register,  page level writes transparent flag.
 */
#define CR3_PG_WR_TRANSPARENT   0x8

/**
 * \brief   CR3 register,  page level cache disable flag.
 */
#define CR3_PG_NO_CACHE     0x10

/**
 * \brief   CR3 register, all flags activated.
 */
#define CR3_ALL_OPT     0x18

/**
 * \brief   CR4 register, virtual 8086 mode extensions flag.
 */
#define CR4_VME         0x1 /* (1 << 0) */

/**
 * \brief   CR4 register, protected mode virtual interrupt flag.
 */
#define CR4_PVI         0x2 /* (1 << 1) */

/**
 * \brief   CR4 register, timestamp disable flag.
 */
#define CR4_TSD         0x4 /* (1 << 2) */

/**
 * \brief   CR4 register, debugging extensions flag.
 */
#define CR4_DE          0x8 /* (1 << 3) */

/**
 * \brief   CR4 register, page size extensions flag.
 */
#define CR4_PSE         0x10 /* (1 << 4) */

/**
 * \brief   CR4 register, physical address extension flag.
 */
#define CR4_PAE         0x20 /* (1 << 5) */

/**
 * \brief   CR4 register, machine check enable flag.
 */
#define CR4_MCE         0x40 /* (1 << 6) */

/**
 * \brief   CR4 register, page global enable flag.
 */
#define CR4_PGE         0x80 /* (1 << 7) */

/**
 * \brief   CR4 register, performance monitoring counter flag.
 */
#define CR4_PCE         0x100 /* (1 << 8) */

/**
 * \brief   CR4 register, os support for fxsave and fxrstor flag.
 */
#define CR4_OSFXSR      0x200 /* (1 << 9) */

/**
 * \brief   CR4 register, os support for unmasked simd floating point
 *      exception flag.
 */
#define CR4_OSXMMEXCPT      0x400 /* (1 << 10) */

/**
 * \brief   Eflags register, carry flag.
 */
#define EFLAGS_CF       0x1 /* (1 << 0) */

/**
 * \brief   Eflags register, parity flag.
 */
#define EFLAGS_PF       0x4 /* (1 << 2) */

/**
 * \brief   Eflags register, adjust flag.
 */
#define EFLAGS_AF       0x10 /* (1 << 4) */

/**
 * \brief   Eflags register, zero flag.
 */
#define EFLAGS_ZF       0x40 /* (1 << 6) */

/**
 * \brief   Eflags register, sign flag.
 */
#define EFLAGS_SF       0x80 /* (1 << 7) */

/**
 * \brief   Eflags register, trap flag.
 */
#define EFLAGS_TRAP     0x100 /* (1 << 8) */

/**
 * \brief   Eflags register, interrupt enable flag.
 */
#define EFLAGS_INTR     0x200 /* (1 << 9) */

/**
 * \brief   Eflags register, direction flag.
 */
#define EFLAGS_DF       0x400 /* (1 << 10) */

/**
 * \brief   Eflags register, overflow flag.
 */
#define EFLAGS_OF       0x800 /* (1 << 11) */

/**
 * \brief   Eflags register, iopl1 flag.
 */
#define EFLAGS_IOPL1        0x1000

/**
 * \brief   Eflags register, iopl2 flag.
 */
#define EFLAGS_IOPL2        0x2000

/**
 * \brief   Eflags register, iopl3 flag.
 */
#define EFLAGS_IOPL3        0x3000

/**
 * \brief   Eflags register, nested task flag.
 */
#define EFLAGS_NT       0x4000 /* (1 << 14) */

/**
 * \brief   Eflags register,  resume flag.
 */
#define EFLAGS_RF       0x10000 /* (1 << 16) */

/**
 * \brief   Eflags register, virtual 8086 mode flag.
 */
#define EFLAGS_VM86     0x20000 /* (1 << 17) */

/**
 * \brief   Eflags register, alignment check flag.
 */
#define EFLAGS_AC       0x40000 /* (1 << 18) */

/**
 * \brief   Eflags register, virtual interrupt flag.
 */
#define EFLAGS_VINTR        0x80000 /* (1 << 19) */

/**
 * \brief   Eflags register, virtual interrupt pending flag.
 */
#define EFLAGS_VINTR_PENDING    0x100000 /* (1 << 20) */

/**
 * \brief   Eflags register, identification flag.
 */
#define EFLAGS_ID       0x200000 /* (1 << 21) */


/**
 * \brief   General purpose registers.
 */
typedef struct          gp_regs_s
{
  /* the first 6 registers are in the order of the pusha */
  /* instruction. */

  uint32_t      eax;    /** eax register. */
  uint32_t      ecx;    /** ecx (counter) register. */
  uint32_t      edx;    /** edx register. */
  uint32_t      ebx;    /** ebx register. */
  uint32_t      esp;    /** esp (stack pointer) register. */
  uint32_t      ebp;    /** ebp (base pointer) register. */
  uint32_t      esi;    /** esi (source instruction) register. */
  uint32_t      edi;    /** edi (destination instruction) register. */

}  __attribute__((packed))                      gp_regs_t;

/**
 * \brief   The control register 0.
 */
typedef uint32_t    cr0_t;

/**
 * \brief   The control register 1.
 * \warning This register has reserved contents.
 */
typedef uint32_t    cr1_t;

/**
 * \brief   The control register 2. This register contains
 *      the page fault linear address.
 */
typedef uint32_t    cr2_t;

/**
 * \brief   The control register 3. This register is used for pagination.
 */
typedef uint32_t    cr3_t;

/**
 * \brief   The control register 4.
 */
typedef uint32_t    cr4_t;

/**
 * \brief   The eflags register.
 */
typedef uint32_t    eflags_t;

/**
 * \param reg   The register to modify
 * \param val   The value to set
 * \brief   Sets a memory reference value in a register
 */
#define set_register(reg, val)          \
do                      \
{                       \
  __asm__ volatile ("mov %0,%%"#reg:: "m"(val));\
} while (0)

/**
 * \param reg   The register to modify
 * \param val   The value to set
 * \brief   Sets an immediate value in a given register
 */
#define set_register_i(reg, val)        \
do                      \
{                       \
  __asm__ volatile ("mov %0,%%"#reg:: "i"(val));\
} while (0)

/**
 * \param reg   The register to read from
 * \return  the value in a given register
 * \brief   Gets the value of a given register
 */
#define get_register(reg)               \
({                          \
  int   __v;                        \
                            \
  __asm__ volatile ("mov %%"#reg ",%0\n\t" : "=m"(__v));\
  (__v);                        \
})


#endif /* REGS_H_ */
