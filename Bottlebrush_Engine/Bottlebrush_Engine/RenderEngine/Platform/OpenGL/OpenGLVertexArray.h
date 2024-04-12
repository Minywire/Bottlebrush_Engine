//
//  Created by Alan Brunet 12/03/2024
//
#pragma once

#include "VertexArray.h"
#include "OpenGLVertexBuffer.h"

/// @author Alan Brunet
/// @brief Object to hold Vertex and Index Buffers.
/// Adds Vertex Buffer.
/// But IndexObject must be called after Layout has been pushed
class OpenGLVertexArray : public VertexArray
{
private:
	// ID for Vertex Array
	unsigned int m_RendererID;

public:
	/// @author Alan Brunet
    /// @brief Constructor that generates a Vertex array on the Graphics API
	OpenGLVertexArray();
	// Deconstructor
	~OpenGLVertexArray() override;

	/// @author Alan Brunet
    /// @brief Adds the vertex Buffer and applies its layout
    /// @param vb Vertex Buffer that contains all vertex data
    /// @see class VertexBuffer
	/// @param layout is how the Vertex Bufffer contains its data, its count, type, and if its normalised.
	/// @see class VertexBufferLayout
    void AddBuffer(const VertexBuffer& vb, VertexBufferLayout& layout) override;

	/// @author Alan Brunet
    /// @brief Bind Vertex Array buffer to add / draw
	void Bind() const override;

	/// @author Alan Brunet
    /// @brief Unbind Vertex Array buffer
	void Unbind() const override;
};
