cmake_minimum_required(VERSION 3.8)

add_library(BBScript STATIC)

target_sources(BBScript PRIVATE BBScript.cpp BBScript.h)
target_link_libraries(BBScript sol2 LUA)
target_include_directories(BBScript PRIVATE ${PROJECT_SOURCE_DIR}/Vendors/Lua/lua-5.4.6/)