/*
   This file is part of exAmour

   Copyright (C) Remy Saissy <remy.saissy@epitech.net>
   exAmour is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

   exAmour is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

OUTPUT_FORMAT("elf32-i386", "elf32-i386", "elf32-i386");
OUTPUT_ARCH("i386");
ENTRY(_start);

phys = 0x1400000;  /* 20Mb */

SECTIONS
{
  .text phys : AT(phys)
   {
  	kernel_start = .;   
    code = .;
	LONG(0x1BADB002)
    LONG(0x00000003)
    LONG(-0x1BADB005)
	*(.text)
     . = ALIGN(4096);
   }
  
  .data : AT(phys + (data - code))
   {
     data = .;
     *(.data)
     . = ALIGN(4096); 
   }
  _edata = .;
  
  .bss : AT(phys + (bss - code))
   {
     bss = .;
     *(.bss)
     *(COMMON)
     . = ALIGN(4096); 
   }
  end = .;
  _end = .;
  kernel_end = .;
}
