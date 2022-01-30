cmake_minimum_required(VERSION 3.16)
project(aedproj2)

set(CMAKE_CXX_STANDARD 14)

add_executable(aedproj2 main.cpp src/Graph.cpp src/Stop.cpp src/STCP.cpp src/Auxiliary.cpp)

include_directories(aedproj2 headers/)
