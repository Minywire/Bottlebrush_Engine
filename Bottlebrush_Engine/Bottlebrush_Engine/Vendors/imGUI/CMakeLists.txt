#Created by Marco Garzon Lara 10/02/2024
cmake_minimum_required(VERSION 3.8)

#I have no idea how to link this in a consistant manner this is a mess
add_library(imGUI STATIC)

file(GLOB SOURCES "*.cpp" "*.h") #we need ALL of the source files at this level in the imGUI folder hierarchy

target_sources(imGUI PRIVATE ${SOURCES})
target_link_libraries(imGUI imGUIbackend)