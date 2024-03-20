cmake_minimum_required(VERSION 3.8)

add_library(GLPlatform STATIC)

file(GLOB SOURCES *.cpp *.h)

include_directories(../../)

target_sources(GLPlatform PRIVATE ${SOURCES})
target_link_libraries(GLPlatform RenderEngine)