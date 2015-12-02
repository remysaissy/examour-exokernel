cmake_minimum_required(VERSION 3.2) 

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# CMake useful variables
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib") 
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

# Define common flags to all projects
set(CMAKE_C_FLAGS "-std=c99 -nostdinc -nostdlib -ffreestanding")

add_subdirectory(libs/libc)
add_subdirectory(libs/libslds)
add_subdirectory(kernel)
#add_subdirectory(drivers)
#add_subdirectory(applications)

add_dependencies(examour c slds)

