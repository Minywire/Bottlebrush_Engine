cmake_minimum_required(VERSION 3.8)

add_library(RenderEngine STATIC)

file(GLOB SOURCES *.cpp *.h)

#set(SOURCES RenderEngine.cpp Shader.cpp OpenGLRenderer.cpp)

add_subdirectory(Platform/OpenGL)

target_sources(RenderEngine PRIVATE ${SOURCES})