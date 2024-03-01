cmake_minimum_required(VERSION 3.8)

add_library(glad STATIC)
target_sources(glad PRIVATE src/glad.c)