
include ../../.config

OUTPUT	:=	eash

OBJS	=	asm/upcalls.o			\
		main.o				\
		parser.o			\
		shell.o				\
		banner.o			\
		handlers.o			\
		mm_ctl.o			\
		input_ctl.o			\
		video_ctl.o			\
		fs_ctl.o			\
		os_ctl.o			\
		segments_ctl.o			\
		drivers_ctl.o			\
		terminal_ctl.o			\
		env_ctl.o			\
		performance_ctl.o		\
		upcalls_ctl.o

CFLAGS	+=  -I../../examour/include -I./ -I../../drivers/video/vga -I../../drivers/input/kbd -I../../libos/libc/klibc/include

ASFLAGS	=	$(CFLAGS)

LDFLAGS		+= -T init.lds# ../../drivers/rt/c/env.lds

LIBOS_COMPONENTS=	../../drivers/video/vga/libvgadrv.a 			\
			../../drivers/input/kbd/libkbddrv.a			\
			../../libos/libc/klibc/libc.a				\
			../../toolkit/libslds/libslds.a			\

#			../../drivers/mm/segment/libsegmentmmdrv.a			\
#			../../drivers/video/vesa/libvesadrv.a			\
#			../../drivers/fs/tgfs/libtgfsdrv.a				\



install: $(OUTPUT)
	@echo "[MK]$(OUTPUT) built."

%.o: %.c
	@echo "[CC] $<"
	@$(CC) -c -o $@ $< $(CFLAGS)

%.o: %.S
	@echo "[CC] $<"
	@$(CC) -c -o $@ $< $(ASFLAGS) -D__ASM__

$(OUTPUT): $(OBJS)
	@echo "[LD] $(OUTPUT)"
	@$(LD) $(OBJS) $(LIBOS_COMPONENTS) $(LDFLAGS) -o $(OUTPUT)

clean:
	@echo "[RM] $(OBJS)"
	@rm -f $(OBJS) *~ \#*

fclean: clean
	@echo "[RM] $(OUTPUT)"
	@rm -f $(OUTPUT)

re: fclean install
