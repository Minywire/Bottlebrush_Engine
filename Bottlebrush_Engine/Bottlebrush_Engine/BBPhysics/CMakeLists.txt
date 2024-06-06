cmake_minimum_required(VERSION 3.8)

add_library(BBPhysics STATIC)
target_include_directories(BBPhysics
        PRIVATE BBPhysics
)
target_sources(BBPhysics
        PRIVATE BBox.cpp
        PRIVATE Collider.cpp
        PRIVATE CollisionMgr.cpp
)
target_link_libraries(BBPhysics
        PRIVATE glm
)