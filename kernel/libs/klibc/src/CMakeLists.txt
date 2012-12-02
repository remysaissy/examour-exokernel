add_subdirectory(ctype)
add_subdirectory(zlib)

add_library(c $<TARGET_OBJECTS:zlib> $<TARGET_OBJECTS:ctype> atoi.c atol.c atoll.c bsearch.c ctypes.c fnmatch.c getopt.c getopt_long.c globals.c interp.s jrand48.c lrand48.c memccpy.c memchr.c memcmp.c memcpy.c memmem.c memmove.c memrchr.c memset.c memswap.c mrand48.c nrand48.c qsort.c seed48.c srand48.c strcasecmp.c strcat.c strchr.c strcmp.c strcpy.c strcspn.c strdup.c strerror.c strlcat.c strlcpy.c strlen.c strncasecmp.c strncat.c strncmp.c strncpy.c strndup.c strnlen.c strntoimax.c strntoumax.c strpbrk.c strrchr.c strsep.c strspn.c strstr.c strtoimax.c strtok.c strtol.c strtoll.c strtoul.c strtoull.c strtoumax.c strxspn.c)
