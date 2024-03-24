//
//  Created by Alan Brunet 12/03/2024
//
#pragma once

#include <vector>

//#include "OpenGLRenderer.h"

#include "VertexBufferLayout.h"

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
    OpenGLVertexBufferLayout();
	/// Deconstructor
    virtual ~OpenGLVertexBufferLayout() override;
	// manually setting the byte count of GL types
	virtual unsigned int GetSizeOfType(unsigned int type) override;

	/// template for pushing the layout of vertex.
	virtual void Push(unsigned int count, DataType dt) override;

	/// Returns member variable m_Elements
	virtual std::vector<VertexBufferElement> GetElements() const & override;

	/// Returns member variable m_Stride
	virtual unsigned int GetStride() const override;
};
