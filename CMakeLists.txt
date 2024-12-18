cmake_minimum_required(VERSION 3.15...3.31)

project(REDBattle)

if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
	set (CMAKE_CXX_STANDARD 23)

	file(TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/CMakeLists.txt" LOC_PATH)
	if(EXISTS "${LOC_PATH}")
		message(FATAL_ERROR "You cannot build in a source directory (or any directory with a CMakeLists.txt file). Please make a build subdirectory. Feel free to remove CMakeCache.txt and CMakeFiles.")
	endif()
endif()

macro( add_recursive dir retVal )
	file( GLOB_RECURSE ${retVal} ${dir}/*.h ${dir}/*.cpp ${dir}/*.c )
endmacro()

add_recursive( ./src SOURCES )
add_recursive( ./src HEADERS )

add_library(REDBattle STATIC ${SOURCES} ${HEADERS})
target_include_directories( REDBattle PUBLIC "./src" )