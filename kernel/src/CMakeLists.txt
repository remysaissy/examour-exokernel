file(GLOB_RECURSE APP_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/../include/examour/*.h")
set(VERSION_HEADERS "${CMAKE_CURRENT_BINARY_DIR}/../include/examour/version.h")

file(GLOB_RECURSE APP_SOURCES
  "${CMAKE_CURRENT_SOURCE_DIR}/../src/arch/i386/*.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/../src/arch/i386/*.S"
  )

# Define specific flags for the library
set(CMAKE_C_FLAGS "-nostdinc -nostdlib -ffreestanding")

# Define the application
add_executable(${PROJECT_NAME} ${APP_SOURCES})
# TODO: integrate .lds

target_link_libraries(${PROJECT_NAME} ${c_LIB} ${slds_LIB})

# Set the build version. It will be used in the name of the lib, with corresponding
# symlinks created. SOVERSION could also be specified for api version. 
set_target_properties(${PROJECT_NAME} PROPERTIES
  VERSION ${VERSION}  # ${VERSION} was defined in the main CMakeLists.
  FRAMEWORK FALSE
  PUBLIC_HEADER "${APP_HEADERS} ${VERSION_HEADERS}" # specify the public headers
)

# Says how and where to install software
install(TARGETS ${PROJECT_NAME}
  EXPORT ${PROJECT_NAME}Targets            # for downstream dependencies
  ARCHIVE DESTINATION lib COMPONENT libs   # static lib
  RUNTIME DESTINATION bin COMPONENT libs   # binaries
  LIBRARY DESTINATION lib COMPONENT libs   # shared lib
  PUBLIC_HEADER DESTINATION include/${PROJECT_NAME} COMPONENT devel   # headers (note the different component -> different package)
#  FRAMEWORK DESTINATION bin COMPONENT libs # for mac
)
