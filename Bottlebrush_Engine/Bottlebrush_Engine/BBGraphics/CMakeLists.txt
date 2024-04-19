cmake_minimum_required(VERSION 3.8)

add_library(BBGraphics STATIC)
target_link_libraries(BBGraphics PRIVATE RenderEngine)
target_include_directories(BBGraphics
        PRIVATE BBGraphics
)
target_sources(BBGraphics
        PRIVATE Camera.cpp Image.cpp Skybox.cpp Terrain.cpp
)
target_link_libraries(BBGraphics
        PRIVATE assimp
)
target_link_libraries(BBGraphics
        PRIVATE glm
)
target_link_libraries(BBGraphics
        PRIVATE stb
)
target_link_libraries(BBGraphics
        PRIVATE RenderEngine
)
