include_directories(${examour-exokernel_SOURCE_DIR}/src/include)

set_property(SOURCE arch/i386/bootstrap.s PROPERTY LANGUAGE C)

add_library(boot OBJECT main.c arch/i386/bootstrap.s)