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

#ifndef EXAPROCESS_INTERNAL_H_
#define EXAPROCESS_INTERNAL_H_

/**
 * \brief   Hint for the flags of examour_env_section_t.
 *      This one specify that the section is the code
 *      segment.
 * \warning It implies the offset field to be
 *      the program counter.
 * \warning An environment can only have one code segment.
 *      If there is more segments at creation time an
 *      error will be returned.
 */
#define ENV_HINT_CODE   0x1

/**
 * \brief   Hint for the flags of examour_env_section_t.
 *      This one specify that the section is a stack
 *      segment.
 * \warning It implies the offset field to be the stack top.
 * \warning An environment can have as many stack segment it
 *      wants but specifies several stack hint at creation
 *      time will lead to an error. Only the stack to be
 *      used at launch time must have this hint.
 */
#define ENV_HINT_STACK  0x2

/**
 * \brief   Hint for the flags of examour_env_section_t.
 *      This one specify that the section is a DS data
 *      segment.
 * \warning It implies the offset field to be the esi register value.
 * \warning An environment can have as many ds segment it
 *      wants but specifies several ds hint at creation
 *      time will lead to an error. Only the ds to be
 *      used at launch time must have this hint.
 */
#define ENV_HINT_DS 0x4

/**
 * \brief   Hint for the flags of examour_env_section_t.
 *      This one specify that the section is a ES data
 *      segment.
 * \warning It implies the offset field to be the edi register value.
 * \warning An environment can have as many es segment it
 *      wants but specifies several es hint at creation
 *      time will lead to an error. Only the es to be
 *      used at launch time must have this hint.
 */
#define ENV_HINT_ES 0x8

/**
 * \brief   Hint for the flags of examour_env_section_t.
 *      This one specify that the section is a FS data
 *      segment.
 * \warning An environment can have as many fs segment it
 *      wants but specifies several fs hint at creation
 *      time will lead to an error. Only the fs to be
 *      used at launch time must have this hint.
 */
#define ENV_HINT_FS 0x10

/**
 * \brief   Hint for the flags of examour_env_section_t.
 *      This one specify that the section is a GS data
 *      segment.
 * \warning An environment can have as many gs segment it
 *      wants but specifies several gs hint at creation
 *      time will lead to an error. Only the gs to be
 *      used at launch time must have this hint.
 */
#define ENV_HINT_GS 0x20

/**
 * \brief   Section of a binary.
 *      This is provided to env_create.
 *      It aims to describes efficiently
 *      the env to create and its state.
 *      We think it is much convenient
 *      and flexible that a callback function
 *      or a fixed launch state.
 */
typedef struct  exaprocess_section_s
{
  uint32_t      flags;      /** flags in the ldt_add_entry format. */
  paddr_t       base_addr;  /** physical base address of PADDR_ERROR */
  size_t        size;       /** size of the section. */
  uint32_t      hint;       /** hint for env_create. */
  paddr_t       offset;     /** address to set if relevant. (see hint) */
  int           ldt_idx;    /** index in the ldt. */

}       exaprocess_section_t;

/**
 * \param sections  The sections of the new process binary.
 * \param n_sections    The number of sections.
 * \return      The pid on success, 0 on error.
 * \brief       Creates a new process in the system and schedule it
 */
pid_t       exaprocess_create(exaprocess_section_t  *sections,
                              uint32_t              n_sections);

/**
 * \param pid   The pid of the process to delete.
 * \return  true on success, false otherwise
 * \brief   Delete a process. an pid of 0 means the calling process
 */
bool        exaprocess_delete(pid_t pid);


/**
 * Yield the currently running process.
 */
bool        exaprocess_yield(pid_t pid);

#endif /* EXAPROCESS_INTERNAL_H_ */
