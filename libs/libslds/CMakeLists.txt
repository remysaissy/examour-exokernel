cmake_minimum_required(VERSION 3.2) 
project(slds)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

include_directories(include)
add_subdirectory(src)
