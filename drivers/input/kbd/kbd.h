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

#ifndef	__KBD_H__
#define	__KBD_H__

/**
 * \brief	The size in bytes of the keyboard input buffer.
 */
#define	KBD_INPUT_BUFFER_SIZE	255

#ifndef	__ASM__

#include	<stdint.h>


typedef struct	kbd_map_table_s
{
  const char	*id;
  const char	*desc;
  const	char	**locase;
  const char	**upcase;

}		kbd_map_table_t;

/**
 * \brief	Initialize the keyboard driver.
 */
void	kbd_init(void);


/**
 * \brief	List available keymaps.
 */
void	kbd_list_keymap(void);

/**
 * \param id	Id of the the new map table.
 * \return	0 on failure, non zero value otherwise.
 * \brief	Change the translation table.
 */
int	kbd_set_kbd_map(const char *id);

/**
 * \param buf	Buffer to be filled.
 * \param size	The size in bytes of the buffer.
 * \return	Number of bytes filled in buf.
 * \brief	Get the last size characters typed.
 */
int	kbd_read(char *buf, size_t size);

/* /\** */
/*  * *\param c	Character to be added. */
/*  * \brief	Add a character in the buffer. */
/*  *\/ */
/* void	kbd_add_char(int c); */

#endif /* __ASM__ */

#endif /* __KBD_H__ */
