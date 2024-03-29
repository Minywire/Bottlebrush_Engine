cmake_minimum_required(VERSION 3.8)

add_executable(
        TestBBMaths
        TestMaths.cpp
)
target_link_libraries(
        TestBBMaths
        BBMaths
        gtest gtest_main
)
