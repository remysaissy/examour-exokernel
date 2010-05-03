/* 
 * This file is part of ExAmour

 * Copyright (C) Remy Saissy <remy.saissy@gmail.com>
 * ExAmour is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.

 * ExAmour is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#ifndef	__SEGMENTMM_H__
#define	__SEGMENTMM_H__

#ifndef	__ASM__

#include	<stdbool.h>
#include	<stddef.h>
#include	<stdint.h>

bool		segmentmm_init(size_t amount);

uint32_t	_segmentmm_init(size_t amount);

void		_copy_to_buffer(uint32_t new_data_sel, uint32_t src, size_t size);


void		*malloc(size_t size);

void		*calloc(size_t nmemb, size_t size);

void		free(void *p);

char		*strdup(const char *s);

#endif /* __ASM__ */

#endif /* __SEGMENT_H__ */
