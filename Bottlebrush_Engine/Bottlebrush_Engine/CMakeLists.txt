# CMakeList.txt : CMake project for Bottlebrush_Engine, include source and define
# project specific logic here.
#
cmake_minimum_required(VERSION 3.8)
project(Bottlebrush_Engine)

set(CMAKE_CXX_STANDARD 20)

# GLFW options
option(GLFW_BUILD_DOCS OFF)
option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)

add_subdirectory(BBGUI)
add_subdirectory(RenderEngine)
add_subdirectory(Vendors)

#compiler flags
if(MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
else()
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -std=c++11")
  if(NOT WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Weverything")
    set(GLAD_LIBRARIES dl)
  endif()
endif()

# Vendor include directories
include_directories(
        Vendors/glfw/include
        Vendors/glad/include
        Vendors/imGUI
        Vendors/imGUI/backends #yeah this is a bit messy since it's ALL under imGUI but it wouldn't work otherwise with our folder structure
)

# Add source to this project's executable.
add_executable(${PROJECT_NAME} "EntryPoint.cpp")

target_link_libraries(${PROJECT_NAME} RenderEngine BBGUI glfw ${GLFW_LIBRARIES} glad)

if (CMAKE_VERSION VERSION_GREATER 3.13)
  set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.