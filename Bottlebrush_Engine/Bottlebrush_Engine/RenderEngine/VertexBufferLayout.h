//
//  Created by Alan 12/03/2024
//
#pragma once

#include <vector>

/// @author Alan
/// @brief enum to classify what Data type is 
/// being pushed into the buffer layout
enum class DataType {
	FLOAT, UINT, UCHAR
};

/// @author Alan
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

	/// @author Alan
	/// @brief Constructor
	/// @param c Count
	/// @param t Type
	/// @param n Normalised
	VertexBufferElement(unsigned int c, unsigned int t, bool n)
		: count(c), type(t), normalised(n) {}
};

/// @author Alan
/// @brief This is used to contain a vector array of VertexBuffer Element
/// details that is passed into the API
class VertexBufferLayout
{

public:
    /// Constructor
    VertexBufferLayout(){};

    /// Deconstructor
    virtual ~VertexBufferLayout() = default;

    /// @author Alan
    /// @brief Setting the byte count of types
    virtual unsigned int GetSizeOfType(unsigned int type) = 0;

    /// @author Alan
    /// @brief For pushing the layout of vertex onto the VertexBufferElement vector.
    /// You must use this for every different element into a vertex.
    /// The order in which you push must match the element data.
    /// If the criteria is not met, don't expect openGL to draw it correctly, or even at all.
    /// e.g., 
    /// call once Push(3, DataType::Float) for vec3 positions
    /// call a second time Push(3, DataType::Float) for vec3 normals
    /// call a third time Push(2, DataType::Float) for vec2 Texture coords
    virtual void Push(unsigned int count, DataType dt) = 0;

    /// @author Alan
    /// @return member variable m_Elements
    virtual std::vector<VertexBufferElement> GetElements() const& = 0;

    /// @author Alan
    /// @return member variable m_Stride
    virtual unsigned int GetStride() const = 0;
	
};
