set(LIB_HEADERS
  "${CMAKE_CURRENT_BINARY_DIR}/../include/libslds/Version.h" # Generated header
  ../include/libslds/tree/nary/rstar_tree.h
  ../include/libslds/tree/nary/bsharp_tree.h
  ../include/libslds/tree/nary/tpyramid_tree.h
  ../include/libslds/tree/nary/bplus_tree.h
  ../include/libslds/tree/nary/quad_tree.h
  ../include/libslds/tree/nary/hilbert_rtree.h
  ../include/libslds/tree/nary/trie_tree.h
  ../include/libslds/tree/nary/r_tree.h
  ../include/libslds/tree/nary/gist_tree.h
  ../include/libslds/tree/nary/common.h
  ../include/libslds/tree/nary/23_tree.h
  ../include/libslds/tree/nary/ub_tree.h
  ../include/libslds/tree/nary/rplus_tree.h
  ../include/libslds/tree/nary/oc_tree.h
  ../include/libslds/tree/nary/b_tree.h
  ../include/libslds/tree/nary/ab_tree.h
  ../include/libslds/tree/nary/bstar_tree.h
  ../include/libslds/tree/nary/fusion_tree.h
  ../include/libslds/tree/nary/top_tree.h
  ../include/libslds/tree/nary/nary_tree.h
  ../include/libslds/tree/nary/234_tree.h
  ../include/libslds/tree/nary/ternary_tree.h
  ../include/libslds/tree/binary/randomized_btree.h
  ../include/libslds/tree/binary/weight_balanced_tree.h
  ../include/libslds/tree/binary/kd_tree.h
  ../include/libslds/tree/binary/radix_tree.h
  ../include/libslds/tree/binary/redblack_tree.h
  ../include/libslds/tree/binary/left_child_right_sibling_tree.h
  ../include/libslds/tree/binary/dsw_algorihm.h
  ../include/libslds/tree/binary/ebst_tree.h
  ../include/libslds/tree/binary/bst_tree.h
  ../include/libslds/tree/binary/scapegoat_tree.h
  ../include/libslds/tree/binary/threaded_btree.h
  ../include/libslds/tree/binary/aa_tree.h
  ../include/libslds/tree/binary/splay_tree.h
  ../include/libslds/tree/binary/t_tree.h
  ../include/libslds/tree/binary/treap.h
  ../include/libslds/common.h
  ../include/libslds/hash.h
  ../include/libslds/tree.h
  ../include/libslds/list.h
)

set(LIB_SOURCES
  ../src/tree/nary/trie_tree.c
  ../src/tree/nary/ub_tree.c
  ../src/tree/nary/fusion_tree.c
  ../src/tree/nary/bplus_tree.c
  ../src/tree/nary/b_tree.c
  ../src/tree/nary/top_tree.c
  ../src/tree/nary/r_tree.c
  ../src/tree/nary/gist_tree.c
  ../src/tree/nary/quad_tree.c
  ../src/tree/nary/nary_tree.c
  ../src/tree/nary/oc_tree.c
  ../src/tree/nary/bstar_tree.c
  ../src/tree/nary/tpyramid_tree.c
  ../src/tree/nary/hilbert_rtree.c
  ../src/tree/nary/rstar_tree.c
  ../src/tree/nary/23_tree.c
  ../src/tree/nary/rplus_tree.c
  ../src/tree/nary/ab_tree.c
  ../src/tree/nary/234_tree.c
  ../src/tree/nary/common.c
  ../src/tree/nary/ternary_tree.c
  ../src/tree/binary/splay_tree.c
  ../src/tree/binary/kd_tree.c
  ../src/tree/binary/t_tree.c
  ../src/tree/binary/aa_tree.c
  ../src/tree/binary/avl_rotation.c
  ../src/tree/binary/randomized_btree.c
  ../src/tree/binary/bst_tree.c
  ../src/tree/binary/scapegoat_tree.c
  ../src/tree/binary/radix_tree.c
  ../src/tree/binary/redblack_tree.c
  ../src/tree/binary/left_child_right_sibling_tree.c
  ../src/tree/binary/weight_balanced_tree.c
  ../src/tree/binary/treap.c
  ../src/tree/binary/ebst_tree.c
  ../src/list/slist.c
  ../src/list/dlist.c
  ../src/list/clist.c
  ../src/hash/integer_hashing.c
  ../src/hash/hash.c
  ../src/hash/string_hashing.c
)

set(APP_HEADERS
)

set(APP_SOURCES
)

# Define two variables in order not to repeat ourselves.
set(LIBRARY_NAME ${PROJECT_NAME})

# Define specific flags for the library
set(CMAKE_C_FLAGS "-nostdinc -nostdlib -fno-builtin")

# Define the library
add_library(${LIBRARY_NAME} STATIC ${LIB_SOURCES})

# Set the build version. It will be used in the name of the lib, with corresponding
# symlinks created. SOVERSION could also be specified for api version. 
set_target_properties(${LIBRARY_NAME} PROPERTIES
  VERSION ${VERSION}  # ${VERSION} was defined in the main CMakeLists.
  FRAMEWORK FALSE
  PUBLIC_HEADER "${LIB_HEADERS}" # specify the public headers
)

# This is a make target, so you can do a "make projArunner"
#set(APPLICATION_NAME projArunner)
#add_executable(${APPLICATION_NAME} ${APP_SOURCES})

# Links the target exe (projArunner) against the library (libprojA) and other required libraries
#target_link_libraries(${APPLICATION_NAME} ${LIBRARY_NAME} ${Boost_PROGRAM_OPTIONS_LIBRARY})

# Says how and where to install software
install(TARGETS ${LIBRARY_NAME} # ${APPLICATION_NAME}
  EXPORT ${PROJECT_NAME}Targets            # for downstream dependencies
  ARCHIVE DESTINATION lib COMPONENT libs   # static lib
#  RUNTIME DESTINATION bin COMPONENT libs   # binaries
#  LIBRARY DESTINATION lib COMPONENT libs   # shared lib
  PUBLIC_HEADER DESTINATION include/${PROJECT_NAME} COMPONENT devel   # headers (note the different component -> different package)
#  FRAMEWORK DESTINATION bin COMPONENT libs # for mac
)

