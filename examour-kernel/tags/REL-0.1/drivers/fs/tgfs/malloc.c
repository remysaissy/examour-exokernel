/*
** malloc.c for  in /u/ept2/guerin_t/c/rendu/proj/malloc
** 
** Made by thibaud guerin
** Login   <guerin_t@epita.fr>
** 
** Started on  Sat Feb 14 14:52:48 2004 thibaud guerin
 * Last update Sun Feb  4 19:14:55 2007 remy
*/

#include "include/buckets.h"
#include "include/malloc_init.h"
#include "include/malloc.h"
#include "include/powers.h"
#include	"../../video/vga/vga.h"

#include	<examour/support/string.h>

/* extern char			*__progname; */
/* extern char			gl_opt[]; */
extern unsigned long		gl_powers[PROC_TYPE][4];
extern unsigned int		gl_start_brk;
extern t_block_descriptor	*gl_start;
const unsigned int		gl_struct_size = sizeof(t_block_descriptor);
t_block_descriptor		*gl_sbrk = NULL;
t_block_descriptor		*gl_buckets[PROC_TYPE] = {0, };
extern char			*MY_SPACE;


void			ufree(void *ptr)
{
  if ((unsigned long)(ptr) % 4)
    {
      puts("sbrk: ");
      ltoa((unsigned long)(ptr) % 4, 10);
      putchar('\n');
    }

  if (!ptr)
    return ;
  else
    {
      if (!gl_start_brk)
	{
/* 	  putstr(__progname); */
	  puts(": warning: malloc() has never been called\n");
	  return ;
	}
      else
	{
	  register t_block_descriptor	*tmp;

	  tmp = (t_block_descriptor *)((char *)ptr - gl_struct_size);
	  if ((tmp >= gl_start) && (tmp < gl_sbrk)
	      && (tmp->next == NULL) && (tmp->p < PROC_TYPE3))
	    {
/* 	      if (gl_opt[1]) */
/* 		memset(ptr, 0xd0, tmp->p); */
/* 	      if (gl_opt[7]) */
/* 		memset(ptr, 0, tmp->p); */
	      tmp->next = gl_buckets[tmp->p];
	      gl_buckets[tmp->p] = tmp;
	      return ;
	    }
	  puts("LE POINTEUR A BOUGE, C PAS BIEN\n");
	}
    }
}



void		*collapse_create(unsigned int power, size_t size)
{
  t_block_descriptor	*new;

  if (gl_buckets[power])
    {
      new = gl_buckets[power];
      gl_buckets[power] = gl_buckets[power]->next;
    }
  else
    {
/*       if ((new = sbrk(size)) == (void *)-1) */
      if ((new = get_memory(size)) == (void *)-1)  /////////////////////// HERE
	return (NULL);
      (new)->p = power;

      /* (new)->p == p so .... */
      (new)->next = (void *)power;


/*       gl_sbrk = (t_block_descriptor *)sbrk(0); */
      gl_sbrk = get_memory(0); ////////////////////////////////// HERE
    }
  new->next = NULL;
/*   if (gl_opt[1]) */
/*     memset((unsigned char *)new + gl_struct_size, 0xd0, */
/* 	   P2(new->p) - gl_struct_size); */
/*   if (gl_opt[7]) */
/*     memset((unsigned char *)new + gl_struct_size, 0, */
/* 	   P2(new->p) - gl_struct_size); */
  return (new);
}


void		*free_n_malloc(char *cnew, char *cptr)
{
  unsigned long		len;

  len = P2((((t_block_descriptor *)cptr)->p)) - gl_struct_size;
/*   if (gl_opt[3] && */
/*       ((t_block_descriptor *)cptr)->p > */
/*       ((t_block_descriptor *)(cnew - gl_struct_size))->p) */
/*     len = P2(((t_block_descriptor *)(cnew - gl_struct_size))->p) */
/*       - gl_struct_size; */
  memcpy(cnew, cptr + gl_struct_size, len);
  ufree(cptr + gl_struct_size);
  return (cnew);
}



void			*urealloc(void *ptr, size_t size)
{
  if (!ptr)
    return (umalloc(size));
  if (!gl_start_brk)
    {
/*       putstr(__progname); */
      puts(/* " in "__func__ */
		     "(): warning: malloc() has never been called.\n");
      set_start(/* __func__ */);
      return (NULL);
    }
  else
    {
/*       if (gl_opt[5] && !size) */
/* 	{ */
/* 	  free(ptr); */
/* 	  return (NULL); */
/* 	} */
/*       else */
/* 	{ */
	  char			*cptr;
	  unsigned int		power;
	  unsigned int		nsize;

	  cptr = (char *)ptr - gl_struct_size;
	  power = r_p2_power(size + gl_struct_size);
	  nsize = P2(power);
	  if ((power <= ((t_block_descriptor *)cptr)->p)/*  && !gl_opt[3] */)
	    {
/* 	      if (gl_opt[7]) */
/* 		memset(cptr + gl_struct_size, 0, size); */
	      return (cptr + gl_struct_size);
	    }
	  else
	    {
	      t_block_descriptor	*new;

	      if (!(new = collapse_create(power, nsize)))
		return (NULL);
	      else
		{
/* 		  if (gl_opt[7]) */
/* 		    memset((char *)new + gl_struct_size, 0, size); */
		  return (free_n_malloc((char *)new + gl_struct_size, cptr));
		}
	    }
/* 	} */
    }
  return (0);
}



void			*ucalloc(size_t number, size_t size)
{
  char			*new;
  unsigned int		i;
  unsigned int		power;
  size_t		total;

  set_start(/* __func__ */);
  if (/* gl_opt[5] &&  */!size)
    return (NULL);
  power = r_p2_power((size * number) + gl_struct_size);
  size = P2(power);
  new = (char *)collapse_create(power, size) + gl_struct_size;
  total = size - gl_struct_size;
  for (i = 0; i < total; i += 2)
    memset(new + i, 0, 2);
  return (new);
}



void			*umalloc(size_t size)
{
  unsigned int		power;
  char			*ptr;
  size_t		nsize;

/*   if ((unsigned long)(sbrk(0)) % 4) */
  if ((unsigned long)(get_memory(0)) % 4)
    {
      puts("sbrk: ");
/*       aff_ulong((unsigned long)(sbrk(0)) % 4); */
      ltoa((unsigned long)(get_memory(0)) % 4, 10);
      putchar('\n');
    }
  set_start(/* __func__ */);
  if (/* gl_opt[5] &&  */!size)
    return (NULL);
  printf("size %i + gl_struct_size %i\n", size, gl_struct_size);
  power = r_p2_power(size + gl_struct_size);
  nsize = P2(power);
  ptr = (char *)(collapse_create(power, nsize)) + gl_struct_size;
  printf("nsize : %i\n", nsize);
/*   if (gl_opt[7]) */
/*     memset(ptr, 0, size); */
  return (ptr);
}
