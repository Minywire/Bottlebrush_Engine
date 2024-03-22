cmake_minimum_required(VERSION 3.8)

add_library(GLPlatform STATIC
        OpenGLVertexBufferLayout.cpp)

file(GLOB SOURCES *.cpp *.h)

target_sources(GLPlatform PRIVATE ${SOURCES})