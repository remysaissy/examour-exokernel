include_directories(${examour-exokernel_SOURCE_DIR}/src/include)

add_library(mm OBJECT mm.c hdr_mm_blk.c mm_blk.c arch/i386/arch_mm.c)