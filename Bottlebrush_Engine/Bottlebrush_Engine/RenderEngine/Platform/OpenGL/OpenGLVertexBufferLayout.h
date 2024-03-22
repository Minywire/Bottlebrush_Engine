//
//  Created by Alan Brunet 12/03/2024
//
#pragma once

#include <vector>
#include <glad/glad.h>
#include "OpenGLRenderer.h"

#include "VertexBufferLayout.h"

// manually setting the byte count of GL types
static unsigned int GetSizeOfType(unsigned int type)
{
	switch (type)
	{
	case GL_FLOAT:				return 4;
	case GL_UNSIGNED_INT:		return 4;
	case GL_UNSIGNED_BYTE:		return 1;
	}
	assert(false && "This is false.");
	return 0;
}

class OpenGLVertexBufferLayout : public VertexBufferLayout
{
private:
	///
	std::vector<VertexBufferElement> m_Elements;

	/// OpenGL stride (in glVertexAttribPointer())
	/// is the byte space needed for the attribute, i.e, position, texure coord,
	/// colour
	unsigned int m_Stride;

 public:
	/// template for pushing the layout of vertex.
	template<typename T>
	void Push(unsigned int count);

	/// Returns member variable m_Elements
	std::vector<VertexBufferElement> GetElements() const &;

	/// Returns member variable m_Stride
	unsigned int GetStride() const;
};
