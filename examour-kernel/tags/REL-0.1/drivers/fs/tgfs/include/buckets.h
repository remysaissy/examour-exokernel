/*
** buckets.h for malloc in /u/ept2/malver_l
** 
** Made by laurent malvert
** Login   <malver_l@epita.fr>
** 
** Started on  Mon Mar  1 18:25:09 2004 laurent malvert
** Last update Thu May 25 18:29:38 2006 Thibaud_GUERIN
*/

#ifndef __BUCKETS_H__
# define __BUCKETS_H__

/**
 * \brief	bucket structure
 * \param p	block size
 * \param next	next bucket
 */
typedef struct			u_block_descriptor
{
  unsigned long			p;	/* blocksize power of 2  */
  struct u_block_descriptor	*next;	/* next block pointer */
}				t_block_descriptor;


#endif
