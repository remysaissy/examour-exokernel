file(GLOB_RECURSE APP_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/../include/examour/*.h")
set(VERSION_HEADERS "${CMAKE_CURRENT_BINARY_DIR}/../include/examour/version.h")

file(GLOB_RECURSE APP_SOURCES
  "${CMAKE_CURRENT_SOURCE_DIR}/arch/x86_64/asm/*.s"  
  "${CMAKE_CURRENT_SOURCE_DIR}/arch/x86_64/*.c"
  )

enable_language(ASM)
set(CMAKE_ASM_SOURCE_FILE_EXTENSIONS "s;S")
set(ASM_OPTIONS "-x assembler-with-cpp -D__ASM__")
set(CMAKE_ASM_FLAGS "${CMAKE_C_FLAGS} ${ASM_OPTIONS}")
set(LINKER_SCRIPT "${CMAKE_CURRENT_SOURCE_DIR}/arch/x86_64/linkmap.lds")

# Define the application
add_executable(${PROJECT_NAME} ${APP_SOURCES})
set_target_properties(${PROJECT_NAME} PROPERTIES COMPILE_FLAGS "-m64" LINK_FLAGS "-m64 -T ${LINKER_SCRIPT}")

target_link_libraries(${PROJECT_NAME} ${c_LIB} ${slds_LIB})

# Set the build version. It will be used in the name of the lib, with corresponding
# symlinks created. SOVERSION could also be specified for api version. 
set_target_properties(${PROJECT_NAME} PROPERTIES
  VERSION ${VERSION}  # ${VERSION} was defined in the main CMakeLists.
  FRAMEWORK FALSE
  PUBLIC_HEADER "${APP_HEADERS} ${VERSION_HEADERS}" # specify the public headers
)
