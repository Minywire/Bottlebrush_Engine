#created by Alan 01/06/2024
cmake_minimum_required(VERSION 3.8)

add_library(BBEvent STATIC)

set(CMAKE_CXX_STANDARD 20)

set(SOURCES
	Message.cpp Message.h
	EventDispatcher.cpp EventDispatcher.h
	Singleton.h)

target_sources(BBEvent PRIVATE ${SOURCES})

target_link_libraries(BBEvent PRIVATE BBAI)
target_link_libraries(BBEvent PUBLIC sol2)
