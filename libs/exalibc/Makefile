
VERSION=1.1
OUTPUT=exalibc
SRC=$(shell find . -regextype posix-extended -type f -regex \./.*\.c -not -regex '.*/(tests|tests-core)/.*' -print)
OBJS=$(SRC:%.c=%.o)

SRC_UT=$(shell find . -regextype posix-extended -type f -regex \./.*\.c -print)
OBJS_UT=$(SRC_UT:%.c=%.o)

# Static library
AR=ar
AR_FLAGS=rcs

# C code object file compiler
INCS=-Iinclude
OPTIMIZATIONS=-O3 -msse2 -march=native -mfpmath=387 -funroll-loops -fomit-frame-pointer
CFLAGS=$(INCS) $(OPTIMIZATIONS) -ffreestanding -fPIC -W -Werror -Iinclude/arch/i386
LDFLAGS=-nostdlib
CC=gcc

#CFLAGS_UT=-ggdb3 -pg -W -Werror $(INCS) -Itests-core

%.o: %.c
	@echo "[CC] $<"
	@$(CC) $(CFLAGS) -c -o $@ $<

# Build rules.

build-i386: $(OBJS)
	@echo "[MK] build/i386 directory"
	@mkdir -p build/i386
	@echo "[LD] build/i386/$(OUTPUT).a"
	@$(AR) $(AR_FLAGS) build/i386/$(OUTPUT).a $(OBJS)
#	@echo "[LD] build/i386/$(OUTPUT).so"
#	@$(CC) $(LDFLAGS) -shared -Wl,-soname,build/i386/$(OUTPUT).so.$(VERSION) -o build/i386/$(OUTPUT).so $(OBJS)

build: build-i386


# Unit testing rules.

unit-testing-i386: $(OBJS_UT) ./tests-core/AllTests.o
	@echo "[GEN] Unit testing entry point"
	@tests-core/gen-tests.sh `pwd`
	@echo "[MK] unit_testing/i386 directory"
	@mkdir -p unit_testing/i386
	@echo "[BIN] unit_testing/i386/$(OUTPUT)"
	@$(CC) $(LDFLAGS_UT) -o unit_testing/i386/$(OUTPUT) $(OBJS_UT) ./tests-core/AllTests.o

unit-testing: unit-testing-i386


# Clean rules.

clean:
	@echo "[RM] $(OBJS)"
	@$(RM) -f $(OBJS)

fclean-i386: clean
	@echo "[RM] $(OUTPUT)"
	@$(RM) -rf build/i386

fclean: fclean-i386
