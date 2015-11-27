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

#ifndef	__ASM_H__
#define	__ASM_H__

/**
 * \brief	Defines some useful macros used in the assembly
 *		files by exception/intr forwarding or syscalls
 *		routines for example.
 *		Defines C routines for low level interaction.
 */

#include	<examour/mm/mem.h>
#include	<examour/event/exception.h>

/* Warning: This comment may be outdated. */
/* exception/interruption flow chart. */
/* The stack0 has already been switched (tss) */
/* - save the mandatory on the current env's stack0. */
/* - install the ds,es kernel register for gl_current_env. */
/* - save the esp0 of the env. */
/* - call the epilogue. */
/* - install the ds,es kernel register for gl_current_env. */
/* - call sched_next to find a new env. */
/* - move toward the new stack using the esp0 of the new env. */
/* - call the prologue. */
/* - pop off the mandatory registers. */
/* - iret. */

/**
 * \brief	Offset in bytes of the environment's prologue
 *		callback in an examour_env_t structure.
 */
#define		PROLOGUE_OFFSET		0

/**
 * \brief	Offset in bytes of the environment's epilogue
 *		callback in an examour_env_t structure.
 */
#define		EPILOGUE_OFFSET		8

/**
 * \brief	Offset in bytes of the environment's exception
 *		callbacks vector in an examour_env_t structure.
 */
#define		EXCEPTION_OFFSET	16

/* exceptions/intr/syscall routines */

/*
 * Once the context has been saved, the kernel
 * stack layout is has follow:
 *
 *	%ds	-> 34(%esp)
 *	%es	-> 32(%esp)
 *	%fs	-> 30(%esp)
 *	%gs	-> 28(%esp)
 *	%eax	-> 24(%esp)	-> syscall 7th arg, syscall ret
 *	%ebp	-> 20(%esp)	-> syscall 6th arg
 *	%edi	-> 16(%esp)	-> syscall 5th arg
 *	%esi	-> 12(%esp)	-> syscall 4th arg
 *	%edx	-> 8(%esp)	-> syscall 3rd arg
 *	%ecx	-> 4(%esp)	-> syscall 2nd arg
 *	%ebx	-> (%esp)	-> syscall 1st arg
 */

#include	<examour/event/event_types.h>

#ifndef	__ASM__

/**
 * \brief	Disable external interruptions.
 */
#define	disable_intr()	__asm__ volatile("cli")

/**
 * \brief	Enable external interruptions.
 */
#define	enable_intr()	__asm__ volatile("sti")

/* i/o control */

/**
 * \param port	The port to write to
 * \param val	The value to write in port
 * \brief	Writes a byte to an I/O port
 */
#define	outb(port, val)	__asm__ volatile ("outb %%al, %%dx":: "d"(port), "a"((val) & 0xff))

/**
 * \param port	The port to write to
 * \param val	The value to write in port
 * \brief	Writes a byte to an I/O port with a delay for
 *		slow devices
 */
#define	outbp(port, val)							\
	__asm__ volatile ("outb %%al, %%dx; jmp 1f; 1:":: "d"(port), "a"((val) & 0xff))

/**
 * \param port	The port to read from
 * \return	The byte read fromthe port
 * \brief	Reads a byte from an I/O port
 */
#define	inb(port)				\
({						\
  unsigned char	_val;				\
  __asm__ volatile ("inb %%dx, %%al"		\
		: "=a"(_val)			\
		: "d"(port));			\
  _val;						\
})

/**
 * \param port	The port to read from
 * \return	The byte read fromthe port
 * \brief	Reads a byte from an I/O port with a delay
 *		for slow devices
 */
#define	inbp(port)				\
({						\
  unsigned char	_val;				\
  __asm__ volatile ("inb %%dx, %%al; jmp 1f; 1:"\
		: "=a"(_val)			\
		: "d"(port));			\
  _val;						\
})

#endif /* !__ASM__ */

#endif /* __ASM_H__ */
