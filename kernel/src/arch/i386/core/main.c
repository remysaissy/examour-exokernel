/*
** This file is part of examour

** Copyright (C) Remy Saissy <remy.saissy@epitech.net>
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

#include	<examour/core/reg.h>
#include	<examour/core/globals.h>
#include	<examour/mm/mem.h>
#include	<examour/env/env.h>
#include	<examour/env/timeslice.h>
#include	<examour/event/event.h>
#include	<examour/env/sched.h>
#include	<examour/version.h>
#include	<examour/event/syscall.h>
#include	<examour/support/log.h>
#include	<examour/mm/ldt.h>
#include	<examour/core/asm.h>
#include	<examour/core/multiboot.h>
#include	<examour/event/io.h>

static void	create_first_env(paddr_t first_env, size_t first_env_sz)
{
  {
    examour_env_section_t sections[3];
    eid_t	eid;

#define	UCODE_IDX	0
#define	USTACK_IDX	1
#define	UDATA_IDX	2
#define	UMAX_IDX	3

    /* This should be parsed in the grub's command line. */
    sections[UCODE_IDX].base_addr = first_env;
    sections[UCODE_IDX].size = first_env_sz;
    sections[UCODE_IDX].flags = SEGMENT_TYPE_CODE_EXEC |
				SEGMENT_PRIV_3 |
				SEGMENT_32BITS;
    sections[UCODE_IDX].hint = ENV_HINT_CODE;
    sections[UCODE_IDX].offset = 0;

    sections[USTACK_IDX].base_addr = PADDR_ERROR;
    sections[USTACK_IDX].size = PAGE_SIZE;
    sections[USTACK_IDX].flags = SEGMENT_TYPE_DATA_RW |
				 SEGMENT_PRIV_3 |
				 SEGMENT_32BITS;
    sections[USTACK_IDX].hint = ENV_HINT_STACK;
    sections[USTACK_IDX].offset = PAGE_SIZE - 1;

    sections[UDATA_IDX].base_addr = first_env;
    sections[UDATA_IDX].size = first_env_sz;
    sections[UDATA_IDX].flags = SEGMENT_TYPE_DATA_RW |
				SEGMENT_PRIV_3 |
				SEGMENT_32BITS;
    sections[UDATA_IDX].hint =  ENV_HINT_DS |
				ENV_HINT_ES |
				ENV_HINT_FS |
				ENV_HINT_GS;
    sections[UDATA_IDX].offset = 0;

    if ((eid = env_create("init",
			  CAP_ALIVE |
			  CAP_CREATE_ENV |
			  CAP_DESTROY_ENV |
			  CAP_ALLOC_MEM |
			  CAP_CREATE_MEM_CTX |
			  CAP_GRANT_IO |
			  CAP_EVENT,
			  sections,
			  UMAX_IDX)) == -1)
      panic("Unable to create the init env...\n");
    else
      info("eid is %d.\n", eid);
  }
}

/**
 * ExAmour's entry point.
 */
void		kmain(unsigned long magic, uint32_t mbi_addr)
{
  paddr_t	first_env = PADDR_ERROR;
  size_t	first_env_sz = 0;

  /* clear the screen. */
  cls();

  if (magic != MULTIBOOT_BOOTLOADER_MAGIC)
    panic("Bad magic number, unable to boot ExAmour.\n");
  mbi = (multiboot_info_t *)mbi_addr;

  {
    module_t *mod;
    int i;

    for (i = 0, mod = (module_t *)mbi->mods_addr;
	 i < mbi->mods_count; i++, mod++)
      {
	if (((char *)mod->string)[0] == '/' &&
	    ((char *)mod->string)[1] == 'i' &&
	    ((char *)mod->string)[2] == 'n' &&
	    ((char *)mod->string)[3] == 'i' &&
	    ((char *)mod->string)[4] == 't' &&
	    ((char *)mod->string)[5] == '\0')
	  {
	    /* setup the memory manager */
	    first_env = (paddr_t)mod->mod_start;
	    first_env_sz = (size_t)(mod->mod_end - mod->mod_start);
	    goto  first_env_mem_ok;
	  }
      }
    panic("No first env provided!\n");
  }
 first_env_mem_ok:

  /* Memory manager component */
  mem_init(&first_env, first_env_sz);

  /* caps manager component */
  io_init();

  /* Event manager component */
  event_init();

  /* setup the timeslices. */
  timeslice_init();

  /* Environnement manager component */
  /* setup the env. */
  env_init();

  /* setup the scheduler. */
  sched_init();

  /* begin running. */
  message(examour_VERSION_STRING " (" examour_VCS_REVISION ")\n");

  /* print_mbinfo(); */
  /* launch the init environment. */
  create_first_env(first_env, first_env_sz);
  enable_intr();
  while (1);
}
