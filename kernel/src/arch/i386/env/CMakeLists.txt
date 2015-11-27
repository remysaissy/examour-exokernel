add_subdirectory(asm)

add_library(env OBJECT timer.c env.c timeslice.c sched.c $<TARGET_OBJECTS:env_asm>)
