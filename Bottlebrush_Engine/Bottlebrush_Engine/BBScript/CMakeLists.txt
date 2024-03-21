cmake_minimum_required(VERSION 3.8)

add_library(BBSCRIPT STATIC)

target_sources(BBSCRIPT PRIVATE BBScript.cpp BBScript.h)

target_link_libraries(BBSCRIPT SOL_VENDOR)