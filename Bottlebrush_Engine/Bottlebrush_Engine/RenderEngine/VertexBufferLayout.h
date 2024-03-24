//
//  Created by Alan Brunet 12/03/2024
//
#pragma once

#include <vector>

enum class DataType {
	FLOAT, UINT, UCHAR
};

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
      : count(c), type(t), normalised(n) {}
};

/// This is used to contain a vector array of VertexBuffer Element details that is passed into API
/// See child class for push_back() methods
class VertexBufferLayout
{

public:
	/// Constructor, defaulting member variable
	VertexBufferLayout(){};

	/// Deconstructor
    virtual ~VertexBufferLayout(){};

	virtual unsigned int GetSizeOfType(unsigned int type) = 0;

	/// template for pushing the layout of vertex.
    virtual void Push(unsigned int count, DataType dt) = 0;

	/// Returns member variable m_Elements
    virtual std::vector<VertexBufferElement> GetElements() const& = 0;

	/// Returns member variable m_Stride
    virtual unsigned int GetStride() const = 0;
	
};
