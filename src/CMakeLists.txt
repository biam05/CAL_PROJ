cmake_minimum_required(VERSION 3.14.5)
project(src)

set(CMAKE_CXX_STANDARD 14)

add_executable(src main.cpp gui.cpp inputHandler.cpp spot.cpp edge.cpp vertex.cpp user.cpp house.cpp fileHandler.cpp include/fileHandler.h request.cpp include/request.h)
include_directories(include)