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

#ifndef EXAMEM_H_
#define EXAMEM_H_

#include        <stdbool.h>
#include		    <stddef.h>
#include        "exaboot.h"

/* Public Datatypes */

/**
 * Exabus's namespace.
 */
#define	EXAPMEM_NAMESPACE	"kernel.memory"

/**
 * The interface of examem.
 *
 * Content of kernel.event.examem:
 *
 */
#define	EXAMEM_INTERFACE	"examem"


/**
 * The memory address type.
 */
typedef uint32_t  paddr_t;

/**
 * The impossible address.
 */
#define PADDR_ERROR (paddr_t)(0xffffffff)

/* configures the memory alignment of memory allocations. */
#define EXAMEM_ALIGNED_NONE 0x0
#define EXAMEM_ALIGNED_8B   0x1
#define EXAMEM_ALIGNED_16B  0x2
#define EXAMEM_ALIGNED_4KB  0x4
#define EXAMEM_ALIGNED_4MB  0x8
#define EXAMEM_ALIGNED_ALL  (EXAMEM_ALIGNED_8B | EXAMEM_ALIGNED_16B | EXAMEM_ALIGNED_4KB | EXAMEM_ALIGNED_4MB)
#define EXAMEM_ALIGNED_DEFAULT EXAMEM_ALIGNED_NONE

/* Configures the type of memory mapping. Some mapings are only applicable */
/* when dealing with userspace applications (because they are related to segment configuration) */
/* But for the sake of safety, all must be available to the kernel too. */

/* Read/Write (not execute) mapping. */
#define EXAMEM_MAP_RDWR 0x0

/* Read only mapping. */
#define EXAMEM_MAP_RD 0x8

/* Write only mapping. */
#define EXAMEM_MAP_WR 0x10

/* Execute only mapping. */
#define EXAMEM_MAP_EXEC 0x20

/* Read only exclusive mapping. Any other mapping here can't be with the read capability. */
#define EXAMEM_MAP_EXCL_RD 0x40

/* Write only exclusive mapping. Any other mapping here can't be with the write capability. */
#define EXAMEM_MAP_EXCL_WR 0x80

/* Execute only exclusive mapping. Any other mapping here can't be with the execute capability. */
#define EXAMEM_MAP_EXCL_EXEC 0x100

/* Beware that a MAP_EXCL_* doesn't imply the READ,WRITE or EXEC capability. In fact, a memory area can */
/* be allocated as write only and set a lock with the three EXCL. In that case, nobody will be able to get the memory area. */

/* Stack like mapping. On intels, it means that the segment is a STACK segment. Addresses count is reversed. */
#define EXAMEM_MAP_STACK 0x200

/* EXCL flags on that memory segment are system wide. */
#define EXAMEM_SCOPE_SYSTEM 0x0

/* EXCL flags on that memory segment are SYSTEM but PROCESS wide. It means that the set of EXCL will be applied only to other processes in the system. */
/* It would be useful for segment sharing only between threads of a process. */
/* However, it implies that threads are fully trusted. */
#define EXAMEM_SCOPE_SYSTEM_BUT_PROCESS 0x800

/* Regular memory. (range >= 16Mb - End of memory except APIC area). */
#define EXAMEM_TYPE_REGULAR 0x1000

/* ACPI mapped memory (range 0xfe000000 - ???). */
#define EXAMEM_TYPE_ACPI 0x2000

/* DMA mapped memory. (range 1Mb - 16Mb). */
#define EXAMEM_TYPE_DMA 0x4000

/* Reserved memory. (mapped for other purposes, ...) */
#define EXAMEM_TYPE_RESERVED    0x8000

#define EXAMEM_TYPE_ALL (EXAMEM_TYPE_REGULAR | EXAMEM_TYPE_ACPI | EXAMEM_TYPE_DMA | EXAMEM_TYPE_RESERVED)

/* Reserved memory (Below 1Mb) is accessed only through a ref_at() since it is fixed size memory. */

/* Kernel internal Datatypes */



/**********************************************/
/* Kernel API. */

/**
 *  Initialize examem.
 */
bool    _examem_init(const exaboot_t * const inf);


/* Public API. It is bounded to exabus. */

/**
 *  References a new memory address.
 */
void *examem_ref_new(size_t size, int flags);

/**
 *  References a specific memory address.
 */
bool examem_ref_at(paddr_t addr, size_t size, int flags);

/**
 *  Unreference a memory address.
  */
void examem_unref(void *addr);

/**
 *  Initializes the memory component.
  */
bool examem_init(void);

/**
 * Optimize wasted memory space.
 */
void    examem_rationalize(void);

/* Stub for now. will be used by exaprocess. */
//examem_context_t *examem_create_context(void);

/* Stub for now. will be used by exaprocess. */
//bool examem_destroy_context(examem_context_t *ctx);

#endif  /* EXAMEM_H_ */
