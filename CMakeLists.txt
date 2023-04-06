cmake_minimum_required(VERSION 3.23)
project(DAProject)

set(CMAKE_CXX_STANDARD 14)

add_executable(DAProject main.cpp src/StationTrack.h src/StationTrack.cpp src/TripManager.h src/graph.h src/graph.cpp src/TripManager.cpp)
