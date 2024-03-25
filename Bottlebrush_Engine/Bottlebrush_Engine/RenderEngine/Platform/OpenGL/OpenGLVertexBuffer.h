//
//  Created by Alan Brunet 12/03/2024
//
#pragma once

#include "VertexBuffer.h"

/// @author Alan Brunet
/// @brief Buffer data for each vertex.
/// It must have positions (2D or 3D), it can also have normals and texcoords /
/// colour
class OpenGLVertexBuffer : public VertexBuffer
{
private:
	/// OpenGL ID for buffers
	unsigned int m_RendererID;
public:
	/// @author Alan Brunet
    /// @brief Constructor that generates the buffer and sets the data.
    /// Called from GraphicsFractory when creating
    /// @param data is the stream on data of vertex
	/// @param size is the Vertex Count * the Vertex data size * sizeof(float).
	OpenGLVertexBuffer(const void* data, unsigned int size);

	/// @author Alan Brunet
    /// @brief Deconstructor
	~OpenGLVertexBuffer() override;

	/// @author Alan Brunet
    /// @brief Binding buffer
	void Bind() const override;

    /// @author Alan Brunet
    /// @brief Unbinding buffer
	void UnBind() const override;
};
