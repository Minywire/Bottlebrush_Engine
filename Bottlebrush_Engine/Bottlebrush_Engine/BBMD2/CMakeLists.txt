cmake_minimum_required(VERSION 3.8)

add_library(BBMD2 STATIC)

set(CMAKE_CXX_STANDARD 20)

target_sources(BBMD2 PRIVATE BBMD2.cpp BBMD2.h MD2Model.cpp MD2Model.h MD2Texture.cpp MD2Texture.h)
target_link_libraries(BBMD2 PRIVATE stb glm RenderEngine)