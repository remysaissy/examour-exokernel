cmake_minimum_required(VERSION 3.2) 


message("EXECUTABLE_OUTPUT_PATH: " ${EXECUTABLE_OUTPUT_PATH} " CMAKE_BINARY_DIR" ${CMAKE_BINARY_DIR} " CMAKE_CURRENT_BINARY_DIR: " ${CMAKE_CURRENT_BINARY_DIR} " PROJECT_BINARY_DIR: " ${PROJECT_BINARY_DIR})

# if(${CMAKE_BINARY_DIR} STREQUAL ${CMAKE_SOURCE_DIR})
# message(FATAL_ERROR "source and build directories are the same. Please create a separate build directory and execute cmake ../CMakeLists.txt from there.")
# endif()

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/bin)

#add_subdirectory(libs)
#add_subdirectory(kernel)
#add_subdirectory(drivers)
#add_subdirectory(applications)
