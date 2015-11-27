cmake_minimum_required(VERSION 3.2)
project(kernel)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include_directories(include)
add_subdirectory(src)
