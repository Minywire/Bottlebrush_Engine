cmake_minimum_required(VERSION 3.8)

add_library(RenderEngine STATIC)

file(GLOB SOURCES RenderEngine.cpp)

add_subdirectory(Platform/OpenGL)

include_directories(Platform/OpenGL)
target_sources(RenderEngine PRIVATE ${SOURCES})
target_link_libraries(RenderEngine PRIVATE GLPlatform)
target_link_libraries(RenderEngine PUBLIC assimp)
target_link_libraries(RenderEngine PRIVATE glm)
target_link_libraries(RenderEngine PRIVATE BBGraphics)
