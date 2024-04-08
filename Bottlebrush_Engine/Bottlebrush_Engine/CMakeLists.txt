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

set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(ASSIMP_NO_EXPORT ON CACHE BOOL "" FORCE)
set(ASSIMP_INSTALL OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_ALL_IMPORTERS_BY_DEFAULT OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_FBX_IMPORTER ON CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_OBJ_IMPORTER ON CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_GLTF_IMPORTER ON CACHE BOOL "" FORCE)
set(ASSIMP_WARNINGS_AS_ERRORS OFF CACHE BOOL "" FORCE)
set(ASSIMP_WARNINGS_AS_ERRORS OFF CACHE BOOL "" FORCE)

add_subdirectory(Vendors/assimp)
add_subdirectory(Vendors/Lua)
add_subdirectory(Vendors/EnTT)
add_subdirectory(Vendors/glfw)
add_subdirectory(Vendors/imGUI)
add_subdirectory(Vendors/imGUI/backends)


#compiler flags
if(MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
  add_definitions(-std=c++20)
else()
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -std=c++20")
  if(NOT WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Weverything")
    set(GLAD_LIBRARIES dl)
  endif()
endif()

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        v1.14.0
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

FetchContent_Declare(
        glm
        GIT_REPOSITORY https://github.com/g-truc/glm.git
        GIT_TAG 	   1.0.1
)
FetchContent_MakeAvailable(glm)
include_directories(${glm_SOURCE_DIR})

# Vendor include directories
include_directories(
        BBComponentSystem BBMaths BBScene BBScript RenderEngine
        include
        Vendors/assimp
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

#copy_directory(${CMAKE_SOURCE_DIR}/Resources ${CMAKE_BINARY_DIR})

# Add source to this project's executable.
add_executable(Bottlebrush_Engine "EntryPoint.cpp" ${VENDORS_SOURCES})

target_link_libraries(Bottlebrush_Engine BBScene BBComponentSystem RenderEngine BBGUI BBMaths BBScript BBAssetImporter glfw ${GLFW_LIBRARIES} LUA)


if (CMAKE_VERSION VERSION_GREATER 3.13)
  set_property(TARGET Bottlebrush_Engine PROPERTY CXX_STANDARD 20)
endif()

add_subdirectory(BBAssetImporter)
add_subdirectory(BBScript)
add_subdirectory(BBScene)
add_subdirectory(BBComponentSystem)
add_subdirectory(BBGUI)
add_subdirectory(BBMaths)
add_subdirectory(RenderEngine)
add_subdirectory(Tests/BBMaths)


FILE(COPY ${CMAKE_SOURCE_DIR}/Bottlebrush_Engine/Resources/ DESTINATION ${CMAKE_BINARY_DIR})
# TODO: Add tests and install targets if needed.
