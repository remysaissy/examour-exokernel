
include ../.config

OUTPUT	:=	init

SUBDIRS	:=	.

OBJS	=	asm/start.o			\
		test_suites.o		\
		uenv.o				\
		malloc.o			\
		malloc_init.o			\
		display.o			\
		powers.o			\
		tgfs.o
# 		test_suites.o			\


find_csources   = $(wildcard $(subdir)/*.c)
find_asmsources = $(wildcard $(subdir)/asm/*.S)

csources   := $(foreach subdir,$(SUBDIRS),$(find_csources))
asmsources := $(foreach subdir,$(SUBDIRS),$(find_asmsources))

cobjs	:= $(csources:.c=.o)
asmobjs	:= $(asmsources:.S=.o)

CFLAGS	+=	-S -fno-builtin  -I../include -I../ -Wstrict-aliasing=2 \
		-nostdinc -nostdlib -Werror #-O3 #-S

LDFLAGS	+=	-T init.lds

install: $(OUTPUT)
	@echo "[MK]$(OUTPUT) built."

%.o: %.c
	@echo "[CC] $<"
	@$(CC) -c -o $@ $< $(CFLAGS)

%.o: %.S
	@echo "[CC] $<"
	@$(CC) -c -o $@ $< $(CFLAGS) -D__ASM__

# $(OUTPUT): $(cobjs) $(asmobjs)
# 	@echo "[LD] $(OUTPUT)"
# 	@$(LD) $(cobjs) $(asmobjs) $(LDFLAGS) -o $(OUTPUT)
$(OUTPUT): $(OBJS)
	@echo "[LD] $(OUTPUT)"
	@$(LD) $(OBJS) $(LDFLAGS) -o $(OUTPUT)

clean:
	@echo "[RM] $(cobjs) $(asmobjs)"
	@rm -f $(cobjs) $(asmobjs) *~ \#*

fclean: clean
	@echo "[RM] $(OUTPUT)"
	@rm -f $(OUTPUT)

re: fclean install
