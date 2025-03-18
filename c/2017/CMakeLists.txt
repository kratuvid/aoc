cmake_minimum_required(VERSION 3.31)

set(CMAKE_COLOR_DIAGNOSTICS ON)
if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Debug)
endif()
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_FLAGS "-march=native -Wall -Wextra -Wpedantic -Werror -pipe -fsanitize=address")
# set(CMAKE_C_FLAGS "-march=native -Wall -Wextra -Wpedantic -Werror -pipe")

project(aoc2017 LANGUAGES C)

add_library(utils OBJECT utils.c)

add_executable(1 1.c $<TARGET_OBJECTS:utils>)
add_executable(2 2.c $<TARGET_OBJECTS:utils>)
