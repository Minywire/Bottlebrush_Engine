cmake_minimum_required(VERSION 3.8)

add_executable(
        ResourceCreationTests
        ResourceCreationTests.cpp
)

target_link_libraries(
        ResourceCreationTests
        BBScene
        BBResourceManager
        BBComponentSystem
        EnTT
        glfw
        gtest gtest_main
)
