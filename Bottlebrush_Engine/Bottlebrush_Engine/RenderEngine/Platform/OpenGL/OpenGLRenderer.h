//
//  Created by Alan Brunet 12/03/2024
//
#pragma once

#include <glad/glad.h>

#include "../../RenderEngine.h"

#include "OpenGLVertexArray.h"
#include "OpenGLIndexBuffer.h"
#include "OpenGLShader.h"

namespace
{
    // __debugbreak() = instrinctic to MSVC compiler?
    #define ASSERT(x) if (!(x)) __debugbreak();

    #define GLCall(x) GLClearError();\
        x;\
        ASSERT(GLLogCall(#x, __FILE__, __LINE__))


    void GLClearError()
    {
        while (glGetError() != GL_NO_ERROR);
    }

    bool GLLogCall(const char* function, const char* file, int line)
    {
        while (GLenum error = glGetError())
        {
            std::cout << "[OpenGL Error] (" << error << ") " <<
                function << " " <<
                file << ":" <<
                line << std::endl;
            return false;
        }
        return true;
    }

}

class OpenGLRenderer : RenderEngine
{
private:

public:
    void Clear() const;
    virtual void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const override;
};
