/* 
 * This file is part of eash

 * Copyright (C) Remy Saissy <remy.saissy@gmail.com>
 * eash is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.

 * eash is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#include	<vga.h>
#include	<examour_api.h>

#include	<examour/mm/ldt.h>

#include	"commands.h"
#include	"env_ctl.h"

const command_t	const env_subcommands[] =
  {
    {"help", "?", "Help of the env subcommands.", NULL, do_env_help},
    {"state", "s", "Get the status of the current env.", NULL, do_env_status_dump},
    {"upcalls", "u", "Get the upcalls of the current env.", NULL, do_env_upcalls_dump},
    {NULL, NULL, NULL, NULL, NULL},
  };

int	do_env_help(void)
{
  puts("Env subcommands list:\n");
  list_commands(env_subcommands);
  return (0);
}

int	do_env_status_dump(void)
{
  env_state_e		state;		/** current state of the env */
  eid_t			eid;		/** eid of the environment. */
  struct iocap_s	*iocaps;		/** The capabilities of the env. */
  basic_cap_t		basic_cap;	/** The basic capabilities of the env. */
  uint64_t		total_cputime;  /** amount of time currently allocated */

  segment_read4_by_index(KENV_ENTRY_IDX,
			 (paddr_t)EXAMOUR_ENV_RO_MAPPING_BEGIN,
			 (uint32_t)&state);
  segment_read4_by_index(KENV_ENTRY_IDX,
			 (paddr_t)(EXAMOUR_ENV_RO_MAPPING_BEGIN + 4),
			 (uint32_t)&eid);
  segment_read4_by_index(KENV_ENTRY_IDX,
			 (paddr_t)(EXAMOUR_ENV_RO_MAPPING_BEGIN + 12),
			 (uint32_t)iocaps);
  segment_read4_by_index(KENV_ENTRY_IDX,
			 (paddr_t)(EXAMOUR_ENV_RO_MAPPING_BEGIN + 16),
			 (uint32_t)&basic_cap);
  segment_read4_by_index(KENV_ENTRY_IDX,
			 (paddr_t)(EXAMOUR_ENV_RO_MAPPING_BEGIN + 28),
			 (uint32_t)&total_cputime);
  segment_read4_by_index(KENV_ENTRY_IDX,
			 (paddr_t)(EXAMOUR_ENV_RO_MAPPING_BEGIN + 24),
			 (uint32_t)(&total_cputime + 1));
  printf("Environment informations:\n"
	 "state is %s\n"
	 "eid is %u\n"
	 "%s io capabilities\n"
	 "basic caps are %u\n"
	 "%u ticks of cpu time consumed\n",
	 (state == env_stopped) ? "stopped" :
	 (state == env_running) ? "running" :
	 (state == env_out_of_cpu) ? "out of cpu time" :
	 (state == env_in_syscall) ? "in a syscall" :
	 "abnormal (empty)",	
	 eid,
	 (iocaps != NULL) ? "has" : "has not",
	 basic_cap,
	 total_cputime);
  return (0);
}

int	do_env_upcalls_dump(void)
{
  predicate_t	prologue;	/** Used before scheduling. (save) */
  predicate_t	epilogue;	/** Used before unscheduling. (restore) */
/*   predicate_t	exceptions[EXCEPTION_MAX_NUM]; /\** Exception handlers. *\/ */

  segment_read4_by_index(KENV_PREDICATE_IDX,
			 (paddr_t)EXAMOUR_ENV_RW_MAPPING_BEGIN,
			 (uint32_t)(&prologue + 1));
  segment_read4_by_index(KENV_PREDICATE_IDX,
			 (paddr_t)(EXAMOUR_ENV_RW_MAPPING_BEGIN + 4),
			 (uint32_t)(&prologue));
  segment_read4_by_index(KENV_PREDICATE_IDX,
			 (paddr_t)EXAMOUR_ENV_RW_MAPPING_BEGIN,
			 (uint32_t)(&epilogue + 1));
  segment_read4_by_index(KENV_PREDICATE_IDX,
			 (paddr_t)(EXAMOUR_ENV_RW_MAPPING_BEGIN + 4),
			 (uint32_t)(&epilogue));

  printf("Environnement upcall informations:\n"
	 "prologue is at %p:%p\n"
	 "epilogue is at %p:%p\n",
	 prologue.cs, prologue.offset,
	 epilogue.cs, epilogue.offset);  
  return (0);
}
