//
//  Created by Alan Brunet 12/03/2024
//
#pragma once

#include <vector>
#include <glad/glad.h>
#include "OpenGLRenderer.h"
#include <stdexcept>

// used to pass into glVertexAttribPointer() call
struct OpenGLVertexBufferElement
{
	// number of components per vertex attribute (2D position = 2. 3D position = 3)
	// must be 1,2,3,4
	unsigned int count;

	// what GL_TYPE it is, e.g., GL_FLOAT, GL_UNSIGNED_INT
	unsigned int type;

	// normalised meaning does it need to be converted to scale 0-1
	// colours being 0-225 needs to be normalised
	// floats are already normalised
	unsigned char normalised;

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

	// Constructor
	OpenGLVertexBufferElement(unsigned int c, unsigned int t, bool n)
		: 
		count(c),
		type(t),
		normalised(n)
	{}
};

class OpenGLVertexBufferLayout
{
private:
	std::vector<OpenGLVertexBufferElement> m_Elements;

	// OpenGL stride (in glVertexAttribPointer()) 
	// is the byte space needed for the attribute, i.e, position, texure coord, colour
	unsigned int m_Stride;

public:
	// Constructor
	OpenGLVertexBufferLayout()
		: m_Stride(0) {}

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
		m_Stride += count * OpenGLVertexBufferElement::GetSizeOfType(GL_FLOAT);
	}

	template<>
	void Push<unsigned int>(unsigned int count)
	{
		// unsigned int is normalised
		m_Elements.push_back({ count, GL_UNSIGNED_INT, GL_FALSE });
		m_Stride += count * OpenGLVertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT);
	}

	template<>
	void Push<unsigned char>(unsigned int count)
	{
		// chars are not normalised
		m_Elements.push_back({ count, GL_UNSIGNED_BYTE, GL_TRUE });
		m_Stride += count * OpenGLVertexBufferElement::GetSizeOfType(GL_BYTE);
	}

	inline const std::vector<OpenGLVertexBufferElement> GetElements() const& { return m_Elements;  }
	inline unsigned int GetStride() const { return m_Stride; }
};
