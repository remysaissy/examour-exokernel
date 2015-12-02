file(GLOB_RECURSE LIB_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/../include/*.h")
set(VERSION_HEADERS "${CMAKE_CURRENT_BINARY_DIR}/../include/version.h")

file(GLOB_RECURSE LIB_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/../src/*.c")

# Define the library
add_library(${PROJECT_NAME} STATIC ${LIB_SOURCES})
set_target_properties(${PROJECT_NAME} PROPERTIES COMPILE_FLAGS "-m64" LINK_FLAGS "-m64")

# Set the build version. It will be used in the name of the lib, with corresponding
# symlinks created. SOVERSION could also be specified for api version. 
set_target_properties(${PROJECT_NAME} PROPERTIES
  VERSION ${VERSION}  # ${VERSION} was defined in the main CMakeLists.
  FRAMEWORK FALSE
  PUBLIC_HEADER "${LIB_HEADERS} ${VERSION_HEADERS}" # specify the public headers
)
