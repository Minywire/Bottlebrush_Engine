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

public:
	/// will be deleted at some point, this is just for demostration of setting up render engine
	void TestSetupValues();
	/// This needs to be called within the draw loop 
	virtual void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const = 0;
	/// This just display current graphics API - version, vendor, and renderer
	virtual void DisplayGPUInfo() const = 0;
};
