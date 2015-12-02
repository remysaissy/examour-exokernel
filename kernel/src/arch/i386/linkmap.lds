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

ENTRY(_start)

OUTPUT_FORMAT(elf32-i386)

SECTIONS
{

  /DISCARD/ :
  {
    *(".text.inlined*")
    *(.comment)
    *(.eh_frame)
  }

  . = 0x00007E00; /* Conventional memory. End of kernel is at 0x0007FFFF (480kib max). */

 .text BLOCK(4K) : ALIGN(4K)
 {
   *(.multiboot)
   *(.text)
 }

 .note.gnu.build-id BLOCK(4K) : ALIGN(4K)
 {
  *(.note.gnu.build-id)
 }

 .rodata BLOCK(4K) : ALIGN(4K)
 {
  *(.rodata)
 }

 .data BLOCK(4K) : ALIGN(4K)
 {
  *(.data)
 }

 .bss BLOCK(4K) : ALIGN(4K)
 {
  *(COMMON)
  *(.bss)
  *(.bootstrap_stack)
 }
}
