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

public:
	// Constructor
	OpenGLVertexArray();
	// Deconstructor
	virtual ~OpenGLVertexArray() override;

	// Adding Vertex and Layout buffers to this Vertex Array
    virtual void AddBuffer(const VertexBuffer& vb, VertexBufferLayout& layout) override;

	// Bind VA buffer to add / draw
	virtual void Bind() const override;
	// Unbind VA
	virtual void Unbind() const override;
};
