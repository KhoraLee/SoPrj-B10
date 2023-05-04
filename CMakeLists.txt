cmake_minimum_required(VERSION 3.10)
project(POS C) # C Project

set(CMAKE_C_STANDARD 11) # C11
set_property(GLOBAL PROPERTY USE_FOLDERS TRUE)

if(MSVC)
	add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>") # Force UTF-8
endif()

add_subdirectory(external)
add_subdirectory(POS)
add_subdirectory(test)

add_executable(runner POS/main.c)
target_link_libraries(runner PRIVATE core)
set_property(TARGET runner PROPERTY FOLDER POS)

set_target_properties(runner PROPERTIES OUTPUT_NAME POS
	ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
	LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
	RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/../bin"
)


if(MSVC)
	target_compile_options(POS PUBLIC "/wd4819") # Disable warning C4996
endif()

