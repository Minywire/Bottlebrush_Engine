#Created by Marco Garzon Lara 10/02/2024
cmake_minimum_required(VERSION 3.8)

#I have no idea how to link this in a consistant manner this is a mess
add_library(imGUI STATIC)

set(SOURCES imconfig.h
            imgui.h
            imgui_internal.h
            imstb_rectpack.h
            imstb_textedit.h
            imstb_truetype.h
            imgui.cpp
            imgui_demo.cpp
            imgui_widgets.cpp
            imgui_tables.cpp
            imgui_draw.cpp
    )

#I hope this is the right OpenGL version...
set(BACKEND backends/imgui_impl_glfw.h
            backends/imgui_impl_opengl3.h
            backends/imgui_impl_glfw.cpp
            backends/imgui_impl_opengl3.cpp
    )

target_sources(imGUI PRIVATE ${SOURCES} ${BACKEND})
