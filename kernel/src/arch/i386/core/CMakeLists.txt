add_subdirectory(asm)

add_library(core OBJECT globals.c main.c $<TARGET_OBJECTS:core_asm>)
