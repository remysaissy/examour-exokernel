/*
** This file is part of ExAmour

** Copyright (C) Remy Saissy <remy.saissy@gmail.com>
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

#include     <string.h>
#include    "../debugging/log.h"

#include    <exaboot.h>
#include    <exabus.h>
#include    <examem.h>
#include    <exaevent.h>
#include    <exaprocess.h>

#define __NOT_ASM__
#include    "include/multiboot.h"

/** The exaboot instance. Used to pass information along to modules. */
static exaboot_t sgl_exaboot;

/**
 * Start address of the kernel. Symbol defined in the ld script.
 */
int	kernel_start;

/**
 * End address of the kernel. Symbol defined in the ld script.
 */
int	kernel_end;

/* TODO: set the code to be MP startup. */
/*TODO: Remove any call to print of data. */
void examain(unsigned long magic, multiboot_info_t *mbi)
  {
    module_t *mod;

    if (magic != MULTIBOOT_BOOTLOADER_MAGIC)
      {
        panic("Error, multiboot magic number invalid.\n");
        return;
      }
    /* if (!MULTIBOOT_CHECK_FLAG(mbi->flags, MULTIBOOT_MMAP))
     return; *//* Panic: not memory map provided. */
    /*TODO: Init process check is currently disabled.*/
    /*    if (mbi->mods_count == 0) */
    /*      return; *//* Ptanic: init not provided. */

    mod                     =   (module_t *)mbi->mods_addr;
    sgl_exaboot.init_start  =   mod->mod_start;
    sgl_exaboot.init_end    =   mod->mod_end;
    sgl_exaboot.kernel_start  =   (typeof(sgl_exaboot.kernel_start))&kernel_start;
    sgl_exaboot.kernel_end    =   (typeof(sgl_exaboot.kernel_end))&kernel_end;
    /* structures are the same, map it into the module provided informations. */
    sgl_exaboot.n_exa_mmap  =   mbi->mmap_length;
    sgl_exaboot.exa_mmap    =   (exa_mmap_t *)mbi->mmap_addr;
    cls();
    message("Welcome on ExAmour 0.2.\n");
    // Init in the following order:
    // - exabus
    // - examem
    // - exaevent
    // - exaprocess

    if (_exabus_init((void *)&sgl_exaboot)== false)
      {
        panic("Error in exabus initialization.\n");
        return;
      }
    if (_examem_init((void *)&sgl_exaboot)== false)
      {
        panic("Error in examem initialization.\n");
        return;
      }
    if (_exaevent_init((void *)&sgl_exaboot)== false)
      {
        panic("Error in exaevent initialization.\n");
        return;
      }
//    if (_exaprocess_init((void *)&sgl_exaboot)== false)
//      {
//        panic("Error in exaprocess initialization.\n");
//        return;
//      }
    /* idle loop. */
    while (1)
      ;
  }
