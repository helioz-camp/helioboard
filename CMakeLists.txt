cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)

project("HelioBoard")

SET(CMAKE_CXX_COMPILER g++)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")

find_package(PkgConfig REQUIRED)
pkg_check_modules(CURL REQUIRED curlpp)

include_directories(${CURLINCLUDE_DIRS})
link_directories(${CURLLIBRARY_DIRS})

add_executable(helioboard blooms.cpp circleblooms.cpp strobe.cpp cellstrobe.cpp fill.cpp game.cpp gridcontroller.cpp decay.cpp canvas.cpp renderer.cpp helioboard.cpp)

target_link_libraries(helioboard rtmidi ${CURL_LIBRARIES})