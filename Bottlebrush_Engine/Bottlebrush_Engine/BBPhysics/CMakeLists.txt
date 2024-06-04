cmake_minimum_required(VERSION 3.8)

add_library(BBPhysics STATIC)
target_include_directories(BBPhysics
        PRIVATE BBPhysics
)
target_sources(BBPhysics
        PRIVATE PhysicsBody.cpp
        PRIVATE PhysicsMgr.cpp
)
target_link_libraries(BBPhysics
        PRIVATE glm
        PRIVATE reactphysics3d
)

add_executable(physics-test physics_test.cpp)
target_link_libraries(physics-test
        PRIVATE glm
        PRIVATE reactphysics3d
        PRIVATE BBPhysics
)