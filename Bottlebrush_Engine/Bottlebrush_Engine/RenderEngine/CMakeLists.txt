cmake_minimum_required(VERSION 3.8)

add_library(RenderEngine STATIC)

file(GLOB SOURCES RenderEngine.cpp 
	RenderEngine.h 
	GraphicsFactory.h 
	IndexBuffer.h 
	Shader.h 
	Texture.h 
	VertexArray.h 
	VertexBuffer.h 
	VertexBufferLayout.h
    Model.h)

add_subdirectory(Platform/OpenGL)

include_directories(Platform/OpenGL)
target_sources(RenderEngine PRIVATE ${SOURCES})
target_link_libraries(RenderEngine GLPlatform BBAssetImporter)
