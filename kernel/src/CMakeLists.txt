add_subdirectory(arch/i386)

set(CMAKE_C_FLAGS "-nostdinc -nostdlib -fno-builtin")

include_directories(${CMAKE_BINARY_DIR}/libs/klibc/include ${CMAKE_BINARY_DIR}/libs/libslds/include ${CMAKE_BINARY_DIR}/libs/klibc/include/bits32)

add_executable(kernel $<TARGET_OBJECTS:event> $<TARGET_OBJECTS:support> $<TARGET_OBJECTS:core> $<TARGET_OBJECTS:mm> $<TARGET_OBJECTS:env>)

target_link_libraries(kernel slds klibc)


