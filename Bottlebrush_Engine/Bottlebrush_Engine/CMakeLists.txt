# CMakeList.txt : CMake project for Bottlebrush_Engine, include source and define
# project specific logic here.
#
cmake_minimum_required(VERSION 3.8)
project(Bottlebrush_Engine)

include(FetchContent)

set(CMAKE_CXX_STANDARD 20)

# GLFW options
option(GLFW_BUILD_DOCS OFF)
option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)
option(RP3D_COMPILE_TESTBED OFF)
option(RP3D_COMPILE_TEST OFF)
option(RP3D_PROFILING_ENABLED OFF)
option(RP3D_DOUBLE_PRECISION_ENABLED OFF)

add_subdirectory(Vendors/Lua)
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

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.14.0
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
include_directories(${googletest_SOURCE_DIR}/include ${googletest_SOURCE_DIR})

FetchContent_Declare(
        glm
        GIT_REPOSITORY https://github.com/g-truc/glm.git
        GIT_TAG 1.0.1
)
FetchContent_MakeAvailable(glm)
include_directories(${glm_SOURCE_DIR})

FetchContent_Declare(
        reactphysics3d
        GIT_REPOSITORY https://github.com/DanielChappuis/reactphysics3d
        GIT_TAG v0.10.0
)
FetchContent_MakeAvailable(reactphysics3d)
include_directories(${reactphysics3d_SOURCE_DIR}/include ${reactphysics3d_SOURCE_DIR})

# Vendor include directories
include_directories(
        BBComponentSystem BBMaths BBScene BBScript RenderEngine
        Vendors/Lua
        Vendors/EnTT
        Vendors/glfw/include
        Vendors/glad/include
        Vendors/imGUI
        Vendors/imGUI/backends
        Vendors/Lua/sol2-3.3.0/include/sol
        #yeah this is a bit messy since it's ALL under imGUI but it wouldn't work otherwise with our folder structure
)

file(GLOB VENDORS_SOURCES Vendors/glad/src/glad.c)
source_group("Vendors" FILES ${VENDORS_SOURCES})

# Add source to this project's executable.
add_executable(Bottlebrush_Engine "EntryPoint.cpp" ${VENDORS_SOURCES})

target_link_libraries(Bottlebrush_Engine PRIVATE BBScene BBComponentSystem RenderEngine BBGUI BBMaths BBScript glfw ${GLFW_LIBRARIES} LUA)
target_link_libraries(Bottlebrush_Engine PRIVATE glm)
target_link_libraries(Bottlebrush_Engine PRIVATE reactphysics3d)


if (CMAKE_VERSION VERSION_GREATER 3.13)
  set_property(TARGET Bottlebrush_Engine PROPERTY CXX_STANDARD 20)
endif()

add_subdirectory(BBScript)
add_subdirectory(BBScene)
add_subdirectory(BBComponentSystem)
add_subdirectory(BBGUI)
add_subdirectory(BBMaths)
add_subdirectory(RenderEngine)
add_subdirectory(Tests/BBMaths)
