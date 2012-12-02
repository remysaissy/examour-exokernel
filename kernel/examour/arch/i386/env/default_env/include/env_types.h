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

#ifndef	__ENV_TYPES_H__
#define	__ENV_TYPES_H__

#include	<examour/core/segment_types.h>
#include	<examour/env/env_enum.h>
#include	<examour/event/io_types.h>
#include	<examour/event/exception.h>
#include	<examour/core/predicates.h>
#include	<examour/security/security.h>

/* these are asm compatible versions of the same macros defined below. */

/**
 * \brief	Offset of the first readonly mapped byte in the env structure.
 */
#define	ASM_EXAMOUR_ENV_RO_MAPPING_BEGIN	(8+8+EXCEPTION_MAX_NUM*8)

/**
 * \brief	Size in bytes of the readonly mapped byte in the env structure.
 */
#define	ASM_EXAMOUR_ENV_RO_MAPPING_SIZE		(0x58)

/**
 * \brief	Offset of the first readwrite mapped byte in the env structure.
 */
#define	ASM_EXAMOUR_ENV_RW_MAPPING_BEGIN	(0)

/**
 * \brief	Size in bytes of the readwrite mapped byte in the env structure.
 */
#define	ASM_EXAMOUR_ENV_RW_MAPPING_SIZE	(ASM_EXAMOUR_ENV_RO_MAPPING_BEGIN)

/**
 * \brief	Size of the envs hash tables.
 */
#define	ASM_ENV_HASHING_SIZE	1024


#ifndef	__ASM__

#include	<toolkit/list.h>
#include	<toolkit/hash.h>

/**
 * \brief	The ExAmour env id.
 *		This is is an unique identifier for every environnement.
 */
typedef uint32_t	eid_t;

/**
 * \brief	The env data structure. This data structure describes an
 *		environnement and a part is available to the userspace in
 *		readwrite while another one is in readonly.
 *		It allows easy dynamic modifications of exception handlers
 *		for example.
 */
typedef struct	examour_env_s
{
  /* Here is the readwrite mapping. */
  predicate_t	prologue;	/** Used before scheduling. (save) */
  predicate_t	epilogue;	/** Used before unscheduling. (restore) */
  predicate_t	exceptions[EXCEPTION_MAX_NUM]; /** Exception handlers. */

  /* Here is the readonly mapping. */
  env_state_e	state;		/** current state of the env */
  eid_t		eid;		/** eid of the environment. */
  dlist_t	iocaps_list;	/** list of capabilities of the env. */
  struct iocap_s	*iocaps;		/** The capabilities of the env. */
  basic_cap_t	basic_cap;	/** The basic capabilities of the env. */
  ldtr_t	ldtr;		/** ldt context. */
  uint64_t	total_cputime;  /** amount of time currently allocated */
  hashtable_t	env_list;       /** list of environment. */

}		examour_env_t;



/**
 * \brief	Offset of the first readonly mapped byte in the env structure.
 */
#define	EXAMOUR_ENV_RO_MAPPING_BEGIN	(8+8+EXCEPTION_MAX_NUM*8)

/**
 * \brief	Size in bytes of the readonly mapped byte in the env structure.
 */
#define	EXAMOUR_ENV_RO_MAPPING_SIZE	(sizeof(examour_env_t) - EXAMOUR_ENV_RO_MAPPING_BEGIN)

/**
 * \brief	Offset of the first readwrite mapped byte in the env structure.
 */
#define	EXAMOUR_ENV_RW_MAPPING_BEGIN	(0)

/**
 * \brief	Size in bytes of the readwrite mapped byte in the env structure.
 */
#define	EXAMOUR_ENV_RW_MAPPING_SIZE	(EXAMOUR_ENV_RO_MAPPING_BEGIN)

/**
 * \brief	Size of the envs hash tables.
 */
#define	ENV_HASHING_SIZE	1024


/**
 * \brief	This structure holds the envs pointers.
 */
typedef struct	examour_env_informations_s
{
  examour_env_t	*idle;					/** The idle env. */
  examour_env_t	*alive_envs[ENV_HASHING_SIZE];	/** Alive envs. */
  examour_env_t	*dead_envs[ENV_HASHING_SIZE];	/** Dead envs. */

}		examour_env_informations_t;

/**
 * \brief	Hint for the flags of examour_env_section_t.
 *		This one specify that the section is the code
 *		segment.
 * \warning	It implies the offset field to be
 *		the program counter.
 * \warning	An environment can only have one code segment.
 *		If there is more segments at creation time an
 *		error will be returned.
 */
#define	ENV_HINT_CODE	0x1

/**
 * \brief	Hint for the flags of examour_env_section_t.
 *		This one specify that the section is a stack
 *		segment.
 * \warning	It implies the offset field to be the stack top.
 * \warning	An environment can have as many stack segment it
 *		wants but specifies several stack hint at creation
 *		time will lead to an error. Only the stack to be
 *		used at launch time must have this hint.
 */
#define	ENV_HINT_STACK	0x2

/**
 * \brief	Hint for the flags of examour_env_section_t.
 *		This one specify that the section is a DS data
 *		segment.
 * \warning	It implies the offset field to be the esi register value.
 * \warning	An environment can have as many ds segment it
 *		wants but specifies several ds hint at creation
 *		time will lead to an error. Only the ds to be
 *		used at launch time must have this hint.
 */
#define	ENV_HINT_DS	0x4

/**
 * \brief	Hint for the flags of examour_env_section_t.
 *		This one specify that the section is a ES data
 *		segment.
 * \warning	It implies the offset field to be the edi register value.
 * \warning	An environment can have as many es segment it
 *		wants but specifies several es hint at creation
 *		time will lead to an error. Only the es to be
 *		used at launch time must have this hint.
 */
#define	ENV_HINT_ES	0x8

/**
 * \brief	Hint for the flags of examour_env_section_t.
 *		This one specify that the section is a FS data
 *		segment.
 * \warning	An environment can have as many fs segment it
 *		wants but specifies several fs hint at creation
 *		time will lead to an error. Only the fs to be
 *		used at launch time must have this hint.
 */
#define	ENV_HINT_FS	0x10

/**
 * \brief	Hint for the flags of examour_env_section_t.
 *		This one specify that the section is a GS data
 *		segment.
 * \warning	An environment can have as many gs segment it
 *		wants but specifies several gs hint at creation
 *		time will lead to an error. Only the gs to be
 *		used at launch time must have this hint.
 */
#define	ENV_HINT_GS	0x20

/**
 * \brief	Section of a binary.
 *		This is provided to env_create.
 *		It aims to describes efficiently
 *		the env to create and its state.
 *		We think it is much convenient
 *		and flexible that a callback function
 *		or a fixed launch state.
 */
typedef struct	examour_env_section_s
{
  uint32_t	flags;		/** flags in the ldt_add_entry format. */
  paddr_t	base_addr;	/** physical base address of PADDR_ERROR */
  size_t	size;		/** size of the section. */
  uint32_t	hint;		/** hint for env_create. */
  paddr_t	offset;		/** address to set if relevant. (see hint) */
  int		ldt_idx;	/** index in the ldt. */

}		examour_env_section_t;

#endif /* __ASM__ */

#endif /* __ENV_TYPES_H__ */
