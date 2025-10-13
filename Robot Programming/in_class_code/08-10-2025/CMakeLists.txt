cmake_minimum_required (VERSION 2.8.11)
project (binary_tree)

add_library(btree_lib node.cpp btree.cpp) 

add_executable(main main.cpp)
target_link_libraries(main btree_lib)





