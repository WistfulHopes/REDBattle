cmake_minimum_required(VERSION 3.18)

project(REDBattle)

set (CMAKE_CXX_STANDARD 20)

include_directories( "./src" )

macro( add_recursive dir retVal )
	file( GLOB_RECURSE ${retVal} ${dir}/*.h ${dir}/*.cpp ${dir}/*.c )
endmacro()

add_recursive( ./src SOURCES )
add_recursive( ./src HEADERS )

add_library(REDBattle STATIC ${SOURCES} ${HEADERS})