//
//  Created by Alan Brunet 12/03/2024
//
#pragma once

#include "IndexBuffer.h"

// indexing which positions in the VertexBuffer are being drawn.
// Saving memory space of referencing positions more than once.
// IB must be called after Vertex Array Object (VAO) has been set up with VB and VBL
class OpenGLIndexBuffer : public IndexBuffer
{
private:
	// OpenGL ID for IndexBuffer
	unsigned int m_RendererID;
	// How many vertex points are being used
	unsigned int m_Count;
public:
	// Constructor
	OpenGLIndexBuffer(const unsigned int* data, unsigned int count);
	// Deconstructor
	~OpenGLIndexBuffer();

	// Binding buffer to draw / add
	virtual void Bind() const override;
	// Unbinding buffer
	virtual void UnBind() const override;
};
