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

class RenderEngine
{
private:

public:
	void TestSetupValues();
	virtual void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const = 0;
};
