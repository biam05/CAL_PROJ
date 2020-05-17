cmake_minimum_required(VERSION 3.14.5)
project(src)

set(CMAKE_CXX_STANDARD 14)
link_libraries(ws2_32 wsock32)

add_executable(src main.cpp gui.cpp inputHandler.cpp spot.cpp edge.cpp vertex.cpp user.cpp house.cpp
        fileHandler.cpp request.cpp wasteApp.cpp lib/connection.cpp lib/connection.h lib/edgetype.h
        lib/graphviewer.cpp lib/graphviewer.h lib/GraphViewerController.jar houseRequest.cpp)
include_directories(include)