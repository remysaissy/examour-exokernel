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

/* exAmour's support routines */

#include	"debugging.h"
#include	<string.h>
#include    <sys/io.h>

/* Point to the video memory.  */
static volatile unsigned short *video = (unsigned short *)(VGA_COLOR);
static long	pos = 0;
static long	dec = COLUMNS;
static long	y = 0;

void			cls(void)
{
  memset((void *)video, 0, ROWS * COLUMNS * sizeof(*video));
  pos = 0;
  dec = COLUMNS;
  y = 0;
}

/* If you use a pointer increment, it segfaults. */
void			kputstr(const char *s)
{
  while (*s)
    kputchar(*s++);
}

static inline void	scroll_screen(void)
{
  int		decal;
  int		b;
  int		e;

  decal = y - ROWS;
  b = decal * COLUMNS;
  e = ROWS * COLUMNS - b;
  memcpy((void *)video,
	 (void *)(video + b),
	 e * sizeof(*video));
  memset((void *)(video + e), 0,
	 b * sizeof(*video));
  y -= decal;
  pos = ((y-1) * COLUMNS);
  dec = COLUMNS;
}

/* inline functions to manage special caracters */

static inline void	manage_newline(void)
{
  y++;
  pos += dec;
  dec = COLUMNS;
  if (y > ROWS)
    scroll_screen();
}

static inline void	manage_cariage_return(void)
{
  pos -= (COLUMNS - dec);
  dec = COLUMNS;
}

/* a tab is equal to 4 spaces */
static inline void	manage_tabulation(void)
{
  /* put the spaces */
  memset((void *)(video + pos), 0, 4 * sizeof(*video));
  if (dec - 4 < 0)
    {
      int	temp;

      temp = 4 - dec;
      manage_newline();
      dec -= temp;
      pos += temp;
    }
}

/* TODO: rewrite this function to manage scrolling */
void			kputchar(long c)
{
  video[pos] = 0;
  if (dec <= 0)
    manage_newline();
  switch ((char)c)
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
    default:
      video[pos++] = ((c & 0xff)| ATTRIBUTE);
      dec--;
    }
  /* move the cursor. */
  outb(0xf, 0x3d4);
  outb((COLUMNS - dec), 0x3d5);
  outb(0xe, 0x3d4);
  outb(-3, 0x3d5);
  video[pos] |= 0x8000;
}

void			kltoa(unsigned long n, long base_sz)
{
  static const char	*base =
      "0123456789abcdef";

  if (n)
    {
      kltoa(n/base_sz, base_sz);
	  kputchar(base[n%base_sz]);
    }
  else
    {
  	  kputchar(base[0]);
    }
}

void			khtoa(unsigned short n, long base_sz)
{
  static const char	*base =
      "0123456789abcdef";

  if (n)
    {
      khtoa(n/base_sz, base_sz);
	  kputchar(base[n%base_sz]);
    }
  else
    {
        kputchar(base[0]);
    }
}

int		kvprintf(const char *fmt, va_list ap)
{
  char		*s;
  long		c;
  int		val;

  while (*fmt)
    {
      switch (*fmt)
	{
	case '%':
	  fmt++;
	  switch (*fmt)
	    {
	    case 'p':
	      kputstr("0x");
	    case 'x':
	      kltoa(va_arg(ap, unsigned long), 16);
	      break;
	    case 'P':
	      kputstr("0x");
	    case 'X':
	      val = va_arg(ap, unsigned long);
	      kltoa(va_arg(ap, unsigned long), 16);
	      kltoa(val, 16);
	      break;
	    case 'h':
	      khtoa(va_arg(ap, unsigned long) & 0xffff, 10);
	      break;
	    case 'H':
	      khtoa(va_arg(ap, unsigned long) & 0xffff, 16);
	      break;
	    case 'd':
	    case 'u':
	    case 'i':
	      kltoa(va_arg(ap, unsigned long), 10);
	      break;
	    case 'o':
	      kputchar('0');
	      kltoa(va_arg(ap, unsigned long), 8);
	      break;
	    case 'b':
	      val = va_arg(ap, unsigned long);
	      if (val)
		kputstr("true");
	      else
		kputstr("false");
	      break;
	    case 'c':
	      c = va_arg(ap, unsigned long) & 0xff;
	      kputchar(c);
	    case 's':
	      s = va_arg(ap, char *);
	      if (s == NULL)
		kputstr("(null)");
	      else
		kputstr(s);
	      break;
	    default:
	      kputchar(*fmt);
	    }
	  fmt++;
	  break;
	default:
	  kputchar(*fmt++);
	}
    }
  return (0);
}

int			kprintf(const char *fmt, ...)
{
  va_list	ap;

  va_start(ap, fmt);
  kvprintf(fmt, ap);
  va_end(ap);
  return (0);
}
