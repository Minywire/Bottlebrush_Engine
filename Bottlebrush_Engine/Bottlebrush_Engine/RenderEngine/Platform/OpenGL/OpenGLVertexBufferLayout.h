//
//  Created by Alan Brunet 12/03/2024
//
#pragma once

#include <vector>
#include <glad/glad.h>
#include "OpenGLRenderer.h"
#include <stdexcept>

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

class OpenGLVertexBufferLayout : VertexBufferLayout
{
private:

public:
	/// template for pushing the layout of vertex.
	template<typename T>
	void Push(unsigned int count);

	/// Returns member variable m_Elements
	inline std::vector<VertexBufferElement> GetElements() const &;

	/// Returns member variable m_Stride
	inline unsigned int GetStride() const;
};
