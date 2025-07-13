cmake_minimum_required(VERSION 3.5)

project(MyTemplate)
include_directories(${CMAKE_SOURCE_DIR})
set(CMAKE_CXX_STANDARD 23)

add_executable(main main.cpp)