//
//  Created by Alan Brunet 12/03/2024
//
#pragma once

/// @author Alan Brunet
/// @brief indexing which positions in the VertexBuffer are being drawn.
/// Saving memory space of referencing positions more than once.
/// IB must be called after Vertex Array Object (VAO) has been set up with VB and VBL
class IndexBuffer
{
protected:
	

 public:
	/// Default Constructor
	IndexBuffer(){};
	/// Constructor
    IndexBuffer(const unsigned int* data, unsigned int count) {};
	/// Deconstructor
	~IndexBuffer(){};

	/// @author Alan Brunet
	/// @brief Binding buffer to draw / add
	virtual void Bind() const = 0;

	/// @author Alan Brunet
	/// @brief Unbinding buffer
	virtual void Unbind() const = 0;

	/// @author Alan Brunet
	/// @brief returning the number of vertex points used
	virtual unsigned int GetCount() const = 0;
};
