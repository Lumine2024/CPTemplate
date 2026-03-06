cmake_minimum_required(VERSION 3.16)
project(CPTemplate CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Make 'include' the general include directory so that headers such as
# "common.h" and "geo/basic.h" can be found without any relative-path prefix.
include_directories(${CMAKE_SOURCE_DIR}/include)

# Collect all usage source files and register each as a separate executable.
# Targets are named after their path relative to the usage/ directory, with
# directory separators replaced by underscores (e.g. ds/seg.cpp -> ds_seg).
#
# Note: GLOB_RECURSE is used here for convenience. If you add or remove source
# files, re-run CMake (e.g. `cmake ..`) to pick up the change before building.
file(GLOB_RECURSE USAGE_SOURCES RELATIVE "${CMAKE_SOURCE_DIR}/usage" "usage/*.cpp")

foreach(rel_source IN LISTS USAGE_SOURCES)
    # Derive a unique, filesystem-safe target name from the relative path.
    string(REPLACE "/" "_" target_name "${rel_source}")
    string(REPLACE ".cpp" "" target_name "${target_name}")

    add_executable(${target_name} "usage/${rel_source}")
endforeach()
