CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(simple_simulator)

FIND_PACKAGE(OpenCV REQUIRED)
INCLUDE_DIRECTORIES(${OpenCV_INCLUDE_DIRS})

add_executable(linalg_main linalg_main.cpp)

add_library(grid_library grid.cpp)