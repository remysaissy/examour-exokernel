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

#ifndef APIC_H_
#define APIC_H_

/**
 * This header contains declarations for APIC support in the kernel.
 * Kernel internal functions are declared in the global include exaevent.h since it
 * aims to be used by the rest of the kernel.
 */

#include	<stdint.h>
#include	<list.h>

/**
 * An APIC map. It contains among others, the apic_id, the LVR, ...
 */
typedef struct	__attribute__((aligned(16))) apic_map_s
{
	uint32_t	reserved0 __attribute__ ((aligned (16)));
	uint32_t	reserved1 __attribute__ ((aligned (16)));
	uint32_t	lapic_id __attribute__ ((aligned (16))); /** read write. */
	uint32_t	lapic_version __attribute__ ((aligned (16))); /** read only. */
	uint32_t	reserved2 __attribute__ ((aligned (16)));
	uint32_t	reserved3 __attribute__ ((aligned (16)));
	uint32_t	reserved4 __attribute__ ((aligned (16)));
	uint32_t	reserved5 __attribute__ ((aligned (16)));
	uint32_t	tpr __attribute__ ((aligned (16))); /** read write. */
	uint32_t	apr __attribute__ ((aligned (16))); /** read only. */
	uint32_t	ppr __attribute__ ((aligned (16))); /** read only. */
	uint32_t	eoi_reg __attribute__ ((aligned (16))); /** write only. */
	uint32_t	reserved6 __attribute__ ((aligned (16)));
	uint32_t	logical_dest_reg __attribute__ ((aligned (16))); /** read write. */
	uint32_t	dest_format_reg __attribute__ ((aligned (16))); /** read only (0-27). read write (28-31). */
	uint32_t	spurious_iv_reg __attribute__ ((aligned (16))); /** read write (0-8). read only (9-31). */
	uint32_t	isr1 __attribute__ ((aligned (16))); /** read only. */
	uint32_t	isr2 __attribute__ ((aligned (16))); /** read only. */
	uint32_t	isr3 __attribute__ ((aligned (16))); /** read only. */
	uint32_t	isr4 __attribute__ ((aligned (16))); /** read only. */
	uint32_t	isr5 __attribute__ ((aligned (16))); /** read only. */
	uint32_t	isr6 __attribute__ ((aligned (16))); /** read only. */
	uint32_t	isr7 __attribute__ ((aligned (16))); /** read only. */
	uint32_t	isr8 __attribute__ ((aligned (16))); /** read only. */
	uint32_t	tmr1 __attribute__ ((aligned (16))); /** read only. */
	uint32_t	tmr2 __attribute__ ((aligned (16))); /** read only. */
	uint32_t	tmr3 __attribute__ ((aligned (16))); /** read only. */
	uint32_t	tmr4 __attribute__ ((aligned (16))); /** read only. */
	uint32_t	tmr5 __attribute__ ((aligned (16))); /** read only. */
	uint32_t	tmr6 __attribute__ ((aligned (16))); /** read only. */
	uint32_t	tmr7 __attribute__ ((aligned (16))); /** read only. */
	uint32_t	tmr8 __attribute__ ((aligned (16))); /** read only. */
	uint32_t	irr1 __attribute__ ((aligned (16))); /** read only. */
	uint32_t	irr2 __attribute__ ((aligned (16))); /** read only. */
	uint32_t	irr3 __attribute__ ((aligned (16))); /** read only. */
	uint32_t	irr4 __attribute__ ((aligned (16))); /** read only. */
	uint32_t	irr5 __attribute__ ((aligned (16))); /** read only. */
	uint32_t	irr6 __attribute__ ((aligned (16))); /** read only. */
	uint32_t	irr7 __attribute__ ((aligned (16))); /** read only. */
	uint32_t	irr8 __attribute__ ((aligned (16))); /** read only. */
	uint32_t	error_status_reg __attribute__ ((aligned (16))); /** read only. */
	uint32_t	reserved7 __attribute__ ((aligned (16)));
	uint32_t	reserved8 __attribute__ ((aligned (16)));
	uint32_t	reserved9 __attribute__ ((aligned (16)));
	uint32_t	reserved10 __attribute__ ((aligned (16)));
	uint32_t	reserved11 __attribute__ ((aligned (16)));
	uint32_t	reserved12 __attribute__ ((aligned (16)));
	uint32_t	reserved13 __attribute__ ((aligned (16)));
	uint32_t	icrlo __attribute__ ((aligned (16))); /** read write. */
	uint32_t	icrhi __attribute__ ((aligned (16))); /** read write. */
	uint32_t	timer_reg __attribute__ ((aligned (16))); /** read write. */
	uint32_t	thermal_sensor_reg __attribute__ ((aligned (16))); /** read write. */
	uint32_t	pmc_reg __attribute__ ((aligned (16))); /** read write. */
	uint32_t	lint0 __attribute__ ((aligned (16))); /** read write. */
	uint32_t	lint1 __attribute__ ((aligned (16)));	 /** read write. */
	uint32_t	lvt_error_reg __attribute__ ((aligned (16))); /** read write. */
	uint32_t	initial_timer_count __attribute__ ((aligned (16))); /** read write. */
	uint32_t	current_timer_count __attribute__ ((aligned (16))); /** read only. */
	uint32_t	reserved14 __attribute__ ((aligned (16)));
	uint32_t	reserved15 __attribute__ ((aligned (16)));
	uint32_t	reserved16 __attribute__ ((aligned (16)));
	uint32_t	reserved17 __attribute__ ((aligned (16)));
	uint32_t	timer_divide __attribute__ ((aligned (16))); /** read write. */
	uint32_t	reserved18 __attribute__ ((aligned (16)));

}				apic_map_t;

/**
 * The APIC structure. It is a chained list, one entry per cpu.
 */
typedef struct	apic_entry_s
{
	slist_t		entries;
	apic_map_t	*map;	/* uint64_t	apic_base_addr; */

}				apic_entry_t;

apic_entry_t	apic_entries[1];


/* APIC related functions. */
/** NOTE: If one APIc function is needed globally for the kernel,
 * move the delcaration from this file to the global exaevent header.
 */


/**
 * Get the current local APIC id. This is also use to identify cpus in the kernel.
 * @returns the current apic id.
 */
uint32_t    get_lapic_id(void);


/**
 * Set a value to the current local APIC id.
 */
void		set_lapic_id(uint32_t lapic_id);

/**
 * Get the local APIC version.
 * @returns the local APIC version.
 */
uint32_t	get_lapic_version(void);

/**
 * Get the maximum LVT entries.
 * @returns The maximum number of LVT entries.
 */
uint32_t	get_lapic_max_lvt(void);

/**
 * Get the current value of the task priority register.
 * @returns the current value of the task priority register.
 */
void		get_task_priority_register(uint32_t *task_priority, uint32_t *task_priority_subclass);

/**
 * Set a new value to the task priority register.
 */
void		set_task_priority_register(uint32_t task_priority, uint32_t task_priority_subclass);

/**
 * Get the current value of the arbitration priority register.
 * @returns the current value of the arbitration priority register.
 */
void		get_arbitration_priority_register(uint32_t *arb_priority, uint32_t *arb_priority_subclass);

/**
 * Get the current value of the processor priority register.
 * @returns the current value of the processor priority register.
 */
void		get_processor_priority_register(uint32_t *proc_priority, uint32_t *proc_priority_subclass);

/**
 * Set a new value to the end of interrupt register.
 */
void		set_eoi_register(uint32_t eoi);

/**
 * Get the current value of the logical destination register.
 * @returns the current value of the logical destination register.
 */
uint32_t	get_logical_destination_register(void);

/**
 * Set a new value to the logical destination register.
 */
void		set_logical_destination_register(uint32_t logical_destination_register);

/* Macros related to DFR. */

#define	DFR_FLAT_MODEL		0xf
#define	DFR_CLUSTER_MODEL	0x0

/**
 * Get the current value of the destination format register.
 * @returns the current value of the destination format register.
 */
uint32_t	get_destination_format_register(void);

/**
 * Set a new value to the destination format register.
 */
void		set_destination_format_register(uint32_t destination_format_register);


/* Macros related to spurious vector register. */

#define	SPURIOUS_APIC_DISABLED	0x0
#define	SPURIOUS_APIC_ENABLED	0x100

#define	SPURIOUS_FOCUS_PROC_CHECK_DISABLED	0x0
#define	SPURIOUS_FOCUS_PROC_CHECK_ENABLED	0x200

/**
 * Get the current value of the spurious IV register.
 * @returns the current value of the spurious IV register.
 */
void		get_spurious_iv_register(uint32_t *vector, uint32_t *flags);

/**
 * Set a new value to the spurious IV register.
 */
void		set_spurious_iv_register(uint32_t vector, uint32_t flags);

/**
 * Get the current value of an in-service register (ISR).
 * @param	vector	the isr's vector. (through 1 to 8).
 * @returns the current value of the ISR register.
 */
uint32_t	get_isr_register(uint32_t vector);

/**
 * Get the current value of a trigger mode register (TMR).
 * @param	vector	the tmr's vector. (through 1 to 8).
 * @returns the current value of the TMR register.
 */
uint32_t	get_tmr_register(uint32_t vector);

/**
 * Get the current value of a interrupt request register (IRR).
 * @param	vector	the irr's vector. (through 1 to 8).
 * @returns the current value of the IRR register.
 */
uint32_t	get_irr_register(uint32_t vector);

/* Macros related to ESR. */

#define	ESR_SEND_CHECKSUM_ERROR	0x1
#define	ESR_RECEIVE_CHECKSUM_ERROR	0x2
#define	ESR_SEND_ACCEPT_ERROR		0x4
#define	ESR_RECEIVE_ACCEPT_ERROR	0x8
#define	ESR_SEND_ILLEGAL_VECTOR		0x20
#define	ESR_RECEIVE_ILEGAL_VECTOR	0x40
#define	ESR_ILLEGAL_REG_ADDRESS		0x80

/**
 * Get the current value of a error status register.
 * @returns the current value of the error status register.
 */
uint32_t	get_error_status_register(void);

void		set_error_status_register(uint32_t esr);

/* ICR flags macros. */
#define	ICR_DELIVERY_FIXED						0x0
#define	ICR_DELIVERY_LOWEST_PRIORITY			0x100
#define	ICR_DELIVERY_SMI						0x200
#define	ICR_DELIVERY_NMI						0x400
#define	ICR_DELIVERY_INIT						0x500
#define	ICR_DELIVERY_SIPI						0x600

#define	ICR_DESTINATION_MODE_PHYSICAL			0x0
#define	ICR_DESTINATION_MODE_LOGICAL			0x800

#define	ICR_DELIVERY_STATUS_IDLE				0x0
#define	ICR_DELIVERY_STATUS_PENDING				0x1000

#define	ICR_LEVEL_DEASSERT						0x0
#define	ICR_LEVEL_ASSERT						0x4000

#define	ICR_TRIGGER_EDGE						0x0
#define	ICR_TRIGGER_LEVEL						0x8000

#define	ICR_DESTINATION_SHORTHAND_NONE			0x0
#define	ICR_DESTINATION_SHORTHAND_SELF			0x40000
#define	ICR_DESTINATION_SHORTHAND_ALL			0x80000
#define	ICR_DESTINATION_SHORTHAND_ALL_BUT_SELF	0xC0000

/**
 * Get the current value of a interrupt command register (ICR).
 */
void		get_icr_register(uint32_t *vector, uint32_t *flags, uint32_t *destination);

/**
 * Set a new value to the interrupt command register (ICR).
 */
void		set_icr_register(uint32_t vector, uint32_t flags, uint32_t destination);

/* Timer related macros. */

#define	TIMER_DELIVERY_STATUS_IDLE				0x0
#define	TIMER_DELIVERY_STATUS_PENDING				0x1000

#define	TIMER_NOT_MASKED	0x0
#define	TIMER_MASKED		0x10000

#define	TIMER_MODE_ONE_SHOT	0x0
#define	TIMER_MODE_PERIODIC	0x20000

/**
 * Get the current value of a timer register.
 * @returns the current value of the timer register.
 */
void		get_timer_register(uint32_t *vector, uint32_t *flags);

/**
 * Set a new value to the timer register.
 */
void		set_timer_register(uint32_t vector, uint32_t flags);

/* macros related to thermal sensor */

#define	THERMAL_SENSOR_DELIVERY_MODE_FIXED			0x0
#define	THERMAL_SENSOR_DELIVERY_MODE_SMI			0x200
#define	THERMAL_SENSOR_DELIVERY_MODE_NMI			0x400
#define	THERMAL_SENSOR_DELIVERY_MODE_EXTINT			0x700
#define	THERMAL_SENSOR_DELIVERY_MODE_INIT			0x500

#define	THERMAL_SENSOR_DELIVERY_STATUS_IDLE			0x0
#define	THERMAL_SENSOR_DELIVERY_STATUS_PENDING		0x1000

#define	THERMAL_SENSOR_NOT_MASKED					0x0
#define	THERMAL_SENSOR_MASKED						0x10000

/**
 * Get the current value of a thermal sensor register.
 * @returns the current value of the thermal sensor register.
 */
void		get_thermal_sensor_register(uint32_t *vector, uint32_t *flags);

/**
 * Set a new value to the thermal sensor register.
 */
void		set_thermal_sensor_register(uint32_t vector, uint32_t flags);

/* macros related to performance monitoring counter. */

#define	PMC_DELIVERY_MODE_FIXED	0x0
#define	PMC_DELIVERY_MODE_SMI		0x200
#define	PMC_DELIVERY_MODE_NMI		0x400
#define	PMC_DELIVERY_MODE_EXTINT	0x700
#define	PMC_DELIVERY_MODE_INIT		0x500

#define	PMC_DELIVERY_STATUS_IDLE	0x0
#define	PMC_DELIVERY_STATUS_PENDING	0x1000

#define	PMC_NOT_MASKED							0x0
#define	PMC_MASKED								0x10000

/**
 * Get the current value of a performance monitoring counters register.
 * @returns the current value of the performance monitoring counters register.
 */
void		get_pmc_register(uint32_t *vector, uint32_t *flags);

/**
 * Set a new value to the performance monitoring counters register.
 */
void		set_pmc_register(uint32_t vector, uint32_t flags);

/* macros related to lint. */

#define	LINT_DELIVERY_MODE_FIXED	0x0
#define	LINT_DELIVERY_MODE_SMI		0x200
#define	LINT_DELIVERY_MODE_NMI		0x400
#define	LINT_DELIVERY_MODE_EXTINT	0x700
#define	LINT_DELIVERY_MODE_INIT		0x500

#define	LINT_DELIVERY_STATUS_IDLE	0x0
#define	LINT_DELIVERY_STATUS_PENDING	0x1000

#define	LINT_INTERRUPT_INPUT_PIN_POLARITY_HIGH	0x0
#define	LINT_INTERRUPT_INPUT_PIN_POLARITY_LOW	0x2000

#define	LINT_REMOTE_IRR							0x4000

#define	LINT_TRIGGER_EDGE						0x0
#define	LINT_TRIGGER_LEVEL						0x8000

#define	LINT_NOT_MASKED							0x0
#define	LINT_MASKED								0x10000

/**
 * Get the current value of a LINT register.
 * @param	vector	LINT's vector (through 1 to 2).
 * @returns the current value of the LINT register.
 */
void		get_lint_register(uint32_t id, uint32_t *vector, uint32_t *flags);

/**
 * Set a new value to the LINT register.
 * @param	vector	LINT's vector (through 1 to 2).
 */
void		set_lint_register(uint32_t id, uint32_t vector, uint32_t flags);

/* Macros related to LVT error. */

#define	LVT_EROR_DELIVERY_STATUS_IDLE		0x0
#define	LVT_ERROR_DELIVERY_STATUS_PENDING	0x1000

#define	LVT_ERROR_NOT_MASKED				0x0
#define	LVT_ERROR_MASKED					0x10000

/**
 * Get the current value of a LVT error register.
 * @returns the current value of the LVT error register.
 */
void		get_lvt_error_register(uint32_t *vector, uint32_t *flags);

/**
 * Set a new value to the LVT error register.
 */
void		set_lvt_error_register(uint32_t vector, uint32_t flags);

/**
 * Get the current value of a initial timer count register.
 * @returns the current value of the initial timer count register.
 */
uint32_t	get_initial_timer_count_register(void);

/**
 * Set a new value to the initial timer count register.
 */
void		set_initial_timer_count_register(uint32_t initial_timer_count);

/**
 * Get the current value of a current timer count register.
 * @returns the current value of the current timer count register.
 */
uint32_t	get_current_timer_count_register(void);

/* Macro related to divide count timer. */

#define	TIMER_DIVIDE_BY_1		0x7
#define	TIMER_DIVIDE_BY_2		0x0
#define	TIMER_DIVIDE_BY_4		0x1
#define	TIMER_DIVIDE_BY_8		0x2
#define	TIMER_DIVIDE_BY_16		0x3
#define	TIMER_DIVIDE_BY_32		0x8
#define	TIMER_DIVIDE_BY_64		0x9
#define	TIMER_DIVIDE_BY_128		0xa

#define	TIMER_DIVIDE_MASK		0x7

/**
 * Get the current value of a timer divide register.
 * @returns the current value of the timer divide register.
 */
uint32_t	get_timer_divide_count_register(void);

/**
 * Set a new value to the timer divide register.
 */
void		set_timer_divide_register(uint32_t timer_divide);


#endif /*APIC_H_*/
