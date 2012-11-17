/*
** This file is part of ExAmour

** Copyright (C) Rémy Saissy <remy.saissy@gmail.com>
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

#include	<stddef.h>
#include	<stdbool.h>

#include	"include/msr.h"

/* Kernel internal methods. */

uint64_t	get_tsc(void)
{
        uint64_t	val;

        asm volatile("rdtsc" : "=A" (val));
        return (val);
}

uint64_t	get_pmc(pmc_e pmc)
{
	uint64_t	val;

	asm volatile("rdpmc" : "=A" (val) : "c"(pmc));
    return (val);
}

uint64_t	get_msr(msr_e msr)
{
    uint64_t val;

    asm volatile("rdmsr" : "=A" (val) : "c" (msr));
    return (val);

}

void	set_msr(msr_e msr, uint64_t val)
{
    asm volatile("wrmsr" : : "c" (msr), "A"(val));
}
