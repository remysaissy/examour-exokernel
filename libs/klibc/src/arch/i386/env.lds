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

OUTPUT_FORMAT("binary")
OUTPUT_ARCH("i386")
ENTRY(_start)

SECTIONS
 {
  . = 0;

  .text :
   {
    start = .;
    _start = .;
    __start = .;
    *(.text*)
    etext = .;
   }


  .data SIZEOF(.text) + ADDR(.text) :
   {
    *(.data*)
    edata = .;
   }


  .rodata SIZEOF(.data) + ADDR(.data) :
   {
    *(.rodata*)
    erodata = .;
   }

  .bss SIZEOF(.rodata) + ADDR(.rodata) :
  {
    *(.bss*)
    ebss = .;
  }

  /DISCARD/ :
  {
    *(.note*)
    *(.indent)
    *(.comment)
    *(.stab)
    *(.stabstr)
   }
 }
