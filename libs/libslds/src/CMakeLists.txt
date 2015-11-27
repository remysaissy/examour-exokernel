add_subdirectory(hash)
add_subdirectory(list)
add_subdirectory(tree)

set(CMAKE_C_FLAGS "-nostdinc -nostdlib -fno-builtin")

add_library(slds STATIC $<TARGET_OBJECTS:hash> $<TARGET_OBJECTS:list> $<TARGET_OBJECTS:tree_binary> $<TARGET_OBJECTS:tree_nary>)
