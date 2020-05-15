cmake_minimum_required(VERSION 3.14.5)
project(src)

set(CMAKE_CXX_STANDARD 14)

add_executable(src main.cpp gui.cpp inputHandler.cpp spots.cpp edges.cpp vertexes.cpp user.cpp)
include_directories(include)