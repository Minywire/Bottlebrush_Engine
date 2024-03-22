//
//  Created by Alan Brunet 12/03/2024
//
#pragma once

/// Buffer for each vertex 
class VertexBuffer
{
protected:
	
public:
	/// Deconstructor
	virtual ~VertexBuffer() = default;

	/// Binding buffer
	virtual void Bind() const = 0;
	/// Unbinding buffer
	virtual void UnBind() const = 0;
};
