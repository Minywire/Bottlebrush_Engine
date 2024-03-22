//
//  Created by Alan Brunet 12/03/2024
//
#pragma once

#include <vector>
#include <glad/glad.h>
#include "OpenGLRenderer.h"

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
	/// template for pushing the layout of vertex.
	template<typename T>
	void Push(unsigned int count);

	/// Returns member variable m_Elements
	virtual std::vector<VertexBufferElement> GetElements() const & override;

	/// Returns member variable m_Stride
	virtual unsigned int GetStride() const override;
};
