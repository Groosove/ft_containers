cmake_minimum_required(VERSION 3.17)
project(ft_containers)

set(CMAKE_CXX_STANDARD 98)
add_compile_options( -Wall -Wextra -Werror -Wconversion -Wno-unused)


set(INCLUDE_DIRS includes)

include_directories(${INCLUDE_DIRS})

set(SRCS
		includes/list.hpp
		includes/vector.hpp
		includes/stack.hpp
		includes/queue.hpp)

add_executable(ft_containers main.cpp ${SRCS})

add_library(testlib INTERFACE)
target_include_directories(testlib INTERFACE ./srcs)
add_subdirectory(sources)
