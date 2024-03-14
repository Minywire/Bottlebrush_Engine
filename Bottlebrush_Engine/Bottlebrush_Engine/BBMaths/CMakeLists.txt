cmake_minimum_required(VERSION 3.8)

add_library(
        BBMaths
        STATIC
)

target_include_directories(
        BBMaths
        PUBLIC
        ${PROJECT_SOURCE_DIR}/BBMaths
)

target_sources(
        BBMaths
        PRIVATE
        Maths.cpp Point2D.cpp Point3D.cpp Vector2D.cpp Vector3D.cpp
)
