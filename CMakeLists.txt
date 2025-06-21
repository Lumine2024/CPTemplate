cmake_minimum_required(VERSION 3.1)

project(MyTemplate)
include_directories(${CMAKE_SOURCE_DIR})
set(CMAKE_CXX_STANDARD 20)

add_executable(main main.cpp)