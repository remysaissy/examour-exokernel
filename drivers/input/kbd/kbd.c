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

#include	<string.h>
#include	"kbd.h"
#include	"../../video/vga/vga.h"

char		kbd_buf[KBD_INPUT_BUFFER_SIZE] = {0, };
uint32_t	kbd_off = 0;

char		kbd_ubuf[KBD_INPUT_BUFFER_SIZE] = {0, };
int		kbd_usize = 0;

static const char	*us_locase_keymap[] =
  {
    0,
    "0",
    "1",
    "2",
    "3",
    "4",
    "5",
    "6",
    "7",
    "8",
    "9",
    "0",
    "-",
    "=",
    "\b",
    "\t",
    "q",
    "w",
    "e",
    "r",
    "t","y","u","i","o","p","[","]","\n",0,"a","s","d","f","g","h","j","k","l",
    ";","`",0,0,"\\","z","x","c","v","b","n","m",",",".","/",
    0,"-",0," ",0,0,0,0,0,0,0,0,0,0,0,0,0,"7","8","9","-","4","5","6","+",
    "1","2","3","0",".",0,0,0,0,0,0,0,0,0,0,0,0,"\n",0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
  };

static const char	*us_upcase_keymap[] =
  {
    0,
    "0",
    "!",
    "@",
    "#",
    "$","%","^","&","*","(",")","_","+","\b",0,"Q","W","E","R","T","Y","U","I",
    "O","P","{","}","\n",0,"A","S","D","F","G","H","J","K","L",":","\"","~",0,
    "|","Z","X","C","V","B","N","M","<",">","?",0,"*",0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"\n",0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
  };				/* 0x0 - 0x53 */


static const char       *fr_locase_keymap[] =
  {
  /* 0 */ 0,
  /* 1 */ "\e",
  /* 2 */ "&",
  /* 3 */ "é",
  /* 4 */ "\"",
  /* 5 */ "'",
  /* 6 */ "(",
  /* 7 */ "-",
  /* 8 */ "è",
  /* 9 */ "_",
  /* 10 */ "ç",
  /* 11 */ "à",
  /* 12 */ ")",
  /* 13 */ "=",
  /* 14 */ "\b", /* Backspace */
  /* 15 */ "\t", /* Tab */
  /* 16 */ "a",
  /* 17 */ "z",
  /* 18 */ "e",
  /* 19 */ "r",
  /* 20 */ "t",
  /* 21 */ "y",
  /* 22 */ "u",
  /* 23 */ "i",
  /* 24 */ "o",
  /* 25 */ "p",
  /* 26 */ "^",
  /* 27 */ "$",
  /* 28 */ "\n",
  /* 29 */ 0, /* left control */
  /* 30 */ "q",
  /* 31 */ "s",
  /* 32 */ "d",
  /* 33 */ "f",
  /* 34 */ "g",
  /* 35 */ "h",
  /* 36 */ "j",
  /* 37 */ "k",
  /* 38 */ "l",
  /* 39 */ "m",
  /* 40 */ "ù",
  /* 41 */ 0,
  /* 42 */ 0, /* left shift */
  /* 43 */ "*",
  /* 44 */ "w",
  /* 45 */ "x",
  /* 46 */ "c",
  /* 47 */ "v",
  /* 48 */ "b",
  /* 49 */ "n",
  /* 50 */ ",",
  /* 51 */ ";",
  /* 52 */ ":",
  /* 53 */ "!",
  /* 54 */ 0,
  /* 55 */ 0,
  /* 56 */ 0,
  /* 57 */ " ",
  /* 58 */ 0,
  /* 59 */ 0,   /* F1 */
  /* 60 */ 0,   /* F2 */
  /* 61 */ 0,   /* F3 */
  /* 62 */ 0,   /* F4 */
  /* 63 */ 0, /* F5 */
  /* 64 */ 0, /* F6 */
  /* 65 */ 0, /* F7 */
  /* 66 */ 0, /* F8 */
  /* 67 */ 0, /* F9 */
  /* 68 */ 0, /* F10 */
  /* 69 */ 0,
  /* 70 */ 0,
  /* 71 */ 0,
  /* 72 */ 0,
  /* 73 */ 0,
  /* 74 */ 0,
  /* 75 */ 0,
  /* 76 */ 0,
  /* 77 */ 0,
  /* 78 */ 0,
  /* 79 */ 0,
  /* 80 */ 0,
  /* 81 */ 0,
  /* 82 */ 0,
  /* 83 */ 0,
  /* 84 */ 0,
  /* 85 */ 0,
  /* 86 */ "<",
  /* 87 */ 0, /* F11 */
  /* 88 */ 0, /* F12 */
  /* 89 */ 0,
  /* 90 */ 0,
  /* 91 */ 0,
  /* 92 */ 0,
  /* 93 */ 0,
  /* 94 */ 0,
  /* 95 */ 0,
  /* 96 */ 0,
  /* 97 */ 0,
  /* 98 */ 0,
  /* 99 */ 0,
  /* 100 */ 0,
  /* 101 */ 0,
  /* 102 */ 0,
  /* 103 */ 0,
  /* 104 */ 0,
  /* 105 */ 0,
  /* 106 */ 0,
  /* 107 */ 0,
  /* 108 */ 0,
  /* 109 */ 0,
  /* 110 */ 0,
  /* 111 */ 0,
  /* 112 */ 0,
  /* 113 */ 0,
  /* 114 */ 0,
  /* 115 */ 0,
  /* 116 */ 0,
  /* 117 */ 0,
  /* 118 */ 0,
  /* 119 */ 0,
  /* 120 */ 0,
  /* 121 */ 0,
  /* 122 */ 0,
  /* 123 */ 0,
  /* 124 */ 0,
  /* 125 */ 0,
  /* 126 */ 0,
  /* 127 */ 0
  };				/* 0x0 - 0x53 */


static const char	*fr_upcase_keymap[] =
  {
    /* 0 */ 0,
  /* 1 */ "\e",
  /* 2 */ "1",
  /* 3 */ "2",
  /* 4 */ "3",
  /* 5 */ "4",
  /* 6 */ "5",
  /* 7 */ "6",
  /* 8 */ "7",
  /* 9 */ "8",
  /* 10 */ "9",
  /* 11 */ "0",
  /* 12 */ "°",
  /* 13 */ "+",
  /* 14 */ "\b",   /* Shift-Backspace */
  /* 15 */ "\e[Z", /* Shift-Tab */
  /* 16 */ "A",
  /* 17 */ "Z",
  /* 18 */ "E",
  /* 19 */ "R",
  /* 20 */ "T",
  /* 21 */ "Y",
  /* 22 */ "U",
  /* 23 */ "I",
  /* 24 */ "O",
  /* 25 */ "P",
  /* 26 */ "\"",
  /* 27 */ "£",
  /* 28 */ "\n",
  /* 29 */ 0, /* left control */
  /* 30 */ "Q",
  /* 31 */ "S",
  /* 32 */ "D",
  /* 33 */ "F",
  /* 34 */ "G",
  /* 35 */ "H",
  /* 36 */ "J",
  /* 37 */ "K",
  /* 38 */ "L",
  /* 39 */ "M",
  /* 40 */ "%",
  /* 41 */ 0,
  /* 42 */ 0,
  /* 43 */ "µ",
  /* 44 */ "W",
  /* 45 */ "X",
  /* 46 */ "C",
  /* 47 */ "V",
  /* 48 */ "B",
  /* 49 */ "N",
  /* 50 */ "?",
  /* 51 */ ".",
  /* 52 */ "/",
  /* 53 */ "§",
  /* 54 */ 0,
  /* 55 */ 0,
  /* 56 */ 0,
  /* 57 */ 0,
  /* 58 */ 0,
  /* 59 */ 0,    /* Shift-F1 */
  /* 60 */ 0,     /* Shift-F2 */
  /* 61 */ 0,     /* Shift-F3 */
  /* 62 */ 0,     /* Shift-F4 */
  /* 63 */ 0, /* Shift-F5 */
  /* 64 */ 0, /* Shift-F6 */
  /* 65 */ 0, /* Shift-F7 */
  /* 66 */ 0, /* Shift-F8 */
  /* 67 */ 0, /* Shift-F9 */
  /* 68 */ 0, /* Shift-F10 */
  /* 69 */ 0,
  /* 70 */ 0,
  /* 71 */ 0,
  /* 72 */ 0,
  /* 73 */ 0,
  /* 74 */ 0,
  /* 75 */ 0,
  /* 76 */ 0,
  /* 77 */ 0,
  /* 78 */ 0,
  /* 79 */ 0,
  /* 80 */ 0,
  /* 81 */ 0,
  /* 82 */ 0,
  /* 83 */ 0,
  /* 84 */ 0,
  /* 85 */ 0,
  /* 86 */ ">",
  /* 87 */ 0, /* Shift-F11 */
  /* 88 */ 0, /* Shift-F12 */
  /* 89 */ 0,
  /* 90 */ 0,
  /* 91 */ 0,
  /* 92 */ 0,
  /* 93 */ 0,
  /* 94 */ 0,
  /* 95 */ 0,
  /* 96 */ 0,
  /* 97 */ 0,
  /* 98 */ 0,
  /* 99 */ 0,
  /* 100 */ 0,
  /* 101 */ 0,
  /* 102 */ 0,
  /* 103 */ 0,
  /* 104 */ 0,
  /* 105 */ 0,
  /* 106 */ 0,
  /* 107 */ 0,
  /* 108 */ 0,
  /* 109 */ 0,
  /* 110 */ 0,
  /* 111 */ 0,
  /* 112 */ 0,
  /* 113 */ 0,
  /* 114 */ 0,
  /* 115 */ 0,
  /* 116 */ 0,
  /* 117 */ 0,
  /* 118 */ 0,
  /* 119 */ 0,
  /* 120 */ 0,
  /* 121 */ 0,
  /* 122 */ 0,
  /* 123 */ 0,
  /* 124 */ 0,
  /* 125 */ 0,
  /* 126 */ 0,
  /* 127 */ 0
  };				/* 0x0 - 0x53 */


static const kbd_map_table_t	kbd_map_table[] =
  {
    {"us", "US keyboard (QWERTY)", us_locase_keymap, us_upcase_keymap},
    {"fr","FR keyboard (AZERTY)", fr_locase_keymap, fr_upcase_keymap},
    {NULL, NULL, NULL, NULL}
  };


static const char	**locase_map = us_locase_keymap;
static const char	**upcase_map = us_upcase_keymap;


int	kbd_set_kbd_map(const char *id)
{
  int	i;

  for (i = 0; i < sizeof(kbd_map_table)/sizeof(kbd_map_table[0]); i++)
    {
      if (!strcmp(kbd_map_table[i].id, id))
	{
	  locase_map = kbd_map_table[i].locase;
	  upcase_map = kbd_map_table[i].upcase;
	  return (1);
	}
    }
  return (0);
}

void	kbd_list_keymap(void)
{
  int	i;

  puts("Available keymaps:\n");
  for (i = 0; kbd_map_table[i].id != NULL; i++)
    {
      if (kbd_map_table[i].locase == locase_map)
	putchar('*');
      puts(kbd_map_table[i].id);
      puts(":\t");
      puts(kbd_map_table[i].desc);
      putchar('\n');
    }
}


int	kbd_read(char *buf, size_t size)
{
  int	cnt;

  if (buf == NULL || size == 0)
    return (-1);
  if (kbd_usize <= 0)
    return (0);
  cnt = (kbd_usize <= size) ? kbd_usize : size;
  memcpy(buf, kbd_ubuf, cnt);
  buf[cnt] = '\0';
  kbd_usize = 0;
  return (cnt);
}

#define	UPCASE_MODE	0x1
#define	KEY_PRESSED	0x2

#define	IS_RELEASED(code)	(code & 0x80)
#define	GET_SCANCODE(code)	(code & 0x7f)

#define	IS_UPCASE(flag)		(flag & UPCASE_MODE)
#define	IS_KEYPRESS(flag)	(flag & KEY_PRESSED)

void	kbd_add_char(int code)
{
  static int		flags = 0;
  static int		last_char_length = 0;
  int			kbd_ready = 0;
  int			scancode;

  if (kbd_off < sizeof(kbd_buf))
    {
      scancode = GET_SCANCODE(code);
      if (IS_RELEASED(code))
	flags &= ~KEY_PRESSED;
      else
	flags |= KEY_PRESSED;

      switch (scancode)
	{
	  /* Check for left and right maj keys. */
	case 0x36:
	case 0x2a:
	  if (IS_RELEASED(code))
	    flags &= ~UPCASE_MODE;
	  else
	    flags |= UPCASE_MODE;
	  break;
	default:
	  if (IS_UPCASE(flags))
	    {
	      if (!IS_KEYPRESS(flags))
		{
		  if (upcase_map[scancode] != NULL)
		    {
		      if (upcase_map[scancode][0] == '\b')
			kbd_off -= last_char_length;
		      else
			{
			  last_char_length = strlen(upcase_map[scancode]);
			  memcpy(kbd_buf + kbd_off,
				 upcase_map[scancode],
				 last_char_length);
			  kbd_off += last_char_length;
			}
		      if (last_char_length)
			puts(upcase_map[scancode]);
		    }
		  else
		    puts("Unknow escape code!");
		}
	    }
	  else
	    {
	      if (!IS_KEYPRESS(flags))
		{
		  if (locase_map[scancode] != NULL)
		    {
		      if (locase_map[scancode][0] == '\b')
			kbd_off -= last_char_length;
		      else
			{
			  last_char_length = strlen(locase_map[scancode]);
			  memcpy(kbd_buf + kbd_off,
				 locase_map[scancode],
				 last_char_length);
			  kbd_off += last_char_length;
			}
		      if (last_char_length)
			puts(locase_map[scancode]);
		    }
		  else
		    puts("Unknow escape code!");
		}
	    }
	}
    }
  if (kbd_off == sizeof(kbd_buf) || kbd_buf[kbd_off - 1] == '\n')
    kbd_ready = 1;
  if (kbd_ready == 1)
    {
      memcpy(kbd_ubuf, kbd_buf, kbd_off);
      kbd_usize = kbd_off;
      kbd_ubuf[kbd_usize] = '\0';
      kbd_off = 0;
    }
}
