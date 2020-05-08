cmake_minimum_required(VERSION 3.14.5)
project(src)

set(CMAKE_CXX_STANDARD 14)

add_executable(src main.cpp gui.cpp include/gui.h inputHandler.cpp include/inputHandler.h)