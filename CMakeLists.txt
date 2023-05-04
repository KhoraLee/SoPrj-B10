cmake_minimum_required(VERSION 3.10)
project(POS C) # C Project

set(CMAKE_C_STANDARD 11) # C11

if(MSVC)
	add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
endif()

add_subdirectory(external)
add_subdirectory(POS)

add_executable(POS POS/main.c)
target_link_libraries(POS PRIVATE core)

if(MSVC)
	target_compile_options(POS PUBLIC "/wd4819")
endif()
