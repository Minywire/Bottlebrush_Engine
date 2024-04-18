cmake_minimum_required(VERSION 3.8)

add_library(stb STATIC
        src/stb_image.cpp
)

target_include_directories(stb
        PRIVATE include
)
