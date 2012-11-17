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

#ifndef LDT_H_
#define LDT_H_

#include    <stdint.h>
#include    <stdbool.h>

#include    "segments.h"

/**
 * This file contains the arch specific LDT interaction component.
 */

/**
 * The size, in bytes, of an LDT table.
 */
#define LDT_TABLE_SIZE  512

/**
 * Creates a new LDT context. This is typically an array of LDT entries.
 * @param context   The context to be created.
 * @return true on success, false otherwise.
 */
bool    ldt_create(ldt_t *context);

/**
 * Destroy an LDT context.
 * @param context   The LDT context to destroy.
 * @return true on success, false otherwise.
 */
bool    ldt_destroy(ldt_t *context);

/**
 * Add a new entry to an LDT context.
 * @param addr  The base address of the new entry. PADDR_ERROR is used is the base address doesn't matter.
 * @param context The LDT context.
 * @param size  The size, in bytes, of the entry.
 * @param flags The flags applied to the entry.
 * @param   index   The index to be created.
 * @return True on success, false otherwise.
 */
bool    ldt_add_entry(ldt_t *context, uint32_t base, size_t limit, uint32_t flags, uint16_t *index);

/**
 * Add a new entry to an LDT context at a specific index. It fails if it is not free.
 * @param addr  The base address of the new entry. PADDR_ERROR is used is the base address doesn't matter.
 * @param context The LDT context.
 * @param size  The size, in bytes, of the entry.
 * @param flags The flags applied to the entry.
 * @param   index   The index to be created.
 * @return True on success, false otherwise.
 */
bool    ldt_add_entry_at(ldt_t *context, uint16_t index, uint32_t base, size_t limit, uint32_t flags);

/**
 * Remove an entry from the LDT context.
 * @param context   The LDT context.
 * @param index The index of the entry to remove.
 * @return true on success, false otherwise.
 */
bool    ldt_remove_entry(ldt_t *context, uint16_t index);

#endif /* LDT_H_ */
