/*
** malloc_init.h for  in /home/guth/WORKS/PFE/svn/exAmour/kernel/src/tgfs
** 
** Made by Thibaud_GUERIN
** Login   <guth@epita.fr>
** 
** Started on  Thu May 25 18:24:17 2006 Thibaud_GUERIN
** Last update Thu May 25 18:25:05 2006 Thibaud_GUERIN
*/

#ifndef __INIT_H__
# define __INIT_H__

/**
 * unused options for now
 */

/* # define OPT		{ return (1); } */
/* # define SET_J		{ gl_opt[1] = 1; gl_opt[3] = 1; OPT; } */
/* # define SET_Z		{ gl_opt[7] = 1; SET_J; } */
/* # define UNSET_J	{ gl_opt[1] = 0; gl_opt[3] = 0; OPT; } */
/* # define UNSET_Z	{ gl_opt[7] = 0; UNSET_J; } */
/* # define MALLOC_OPTIONS	19 */



int	setting_options(char *ptr, unsigned int i);
int	disabling_options(char *ptr, unsigned int i, int flag);

#endif
