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

#ifndef GDT_H_
#define GDT_H_

#include    <stdint.h>
#include    <stdbool.h>

#include    "segments.h"

/**
 * This file contains the arch specific GDT interaction component.
 */

/**
 * The size, in bytes, of an GDT table.
 */
#define GDT_TABLE_SIZE  512

/**
 * Flush the Gdtr register in order to install the new gdt.
 * @param   gdtr    The new gdt to be installed.
 * @param   ds      The ds data segment selector.
 * @param   es      The es data segment selector.
 * @param   fs      The fs data segment selector.
 * @param   gs      The gs data segment selector.
 * @param   ss      The ss data segment selector.
 * @param   cs      The cs data segment selector.
 */
void    gdt_flush(gdtr_t *gdtr, selector_t ds, selector_t es, selector_t fs, selector_t gs, selector_t ss, selector_t cs);

/**
 * Creates a new GDT context. This is typically an array of GDT entries.
 * @param context   The context to be created.
 * @return true on success, false otherwise.
 */
bool    gdt_create(gdt_t *context);

/**
 * Destroy an GDT context.
 * @param context   The GDT context to destroy.
 * @return true on success, false otherwise.
 */
bool    gdt_destroy(gdt_t *context);

/**
 * Add a new entry to an GDT context.
 * @param addr  The base address of the new entry. PADDR_ERROR is used is the base address doesn't matter.
 * @param context The GDT context.
 * @param size  The size, in bytes, of the entry.
 * @param flags The flags applied to the entry.
 * @param   index   The index to be created.
 * @return True on success, false otherwise.
 */
bool    gdt_add_entry(gdt_t *context, uint32_t base, size_t limit, uint32_t flags, uint16_t *index);

/**
 * Add a new entry to an GDT context at a specific index. It fails if it is not free.
 * @param addr  The base address of the new entry. PADDR_ERROR is used is the base address doesn't matter.
 * @param context The GDT context.
 * @param size  The size, in bytes, of the entry.
 * @param flags The flags applied to the entry.
 * @param   index   The index to be created.
 * @return True on success, false otherwise.
 */
bool    gdt_add_entry_at(gdt_t *context, uint16_t index, uint32_t base, size_t limit, uint32_t flags);

/**
 * Remove an entry from the GDT context.
 * @param context   The GDT context.
 * @param index The index of the entry to remove.
 * @return true on success, false otherwise.
 */
bool    gdt_remove_entry(gdt_t *context, uint16_t index);

#endif /* GDT_H_ */
