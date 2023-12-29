cmake_minimum_required(VERSION 3.8)

add_library(RenderEngine RenderEngine.cpp RenderEngine.cpp)
target_sources(RenderEngine PRIVATE RenderEngine.cpp Shader.cpp)