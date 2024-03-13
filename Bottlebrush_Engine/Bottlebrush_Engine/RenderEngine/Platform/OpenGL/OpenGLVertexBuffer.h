//
//  Created by Alan Brunet 12/03/2024
//
#pragma once

// Buffer for each vertex 
class OpenGLVertexBuffer
{
private:
	// OpenGL ID for buffers
	unsigned int m_RendererID;
public:
	// Constructor
	OpenGLVertexBuffer(const void* data, unsigned int size);
	// Deconstructor
	~OpenGLVertexBuffer();

	// Binding buffer
	void Bind() const;
	// Unbinding buffer
	void UnBind() const;
};
