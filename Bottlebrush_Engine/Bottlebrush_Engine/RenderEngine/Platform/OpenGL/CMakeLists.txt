cmake_minimum_required(VERSION 3.8)

add_library(GLPlatform STATIC)

file(GLOB SOURCES 
	OpenGLIndexBuffer.h OpenGLIndexBuffer.cpp 
	OpenGLRenderer.h OpenGLRenderer.cpp
	OpenGLShader.h OpenGLShader.cpp
	OpenGLTexture.h OpenGLTexture.cpp
	OpenGLVertexArray.h OpenGLVertexArray.cpp
	OpenGLVertexBuffer.h OpenGLVertexBuffer.cpp
	OpenGLVertexBufferLayout.h OpenGLVertexBufferLayout.cpp
	OpenGLModel.cpp OpenGLModel.h
	OpenGLMesh.cpp OpenGLMesh.h
	OpenGLFrameBuffer.cpp OpenGLFrameBuffer.h
	)

target_sources(GLPlatform PRIVATE ${SOURCES})
target_link_libraries(GLPlatform PUBLIC assimp)
target_link_libraries(GLPlatform PRIVATE glm)
target_link_libraries(GLPlatform PRIVATE BBGraphics)
target_link_libraries(GLPlatform PRIVATE glad)
