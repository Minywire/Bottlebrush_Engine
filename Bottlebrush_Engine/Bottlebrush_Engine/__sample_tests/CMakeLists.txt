# @TODO: Put everything here in either root CMakeLists.txt or root tests folder later on once formal tests are set up.
cmake_minimum_required(VERSION 3.8)

project(sample_tests)

include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        v1.14.0
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(sample_tests sample1.cpp sample1_unittest.cpp)
target_link_libraries(sample_tests gtest gtest_main)
