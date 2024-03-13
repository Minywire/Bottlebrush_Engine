cmake_minimum_required(VERSION 3.8)

file(GLOB SOURCES *.cpp *.h)

target_sources(RenderEngine PRIVATE ${SOURCES})