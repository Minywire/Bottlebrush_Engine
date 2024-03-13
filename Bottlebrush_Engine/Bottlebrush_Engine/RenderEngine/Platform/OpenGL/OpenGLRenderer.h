//
//  Created by Alan Brunet 12/03/2024
//
#pragma once

#include <glad/glad.h>

#include "OpenGLVertexArray.h"
#include "OpenGLIndexBuffer.h"
#include "OpenGLShader.h"

// __debugbreak() = instrinctic to MSVC compiler?
#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);

class OpenGLRenderer
{
private:

public:
    void Clear() const;
    void Draw(const OpenGLVertexArray& va, const OpenGLIndexBuffer& ib, const OpenGLShader& shader) const;
};
