cmake_minimum_required(VERSION 3.8)

add_library(BBAssetImporter STATIC)

set(SOURCES BBAssetImporter.cpp BBAssetImporter.h)
target_sources(BBAssetImporter PRIVATE ${SOURCES})
target_link_libraries(BBAssetImporter assimp)

