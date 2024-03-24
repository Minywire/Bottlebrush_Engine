//
//  Created by Alan Brunet 12/03/2024
//
#pragma once

#include "VertexBuffer.h"

// Buffer for each vertex 
class OpenGLVertexBuffer : public VertexBuffer
{
private:
	// OpenGL ID for buffers
	unsigned int m_RendererID;
public:
	// Constructor
	OpenGLVertexBuffer(const void* data, unsigned int size);
	// Deconstructor
	~OpenGLVertexBuffer() override;

	// Binding buffer
	void Bind() const override;
	// Unbinding buffer
	void UnBind() const override;
};
