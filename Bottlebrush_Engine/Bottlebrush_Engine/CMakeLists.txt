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
add_subdirectory(Vendors/EnTT)
add_subdirectory(Vendors/glfw)
add_subdirectory(Vendors/imGUI)
add_subdirectory(Vendors/imGUI/backends)

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
        Vendors/EnTT
        include
        Vendors/glfw/include
        Vendors/glad/include
        Vendors/imGUI
        Vendors/imGUI/backends #yeah this is a bit messy since it's ALL under imGUI but it wouldn't work otherwise with our folder structure
)

file(GLOB VENDORS_SOURCES Vendors/glad/src/glad.c)
source_group("Vendors" FILES ${VENDORS_SOURCES})

# Add source to this project's executable.
add_executable(Bottlebrush_Engine "EntryPoint.cpp" ${VENDORS_SOURCES})

target_link_libraries(Bottlebrush_Engine BBScene BBComponentSystem RenderEngine BBGUI BBMaths glfw ${GLFW_LIBRARIES})

if (CMAKE_VERSION VERSION_GREATER 3.13)
  set_property(TARGET Bottlebrush_Engine PROPERTY CXX_STANDARD 20)
endif()

add_subdirectory(BBScene)
add_subdirectory(BBComponentSystem)
add_subdirectory(src)
add_subdirectory(BBGUI)
add_subdirectory(RenderEngine)
add_subdirectory(__sample_tests) # Put this here for now just as a reference to some sample tests. @TODO: Delete later.

# TODO: Add tests and install targets if needed.