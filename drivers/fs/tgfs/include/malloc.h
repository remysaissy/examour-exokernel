/*
** malloc.h for malloc in /u/ept2/malver_l
** 
** Made by laurent malvert
** Login   <malver_l@epita.fr>
** 
** Started on  Mon Mar  1 10:18:04 2004 laurent malvert
 * Last update Sun Feb  4 17:40:51 2007 remy
*/

#ifndef __MALLOC_H__
# define __MALLOC_H__

#include	<examour/core/segment_types.h>
#include	<stddef.h>

/**
 * set the number of buckets (= number of processor's bits)
 */
# define PROC_TYPE	32
# define PROC_TYPE2	(PROC_TYPE - 1)
# define PROC_TYPE3	(PROC_TYPE + 1)

extern ldt_t			my_seg[1];
#include "buckets.h"


t_block_descriptor	*get_memory(size_t size);
void	*umalloc(size_t size);
void	*ucalloc(size_t number, size_t size);
void	set_start(/* char *func */);
void	*urealloc(void *ptr, size_t size);
void	*free_n_malloc(char *cnew, char *cptr);
void	*collapse_create(unsigned int power, size_t size);
void	ufree(void *ptr);

#endif
