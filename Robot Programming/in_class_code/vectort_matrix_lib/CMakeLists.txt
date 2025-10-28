cmake_minimum_required (VERSION 2.8.11)
project (rp_cpp_intro)

add_library(linear_algebra_library vec_d.cpp mat_d.cpp) 

add_executable(vec_d_main vec_d_main.cpp)
target_link_libraries(vec_d_main linear_algebra_library)

add_executable(mat_d_main mat_d_main.cpp)
target_link_libraries(mat_d_main linear_algebra_library)



