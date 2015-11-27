/*
** powers.c for malloc in /u/ept2/malver_l
** 
** Made by laurent malvert
** Login   <malver_l@epita.fr>
** 
** Started on  Tue Mar  2 00:46:49 2004 laurent malvert
 * Last update Sun Feb  4 19:07:56 2007 remy
*/

#include "include/malloc.h"
#include "include/powers.h"

unsigned long		gl_powers[PROC_TYPE][4] = {0, };


/**
 * malloc's helper functions
 */
void			powers_of_two(void)
{
/*   register unsigned int	i; */

  gl_powers[0][0] = 0;
  gl_powers[0][1] = 0;
  gl_powers[0][2] = 1;
  gl_powers[1][0] = 1;
  gl_powers[1][1] = 1;
  gl_powers[1][2] = 2;

/*   for (i = PROC_TYPE2; i > 1; i--) */
/*     { */
/*       gl_powers[i][0] = i; */
/*       gl_powers[i][1] = 2 << (i - 2); */
/*       gl_powers[i][2] = 2 << (i - 1); */
/*     } */

  unsigned int	i = PROC_TYPE2;

  for (; i > 1; i--)
    {
      gl_powers[i][0] = i;
      gl_powers[i][1] = 2 << (i - 2);
      gl_powers[i][2] = 2 << (i - 1);
    }
}



unsigned int		r_p2_power(unsigned long value)
{
/*   register unsigned int	i; */

/*   for (i = PROC_TYPE2; i > 2; i -= 4) */
/*     {		/\* stops at 3 because of struct *\/ */
/*       if ((value > gl_powers[i][1]) && (value <= gl_powers[i][2])) */
/* 	return (gl_powers[i][0]); */
/*       if ((value > gl_powers[i - 1][1]) && (value <= gl_powers[i - 1][2])) */
/* 	return (gl_powers[i - 1][0]); */
/*       if ((value > gl_powers[i - 2][1]) && (value <= gl_powers[i - 2][2])) */
/* 	return (gl_powers[i - 2][0]); */
/*       if ((value > gl_powers[i - 3][1]) && (value <= gl_powers[i - 3][2])) */
/* 	return (gl_powers[i - 3][0]); */
/*     } */

  unsigned int	i;

  for (i = PROC_TYPE2; i > 2; i -= 4)
    {		/* stops at 3 because of struct */
      if ((value > gl_powers[i][1]) && (value <= gl_powers[i][2]))
	return (gl_powers[i][0]);
      if ((value > gl_powers[i - 1][1]) && (value <= gl_powers[i - 1][2]))
	return (gl_powers[i - 1][0]);
      if ((value > gl_powers[i - 2][1]) && (value <= gl_powers[i - 2][2]))
	return (gl_powers[i - 2][0]);
      if ((value > gl_powers[i - 3][1]) && (value <= gl_powers[i - 3][2]))
	{
/*       printf("%i %i %i\n", gl_powers[i - 3][1], */
/* 	     gl_powers[i - 3][2], gl_powers[i - 3][0]); */
/*       printf("%i\n", value); */
	  return (gl_powers[i - 3][0]);
	}
    }
  return (0);
}
