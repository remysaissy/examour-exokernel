
include_directories(${libc_SOURCE_DIR}/src/include)

add_library(zlib OBJECT adler32.c compress.c crc32.c deflate.c infback.c inffast.c inflate.c inftrees.c trees.c uncompr.c zutil.c)