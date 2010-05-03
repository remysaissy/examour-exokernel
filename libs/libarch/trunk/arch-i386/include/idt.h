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

#ifndef IDT_H_
#define IDT_H_

#include    <stdint.h>
#include    <stdbool.h>

#include    "segments.h"
#include    "exceptions.h"

/**
 * This file contains the arch specific IDT interaction component.
 */

/**
 * The size, in bytes, of an IDT table.
 */
#define IDT_TABLE_SIZE  256

/**
 * Flush the idt register in order to install the new idt.
 * @param idtr  The new idt to install.
 */
void    idt_flush(idtr_t *idtr);

/**
 * Creates a new IDT context. This is typically an array of IDT entries.
 * @param context   The context to be created.
 * @return true on success, false otherwise.
 */
bool    idt_create(idt_t *context);

/**
 * Destroy an IDT context.
 * @param context   The IDT context to destroy.
 * @return true on success, false otherwise.
 */
bool    idt_destroy(idt_t *context);


/**
 * Add a new entry to an IDT context.
 * @param context The IDT context.
 * @param code_segment the segment selector to be used. (relative to the handler).
 * @param priv_lvl  The requested privilege level.
 * @param type  The type of gate to create.
 * @param  handle   The handler to execute.
 * @param   index   The index of the newly created entry.
 * @return True on success, false otherwise.
 */
bool    idt_add_entry(idt_t *context, selector_t code_segment, uint32_t flags, exception_raised_p handler, uint16_t *index);

/**
 * Add a new entry to an IDT context at a specified index. It fails if something is already present.
 * @param context The IDT context.
 * @param code_segment the segment selector to be used. (relative to the handler).
 * @param priv_lvl  The requested privilege level.
 * @param type  The type of gate to create.
 * @param  handle   The handler to execute.
 * @param   index   The requested index for the newly created entry.
 * @return True on success, false otherwise.
 */
bool    idt_add_entry_at(idt_t *context, uint16_t index, selector_t code_segment, uint32_t flags, exception_raised_p  handler);

/**
 * Remove an entry from the IDT context.
 * @param context   The IDT context.
 * @param index The index of the entry to remove.
 * @return true on success, false otherwise.
 */
bool    idt_remove_entry(idt_t *context, uint16_t index);

#endif /* IDT_H_ */
