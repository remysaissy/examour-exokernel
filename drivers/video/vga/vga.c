/*
 * This file is part of ExAmour

 * Copyright (C) Remy Saissy <remy.saissy@gmail.com>
 * ExAmour is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.

 * ExAmour is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#include	"vga.h"

#include	<stdarg.h>
#include	<examour/core/asm.h>
#include	<examour_api.h>

/* Point to the video memory.  */
static long	pos = 0;
static long	dec = COLUMNS;
static long	y = 0;

static vga_color_t	vga_colors[] =
  {
    {"black",0},
    {"blue", 0x0100},
    {"green", 0x0200},
    {"cyan", 0x0300},
    {"red", 0x0400},
    {"magenta", 0x0500},
    {"brown", 0x0600},
    {"light grey", 0x0700},
    {"dark grey", 0x0800},
    {"light blue", 0x0900},
    {"light green", 0x0a00},
    {"light cyan", 0x0b00},
    {"light red", 0x0c00},
    {"light magenta", 0x0d00},
    {"light brown", 0x0e00},
    {"white/blinking", 0x0f00},
    {NULL, 0}
  };

static int	fg_color = 0x0c00;
static int	bg_color = 0;
static int	vga_selector = 0;

bool		vga_init(void)
{
  vga_selector = ldt_add_entry(NULL,
			       SEGMENT_TYPE_DATA_RW|SEGMENT_PRIV_3|SEGMENT_32BITS,
			       0xb8000,
			       0x80000);
  if (vga_selector == -1)
    return (false);
  return (true);
}

static void	update_cursor(void)
{
  io_send(0x3D4, 14, 1);
  io_send(0x3D5, pos >> 8, 1);
  io_send(0x3D4, 15, 1);
  io_send(0x3D5, pos, 1);
}

void		cls(void)
{
  segment_memset_by_index(vga_selector, 0,
			  bg_color, ROWS * COLUMNS, 2);
  pos = 0;
  dec = COLUMNS;
  y = 0;
  update_cursor();
}

int		set_background_color(char *id)
{
  int		i;
  int		x;
  int		y;
  uint16_t	val;

  for (i = 0; vga_colors[i].id != NULL; i++)
    {
      if (!strcmp(vga_colors[i].id, id))
	{
	  bg_color = vga_colors[i].value;
	  for (y = 0; y < COLUMNS; y++)
	    for (x = 0; x < ROWS; x++)
	      {
		segment_read2_by_index(vga_selector,
				       (y * ROWS + x) * 2,
				       &val);
		val &= 0xfff;
		val |= bg_color;
		segment_write2_by_index(vga_selector,
					(y * ROWS + x) * 2,
					val);
	      }
	  return (1);
	}
    }
  return (0);
}

void		list_bg_colors(void)
{
  int		i;

  puts("Available background colors:\n");
  for (i = 0; vga_colors[i].id != NULL; i++)
    {
      if (vga_colors[i].value == bg_color)
	putchar('*');
      puts(vga_colors[i].id);
      putchar('\n');
    }
}

int		set_foreground_color(char *id)
{
  int		i;

  for (i = 0; vga_colors[i].id != NULL; i++)
    {
      if (!strcmp(vga_colors[i].id, id))
	{
	  fg_color = vga_colors[i].value;
	  return (1);
	}
    }
  return (0);
}

void		list_fg_colors(void)
{
  int		i;

  puts("Available foreground colors:\n");
  for (i = 0; vga_colors[i].id != NULL; i++)
    {
      if (vga_colors[i].value == fg_color)
	putchar('*');
      puts(vga_colors[i].id);
      putchar('\n');
    }
}

/* If you use a pointer increment, it segfaults. */
int		puts(const char *s)
{
  int		cnt;

  cnt = 0;
  while (*s)
    {
      putchar(*s++);
      cnt++;
    }
  return (cnt);
}

static inline void	scroll_screen(void)
{
  int		decal;
  int		b;
  int		e;

  decal = y - ROWS;
  b = decal * COLUMNS;
  e = ROWS * COLUMNS - b;
  segment_memcopy_by_index(vga_selector,
			  0,
			  vga_selector,
			  b * 2,
			  e * 2, 2);
  segment_memset_by_index(vga_selector,
			  e * 2,
			  bg_color,
			  b * 2, 2);
  y -= decal;
  pos = ((y - 1) * COLUMNS);
  dec = COLUMNS;
  update_cursor();
}

/* inline functions to manage special caracters */

static inline void	manage_backspace(void)
{
  pos--;
  dec++;
  segment_write2_by_index(vga_selector,
			  pos * 2,
			  bg_color);
  update_cursor();
}

static inline void	manage_newline(void)
{
  segment_memset_by_index(vga_selector,
			  pos * 2,
			  bg_color,
			  dec, 2);
  y++;
  pos += dec;
  dec = COLUMNS;
  if (y > ROWS)
    scroll_screen();
  update_cursor();
}

static inline void	manage_cariage_return(void)
{
  pos -= (COLUMNS - dec);
  dec = COLUMNS;
  update_cursor();
}

/* a tab is equal to 4 spaces */
static inline void	manage_tabulation(void)
{
  int	i;

  for (i = 0; i < TABULATION_SIZE; i++)
    putchar(' ' | bg_color | fg_color);
}

int			putchar(int c)
{
  if (dec <= 0)
    manage_newline();
  c &= 0xff;
  switch (c)
    {
    case '\n':
      manage_newline();
      break;
    case '\r':
      manage_cariage_return();
      break;
    case '\t':
      manage_tabulation();
      break;
    case '\b':
      manage_backspace();
      break;
    default:
      segment_write2_by_index(vga_selector,
			      pos * 2,
			      c | fg_color | bg_color);
      pos++;
      dec--;
    }
  update_cursor();
  return (1);
}

static const char	base[] = "0123456789abcdef";

void			ltoa(long n, long base_sz)
{
  static int		f = 0;

  if (base_sz < 2 || base_sz > sizeof(base))
    return;
  if (n)
    {
      if (n < 0)
	{
	  putchar('-');
	  n *= -1;
	}
      f = 1;
      ltoa(n/base_sz, base_sz);
      putchar(base[n%base_sz]);
    }
  else
    {
      if (f == 0)
	putchar(base[0]);
      f = 0;
    }
}

void			htoa(short n, long base_sz)
{
  static int f = 0;

  if (base_sz < 2 || base_sz > sizeof(base))
    return;
  if (n)
    {
      if (n < 0)
	{
	  putchar('-');
	  n *= -1;
	}
      f = 1;
      htoa(n/base_sz, base_sz);
      putchar(base[n%base_sz]);
    }
  else
    {
      if (f == 0)
	putchar(base[0]);
      f = 0;
    }
}

int		printf(char *fmt, ...)
{
  int nb = 0;
  va_list	ap;

  va_start(ap, fmt);
  for(; *fmt; fmt++)
    if(*fmt == '%')
      {
	switch(*++fmt)
	  {
	  case 'c':
	    /* char */
	    putchar(va_arg(ap, int));
	    break;
	  case 'd':
	  case 'i':
	    /* decimal int */
	    ltoa(va_arg(ap, int), 10);
	    break;
	  case 'u':
	    /* unsigned int */
	    ltoa(va_arg(ap, int), 10);
	    break;
	  case 'o':
	    /* octal int */
	    ltoa(va_arg(ap, int), 8);
	    break;
	  case 'p':
	  case 'x':
	    /* hexadecimal int */
	    ltoa(va_arg(ap, int), 16);
	    break;
	  case 's':
	    /* string */
	    puts(va_arg(ap, char *));
	    break;
	  case 'l':
	    /* long */
	    switch(*++fmt)
	      {
	      case 'd':
		/* decimal long */
		ltoa(va_arg(ap, long), 10);
		break;
	      case 'u':
		/* unsigned long */
		ltoa(va_arg(ap, long), 10);
		break;
	      case 'o':
		/* octal long */
		ltoa(va_arg(ap, long), 8);
		break;
	      case 'x':
		/* hexadecimal long */
		ltoa(va_arg(ap, long), 16);
		break;
	      }
	    break;
	  case '%':
	    putchar(*fmt);
	    break;
	  default:
	    return -1;
	  }
	nb++;
      } else
      putchar(*fmt);
  va_end(ap);
  return nb;
}


