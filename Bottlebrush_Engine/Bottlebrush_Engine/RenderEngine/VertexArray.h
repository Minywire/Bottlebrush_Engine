//
//  Created by Alan Brunet 12/03/2024
//
#pragma once

/// Needed to hold an array of element buffers
class VertexArray
{
protected:
	// ID for Vertex Array
	unsigned int m_RendererID;
public:
	// Deconstructor
	virtual ~VertexArray() = default;

	// Bind Vertex Array buffer to add / draw
	virtual void Bind() const = 0;
	// Unbind Vertex Array buffer
	virtual void Unbind() const = 0;
};
