##
## This file is part of examour

## Copyright (C) Remy Saissy <remy.saissy@epitech.net>
## examour is free software; you can redistribute it and/or modify
## it under the terms of the GNU General Public License as published by
## the Free Software Foundation; either version 2 of the License, or
## (at your option) any later version.

## examour is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU General Public License for more details.

## You should have received a copy of the GNU General Public License
## along with this program; if not, write to the Free Software
## Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
##

include		../../../.config

OUTPUT	:=	kernel_image

find_csources   = $(wildcard $(subdir)/*.c)
find_asmsources = $(wildcard $(subdir)/asm/*.S)

# Core subsystem sources
corecsources	:= $(foreach subdir,core/$(CORE),$(find_csources))
coreasmsources	:= $(foreach subdir,core/$(CORE),$(find_asmsources))
corecobjs	:= $(corecsources:.c=.o)
coreasmobjs	:= $(coreasmsources:.S=.o)

# Env subsystem sources
envcsources	:= $(foreach subdir,env/$(ENV),$(find_csources))
envasmsources	:= $(foreach subdir,env/$(ENV),$(find_asmsources))
envcobjs	:= $(envcsources:.c=.o)
envasmobjs	:= $(envasmsources:.S=.o)

# Event subsystem sources
eventcsources   := $(foreach subdir,event/$(EVENT),$(find_csources))
eventasmsources := $(foreach subdir,event/$(EVENT),$(find_asmsources))
eventcobjs	:= $(eventcsources:.c=.o)
eventasmobjs	:= $(eventasmsources:.S=.o)

# Mm subsystem sources
mmcsources	:= $(foreach subdir,mm/$(MM),$(find_csources))
mmasmsources	:= $(foreach subdir,mm/$(MM),$(find_asmsources))
mmcobjs		:= $(mmcsources:.c=.o)
mmasmobjs	:= $(mmasmsources:.S=.o)

# Support subsystem sources
supportcsources		:= $(foreach subdir,support/$(SUPPORT),$(find_csources))
supportasmsources	:= $(foreach subdir,support/$(SUPPORT),$(find_asmsources))
supportcobjs		:= $(supportcsources:.c=.o)
supportasmobjs		:= $(supportasmsources:.S=.o)

# Security subsystem sources
securitycsources	:= $(foreach subdir,security/$(SECURITY),$(find_csources))
securityasmsources	:= $(foreach subdir,security/$(SECURITY),$(find_asmsources))
securitycobjs		:= $(securitycsources:.c=.o)
securityasmobjs		:= $(securityasmsources:.S=.o)

# External libraries.
LIBS	=	../../../toolkit/libslds/libslds.a

CFLAGS	+=	-I./ -I../../include

# The linking script is located in the mm library.
LDFLAGS	+=	-T mm/$(MM)/kernel.lds #--strip-all

install: links $(OUTPUT)
	@echo "[MK] $(OUTPUT) built."

%.o: %.c
	@echo "[CC] $<"
	@$(CC) -c -o $@ $< $(CFLAGS)

%.o: %.S
	@echo "[CC] $<"
	@$(CC) -c -o $@ $< $(CFLAGS) -D__ASM__

$(OUTPUT): $(corecobjs) $(coreasmobjs) $(ENV).a $(EVENT).a $(MM).a $(SUPPORT).a $(SECURITY).a
	@$(LD) -o $(OUTPUT) $(LDFLAGS) $(coreasmobjs) $(corecobjs) $(ENV).a $(EVENT).a $(MM).a $(SUPPORT).a $(SECURITY).a $(LIBS)
	@echo "[LD] $(OUTPUT)"

$(CORE).a: $(corecobjs) $(coreasmobjs)
	@echo "[AR] $(CORE).a"
	@ar rcs $(CORE).a $(corecobjs) $(coreasmobjs)

$(SECURITY).a: $(securitycobjs) $(securityasmobjs)
	@echo "[AR] $(SECURITY).a"
	@ar rcs $(SECURITY).a $(securitycobjs) $(securityasmobjs)

$(ENV).a: $(envcobjs) $(envasmobjs)
	@echo "[AR] $(ENV).a"
	@ar rcs $(ENV).a $(envcobjs) $(envasmobjs)

$(EVENT).a: $(eventcobjs) $(eventasmobjs)
	@echo "[AR] $(EVENT).a"
	@ar rcs $(EVENT).a $(eventcobjs) $(eventasmobjs)

$(MM).a: $(mmcobjs) $(mmasmobjs)
	@echo "[AR] $(MM).a"
	@ar rcs $(MM).a $(mmcobjs) $(mmasmobjs)

$(SUPPORT).a: $(supportcobjs) $(supportasmobjs)
	@echo "[AR] $(SUPPORT).a"
	@ar rcs $(SUPPORT).a $(supportcobjs) $(supportasmobjs)

$(SECURITY).a: $(securitycobjs) $(securityasmobjs)
	@echo "[AR] $(SECURITY).a"
	@ar rcs $(SECURITY).a $(securitycobjs) $(securityasmobjs)

clean:
	@echo "[RM] $(corecobjs) $(coreasmobjs) $(envcobjs) $(envasmobjs) $(eventcobjs) $(eventasmobjs) $(eventcobjs) $(mmasmobjs) $(mmcobjs) $(supportasmobjs) $(supportcobjs) $(securityasmobjs) $(securitycobjs) $(CORE).a $(ENV).a $(EVENT).a $(MM).a $(SUPPORT).a $(SECURITY).a"
	@rm -f  $(corecobjs) $(coreasmobjs) $(envcobjs) $(envasmobjs) $(eventcobjs) $(eventasmobjs) $(eventcobjs) $(mmasmobjs) $(mmcobjs) $(supportasmobjs) $(supportcobjs) $(securityasmobjs) $(securitycobjs) $(SUPPORT).a $(SECURITY).a $(CORE).a $(ENV).a $(EVENT).a $(MM).a *~ \#*

fclean: clean
	@echo "[RM] $(OUTPUT)"
	@rm -f $(OUTPUT)

re: fclean install

links:
	@rm -f examour/core examour/event examour/security examour/env examour/mm examour/support
	@ln -s ../core/$(CORE)/include examour/core
	@ln -s ../event/$(EVENT)/include examour/event
	@ln -s ../security/$(SECURITY)/include examour/security
	@ln -s ../env/$(ENV)/include examour/env
	@ln -s ../mm/$(MM)/include examour/mm
	@ln -s ../support/$(SUPPORT)/include examour/support
