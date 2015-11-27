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

#ifndef	__EVENT_TYPES_H__
#define	__EVENT_TYPES_H__

#include	<examour/core/segment_types.h>
#include	<examour/attributes.h>

#ifndef	__ASM__

#pragma pack(push,1)

/**
 * \brief	Data structure that describes an event stack frame.
 */
typedef struct PACKED	kevent_cpu_context_s
{
  uint32_t		ebx;	/** ebx register.  */
  uint32_t		ecx;	/** ecx (counter) register. */
  uint32_t		edx;	/** edx register. */
  uint32_t		esi;	/** esi (source instruction) register. */
  uint32_t		edi;	/** edi (desitnation instruction) register. */
  uint32_t		ebp;	/** ebp (base pointer) register. */
  uint32_t		eax;	/** eax register. */
  selector_t		gs;	/** gs data segment selector. */
  uint16_t		gs_padding;
  selector_t		fs;	/** fs data segment selector. */
  uint16_t		fs_padding;
  selector_t		es;	/** es data segment selector. */
  uint16_t		es_padding;
  selector_t		ds;	/** ds data segment selector. */
  uint16_t		ds_padding;
  uint32_t		ev_id;	/** Identifier of the event. */
  uint32_t		error_code; /** Event error code or 0 if none. */
  uint32_t		eip;	/** interrupted task program counter. */
  selector_t		cs;	/** interrupted task cs code segment selector. */
  uint16_t		padding0;
  eflags_t		eflags;	/** interrupted task eflags register. */
  uint32_t		esp;	/** interrupted task esp (stack pointer) register. */
  selector_t		ss;	/** interrupted task ss stack segment selector. */
  uint16_t		padding1;

}			kevent_cpu_context_t;

#pragma pack(pop)

/**
 * \param args	The environment stack frame,
 * \brief	Event function pointer type. This function belongs to an environnement
 *		and is called when a registered event occurs.
 */
typedef void	(*event_p)(kevent_cpu_context_t *args);

#else	/* __ASM__ */

/**
 * \brief	Offset of the context parameters
 */

/**
 * \brief	General purpose register size.
 */
#define	GP_REG_SZ	4

/**
 * \brief	Segment selector register size.
 */
#define	SEGSEL_REG_SZ	4

/* This is the layout of event_types.h:kevent_cpu_context_t. */

/**
 * \brief	ebx register.
 */
#define	EBX_OFFSET	0

/**
 * \brief	ecx (counter) register.
 */
#define	ECX_OFFSET	EBX_OFFSET+GP_REG_SZ

/**
 * \brief	edx register.
 */
#define	EDX_OFFSET	ECX_OFFSET+GP_REG_SZ

/**
 * \brief	esi (source instruction) register.
 */
#define	ESI_OFFSET	EDX_OFFSET+GP_REG_SZ

/**
 * \brief	edi (desitnation instruction) register.
 */
#define	EDI_OFFSET	ESI_OFFSET+GP_REG_SZ

/**
 * \brief	ebp (base pointer) register.
 */
#define	EBP_OFFSET	EDI_OFFSET+GP_REG_SZ

/**
 * \brief	eax register.
 */
#define	EAX_OFFSET	EBP_OFFSET+GP_REG_SZ

/**
 * \brief	gs data segment selector.
 */
#define	GS_OFFSET	EAX_OFFSET+GP_REG_SZ

/**
 * \brief	fs data segment selector.
 */
#define	FS_OFFSET	GS_OFFSET+SEGSEL_REG_SZ

/**
 * \brief	es data segment selector.
 */
#define	ES_OFFSET	FS_OFFSET+SEGSEL_REG_SZ

/**
 * \brief	ds data segment selector.
 */
#define	DS_OFFSET	ES_OFFSET+SEGSEL_REG_SZ

/**
 * \brief	Identifier of the event. 
 */
#define	EV_ID_OFFSET	DS_OFFSET+SEGSEL_REG_SZ

/**
 * \brief	Event error code or 0 if none.
 */
#define	ERROR_ID_OFFSET	EV_ID_OFFSET+GP_REG_SZ

/**
 * \brief	interrupted task program counter.
 */
#define	EIP_OFFSET	ERROR_ID_OFFSET+GP_REG_SZ

/**
 * \brief	interrupted task cs code segment selector.
 */
#define	CS_OFFSET	EIP_OFFSET+GP_REG_SZ

/**
 * \brief	interrupted task eflags register.
 */
#define	EFLAGS_OFFSET	CS_OFFSET+GP_REG_SZ

/**
 * \brief	interrupted task esp (stack pointer) register.
 */
#define	ESP_OFFSET	EFLAGS_OFFSET+GP_REG_SZ

/**
 * \brief	interrupted task ss stack segment selector.
 */
#define	SS_OFFSET	ESP_OFFSET+GP_REG_SZ

/**
 * \brief	The total size in bytes of the context.
 */
#define	CONTEXT_SIZE	SS_OFFSET+GP_REG_SZ

#endif /* !__ASM__ */

#endif /* __EVENT_TYPES_H__ */
