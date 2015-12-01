cmake_minimum_required(VERSION 3.2) 
project(examour)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake) # project specific cmake dir
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/libs/libc/cmake)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/libs/libslds/cmake)

# CMake useful variables
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib") 
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

# Versioning
set(VERSION_MAJOR "0")
set(VERSION_MINOR "0")
set(VERSION_PATCH "0")
set(VERSION ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH})

include(Common)

## Git (and its revision)
find_package(Git QUIET) # if we don't find git or FindGit.cmake is not on the system we ignore it.
## GetGitRevisionDescription module to retreive branch and revision information from Git
## Starting with Git 1.9 the module will be part of official cMake distribution, until then it has to be
## part of the application
## The Git module will trigger a reconfiguration for each pull that will bring a new revision on the local repository
set (VCS_REVISION "-1")
if(GIT_FOUND)
  include(GetGitRevisionDescription)
  get_git_head_revision(GIT_REFSPEC GIT_SHA1)
  message(STATUS "GIT branch ${GIT_REFSPEC}")
  message(STATUS "GIT revision ${GIT_SHA1}")
  set (VCS_REVISION ${GIT_SHA1})
endif()

set(c_INCLUDE_DIRS
  "${CMAKE_SOURCE_DIR}/libs/libc/include"
  "${CMAKE_BINARY_DIR}/libs/libc/include")

set(c_LIB "${CMAKE_BINARY_DIR}/lib/libc.a")

set(slds_INCLUDE_DIRS
  "${CMAKE_SOURCE_DIR}/libs/libslds/include"
  "${CMAKE_BINARY_DIR}/libs/libslds/include")  

set(slds_LIB "${CMAKE_BINARY_DIR}/lib/libslds.a")

# This sets the include directory for the reference project. This is the -I flag in gcc.
# All the includes should be in this variable To add new directories to the include path,
# just add them in this list (after a space), or add an include_directories statement in a
# subdirectory's CMakeLists.

include_directories(
  ${PROJECT_SOURCE_DIR}/include
  ${PROJECT_BINARY_DIR}/include
  ${c_INCLUDE_DIRS}
  ${slds_INCLUDE_DIRS}  
  )

#enable_testing()
add_subdirectory(include)
add_subdirectory(src)
#add_subdirectory(doc)
#add_subdirectory(test)

#
# SYSTEM PACKAGING (RPM, TGZ, ...)
# _____________________________________________________________________________

include(CPackConfig)

#
# CMAKE PACKAGING (for other CMake projects to use this one easily)
# _____________________________________________________________________________

include(PackageConfigurator)