# CMakeList.txt : CMake project for Bottlebrush_Engine, include source and define
# project specific logic here.
#
cmake_minimum_required(VERSION 3.8)
project(Bottlebrush_Engine)
add_subdirectory(RenderEngine)

# Add source to this project's executable.
add_executable(Bottlebrush_Engine "EntryPoint.cpp")

target_link_libraries(Bottlebrush_Engine RenderEngine)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Bottlebrush_Engine PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
