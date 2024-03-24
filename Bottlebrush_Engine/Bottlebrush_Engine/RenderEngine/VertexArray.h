//
//  Created by Alan Brunet 12/03/2024
//
#pragma once

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

/// Needed to hold an array of element buffers
class VertexArray
{
protected:
	
public:
	// Deconstructor
	virtual ~VertexArray() = default;

	virtual void AddBuffer(const VertexBuffer& vb, VertexBufferLayout& layout) = 0;

	// Bind Vertex Array buffer to add / draw
	virtual void Bind() const = 0;
	// Unbind Vertex Array buffer
	virtual void Unbind() const = 0;
};
