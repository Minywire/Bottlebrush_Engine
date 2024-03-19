#Created by Marco Garzon Lara 10/02/2024
cmake_minimum_required(VERSION 3.8)

add_library(imGUIbackend STATIC)

#we only really need these realistically
set(SOURCES imgui_impl_glfw.h
            imgui_impl_opengl3.h
            imgui_impl_glfw.cpp
            imgui_impl_opengl3.cpp
    )

target_sources(imGUIbackend PRIVATE ${SOURCES})
target_link_libraries(imGUIbackend glfw)