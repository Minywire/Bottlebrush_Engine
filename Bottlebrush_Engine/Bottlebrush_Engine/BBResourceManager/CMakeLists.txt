cmake_minimum_required(VERSION 3.8)

add_library(BBResourceManager STATIC)

set(CMAKE_CXX_STANDARD 20)

target_sources(BBResourceManager PRIVATE BBResourceManager.cpp BBResourceManager.hpp)

target_link_libraries(BBResourceManager PRIVATE EnTT BBComponentSystem glm RenderEngine BBAI BBGraphics BBMD2)

