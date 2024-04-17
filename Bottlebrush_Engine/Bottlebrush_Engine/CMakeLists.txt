cmake_minimum_required(VERSION 3.8)
project(Bottlebrush_Engine)

include(FetchContent)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_TARGET_NAME ${PROJECT_NAME})

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

option(RP3D_COMPILE_TESTBED OFF)
option(RP3D_COMPILE_TEST OFF)
option(RP3D_PROFILING_ENABLED OFF)
option(RP3D_DOUBLE_PRECISION_ENABLED OFF)

add_subdirectory(Vendors/Lua)
add_subdirectory(Vendors/EnTT)
add_subdirectory(Vendors/glfw)
add_subdirectory(Vendors/imGUI)
add_subdirectory(Vendors/imGUI/backends)
add_subdirectory(Vendors/STB)

#compiler flags
if (MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
    add_definitions(-std=c++20)
else ()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -std=c++20")
    if (NOT WIN32)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Weverything")
        set(GLAD_LIBRARIES dl)
    endif ()
endif ()

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.14.0
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

FetchContent_Declare(
        glm
        GIT_REPOSITORY https://github.com/g-truc/glm.git
        GIT_TAG 1.0.1
)
FetchContent_MakeAvailable(glm)

FetchContent_Declare(
        reactphysics3d
        GIT_REPOSITORY https://github.com/DanielChappuis/reactphysics3d
        GIT_TAG v0.10.0
)
FetchContent_MakeAvailable(reactphysics3d)

FetchContent_Declare(
        assimp
        GIT_REPOSITORY https://github.com/assimp/assimp
        GIT_TAG v5.4.0
)
FetchContent_MakeAvailable(assimp)

# Vendor include directories
include_directories(
        Vendors/Lua
        Vendors/EnTT
        Vendors/glfw/include
        Vendors/glad/include
        Vendors/imGUI
        Vendors/imGUI/backends
        Vendors/Lua/sol2-3.3.0/include/
        Vendors/Lua/lua-5.4.6/
        Vendors/STB/include
        #yeah this is a bit messy since it's ALL under imGUI but it wouldn't work otherwise with our folder structure
)

include_directories(BBComponentSystem)
include_directories(BBGraphics)
include_directories(BBGUI)
include_directories(BBScene)
include_directories(BBScript)
include_directories(RenderEngine)

file(GLOB VENDORS_SOURCES Vendors/glad/src/glad.c)
source_group("Vendors" FILES ${VENDORS_SOURCES})

# Add source to this project's executable.
add_executable(${CMAKE_TARGET_NAME} "EntryPoint.cpp" ${VENDORS_SOURCES})

add_subdirectory(BBComponentSystem)
add_subdirectory(BBGraphics)
add_subdirectory(BBGUI)
add_subdirectory(BBScene)
add_subdirectory(BBScript)
add_subdirectory(RenderEngine)

add_custom_command(
        TARGET ${CMAKE_TARGET_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/Resources $<TARGET_FILE_DIR:${CMAKE_TARGET_NAME}>/Resources
)

target_link_libraries(${CMAKE_TARGET_NAME} PRIVATE assimp)
target_link_libraries(${CMAKE_TARGET_NAME} PRIVATE glfw)
target_link_libraries(${CMAKE_TARGET_NAME} PRIVATE glm)
target_link_libraries(${CMAKE_TARGET_NAME} PRIVATE reactphysics3d)
target_link_libraries(${CMAKE_TARGET_NAME} PRIVATE LUA)

target_link_libraries(${CMAKE_TARGET_NAME} PRIVATE BBComponentSystem)
target_link_libraries(${CMAKE_TARGET_NAME} PRIVATE BBGraphics)
target_link_libraries(${CMAKE_TARGET_NAME} PRIVATE BBGUI)
target_link_libraries(${CMAKE_TARGET_NAME} PRIVATE BBScene)
target_link_libraries(${CMAKE_TARGET_NAME} PRIVATE BBScript)
target_link_libraries(${CMAKE_TARGET_NAME} PRIVATE RenderEngine)

if (CMAKE_VERSION VERSION_GREATER 3.13)
    set_property(TARGET ${CMAKE_TARGET_NAME} PROPERTY CXX_STANDARD 20)
endif ()

add_subdirectory(Tests/EntityFactoryAndScriptTest)
