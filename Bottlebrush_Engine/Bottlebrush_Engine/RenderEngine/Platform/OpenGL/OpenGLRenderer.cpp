//
//  Created by Alan Brunet 12/03/2024
//
#include "OpenGLRenderer.h"

#include <iostream>

void OpenGLRenderer::Clear() const
{
    glClear(GL_COLOR_BUFFER_BIT);
}

void OpenGLRenderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
    shader.Bind();
    va.Bind();
    glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);
}

void OpenGLRenderer::DisplayGPUInfo() const 
{
    std::cout << "GL Version - " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GL Vender - " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "GL Renderer - " << glGetString(GL_RENDERER) << std::endl;
}
