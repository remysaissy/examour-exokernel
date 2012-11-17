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

/* exAmour's memory manager layer 1 */
/* local descriptor table manager */
#include	<examour/mm/ldt.h>
#include	<examour/mm/phymem.h>
#include	<examour/mm/mem.h>
#include	<examour/core/globals.h>
#include	<examour/support/log.h>

void		ldt_init(void)
{
  /* Empty for now. */
  /* TODO: initialize the monitoring capabilities of the ldt manager. */
  info("Segmented memory manager initialized.\n");
}

bool		_ldt_create(ldtr_t *context, paddr_t new_env)
{
  ldt_t		*ldt;

  if (context == NULL)
    return (false);
  /* allocate the maximum size of an ldt. */
  if (phymem_ref_new((void *)&ldt,
		     LDT_MAX_SIZE,
		     REGULAR_ZONE|EXCLUSIVE) == false)
    return (false);
  /* cleanup the new ldt. */
  memset(ldt, 0, LDT_MAX_SIZE);

  /* setup the context. */
  context->base_addr = (paddr_t)ldt;
  /* limit for one entry. */
  context->limit = LDT_MAX_SIZE - 1;

  /* The ldt mapping. */
  ldt_add_entry(context,
		SEGMENT_TYPE_DATA_RD |
		SEGMENT_PRIV_3 |
		SEGMENT_32BITS,
		(paddr_t)ldt,
		LDT_MAX_SIZE);

  /* If new_env is PADDR_ERROR then it is probably a syscall from */
  /* userspace. gl_current_env is relevant in this case. */
  if (new_env != PADDR_ERROR)
    {
      /* The env data structure mapping. */
      ldt_add_entry(context,
		    SEGMENT_TYPE_DATA_RD |
		    SEGMENT_PRIV_3 |
		    SEGMENT_32BITS,
		    new_env + EXAMOUR_ENV_RO_MAPPING_BEGIN,
		    EXAMOUR_ENV_RO_MAPPING_SIZE);

      /* The env predicates mapping. */
      ldt_add_entry(context,
		    SEGMENT_TYPE_DATA_RW |
		    SEGMENT_PRIV_3 |
		    SEGMENT_32BITS,
		    new_env + EXAMOUR_ENV_RW_MAPPING_BEGIN,
		    EXAMOUR_ENV_RW_MAPPING_SIZE);
    }
  else
    {
      /* The env data structure mapping. */
      ldt_add_entry(context,
		    SEGMENT_TYPE_DATA_RD |
		    SEGMENT_PRIV_3 |
		    SEGMENT_32BITS,
		    (paddr_t)gl_current_env + EXAMOUR_ENV_RO_MAPPING_BEGIN,
		    EXAMOUR_ENV_RO_MAPPING_SIZE);

      /* The env predicates mapping. */
      ldt_add_entry(context,
		    SEGMENT_TYPE_DATA_RW |
		    SEGMENT_PRIV_3 |
		    SEGMENT_32BITS,
		    (paddr_t)gl_current_env + EXAMOUR_ENV_RW_MAPPING_BEGIN,
		    EXAMOUR_ENV_RW_MAPPING_SIZE);
    }
  return (true);
}

/* SYSCALL */
bool		ldt_create(ldtr_t *context)
{
  return (_ldt_create(context, PADDR_ERROR));
}

/* SYSCALL */
bool		ldt_destroy(ldtr_t *context)
{
  ldtr_t	*current_context;
  int		i;

  if (context)
    current_context = context;
  else
    current_context = &gl_current_env->ldtr;
  i = (current_context->limit + 1) / sizeof(ldt_t);
  /* In this loop there will be control on code segment in order */
  /* to manage correctly dynamic librairies. */
  while (i-- > 0)
    ldt_remove_entry(current_context, i);
  memset((void *)current_context->base_addr, 0, LDT_MAX_SIZE);
  phymem_unref(current_context->base_addr);
  current_context->base_addr = 0;
  current_context->limit = 0;
  return (true);
}

/* SYSCALL */
int		ldt_add_entry(ldtr_t *context,
			      uint32_t flags,
			      paddr_t base_addr,
			      size_t size)
{
  ldtr_t	*ldtr;
  paddr_t	*ldt;
  int		n_idx;
  int		i;
  int		opt;

  /* Size is an unsigned value, negative arguments would result in a huge allocation. */
  if (size == 0)
    return (-1);
  /* Check for the context. Revert to the current ldt if null. */
  ldtr = context;
  if (ldtr == NULL)
    ldtr = &gl_current_env->ldtr;
  ldt = (paddr_t *)ldtr->base_addr;
  n_idx = (ldtr->limit + 1) / sizeof(ldt_t);
  opt = 0;
  if ((flags & LDT_OPT_EXCLUSIVE))
    opt |= EXCLUSIVE;
  if ((flags & LDT_OPT_DMA) && (flags & LDT_OPT_RESERVED))
    return (-1);
  if ((flags & LDT_OPT_DMA))
    opt |= DMA_ZONE;
  if ((flags & LDT_OPT_RESERVED))
    opt |= RESERVED_ZONE;
  for (i = 0; i < n_idx; i++)
    {
      /* Find an available segment descriptor. */
      if (!(ldt[i * 2 + 1] & SEGMENT_PRESENT))
	{
	  /* Cleanup the flags. */
	  flags &= CLEANUP_MASK;

	  /* Set the default flags. */
	  flags |= SEGMENT_PRESENT|SEGMENT_NOT_SYSTEM;

	  if (size > 0x100000)
	    {
	      size = size / PAGE_SIZE + (size % PAGE_SIZE == 0 ? 0 : 1);
	      size *= PAGE_SIZE;
	    }
	  /* Memory allocation check. */
	  if (base_addr == PADDR_ERROR)
	    {
	      if (phymem_ref_new(&base_addr, size, opt) == false)
		{
		  info("Not enough memory for base_address.\n");
		  return (-1);
		}
	    }
	  /** \todo Fix the error here. Memory can't be referenced... */
	  /*	  else */
	  /*	    { */
	  /*	      if (phymem_ref_at(base_addr, size) == false) */
	  /*		{ */
	  /*		  info("Cannot reference memory base_address %p (size: %d byte%s).\n", */
	  /*		       base_addr, size, (size > 1) ? "s" : ""); */
	  /*		  return (false); */
	  /*		} */
	  /*	    } */

	  /* granularity check. */
	  if (size > 0x100000)
	    {
	      size = size / PAGE_SIZE + (size % PAGE_SIZE == 0 ? 0 : 1);
	      flags |= SEGMENT_GRANULARITY_4KB;
	    }
	  size = ((size - 1 == 0) ? 1 : size -1);
	  ldt[i * 2] = ((base_addr & 0xffff) << 16) | (size & 0xffff);
	  ldt[i * 2 + 1] = ((base_addr >> 16) & 0xff) |
	    (flags) | (base_addr & 0xff000000) | (size & 0xf0000);
	  /* Returns the segment index. */
/* 	  info("Flags: %p %p\n", flags, flags & SEGMENT_PRIV_3); */
/* 	  info("Last allocated index is: %p which gives: %p\n", i, i << 3 | 7); */
/* 	  ldt_dump(ldtr); */
	  return (i);
	}
    }
  /* Error, the context is full. */
  return (-1);
}

/* SYSCALL */
bool		ldt_remove_entry(ldtr_t *context, uint32_t index)
{
  ldtr_t	*ldtr;
  ldt_t		*ldt;

  ldtr = context;
  if (ldtr == NULL)
    ldtr = &gl_current_env->ldtr;
  if (index >= (ldtr->limit + 1) / sizeof(ldt[0]))
    return (false);
  ldt = (ldt_t *)ldtr->base_addr;
  /* Here will be the check of the code segment in order to  */
  /* correctly manage dynamic librairies. */
  if (get_segment_present(ldt[index]) == SEGMENT_PRESENT)
    {
      ldt[index][1] &= ~SEGMENT_PRESENT;
      phymem_unref(get_segment_base_address(ldt[0]));
      return (true);
    }
  return (false);
}


#if 0
void		ldt_flush(ldtr_t *context)
{
  ldtr_t	*ldtr;
  ldt_t		*ldt;
  int		i;

  ldtr = context;
  if (ldtr == NULL)
    ldtr = &gl_current_env->ldtr;
  ldt = (ldt_t *)ldtr->base_addr;
  for (i = 0; i < (ldtr->limit + 1) / 8; i++)
    ldt[i][1] &= ~SEGMENT_PRESENT;
}
#endif /* 0 */

void		ldt_dump(ldtr_t *ldtr)
{
  ldt_t		*ldt;
  int		i;

  if (ldtr == NULL)
      return;
  ldt = (ldt_t *)ldtr->base_addr;
  info("Dump of the ldt@%p:\n", ldt);
  for (i = 5; i < 7 && i < (ldtr->limit + 1) / 8; i++)
    {
      info("[LDT]%d(%p) present: %b base_addr: %p limit: %d "
	   "privilege level: %d type: %p\n", i,
	   (i << 3) | 0x7,
	   get_segment_present(ldt[i]),
	   get_segment_base_address(ldt[i]),
	   get_segment_limit(ldt[i]), get_segment_dpl(ldt[i]),
	   get_segment_type(ldt[i]));
    }
  info("End of dump.\n");
}
