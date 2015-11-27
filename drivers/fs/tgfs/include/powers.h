/*
** powers.h for malloc in /u/ept2/malver_l
** 
** Made by laurent malvert
** Login   <malver_l@epita.fr>
** 
** Started on  Tue Mar  2 00:49:51 2004 laurent malvert
** Last update Thu May 25 18:23:52 2006 Thibaud_GUERIN
*/

#ifndef __POWERS_H__
# define __POWERS_H__

/**
 * macro to count powers of 2 at compile time (save time on exec)
 */
# define P2(x)		(gl_powers[(x)][2])

void		powers_of_two(void);
unsigned int	r_p2_power(unsigned long value);

#endif
