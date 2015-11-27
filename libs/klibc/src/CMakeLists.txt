add_subdirectory(ctype)

set(CMAKE_C_FLAGS "-nostdinc -nostdlib -fno-builtin")

add_library(klibc STATIC $<TARGET_OBJECTS:ctype> atoi.c atol.c atoll.c bsearch.c ctypes.c fnmatch.c interp.s jrand48.c lrand48.c memccpy.c memchr.c memcmp.c memcpy.c memmem.c memmove.c memrchr.c memset.c memswap.c mrand48.c nrand48.c qsort.c seed48.c srand48.c strcasecmp.c strcat.c strchr.c strcmp.c strcpy.c strcspn.c strerror.c strlcat.c strlcpy.c strlen.c strncasecmp.c strncat.c strncmp.c strncpy.c strnlen.c strntoimax.c strntoumax.c strpbrk.c strrchr.c strsep.c strspn.c strstr.c strtoimax.c strtok.c strtol.c strtoll.c strtoul.c strtoull.c strtoumax.c strxspn.c)
