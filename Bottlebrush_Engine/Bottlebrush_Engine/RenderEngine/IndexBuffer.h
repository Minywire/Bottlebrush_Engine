//
//  Created by Alan Brunet 12/03/2024
//
#pragma once

/// indexing which positions in the VertexBuffer are being drawn.
/// Saving memory space of referencing positions more than once.
/// IB must be called after Vertex Array Object (VAO) has been set up with VB and VBL
class IndexBuffer
{
protected:
	/// OpenGL ID for IndexBuffer
	unsigned int m_RendererID;
	/// How many vertex points are being used
	unsigned int m_Count;
public:
	/// do not use this constructor
	IndexBuffer() = default;
	/// Constructor
	IndexBuffer(const unsigned int* data, unsigned int count);
	/// Deconstructor
	virtual ~IndexBuffer() = default;

	/// Binding buffer to draw / add
	virtual void Bind() const = 0;
	/// Unbinding buffer
	virtual void UnBind() const = 0;

	/// returning the number of vertex points used
	inline unsigned int GetCount() const { return m_Count; }
};
