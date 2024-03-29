//
//  Created by Alan Brunet 12/03/2024
//
#pragma once

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

/// @author Alan Brunet
/// @brief Object to hold Vertex and Index Buffers. 
/// Adds Vertex Buffer. 
/// But IndexObject must be called after Layout has been pushed
class VertexArray
{
protected:
	
public:
	/// Deconstructor
	~VertexArray()= default;

	/// @author Alan Brunet
    /// @brief Adds the vertex Buffer and applies its layout
    /// @param vb Vertex Buffer that contains all vertex data
    /// @see class VertexBuffer
	/// @param layout is how the Vertex Bufffer contains its data, its count, type, and if its normalised.
	/// @see class VertexBufferLayout
	virtual void AddBuffer(const VertexBuffer& vb, VertexBufferLayout& layout) = 0;

	/// @author Alan Brunet
    /// @brief Bind Vertex Array buffer to add / draw
	virtual void Bind() const = 0;

	/// @author Alan Brunet
    /// @brief Unbind Vertex Array buffer
	virtual void Unbind() const = 0;
};
