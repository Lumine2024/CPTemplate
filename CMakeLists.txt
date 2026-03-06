cmake_minimum_required(VERSION 3.16)
project(CPTemplate CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_SOURCE_DIR}/include)

enable_testing()
add_subdirectory(tests)
