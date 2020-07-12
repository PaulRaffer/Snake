cmake_minimum_required(VERSION 3.9)
project(snake)

if(MSVC)
	add_compile_options(/W4)
else()
	add_compile_options(-Wall -Wextra -Wpedantic)
endif()

set(CMAKE_CXX_STANDARD 17)

add_executable(snake
	src/main.cpp
)
