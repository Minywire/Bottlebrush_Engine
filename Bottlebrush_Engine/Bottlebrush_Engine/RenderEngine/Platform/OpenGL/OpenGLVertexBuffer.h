//
//  Created by Alan 12/03/2024
//
#pragma once

#include "VertexBuffer.h"

/// @author Alan
/// @brief Buffer data for each vertex.
/// It must have positions (2D or 3D), it can also have normals and texcoords /
/// colour
class OpenGLVertexBuffer : public VertexBuffer
{
private:
	/// OpenGL ID for buffers
	unsigned int m_RendererID;
public:
	/// @author Alan
    /// @brief Constructor that generates the buffer and sets the data.
    /// Called from GraphicsFractory when creating
    /// @param data is the stream on data of vertex
	/// @param size is the Vertex Count * sizeof(float).
	OpenGLVertexBuffer(const void* data, unsigned int size);

	/// @author Alan
    /// @brief Deconstructor
	~OpenGLVertexBuffer() override;

	/// @author Alan
    /// @brief Binding buffer
	void Bind() const override;

    /// @author Alan
    /// @brief Unbinding buffer
	void Unbind() const override;
};
