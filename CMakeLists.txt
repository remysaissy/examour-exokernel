cmake_minimum_required(VERSION 3.2) 

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

#enable_testing() # needed on top-level CMakeLists.txt

# Target doc definition
# The challenge here is that the sub projects must all define a custom target but with different names to avoid
# conflicts. We also want to be able to issue "make doc" from the top dir while being able to issue "make doc"
# in the subdirs *when* we compile only a subproject.
# We define as well a function AddDocTarget in cmake/DoxygenTarget.cmake
#add_custom_target(doc) # DEPENDS docProjA docProjB) Note: with CMake 3.X the DEPENDS would work
#ADD_DEPENDENCIES(doc kernel slds klibc)

add_subdirectory(libs/libc)
add_subdirectory(libs/libslds)
add_subdirectory(kernel)
#add_subdirectory(drivers)
#add_subdirectory(applications)
