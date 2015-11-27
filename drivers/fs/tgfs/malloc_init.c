/*
** options.c for malloc in /u/ept2/malver_l
** 
** Made by laurent malvert
** Login   <malver_l@epita.fr>
** 
** Started on  Tue Mar  2 00:38:39 2004 laurent malvert
 * Last update Sun Feb  4 19:21:58 2007 remy
*/

/* #include <stdlib.h> */
/* #include <unistd.h> */

#include "include/buckets.h"
#include "include/malloc_init.h"
#include "include/malloc.h"
#include "include/powers.h"
#include	<examour/support/string.h>

t_block_descriptor		*gl_start = NULL;
/* t_block_descriptor		gl_start[409600] = {0, }; */
int				gl_start_brk = 0;
extern t_block_descriptor	*gl_buckets[PROC_TYPE];

extern int base_addr;


t_block_descriptor		MY_SPACE[40960] = {0, };





t_block_descriptor	*get_memory(size_t size)
{
  static size_t		idx = 0;

  idx += size;
  return ((t_block_descriptor *)((gl_start) + idx));
}


void		set_start(char *func)
{
  if (!gl_start_brk)
    {
      gl_start_brk = 1;
/*       gl_start = (t_block_descriptor *)MY_SPACE; ////////////////// HERE */
      gl_start = MY_SPACE; ////////////////// HERE
      powers_of_two();
      memset(gl_buckets, 0, PROC_TYPE);
    }
}
