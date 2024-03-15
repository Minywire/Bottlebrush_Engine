//
//  Created by Alan Brunet 12/03/2024
//
#pragma once

// Buffer for each vertex 
class VertexBuffer
{
protected:
	// OpenGL ID for buffers
	unsigned int m_RendererID;
public:
	// Deconstructor
	virtual ~VertexBuffer();

	// Binding buffer
	virtual void Bind() const = 0;
	// Unbinding buffer
	virtual void UnBind() const = 0;
};
