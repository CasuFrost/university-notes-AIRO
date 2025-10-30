cmake_minimum_required(VERSION 2.8.3)
project(simple_simulator)

# TODO invokes the routines to find a package called Eigen3

FIND_PACKAGE(OpenCV  REQUIRED)
INCLUDE_DIRECTORIES(${OpenCV_INCLUDE_DIRS})

add_library(stuff_library
            linalg.cpp
            grid.cpp
            world_item.cpp
            laser_scanner.cpp
            unicycle_robot.cpp)

add_executable(linalg_main linalg_main.cpp)
target_link_libraries(linalg_main
        stuff_library
        ${OpenCV_LIBRARIES}
)

add_executable(grid_main
        grid_main.cpp)

target_link_libraries(grid_main
        stuff_library
        ${OpenCV_LIBRARIES}
)

add_executable(laser_scanner_main
        laser_scanner_main.cpp)

target_link_libraries(laser_scanner_main
        stuff_library
        ${OpenCV_LIBRARIES}
)

add_executable(unicycle_main
        unicycle_main.cpp)

target_link_libraries(unicycle_main
        stuff_library
        ${OpenCV_LIBRARIES}
)