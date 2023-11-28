# CMakeList.txt : CMake project for Bottlebrush_Engine, include source and define
# project specific logic here.
#
cmake_minimum_required(VERSION 3.8)
project(Bottlebrush_Engine)

# GLFW options
option(GLFW_BUILD_DOCS OFF)
option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)
add_subdirectory(Vendors/glfw)

if(MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
else()
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -std=c++11")
  if(NOT WIN32)
    set(GLAD_LIBRARIES dl)
  endif()
endif()

# Vendor include directories
include_directories(Vendors/glfw/include
        Vendors/glad/include)


file(GLOB VENDORS_SOURCES Vendors/glad/src/glad.c)
source_group("Vendors" FILES ${VENDORS_SOURCES})

add_subdirectory(RenderEngine)

# Add source to this project's executable.
add_executable(Bottlebrush_Engine "EntryPoint.cpp" ${VENDORS_SOURCES})

target_link_libraries(Bottlebrush_Engine RenderEngine glfw ${GLFW_LIBRARIES})

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Bottlebrush_Engine PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
