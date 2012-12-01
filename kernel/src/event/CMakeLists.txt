include_directories(${examour-exokernel_SOURCE_DIR}/src/include)

set_property(SOURCE arch/i386/asm/isr.s PROPERTY LANGUAGE C)

add_library(event OBJECT event.c io.c arch/i386/pic.c arch/i386/asm/isr.s)