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

#include	<stdlib.h>

#include	"include/apic.h"

/** TODO: exceptions/irq handling through APIC must be implemented. */

uint32_t	get_lapic_id(void)
{
	uint32_t	lapic_id;

	lapic_id = (apic_entries[0].map->lapic_id >> 24) & 0xff;
	return (lapic_id);
}

void		set_lapic_id(uint32_t lapic_id)
{
	apic_entries[0].map->lapic_id = (lapic_id << 24) & 0xff000000;
}

uint32_t	get_lapic_version(void)
{
	uint32_t	lapic_version;

	lapic_version = (apic_entries[0].map->lapic_version & 0xff);
	return (lapic_version);
}

uint32_t	get_lapic_max_lvt(void)
{
	uint32_t	max_lvt;

	max_lvt = (apic_entries[0].map->lapic_version >> 16) & 0xff;
	return (max_lvt + 1);
}

void		get_task_priority_register(uint32_t *task_priority, uint32_t *task_priority_subclass)
{
	uint32_t	tpr;

	if (task_priority == NULL || task_priority_subclass == NULL)
		return;
	tpr = apic_entries[0].map->tpr;
	*task_priority = (tpr >> 4) & 0xf;
	*task_priority_subclass = (tpr & 0xf);
}

void		set_task_priority_register(uint32_t task_priority, uint32_t task_priority_subclass)
{
	apic_entries[0].map->tpr = (task_priority_subclass & 0xf) | ((task_priority << 4) & 0xf0);
}

void		get_arbitration_priority_register(uint32_t *arb_priority, uint32_t *arb_priority_subclass)
{
	uint32_t	apr;

	if (arb_priority == NULL || arb_priority_subclass == NULL)
		return;
	apr = apic_entries[0].map->apr;
	*arb_priority = (apr >> 4) & 0xf;
	*arb_priority_subclass = (apr & 0xf);
}

void	   get_processor_priority_register(uint32_t *proc_priority, uint32_t *proc_priority_subclass)
{
	uint32_t	ppr;

	if (proc_priority == NULL || proc_priority_subclass == NULL)
		return;
	ppr = apic_entries[0].map->ppr;
	*proc_priority = (ppr >> 4) & 0xf;
	*proc_priority_subclass = (ppr & 0xf);
}

void		set_eoi_register(uint32_t eoi)
{
	apic_entries[0].map->eoi_reg = eoi;
}

uint32_t	get_logical_destination_register(void)
{
	uint32_t	ldr;

	ldr = (apic_entries[0].map->logical_dest_reg >> 24) & 0xff;
	return (ldr);
}

void		set_logical_destination_register(uint32_t logical_destination_register)
{
	apic_entries[0].map->logical_dest_reg = (logical_destination_register & 0xff) << 24;
}

uint32_t	get_destination_format_register(void)
{
	uint32_t	dfr;

	dfr = (apic_entries[0].map->dest_format_reg >> 28) & 0xf;
	return (dfr);
}

void		set_destination_format_register(uint32_t destination_format_register)
{
	apic_entries[0].map->dest_format_reg = (destination_format_register & 0xf) << 28;
}

void		get_spurious_iv_register(uint32_t *vector, uint32_t *flags)
{
	uint32_t	spurious_iv;

	if (vector == NULL || flags == NULL)
		return;
	spurious_iv = apic_entries[0].map->spurious_iv_reg;
	*vector = (spurious_iv & 0xff);
}

void		set_spurious_iv_register(uint32_t vector, uint32_t flags)
{
	apic_entries[0].map->spurious_iv_reg = (vector & 0xff) | ((flags << 8) & 0x300);
}

uint32_t	get_isr_register(uint32_t vector)
{
	uint32_t	isr;

	switch (vector)
	{
	case 1:
		isr = apic_entries[0].map->isr1;
		break;
	case 2:
		isr = apic_entries[0].map->isr2;
		break;
	case 3:
		isr = apic_entries[0].map->isr3;
		break;
	case 4:
		isr = apic_entries[0].map->isr4;
		break;
	case 5:
		isr = apic_entries[0].map->isr5;
		break;
	case 6:
		isr = apic_entries[0].map->isr6;
		break;
	case 7:
		isr = apic_entries[0].map->isr7;
		break;
	case 8:
		isr = apic_entries[0].map->isr8;
		break;
	default:
		isr = 0;
	}
	return (isr);
}

uint32_t	get_tmr_register(uint32_t vector)
{
	uint32_t	tmr;

	switch (vector)
	{
	case 1:
		tmr = apic_entries[0].map->tmr1;
		break;
	case 2:
		tmr = apic_entries[0].map->tmr2;
		break;
	case 3:
		tmr = apic_entries[0].map->tmr3;
		break;
	case 4:
		tmr = apic_entries[0].map->tmr4;
		break;
	case 5:
		tmr = apic_entries[0].map->tmr5;
		break;
	case 6:
		tmr = apic_entries[0].map->tmr6;
		break;
	case 7:
		tmr = apic_entries[0].map->tmr7;
		break;
	case 8:
		tmr = apic_entries[0].map->tmr8;
		break;
	default:
		tmr = 0;
	}
	return (tmr);
}

uint32_t	get_irr_register(uint32_t vector)
{
	uint32_t	irr;

	switch (vector)
	{
	case 1:
		irr = apic_entries[0].map->irr1;
		break;
	case 2:
		irr = apic_entries[0].map->irr2;
		break;
	case 3:
		irr = apic_entries[0].map->irr3;
		break;
	case 4:
		irr = apic_entries[0].map->irr4;
		break;
	case 5:
		irr = apic_entries[0].map->irr5;
		break;
	case 6:
		irr = apic_entries[0].map->irr6;
		break;
	case 7:
		irr = apic_entries[0].map->irr7;
		break;
	case 8:
		irr = apic_entries[0].map->irr8;
		break;
	default:
		irr = 0;
	}
	return (irr);
}

uint32_t	get_error_status_register(void)
{
	uint32_t	err_status;

	err_status = apic_entries[0].map->error_status_reg;
	return (err_status);
}

void		set_error_status_register(uint32_t esr)
{
	apic_entries[0].map->error_status_reg = esr;
}

void		get_icr_register(uint32_t *vector,
							uint32_t *flags,
							uint32_t *destination)
{
	if (flags == NULL || destination == NULL || vector == NULL)
		return;
	*destination = (apic_entries[0].map->icrhi >> 24) & 0xff;
	*flags = apic_entries[0].map->icrlo & ~0xff;
	*vector = apic_entries[0].map->icrlo & 0xff;
}

void		set_icr_register(uint32_t vector, uint32_t flags, uint32_t destination)
{
	apic_entries[0].map->icrhi = destination & 0xff000000;
	apic_entries[0].map->icrlo = (vector & 0xff) | (flags & ~0xff);
}

void		get_timer_register(uint32_t *vector, uint32_t *flags)
{
	uint32_t	timer_register;

	if (vector == NULL || flags == NULL)
		return;
	timer_register = apic_entries[0].map->timer_reg;
	*vector = timer_register & 0xff;
	*flags = timer_register & ~0xff;
}

void		set_timer_register(uint32_t vector, uint32_t flags)
{
	apic_entries[0].map->timer_reg = (vector & 0xff) | (flags & ~0xff);
}

void		get_thermal_sensor_register(uint32_t *vector, uint32_t *flags)
{
	uint32_t	thermal_sensor;

	if (vector == NULL || flags == NULL)
		return;
	thermal_sensor = apic_entries[0].map->thermal_sensor_reg;
	*vector = thermal_sensor & 0xff;
	*flags = thermal_sensor & ~0xff;
}

void		set_thermal_sensor_register(uint32_t vector, uint32_t flags)
{
	apic_entries[0].map->thermal_sensor_reg = (vector & 0xff) | (flags & ~0xff);
}

void		get_pmc_register(uint32_t *vector, uint32_t *flags)
{
	uint32_t	pmc;

	if (vector == NULL || flags == NULL)
		return;
	pmc = apic_entries[0].map->pmc_reg;
	*vector = pmc & 0xff;
	*flags = pmc & ~0xff;
}

void		set_pmc_register(uint32_t vector, uint32_t flags)
{
	apic_entries[0].map->pmc_reg = (vector & 0xff) | (flags & ~0xff);
}

void		get_lint_register(uint32_t id, uint32_t *vector, uint32_t *flags)
{
	uint32_t	lint;

	if (vector == NULL || flags == NULL)
		return;
	switch (id)
	{
	case 0:
		lint = apic_entries[0].map->lint0;
		break;
	case 1:
		lint = apic_entries[0].map->lint1;
		break;
	default:
		return;
	}
	*vector = lint & 0xff;
	*flags = lint & ~0xff;
}

void		set_lint_register(uint32_t id, uint32_t vector, uint32_t flags)
{
	switch (id)
	{
	case 0:
		apic_entries[0].map->lint0 = (vector & 0xff) | (flags & ~0xff);
		break;
	case 1:
		apic_entries[0].map->lint1 = (vector & 0xff) | (flags & ~0xff);
		break;
	default:
		break;
	}
}

void		get_lvt_error_register(uint32_t *vector, uint32_t *flags)
{
	uint32_t	lvt_error;

	if (vector == NULL || flags == NULL)
		return;
	lvt_error = apic_entries[0].map->lvt_error_reg;
	*vector = lvt_error & 0xff;
	*flags = lvt_error & ~0xff;
}

void		set_lvt_error_register(uint32_t vector, uint32_t flags)
{
	apic_entries[0].map->lvt_error_reg = (vector & 0xff) | (flags & ~0xff);
}

uint32_t	get_initial_timer_count_register(void)
{
	uint32_t	initial_timer_count;

	initial_timer_count = apic_entries[0].map->initial_timer_count;
	return (initial_timer_count);
}

void		set_initial_timer_count_register(uint32_t initial_timer_count)
{
	apic_entries[0].map->initial_timer_count = initial_timer_count;
}

uint32_t	get_current_timer_count_register(void)
{
	uint32_t	current_timer_count;

	current_timer_count = apic_entries[0].map->current_timer_count;
	return (current_timer_count);
}

uint32_t	get_timer_divide_count_register(void)
{
	uint32_t	timer_divide_count;

	timer_divide_count = apic_entries[0].map->timer_divide;
	return (timer_divide_count);
}


void		set_timer_divide_register(uint32_t timer_divide)
{
	apic_entries[0].map->timer_divide = timer_divide;
}
