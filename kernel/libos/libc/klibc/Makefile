##
## This file is part of ExAmour's klibc

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

include		../../../.config

ARCH			=	arch/i386

OUTPUT			=	libc.a

find_csources   	= $(wildcard $(subdir)/*.c)
find_asmsources 	= $(wildcard $(subdir)/*.S)

csources   	+= $(foreach subdir,./,$(find_csources))
csources   	+= $(foreach subdir,ctype,$(find_csources))
csources   	+= $(foreach subdir,zlib,$(find_csources))
asmsources 	:= $(foreach subdir,$(ARCH),$(find_asmsources))

cobjs		:= $(csources:.c=.o)
asmobjs		:= $(asmsources:.S=.o)

CFLAGS		+=	-Iinclude -Iinclude/bits32 -D__KLIBC__ -I../../../examour/include

AR_FLAGS	=	rcs

build: build_$(OUTPUT)
	@echo	"[Build] $(OUTPUT) completed."

build_$(OUTPUT):	$(cobjs) $(asmobjs)
	@$(AR) $(AR_FLAGS) $(OUTPUT) $(cobjs) $(asmobjs)
	@echo	"[Build] List completed ($(OUTPUT))."

fclean: fclean_$(OUTPUT)
	@echo "[Fclean] All completed."

fclean_$(OUTPUT):
	@rm -f $(cobjs) $(asmobjs) $(OUTPUT)
	@echo "[Fclean] $(cobjs) $(asmobjs) $(OUTPUT)."

re: fclean build

%.o: %.c
	@echo "[CC] $<"
	@$(CC) -c -o $@ $< $(CFLAGS)

%.o: %.S
	@echo "[CC] $<"
	@$(CC) -c -o $@ $< $(CFLAGS) -D__ASM__

