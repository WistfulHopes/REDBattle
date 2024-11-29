cmake_minimum_required(VERSION 3.18)

project(REDBattle)

set (CMAKE_CXX_STANDARD 20)

include_directories( "./src" )

add_recursive( ./src SOURCES )
add_recursive( ./src HEADERS )

add_library(REDBattle STATIC ${SOURCES} ${HEADERS})