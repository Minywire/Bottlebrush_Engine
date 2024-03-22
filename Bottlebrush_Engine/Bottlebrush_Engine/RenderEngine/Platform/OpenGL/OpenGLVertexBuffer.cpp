//
//  Created by Alan Brunet 12/03/2024
//
#include "OpenGLVertexBuffer.h"

#include "OpenGLRenderer.h"

OpenGLVertexBuffer::OpenGLVertexBuffer(float* data, unsigned int size)
{
    // generate 1 buffer for a Vertex
    glGenBuffers(1, &m_RendererID);

    // bind that buffer just created
    Bind(); 

    // add data (positions) to the buffer that was just bound
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

OpenGLVertexBuffer::~OpenGLVertexBuffer()
{
    // deleting 1 buffer
    glDeleteBuffers(1, &m_RendererID);
}

void OpenGLVertexBuffer::Bind() const
{
    // GL_ARRAY_BUFFER is for a vertex
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
}

void OpenGLVertexBuffer::UnBind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
