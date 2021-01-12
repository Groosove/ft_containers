cmake_minimum_required(VERSION 3.17)
project(ft_containers)

set(CMAKE_CXX_STANDARD 98)
add_compile_options( -Wall -Wextra -Werror -Wconversion -Wno-unused)

set(INCLUDE_DIRS includes)

include_directories(${INCLUDE_DIRS})

add_library(testlib INTERFACE)
add_subdirectory(sources)
