cmake_minimum_required(VERSION 3.8)

add_library(LUA STATIC)

file(GLOB LUA_SRC ${PROJECT_SOURCE_DIR}/Vendors/Lua/lua-5.4.6/*)

target_sources(LUA PRIVATE ${LUA_SRC})
#file(GLOB SOURCES lua-5.4.6/*)
#target_sources(LUA PRIVATE ${SOURCES})

