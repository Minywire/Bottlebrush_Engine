//
//  Created by Alan Brunet 12/03/2024
//
#pragma once

#include "VertexArray.h"
#include "OpenGLVertexBuffer.h"

/// forward declaration to avoid link errors
class OpenGLVertexBufferLayout;

/// Needed to hold an array of element buffers
class OpenGLVertexArray : public VertexArray
{
private:
	// ID for Vertex Array
	unsigned int m_RendererID;

public:
	// Constructor
	OpenGLVertexArray();
	// Deconstructor
	~OpenGLVertexArray() override;

	// Adding Vertex and Layout buffers to this Vertex Array
    void AddBuffer(const VertexBuffer& vb, VertexBufferLayout& layout) override;

	// Bind VA buffer to add / draw
	void Bind() const override;
	// Unbind VA
	void Unbind() const override;
};
