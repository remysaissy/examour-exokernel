cmake_minimum_required(VERSION 3.2) 
project(klibc)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

include_directories(include include/bits32)
add_subdirectory(src)
