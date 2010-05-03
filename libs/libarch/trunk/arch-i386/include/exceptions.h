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

#ifndef EXCEPTION_H_
#define EXCEPTION_H_

/**
 * This file contains declarations and types for exceptions.
 * Notice that on intel architecture, an exception is a processor synchronous event
 * related to the current running task.
 * There is a fixed number of exceptions ranging from IRQ0 to IRQ20.
 */

#include    <stdbool.h>
#include    <stdint.h>

#include    "segments.h"
#include    "regs.h"

/* Machine fixed exceptions. */

/**
 * \brief   Division by zero exception number.
 */
#define EXCEPTION_DIVIDE_ERROR      0

/**
 * \brief   Debug exception number.
 */
#define EXCEPTION_DEBUG         1

/**
 * \brief   NMI exception number.
 */
#define EXCEPTION_NMI_INTR      2

/**
 * \brief   Breakpoint (int3) exception number.
 */
#define EXCEPTION_BREAKPOINT        3

/**
 * \brief    Overflow exception number.
 */
#define EXCEPTION_OVERFLOW      4

/**
 * \brief   Bound exceed exception number.
 */
#define EXCEPTION_BOUND_EXCEED      5

/**
 * \brief   Invalid opcode exception number.
 */
#define EXCEPTION_INVL_OPCODE       6

/**
 * \brief   Device not available exception number.
 */
#define EXCEPTION_DEV_NOT_AVL       7

/**
 * \brief   Double fault exception number.
 */
#define EXCEPTION_DOUBLE_FAULT      8

/**
 * \brief   Cop seg overrun exception number.
 */
#define EXCEPTION_COP_SEG_OVERRUN   9

/**
 * \brief   Invalid tss descriptor exception number.
 */
#define EXCEPTION_INVL_TSS      10

/**
 * \brief   Segment not present exception number.
 */
#define EXCEPTION_SEGMENT_NOT_PRESENT   11

/**
 * \brief   Stack fault exception number.
 */
#define EXCEPTION_STACK_FAULT       12

/**
 * \brief   General protection exception number.
 */
#define EXCEPTION_GENERAL_PROTECTION    13

/**
 * \brief   Page fault exception number.
 */
#define EXCEPTION_PAGE_FAULT        14

/**
 * \brief   Unused exception number.
 */
#define EXCEPTION_UNUSED        15

/**
 * \brief   FPU error exception number.
 */
#define EXCEPTION_FPU_ERROR     16

/**
 * \brief   Alignement check exception number.
 */
#define EXCEPTION_ALIGNMENT_CHECK   17

/**
 * \brief   Machine check exception number.
 */
#define EXCEPTION_MACHINE_CHECK     18

/**
 * \brief   SIMD check exception number.
 */
#define EXCEPTION_SIMD_FPU      19

/**
 * \brief   Maximum exception number.
 */
#define EXCEPTION_MAX_NUM       20


/**
 * \brief   Informs from where an exception was thrown
 */
typedef enum
  {
    exception_code_location_gdt = 0,
    exception_code_location_idt,
    exception_code_location_ldt,
    exception_code_location_idt_bis

  }     exception_code_location_e;

/**
 * \brief   Layout of the optional error code of an exception.
 */
typedef struct          exception_error_code_s
{
  bool                        external : 1;
  exception_code_location_e   location : 2;
  selector_t                  index;
  uint32_t                    reserved : 13;

}               exception_error_code_t;


/* the page fault exception has a specific error code layout */
/**
 * \brief   Layout of the optional error code of an exception.
 *      The page fault exception has a specific error code layout.
 */
typedef struct  exception_page_fault_error_code_s
{
  bool      protection_violation : 1; /** false == not present page. */
  bool      write_access : 1;     /** false == read access */
  bool      from_usermode : 1;    /** false == from supervisor mode */
  bool      reserved_bits_page_dir : 1;/** false == reserved bits violation, true == reserved bits in a page directory */
  uint32_t  reserved : 27;

}     __attribute__((packed))   exception_page_fault_error_code_t;

/* Exception or IRQ raising. */
/* when an exception or an IRQ is raised, we use the present data structure to manipulate informations. */


/**
 * \brief   Data structure that describes an event stack frame.
 */
typedef struct  cpu_context_s
{
  /* This is not the order of a pusha (gp_regs_t). */
  uint32_t      ebx;    /** ebx register.  */
  uint32_t      ecx;    /** ecx (counter) register. */
  uint32_t      edx;    /** edx register. */
  uint32_t      esi;    /** esi (source instruction) register. */
  uint32_t      edi;    /** edi (desitnation instruction) register. */
  uint32_t      ebp;    /** ebp (base pointer) register. */
  uint32_t      eax;    /** eax register. */
  selector_t        gs; /** gs data segment selector. */
  uint16_t      gs_padding;
  selector_t        fs; /** fs data segment selector. */
  uint16_t      fs_padding;
  selector_t        es; /** es data segment selector. */
  uint16_t      es_padding;
  selector_t        ds; /** ds data segment selector. */
  uint16_t      ds_padding;
  uint32_t      ev_id;  /** Identifier of the event. */
  uint32_t      error_code; /** Event error code or 0 if none. */
  uint32_t      eip;    /** interrupted task program counter. */
  selector_t        cs; /** interrupted task cs code segment selector. */
  uint16_t      padding0;
  eflags_t      eflags; /** interrupted task eflags register. */
  uint32_t      esp;    /** interrupted task esp (stack pointer) register. */
  selector_t        ss; /** interrupted task ss stack segment selector. */
  uint16_t      padding1;

}        __attribute__((packed))        cpu_context_t;

/**
 * \param args  The environment stack frame,
 * \brief   Event function pointer type. This function belongs to an environment
 *      and is called when a registered event occurs.
 */
typedef void    (*exception_raised_p)(cpu_context_t *args);



#endif /* EXCEPTION_H_ */
