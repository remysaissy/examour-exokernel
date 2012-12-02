##
## This file is part of ExAmour drivers

## Copyright (C) Remy Saissy <remy.saissy@gmail.com>
## ExAmour drivers is free software; you can redistribute it and/or modify
## it under the terms of the GNU General Public License as published by
## the Free Software Foundation; either version 2 of the License, or
## (at your option) any later version.

## ExAmour drivers is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU General Public License for more details.

## You should have received a copy of the GNU General Public License
## along with this program; if not, write to the Free Software
## Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
##

include		../.config

VGA_DRV			=	libvgadrv.a

VESA_DRV		=	libvesadrv.a

KBD_DRV			=	libkbddrv.a

TGFS_DRV		=	libtgfsdrv.a

VFAT_DRV		=	libvfatdrv.a

SLABMM_DRV		=	libslabmmdrv.a

SEGMENTMM_DRV		=	libsegmentmmdrv.a

find_csources   	= $(wildcard $(subdir)/*.c)
find_asmsources 	= $(wildcard $(subdir)/asm/*.S)

vgadrv_csources   	:= $(foreach subdir,video/vga,$(find_csources))
vgadrv_asmsources 	:= $(foreach subdir,video/vga,$(find_asmsources))
vgadrv_cobjs		:= $(vgadrv_csources:.c=.o)
vgadrv_asmobjs		:= $(vgadrv_asmsources:.S=.o)

vesadrv_csources   	:= $(foreach subdir,video/vesa,$(find_csources))
vesadrv_asmsources 	:= $(foreach subdir,video/vesa,$(find_asmsources))
vesadrv_cobjs		:= $(vesadrv_csources:.c=.o)
vesadrv_asmobjs		:= $(vesadrv_asmsources:.S=.o)

kbddrv_csources   	:= $(foreach subdir,input/kbd,$(find_csources))
kbddrv_asmsources 	:= $(foreach subdir,input/kbd,$(find_asmsources))
kbddrv_cobjs		:= $(kbddrv_csources:.c=.o)
kbddrv_asmobjs		:= $(kbddrv_asmsources:.S=.o)

tgfsdrv_csources   	:= $(foreach subdir,fs/tgfs,$(find_csources))
tgfsdrv_asmsources 	:= $(foreach subdir,fs/tgfs,$(find_asmsources))
tgfsdrv_cobjs		:= $(tgfsdrv_csources:.c=.o)
tgfsdrv_asmobjs		:= $(tgfsdrv_asmsources:.S=.o)

vfatdrv_csources   	:= $(foreach subdir,fs/vfat,$(find_csources))
vfatdrv_asmsources 	:= $(foreach subdir,fs/vfat,$(find_asmsources))
vfatdrv_cobjs		:= $(vfatdrv_csources:.c=.o)
vfatdrv_asmobjs		:= $(vfatdrv_asmsources:.S=.o)

slabmmdrv_csources   	:= $(foreach subdir,mm/slab,$(find_csources))
slabmmdrv_asmsources 	:= $(foreach subdir,mm/slab,$(find_asmsources))
slabmmdrv_cobjs		:= $(slabmmdrv_csources:.c=.o)
slabmmdrv_asmobjs	:= $(slabmmdrv_asmsources:.S=.o)

segmentmmdrv_csources   	:= $(foreach subdir,mm/segment,$(find_csources))
segmentmmdrv_asmsources 	:= $(foreach subdir,mm/segment,$(find_asmsources))
segmentmmdrv_cobjs		:= $(segmentmmdrv_csources:.c=.o)
segmentmmdrv_asmobjs		:= $(segmentmmdrv_asmsources:.S=.o)

CFLAGS		+=	-I../examour/include -I../toolkit/libslds/include -I../libos/libc/klibc/include

AR_FLAGS	=	rcs


build: build_$(VGA_DRV) build_$(VESA_DRV) build_$(KBD_DRV) build_$(SEGMENTMM_DRV) #build_$(SLABMM_DRV) build_$(TGFS_DRV)
	@echo	"[Build] All completed."

build_$(VGA_DRV):	$(vgadrv_cobjs) $(vgadrv_asmobjs)
	@$(AR) $(AR_FLAGS) video/vga/$(VGA_DRV) $(vgadrv_cobjs) $(vgadrv_asmobjs)
	@$(RANLIB) video/vga/$(VGA_DRV)
	@echo	"[Build] List completed ($(VGA_DRV))."

build_$(VESA_DRV):	$(vesadrv_cobjs) $(vesadrv_asmobjs)
	@$(AR) $(AR_FLAGS) video/vesa/$(VESA_DRV) $(vesadrv_cobjs) $(vesadrv_asmobjs)
	@$(RANLIB) video/vesa/$(VESA_DRV)
	@echo	"[Build] List completed ($(VESA_DRV))."

build_$(SLABMM_DRV):	$(slabmmdrv_cobjs) $(slabmmdrv_asmobjs)
	@$(AR) $(AR_FLAGS) mm/slab/$(SLABMM_DRV) $(slabmmdrv_cobjs) $(slabmmdrv_asmobjs)
	@$(RANLIB) mm/slab/$(SLABMM_DRV)
	@echo	"[Build] List completed ($(SLABMM_DRV))."

build_$(SEGMENTMM_DRV):	$(segmentmmdrv_cobjs) $(segmentmmdrv_asmobjs)
	@$(AR) $(AR_FLAGS) mm/segment/$(SEGMENTMM_DRV) $(segmentmmdrv_cobjs) $(segmentmmdrv_asmobjs)
	@$(RANLIB) mm/segment/$(SEGMENTMM_DRV)
	@echo	"[Build] List completed ($(SEGMENTMM_DRV))."

build_$(KBD_DRV):	$(kbddrv_cobjs) $(kbddrv_asmobjs)
	@$(AR) $(AR_FLAGS) input/kbd/$(KBD_DRV) $(kbddrv_cobjs) $(kbddrv_asmobjs)
	@$(RANLIB) input/kbd/$(KBD_DRV)
	@echo	"[Build] List completed ($(KBD_DRV))."

build_$(TGFS_DRV):	$(tgfsdrv_cobjs) $(tgfsdrv_asmobjs)
	@$(AR) $(AR_FLAGS) fs/tgfs/$(TGFS_DRV) $(tgfsdrv_cobjs) $(tgfsdrv_asmobjs)
	@$(RANLIB) fs/tgfs/$(TGFS_DRV)
	@echo	"[Build] List completed ($(TGFS_DRV))."

build_$(VFAT_DRV):	$(vfatdrv_cobjs) $(vfatdrv_asmobjs)
	@$(AR) $(AR_FLAGS) fs/vfat/$(VFAT_DRV) $(vfatdrv_cobjs) $(vfatdrv_asmobjs)
	@$(RANLIB) fs/vfat/$(VFAT_DRV)
	@echo	"[Build] List completed ($(VFAT_DRV))."

fclean: fclean_$(VGA_DRV) fclean_$(VESA_DRV) fclean_$(KBD_DRV) fclean_$(TGFS_DRV) fclean_$(VFAT_DRV) fclean_$(SLABMM_DRV) fclean_$(SEGMENTMM_DRV)
	@echo "[Fclean] All competed."

fclean_$(VGA_DRV):
	@rm -f $(vgadrv_cobjs) $(vgadrv_asmobjs) video/vga/$(VGA_DRV)
	@echo "[Fclean] $(VGA_DRV)."

fclean_$(VESA_DRV):
	@rm -f $(vesadrv_cobjs) $(vesadrv_asmobjs) video/vesa/$(VESA_DRV)
	@echo "[Fclean] $(VESA_DRV)."

fclean_$(SLABMM_DRV):
	@rm -f $(slabmmdrv_cobjs) $(slabmmdrv_asmobjs) mm/slab/$(SLABMM_DRV)
	@echo "[Fclean] $(SLABMM_DRV)."

fclean_$(SEGMENTMM_DRV):
	@rm -f $(segmentmmdrv_cobjs) $(segmentmmdrv_asmobjs) mm/segment/$(SEGMENTMM_DRV)
	@echo "[Fclean] $(SEGMENTMM_DRV)."

fclean_$(KBD_DRV):
	@rm -f $(kbddrv_cobjs) $(kbddrv_asmobjs) input/kbd/$(KBD_DRV)
	@echo "[Fclean] $(KBD_DRV)."

fclean_$(TGFS_DRV):
	@rm -f $(tgfsdrv_cobjs) $(tgfsdrv_asmobjs) fs/tgfs/$(TGFS_DRV)
	@echo "[Fclean] $(TGFS_DRV)."

fclean_$(VFAT_DRV):
	@rm -f $(vfatdrv_cobjs) $(vfatdrv_asmobjs) fs/vfat/$(VFAT_DRV)
	@echo "[Fclean] $(VFAT_DRV)."

re: fclean build

%.o: %.c
	@echo "[CC] $<"
	@$(CC) -c -o $@ $< $(CFLAGS)

%.o: %.S
	@echo "[CC] $<"
	@$(CC) -c -o $@ $< $(CFLAGS) -D__ASM__

