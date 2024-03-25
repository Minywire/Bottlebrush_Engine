//
// Created by Marco Garzon Lara on 27/11/2023.
// Edited by Alan Brunet on 16/03/24
//
#pragma once

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

/// @author Alan Brunet
/// @brief Base class for rendering objects. It contains member pointers to a Vertex Array,
/// Vertex Buffer, Index Buffer, and a Shader
class RenderEngine
{
protected:
	std::unique_ptr<VertexArray> m_VA;
	std::unique_ptr<VertexBuffer> m_VB;
    std::unique_ptr<IndexBuffer> m_IB;
    std::unique_ptr<VertexBufferLayout> m_VBL;
	std::unique_ptr<Shader> m_SH;
public:
    RenderEngine(){};
	virtual ~RenderEngine(){};

	/// will be deleted at some point, this is just for demostration of setting up render engine
	void TestSetupValues();

	/// @author Alan Brunet
	/// @brief glClearColor()
    virtual void Clear() const = 0;

	/// @author Alan Brunet
	/// @brief This needs to be called within the draw loop. Uses member pointers to bind a Vertex Array (which has a Vertex Buffer, its layout and Index Buffer bound)
	/// and Shader and then uses the GraphicAPI to draw from the data bound to them.
    virtual void Draw() const = 0;
	//virtual void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const = 0;

	/// @author Alan Brunet
    /// @brief This just display current graphics API - version, vendor, and
    /// renderer
	virtual void DisplayGPUInfo() const = 0;

	/// @author Alan Brunet
	/// @brief Called first to initialise Vertex Buffers. Also initialises a Vertex Array
	/// @param vertData is the stream of data for all vertex data (i.e., position, normal, texture coords
	/// @param vertexcount is the count of how many vertex the object has
	/// @param vertDataSize is the total amount of elements for that vertex (e.g., vec3 position, vec2 texcoord = 5 in total)
	virtual void SetVertexBuffer(float vertData[], unsigned int vertexCount, unsigned int vertDataSize) = 0;

	/// @author Alan Brunet
	/// @brief Called second, Initialises a Vertex Buffer Layout, and inserts as many as count is and adds this to the Vertex Buffer
	/// @param count equals the amount of attributes to be push, 1 = position, 2 = position and texture coords / colour, 3 = position, tex coords / colour, and normals
	/// @param sizes[] needs to specify how many elements are part of that attribute. i.e., vec3 pos = 3, vec2 pos = 2. 
	/// Next element the size of texcoord = 2. Next element the size normal = 3
    virtual void PushLayout(unsigned int count, unsigned int sizes[]) = 0;

	/// @author Alan Brunet
    /// @brief Called third, Initialises the Index Buffer and binds it.
    /// @param indices each element points to which vertex is being drawn for the triangles.
    /// @param count the amount of element in indices
    virtual void SetIndexBuffer(unsigned int indices[], unsigned int count) = 0;

	/// @author Alan Brunet
    /// @brief Called fourth, Initialise the Shader and creates a shader program from each shader source. Each param does not need an entry if we are not using them.
    /// @param vertexsource filename for a Vertex Shader Program. The file path is not required
    /// @param fragmentsource filename for a Fragment Shader Program. The file path is not required
    /// @param computesource filename for a Compute Shader Program. The file path is not required
    /// @param geometrysource filename for a Geometry Shader Program. The file path is not required
    virtual void SetShaderSource(
		std::string vertexsource = "nullptr",
		std::string fragmentsource = "nullptr",
		std::string computesource = "nullptr",
        std::string geometrysource = "nullptr") = 0;

	/// @author Alan Brunet
    /// @brief Must be called last to unbind all data. So it does not flow data into the next buffers.
    virtual void ClearBuffers() = 0;

	/// @author Alan Brunet
    /// @brief Manually set the colour of an object with "u_Color" variable within a basic.frag file.
    ///	all elements must be normalised. i.e., between 0.0f and 1.0f
    /// @param r Red channel
    /// @param g Green channel
    /// @param b Blue channel
	/// @param a Alpha channel / transparency
    virtual void SetColour(float r, float g, float b, float a) = 0;
};
