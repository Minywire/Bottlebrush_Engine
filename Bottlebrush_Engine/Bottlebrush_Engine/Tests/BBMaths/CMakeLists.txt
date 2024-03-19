cmake_minimum_required(VERSION 3.8)

add_executable(
        TestBBMaths
        TestMaths.cpp TestPoint2D.cpp TestPoint3D.cpp TestVector2D.cpp TestVector3D.cpp TestVector4D.cpp
)
target_link_libraries(
        TestBBMaths
        BBMaths
        gtest gtest_main
)
