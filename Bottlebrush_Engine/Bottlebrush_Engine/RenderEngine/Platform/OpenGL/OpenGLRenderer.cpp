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
    GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}
