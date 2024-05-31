#created by Alan 24/04/2024
cmake_minimum_required(VERSION 3.8)

add_library(BBAI STATIC)

set(CMAKE_CXX_STANDARD 20)

set(SOURCES  
	FSM.h FSM.cpp
	NPC.h NPC.cpp
	Movement.h Movement.cpp)

target_sources(BBAI PRIVATE ${SOURCES})

target_link_libraries(BBAI PRIVATE BBComponentSystem)

target_link_libraries(BBAI PUBLIC glm sol2 EnTT)
