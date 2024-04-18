cmake_minimum_required(VERSION 3.8)

add_executable(
        EntityFactoryAndScriptTest
        EntityFactoryandScriptTest.cpp
)

target_link_libraries(
        EntityFactoryAndScriptTest
        BBScript
        BBComponentSystem
        EnTT
        gtest gtest_main
)
