/*
 * Copyright (c) 2006 Chevallerau Franck
 * <cheval_f@epitech.net>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */
/*
 * 10-04-2006 Chevallereau Franck
 * - types.h creation
 * - 
 *
*/
#ifndef _TYPES_H
#define _TYPES_H

//#if defined(IA32)
#include "arch/ia32/types.h"
#define BITS_WORD	(sizeof(word_t)*8)
typedef unsigned int addr_t;
//#elif !defined(IA32)
//#define unsigned int world_t;
//#endif /* defined(ARCH)*/
#endif /* !_TYPES_H */