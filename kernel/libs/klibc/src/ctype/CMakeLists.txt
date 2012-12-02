
include_directories(${libc_SOURCE_DIR}/src/include)

add_library(ctype OBJECT isalnum.c isalpha.c isascii.c isblank.c iscntrl.c isdigit.c isgraph.c islower.c isprint.c ispunct.c isspace.c isupper.c isxdigit.c tolower.c toupper.c)