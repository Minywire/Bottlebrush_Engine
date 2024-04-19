//
//  Created by Alan 12/03/2024
//
#pragma once

/// @author Alan
/// @brief indexing which positions in the VertexBuffer are being drawn.
/// Saving memory space of referencing positions more than once.
/// IndexBuffer must be called after Vertex Array Object (VAO) has
/// added the vertex buffer and its vertex buffer layout
class IndexBuffer
{
protected:
	

 public:
	/// Default Constructor
	IndexBuffer(){};
	/// Deconstructor
	virtual ~IndexBuffer() = default;

	/// @author Alan
	/// @brief Binding buffer to draw / add
	virtual void Bind() const = 0;

	/// @author Alan
	/// @brief Unbinding buffer
	virtual void Unbind() const = 0;

	/// @author Alan
	/// @brief returning the number of vertex points used
	virtual unsigned int GetCount() const = 0;
};
