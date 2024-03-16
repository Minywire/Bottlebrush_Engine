//
//  Created by Alan Brunet 12/03/2024
//
#pragma once

#include "VertexArray.h"
#include "OpenGLVertexBuffer.h"

class OpenGLVertexBufferLayout;

class OpenGLVertexArray : public VertexArray
{
private:

public:
	// Constructor
	OpenGLVertexArray();
	// Deconstructor
	virtual ~OpenGLVertexArray() override;

	// Adding Vertex and Layout buffers to this Vertex Array
	void AddBuffer(const OpenGLVertexBuffer& vb, OpenGLVertexBufferLayout& layout);

	// Bind VA buffer to add / draw
	void Bind() const;
	// Unbind VA
	void Unbind() const;
};
