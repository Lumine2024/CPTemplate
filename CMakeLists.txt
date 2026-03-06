cmake_minimum_required(VERSION 3.16)
project(CPTemplate CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Make 'include' the general include directory so that headers such as
# "common.h" and "geo/basic.h" can be found without any relative-path prefix.
include_directories(${CMAKE_SOURCE_DIR}/include)

# Collect all usage header files and register each as a separate CI test
# executable.  Targets are named after their path relative to the usage/
# directory, with directory separators replaced by underscores
# (e.g. ds/seg.h -> ds_seg).
#
# Because the usage files are now header-only (no main()), a thin wrapper
# .cpp is generated in the build tree for each header.  The wrapper simply
# includes the header and provides an empty main(), which is enough to
# confirm the header compiles cleanly.
#
# Note: GLOB_RECURSE is used here for convenience.  If you add or remove
# header files, re-run CMake (e.g. `cmake ..`) to pick up the change before
# building.
file(GLOB_RECURSE USAGE_HEADERS RELATIVE "${CMAKE_SOURCE_DIR}/usage" "usage/*.h")

foreach(rel_header IN LISTS USAGE_HEADERS)
    # Derive a unique, filesystem-safe target name from the relative path.
    string(REPLACE "/" "_" target_name "${rel_header}")
    string(REPLACE ".h" "" target_name "${target_name}")

    # Generate a minimal wrapper that includes the header and supplies main().
    set(wrapper "${CMAKE_BINARY_DIR}/test_wrappers/${target_name}.cpp")
    file(WRITE "${wrapper}"
        "#include \"${CMAKE_SOURCE_DIR}/usage/${rel_header}\"\nint main(){}\n")

    add_executable(${target_name} "${wrapper}")
    target_include_directories(${target_name} PRIVATE
        ${CMAKE_SOURCE_DIR}/include)
endforeach()
