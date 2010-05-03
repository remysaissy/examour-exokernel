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
** Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#ifndef	__TIMER_H__
#define	__TIMER_H__

/**
 * \brief	Header for the legacy intel timer.
 *		subsystem of the env component.
 */

/* currently only for the interrupt timer */
/* must be splitted into several files to */
/* manage other kind of timers */

/**
 * \brief	Clock frequency in hz, of the legacy i8254 timer.
 */
#define	I8254_MAX_FREQUENCY	1193180

#define I8254_TIMER0		0x40
#define I8254_TIMER1		0x41
#define I8254_TIMER2		0x42
#define I8254_CONTROL		0x43


#define	I8254_BINARY_COUNTER			0x0
#define	I8254_BCD				0x1
#define	I8254_MODE0				0x0			
#define	I8254_MODE1				0x2
#define	I8254_MODE2				0x4
#define	I8254_MODE3				0x6
#define	I8254_MODE4				0x8
#define	I8254_MODE5				0xa
#define	I8254_COUNTER_LATCHING_OPERATION	0x0
#define	I8254_RD_LSB				0x10
#define	I8254_RD_MSB				0x20
#define	I8254_RD_LSB_MSB			0x30
#define	I8254_COUNTER0				0x0
#define	I8254_COUNTER1				0x40
#define	I8254_COUNTER2				0x80



/**
 * \param x	The divisor to apply.
 * \return	The computed latch.
 * \brief	Get the latch of a desired clock rate.
 */
#define	LATCH(x)	((I8254_MAX_FREQUENCY + x / 2) / x)

/**
 * \param ms	Number of milliseconds.
 * \return	The frequency in Hz.
 * \brief	Convert a number of milliseconds in hertz.
 */
#define	MS_TO_HZ(ms)	(1000 / ms)

#ifndef	__ASM__

#include	<stdint.h>

/**
 * \param ms	Number of milliseconds before the next tick.
 * \brief	Configure the timer pulse frequency.
 */
void		timer_set(uint32_t ms);

/**
 * \return	Remaining number of milliseconds before the next tick.
 * \brief	Get the timer countdown value.
 */
uint32_t	timer_get(void);

#endif /* __ASM__ */

#endif /* __TIMER_H__ */
