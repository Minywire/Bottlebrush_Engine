//
//  Created by Alan Brunet 12/03/2024
//
#pragma once

#include <vector>
#include "RenderEngine.h"
#include <stdexcept>

/// used to pass into glVertexAttribPointer() call
struct VertexBufferElement
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

	// Constructor
	VertexBufferElement(unsigned int c, unsigned int t, bool n)
		: 
		count(c),
		type(t),
		normalised(n)
	{}
};

/// This is used to contain a vector array of VertexBuffer Element details that is passed into API
/// See child class for push_back() methods
class VertexBufferLayout
{
protected:
	/// 
	std::vector<VertexBufferElement> m_Elements;

	/// OpenGL stride (in glVertexAttribPointer()) 
	/// is the byte space needed for the attribute, i.e, position, texure coord, colour
	unsigned int m_Stride;

public:
	/// Constructor, defaulting member variable
	VertexBufferLayout()
		: m_Stride(0) {}

	
};
