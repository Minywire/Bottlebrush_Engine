cmake_minimum_required(VERSION 3.8)

add_library(GLAD STATIC)

include_directories(src)
include_directories(include/)

target_sources(GLAD PRIVATE src/glad.c include/glad/glad.h include/KHR/khrplatform.h)