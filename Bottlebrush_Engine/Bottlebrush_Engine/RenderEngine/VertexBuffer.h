//
//  Created by Alan Brunet 12/03/2024
//
#pragma once

/// @author Alan Brunet
/// @brief Buffer data for each vertex. 
/// It must have positions (2D or 3D), it can also have normals and texcoords / colour
class VertexBuffer
{
protected:
	

public:
	/// Deconstructor
	~VertexBuffer(){};

	/// @author Alan Brunet
    /// @brief Binding buffer
	virtual void Bind() const = 0;

	/// @author Alan Brunet
    /// @brief Unbinding buffer
	virtual void Unbind() const = 0;
};
