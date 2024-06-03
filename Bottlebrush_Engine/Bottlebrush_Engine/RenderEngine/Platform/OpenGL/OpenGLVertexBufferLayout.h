//
//  Created by Alan 12/03/2024
//
#pragma once

#include <vector>

#include "VertexBufferLayout.h"

/// @author Alan
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
	/// normal.
	unsigned int m_Stride;

 public:
    OpenGLVertexBufferLayout();
	/// Deconstructor
    ~OpenGLVertexBufferLayout() override;

    /// @author Alan
    /// @brief Setting the byte count of types
	unsigned int GetSizeOfType(unsigned int type) override;

	/// @author Alan
    /// @brief For pushing the layout of vertex onto the VertexBufferElement vector.
    /// You must use this for every different element into a vertex.
    /// The order in which you push must match the element data.
    /// If the criteria is not met, don't expect openGL to draw it correctly, or even at all.
    /// e.g., 
    /// call once Push(3, DataType::Float) for vec3 positions
    /// call a second time Push(3, DataType::Float) for vec3 normals
    /// call a third time Push(2, DataType::Float) for vec2 Texture coords
	void Push(unsigned int count, DataType dt) override;

	/// @author Alan
    /// @return member variable m_Elements
	std::vector<VertexBufferElement> GetElements() const & override;

	/// @author Alan
    /// @return member variable m_Stride
	unsigned int GetStride() const override;
};
