cmake_minimum_required(VERSION 3.16)
project(aedproj2)

set(CMAKE_CXX_STANDARD 14)

add_executable(aedproj2 src/main.cpp src/Graph.cpp src/Stop.cpp src/PathMap.cpp headers/Graph.h headers/Stop.h headers/PathMap.h)
