cmake_minimum_required(VERSION 3.8)

add_library(BBGraphics STATIC)
target_link_libraries(BBGraphics PRIVATE RenderEngine)
target_include_directories(BBGraphics
        PRIVATE Camera.h
)
target_sources(BBGraphics
        PRIVATE Camera.cpp
        Skybox.cpp
)
target_link_libraries(BBGraphics
        PRIVATE glm
)
