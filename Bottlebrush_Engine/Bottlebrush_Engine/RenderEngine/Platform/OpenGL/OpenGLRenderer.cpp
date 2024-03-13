//
//  Created by Alan Brunet 12/03/2024
//
#include "Renderer.h"

#include <iostream>

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

void OpenGLRenderer::Clear() const
{
    glClear(GL_COLOR_BUFFER_BIT);
}

void OpenGLRenderer::Draw(const OpenGLVertexArray& va, const OpenGLIndexBuffer& ib, const OpenGLShader& shader) const
{
    shader.Bind();
    va.Bind();
    GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}
