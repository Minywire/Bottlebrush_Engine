#created by Marco 09/03/2024
cmake_minimum_required(VERSION 3.8)

add_library(BBComponentSystem STATIC)

set(CMAKE_CXX_STANDARD 20)

set(SOURCES Entity.cpp Entity.h Components.h)
target_sources(BBComponentSystem PRIVATE ${SOURCES})

target_link_libraries(BBComponentSystem PUBLIC EnTT BBScene BBMaths sol2)