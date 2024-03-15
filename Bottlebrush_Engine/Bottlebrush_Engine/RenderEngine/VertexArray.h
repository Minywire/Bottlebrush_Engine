//
//  Created by Alan Brunet 12/03/2024
//
#pragma once

#include "VertexBuffer.h"

class VertexBufferLayout;

class VertexArray
{
protected:
	// OpenGL ID for VA
	unsigned int m_RendererID;
public:
	// Deconstructor
	virtual ~VertexArray() = default;

	// Adding Vertex and Layout buffers to this Vertex Array
	virtual void AddBuffer(const VertexBuffer& vb, VertexBufferLayout& layout) = 0;

	// Bind VA buffer to add / draw
	virtual void Bind() const = 0;
	// Unbind VA
	virtual void Unbind() const = 0;
};
