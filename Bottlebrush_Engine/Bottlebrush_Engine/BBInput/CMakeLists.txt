cmake_minimum_required(VERSION 3.8)

add_library(BBInput STATIC)
target_include_directories(BBInput
        PRIVATE BBInput
)
target_sources(BBInput
        PRIVATE Window.cpp
)
target_link_libraries(BBInput
        PRIVATE glfw
)
