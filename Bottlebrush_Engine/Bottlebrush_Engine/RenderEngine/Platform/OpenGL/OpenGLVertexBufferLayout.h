//
//  Created by Alan Brunet 12/03/2024
//
#pragma once

#include <vector>
#include <glad/glad.h>
//#include "OpenGLRenderer.h"
#include "OpenGLLogCall.h"
#include <stdexcept>

#include "../../VertexBufferLayout.h"

// manually setting the byte count of GL types
static unsigned int GetSizeOfType(unsigned int type)
{
	switch (type)
	{
	case GL_FLOAT:				return 4;
	case GL_UNSIGNED_INT:		return 4;
	case GL_UNSIGNED_BYTE:		return 1;
	}
	ASSERT(false);
	return 0;
}

class OpenGLVertexBufferLayout : VertexBufferLayout
{
private:

public:
	// template for pushing the layout of vertex.
	template<typename T>
	void Push(unsigned int count)
	{
		// if T type is unmatched
		std::runtime_error(false);
	}

	template<>
	void Push<float>(unsigned int count)
	{
		// float is normalised
		m_Elements.push_back({ count, GL_FLOAT, GL_FALSE });
		m_Stride += count * GetSizeOfType(GL_FLOAT);
	}

	template<>
	void Push<unsigned int>(unsigned int count)
	{
		// unsigned int is normalised
		m_Elements.push_back({ count, GL_UNSIGNED_INT, GL_FALSE });
		m_Stride += count * GetSizeOfType(GL_UNSIGNED_INT);
	}

	template<>
	void Push<unsigned char>(unsigned int count)
	{
		// chars are not normalised
		m_Elements.push_back({ count, GL_UNSIGNED_BYTE, GL_TRUE });
		m_Stride += count * GetSizeOfType(GL_BYTE);
	}
};
