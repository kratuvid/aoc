cmake_minimum_required(VERSION 3.31)
include(CMakePrintHelpers)

## Defines
if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE "Debug")
endif()
set(CMAKE_COLOR_DIAGNOSTICS YES)
set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

## Global options
set(common_options "")

# Address sanitization
set(enable_asan 1)
if(enable_asan EQUAL 1)
	list(APPEND common_options -fsanitize=address)
endif()

# Build type specifics
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
	add_compile_options(-D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_BACKTRACE)
	link_libraries(stdc++exp)
endif()

add_compile_options(${common_options}
	-march=native -pipe
	-Wall -Wextra -Wpedantic -Werror
)
add_link_options(${common_options})

## Sources setup
project(aoc2018 LANGUAGES CXX)

add_executable(1)
target_sources(1 PRIVATE 1.cpp)
# target_precompile_headers(1 PRIVATE 1.hpp)
