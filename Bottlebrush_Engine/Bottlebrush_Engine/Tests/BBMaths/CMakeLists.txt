cmake_minimum_required(VERSION 3.8)

add_executable(
        AllTests
        TestMaths.cpp TestPoint2D.cpp TestPoint3D.cpp TestVector2D.cpp
)
target_link_libraries(
        AllTests
        BBMaths
        gtest gtest_main
)
