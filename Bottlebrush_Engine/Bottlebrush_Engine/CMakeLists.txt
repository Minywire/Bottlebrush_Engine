# CMakeList.txt : CMake project for Bottlebrush_Engine, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (Bottlebrush_Engine "Bottlebrush_Engine.cpp" "Bottlebrush_Engine.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Bottlebrush_Engine PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
