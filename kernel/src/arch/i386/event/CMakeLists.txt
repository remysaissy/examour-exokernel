add_subdirectory(asm)

add_library(event OBJECT syscall.c io.c 8259a.c event.c irq.c idt.c khandler.c $<TARGET_OBJECTS:event_asm>)
