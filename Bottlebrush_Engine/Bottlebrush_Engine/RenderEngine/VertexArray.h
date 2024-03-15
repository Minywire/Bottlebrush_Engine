//
//  Created by Alan Brunet 12/03/2024
//
#pragma once

class VertexArray
{
protected:
	// OpenGL ID for VA
	unsigned int m_RendererID;
public:
	// Deconstructor
	virtual ~VertexArray() = default;

	// Bind VA buffer to add / draw
	virtual void Bind() const = 0;
	// Unbind VA
	virtual void Unbind() const = 0;
};
