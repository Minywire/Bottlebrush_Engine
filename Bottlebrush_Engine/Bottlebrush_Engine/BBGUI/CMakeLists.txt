cmake_minimum_required(VERSION 3.8)

add_library(BBGUI STATIC)

set(SOURCES BBGUI.h BBGUI.cpp)
target_sources(BBGUI PRIVATE ${SOURCES})

target_link_libraries(BBGUI imGUI glfw)


