//
//  Created by Alan Brunet 12/03/2024
//
#pragma once

#include "../../VertexArray.h"

class OpenGLVertexArray : VertexArray
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
	void Bind() const;
	// Unbind VA
	void Unbind() const;
};
