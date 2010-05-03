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
#include	<examour/core/segment.h>
#include	<examour/mm/ldt.h>

#include	"commands.h"
#include	"mm_ctl.h"

const command_t	const mm_subcommands[] =
  {
    {"help", "?", "Help of the memory subcommands.", NULL, do_mm_help},
    {"alloc", "alloc", "Allocates n bytes of memory.", NULL, do_mm_alloc},
    {"free", "free", "Frees n bytes of memory.", NULL, do_mm_free},
    {"read", "read", "Reads n bytes of memory at a given address.", NULL, do_mm_read},
    {"write", "write", "Writes the given pattern at a given address.", NULL, do_mm_write},
    {"dump", "dump", "Dumps allocated memory segments informations.", NULL, do_mm_dump},
    {NULL, NULL, NULL, NULL}
  };

/* To be moved out. */
int	atoi(const char *s)
{
  bool	neg;
  int	n;

  neg = false;
  n = 0;
  if (s == NULL)
    return (0);
  while (*s)
    {
      if (*s == '-')
	neg = true;
      else
	{
	  if (*s >= '0' && *s <= '9')
	    {
	      n *= 10;
	      n += (*s - '0');
	    }
	  else
	    return (0);
	}
      s++;
    }
  if (neg == true)
    n *= -1;
  return (n);
}

int	do_mm_help(void)
{
  puts("Memory subcommands list:\n");
  list_commands(mm_subcommands);
  return (0);
}

int	do_mm_alloc(void)
{
  size_t size;
  int	index;
  char	*arg;

  size = 0;
  index = -1;
  arg = parse_next_arg();
  if (arg == NULL || !strcmp(arg, "help"))
    {
      puts("Usage: alloc <number of bytes>.\nAllocates a give number of "
	   "bytes as a new memory segment. Returns the index of this segment"
	   " on success, -1 otherwise.\n");
      return (0);
    }
  size = atoi(arg);
  printf("%u bytes allocation requested...\n", size);
  index = ldt_add_entry(NULL,
			SEGMENT_PRIV_3|SEGMENT_TYPE_DATA_RW|SEGMENT_32BITS,
			PADDR_ERROR,
			size);
  if (index == -1)
    puts("Allocation failed.\n");
  else
    printf("Allocation succeeded. Segment index is %d.\n", index);
  return (0);
}

int	do_mm_free(void)
{
  char	*arg;
  int	index;

  index = -1;
  arg = parse_next_arg();
  if (arg == NULL || !strcmp(arg, "help"))
    {
      puts("Usage: free <segment index>.\nFrees a memory segment according "
	   "to its index.\n");
      return (0);
    }
  index = atoi(arg);
  if (ldt_remove_entry(NULL, index) == false)
    puts("Failed to free the memory segment.\n");
  else
    puts("Memory segment successfully freed.\n");
  return (0);
}

int		do_mm_read(void)
{
  char		*arg1;
  char		*arg2;
  char		*arg3;
  int		index;
  paddr_t	offset;
  size_t	number_of_bytes;
  uint32_t	result;

  arg1 = parse_next_arg();
  arg2 = parse_next_arg();
  arg3 = parse_next_arg();
  if (arg1 == NULL || arg2 == NULL || arg3 == NULL)
    {
      puts("Usage: read <selector index> <offset> <number of bytes>\n");
      return (0);
    }
  index = atoi(arg1);
  offset = atoi(arg2);
  number_of_bytes = atoi(arg3);
  result = 0;
  switch (number_of_bytes)
    {
    case 1:
      segment_read1_by_index(index, offset, (uint8_t *)&result);
      break;
    case 2:     
      segment_read2_by_index(index, offset, (uint16_t *)&result);
      break;
    case 4:
      segment_read4_by_index(index, offset, (uint32_t *)&result);
      break;
    default:
      puts("Error, the number of bytes must be either 1,2 or 4.\n");
      return (0);
    }
  printf("Read value is: %d\n", result);
  return (0);
}

int	do_mm_write(void)
{
  char		*arg1;
  char		*arg2;
  char		*arg3;
  char		*arg4;
  int		index;
  paddr_t	offset;
  size_t	number_of_bytes;
  uint32_t	value;

  arg1 = parse_next_arg();
  arg2 = parse_next_arg();
  arg3 = parse_next_arg();
  arg4 = parse_next_arg();
  if (arg1 == NULL || arg2 == NULL || arg3 == NULL || arg4 == NULL)
    {
      puts("Usage: write <selector index> <offset> <size> <value>\n");
      return (0);
    }
  index = atoi(arg1);
  offset = atoi(arg2);
  number_of_bytes = atoi(arg3);
  value = atoi(arg4);
  switch (number_of_bytes)
    {
    case 1:
      segment_write1_by_index(index, offset, value);
      break;
    case 2:
      segment_write2_by_index(index, offset, value);
      break;
    case 4:
      segment_write4_by_index(index, offset, value);
      break;
    default:
      puts("Error, size must be either 1,2 or 4.\n");
      return (0);
    }
  printf("Value %u wrote.\n", value);
  return (0);
}

int	do_mm_dump(void)
{
  ldtr_t	ldtr;
  ldt_t		ldt;
  int		i;

  __asm__ volatile ("sldt %0": "=mr" (ldtr));
  printf("ldtr's limit is: %p. Base address is %p.\n",
	 ldtr.limit, ldtr.base_addr);
  for (i = 0; i < (ldtr.limit + 1) / 8; i++)
    {
      segment_read4_by_index(LDT_ENTRY_IDX,
			     (paddr_t)(i * sizeof(ldt)),
			     (uint32_t *)&ldt);
      segment_read4_by_index(LDT_ENTRY_IDX,
			     (paddr_t)(i * sizeof(ldt)) + sizeof(ldt)/2,
			     (uint32_t *)&ldt + 1);
      printf("[LDT]%d(%p) present: %s base_addr: %p limit: %d "
	     "privilege level: %d type: %p\n", i,
	     (i << 3) | 0x7,
	     (get_segment_present(ldt) == 0) ? "false" : "true",
	     get_segment_base_address(ldt),
	     get_segment_limit(ldt), get_segment_dpl(ldt),
	     get_segment_type(ldt));      
    }
  puts("End of dump.\n");
  return (0);
}
