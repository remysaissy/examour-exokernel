
VERSION=0.1
OUTPUT=libarch
SRC=$(shell find . -regextype posix-extended -type f -regex \./.*\.c -not -regex '.*/(tests|tests-core)/.*' -print)
OBJS=$(SRC:%.c=%.o)

SRC_UT=$(shell find . -regextype posix-extended -type f -regex \./.*\.c -print)
OBJS_UT=$(SRC_UT:%.c=%.o)

# Static library
AR=ar
AR_FLAGS=rcs

# C code object file compiler
INCS=-Iinclude -I../libslds/include
OPTIMIZATIONS=-O3 -msse2 -march=native -mfpmath=387 -funroll-loops -fomit-frame-pointer
CFLAGS=$(INCS) $(OPTIMIZATIONS) -fPIC -W -Werror
CC=gcc

#CFLAGS_UT=-ggdb3 -pg -W -Werror $(INCS) -Itests-core

%.o: %.c
	@echo "[CC] $<"
	@$(CC) $(CFLAGS) -c -o $@ $<

# Build rules.
build: build-i386


setup-i386:
	@rm -rf include
	@ln -s arch-i386/include include

build-i386: setup-i386 $(OBJS)
	@echo "[MK] build/i386 directory"
	@mkdir -p build/i386
	@echo "[LD] build/i386/$(OUTPUT).a"
	@$(AR) $(AR_FLAGS) build/i386/$(OUTPUT).a $(OBJS)


# Unit testing rules.

unit-testing-i386: $(OBJS_UT) ./tests-core/AllTests.o
	@echo "[GEN] Unit testing entry point"
	@tests-core/gen-tests.sh `pwd`
	@echo "[MK] unit_testing/i386 directory"
	@mkdir -p unit_testing/i386
	@echo "[BIN] unit_testing/i386/$(OUTPUT)"
	@$(CC) $(LDFLAGS) -o unit_testing/i386/$(OUTPUT) $(OBJS_UT) ./tests-core/AllTests.o

unit-testing: unit-testing-i386


# Clean rules.

clean:
	@echo "[RM] $(OBJS)"
	@$(RM) -f $(OBJS)

fclean-i386: clean
	@echo "[RM] $(OUTPUT)"
	@$(RM) -rf build/i386

fclean: fclean-i386
