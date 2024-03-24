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
	

 public:
	/// Default Constructor
	IndexBuffer(){};

	/// Deconstructor/// Constructor
    IndexBuffer(const unsigned int* data, unsigned int count) {};

	virtual ~IndexBuffer(){};

	/// Binding buffer to draw / add
	virtual void Bind() const = 0;
	/// Unbinding buffer
	virtual void UnBind() const = 0;

	/// returning the number of vertex points used
	virtual unsigned int GetCount() const = 0;
};
