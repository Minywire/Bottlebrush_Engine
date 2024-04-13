//
//  Created by Alan Brunet 12/03/2024
//
#pragma once

#include <vector>

#include "VertexBufferLayout.h"

/// @author Alan Brunet
/// @brief This is used to contain a vector array of VertexBuffer Element
/// details that is passed into API
/// @see glVertexAttribPointer() https://docs.gl/gl4/glVertexAttribPointer
class OpenGLVertexBufferLayout : public VertexBufferLayout
{
private:
	/// vector of buffer elements
	/// @see struct VertexBufferElement
	std::vector<VertexBufferElement> m_Elements;

	/// OpenGL stride (in glVertexAttribPointer())
	/// is the byte space needed for the attribute, i.e, position, texure coord,
	/// colour
	unsigned int m_Stride;

 public:
    OpenGLVertexBufferLayout();
	/// Deconstructor
    ~OpenGLVertexBufferLayout() override;

    /// @author Alan Brunet
    /// @brief Setting the byte count of types
	unsigned int GetSizeOfType(unsigned int type) override;

	/// @author Alan Brunet
    /// @brief For pushing the layout of vertex onto the VertexBufferElement vector
	void Push(unsigned int count, DataType dt) override;

	/// @author Alan Brunet
    /// @return member variable m_Elements
	std::vector<VertexBufferElement> GetElements() const & override;

	/// @author Alan Brunet
    /// @return member variable m_Stride
	unsigned int GetStride() const override;
};
