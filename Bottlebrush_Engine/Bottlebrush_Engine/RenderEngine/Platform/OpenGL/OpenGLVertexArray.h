//
//  Created by Alan Brunet 12/03/2024
//
#pragma once

#include "OpenGLVertexBuffer.h"

class OpenGLVertexBufferLayout;

class OpenGLVertexArray
{
private:
	// OpenGL ID for VA
	unsigned int m_RendererID;
public:
	// Constructor
	OpenGLVertexArray();
	// Deconstructor
	~OpenGLVertexArray();

	// Adding Vertex and Layout buffers to this Vertex Array
	void AddBuffer(const OpenGLVertexBuffer& vb, OpenGLVertexBufferLayout& layout);

	// Bind VA buffer to add / draw
	void Bind() const;
	// Unbind VA
	void Unbind() const;
};
