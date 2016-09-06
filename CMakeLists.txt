cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)

project("HelioBoard")

SET(CMAKE_CXX_COMPILER g++)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")

add_executable(helioboard circleblooms.cpp game.cpp renderer.cpp helioboard.cpp)

target_link_libraries(helioboard rtmidi)