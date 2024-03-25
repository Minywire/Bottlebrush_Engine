//
//  Created by Alan Brunet 12/03/2024
//
#pragma once

#include <vector>

/// @author Alan Brunet
/// @brief enum to classify what Data type is 
/// being pushed into the buffer layout
enum class DataType {
	FLOAT, UINT, UCHAR
};

/// @author Alan Brunet
/// @brief used to pass into glVertexAttribPointer() call
/// defines the layout of elements - position, or texcoord, or normals
struct VertexBufferElement
{
	/// number of components per vertex attribute (2D position = 2. 3D position = 3)
	/// must be 1,2,3,4
	unsigned int count;

	/// what GL_TYPE it is, e.g., GL_FLOAT, GL_UNSIGNED_INT
	unsigned int type;

	/// normalised meaning does it need to be converted to scale 0-1
	/// colours being 0-225 needs to be normalised
	/// floats are already normalised
	unsigned char normalised;

	/// @author Alan Brunet
	/// @brief Constructor
	/// @param c Count
	/// @param t Type
	/// @param n Normalised
	VertexBufferElement(unsigned int c, unsigned int t, bool n)
		: count(c), type(t), normalised(n) {}
};

/// @author Alan Brunet
/// @brief This is used to contain a vector array of VertexBuffer Element
/// details that is passed into the API
class VertexBufferLayout
{

public:
	/// Constructor
	VertexBufferLayout(){};

	/// Deconstructor
    virtual ~VertexBufferLayout() = 0{};

	/// @author Alan Brunet
    /// @brief Setting the byte count of types
	virtual unsigned int GetSizeOfType(unsigned int type) = 0;

	/// @author Alan Brunet
    /// @brief For pushing the layout of vertex onto the VertexBufferElement vector
    virtual void Push(unsigned int count, DataType dt) = 0;

	/// @author Alan Brunet
    /// @return member variable m_Elements
    virtual std::vector<VertexBufferElement> GetElements() const& = 0;

	/// @author Alan Brunet
    /// @return member variable m_Stride
    virtual unsigned int GetStride() const = 0;
	
};
