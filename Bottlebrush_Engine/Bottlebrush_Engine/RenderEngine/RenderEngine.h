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

void hello_world();

/// Base class for rendering objects
/// @TODO provide this with some Casting methods to child classes for buffers, shader, arrays.
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
	/// @brief Called first to initialise Vertex Buffers
	/// @param vertData is the stream of data for all vertex data (i.e., position, normal, texture coords
	/// @param vertexcount is the count of how many vertex the object has
	/// @param vertDataSize is the total amount of elements for that vertex (e.g., vec3 position, vec2 texcoord = 5 in total)
	void SetVertexBuffer(float vertData[], unsigned int vertexcount, unsigned int vertDataSize);
    void PushLayout(unsigned int count, unsigned int size[]);
    void SetIndexBuffer(unsigned int indices[], unsigned int indicesSize);
    void SetShaderSource(
		std::string vertexsource = "nullptr",
		std::string fragmentsource = "nullptr",
		std::string computesource = "nullptr",
        std::string geometrysource = "nullptr");
    void ClearBuffers();
    void SetColour(float r, float g, float b, float a);

	/// glClearColor()
    virtual void Clear() const = 0;
	/// This needs to be called within the draw loop 
	//virtual void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const = 0;
    virtual void Draw() const = 0;
	/// This just display current graphics API - version, vendor, and renderer
	virtual void DisplayGPUInfo() const = 0;
};
