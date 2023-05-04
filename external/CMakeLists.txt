add_library(dirent INTERFACE)

if(WIN32)
	target_include_directories(dirent INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/dirent/include")
endif()
