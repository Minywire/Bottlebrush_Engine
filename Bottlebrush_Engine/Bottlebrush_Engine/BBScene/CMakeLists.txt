cmake_minimum_required(VERSION 3.8)

add_library(BBScene STATIC)

set(SOURCES Scene.h Scene.cpp)
target_sources(BBScene PRIVATE ${SOURCES})

target_link_libraries(BBScene BBResourceManager RenderEngine EnTT glm) #assimp, camera lib (if any), physics lib, etc.
