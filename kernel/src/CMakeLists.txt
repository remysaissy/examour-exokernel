
add_subdirectory(debug)
add_subdirectory(boot)
add_subdirectory(bus)
add_subdirectory(event)
add_subdirectory(mm)
add_subdirectory(process)


add_library(kernel $<TARGET_OBJECTS:boot> $<TARGET_OBJECTS:debug> $<TARGET_OBJECTS:bus> $<TARGET_OBJECTS:event> $<TARGET_OBJECTS:mm> $<TARGET_OBJECTS:process>)