//
//  Created by Alan Brunet 12/03/2024
//
#include "OpenGLIndexBuffer.h"

#include "OpenGLRenderer.h"

OpenGLIndexBuffer::OpenGLIndexBuffer(const unsigned int* data, unsigned int count)
    : m_Count(count)
{
    // make sure GLuint is the same as commonly used unsigned int
    assert(sizeof(unsigned int) == sizeof(GLuint));

    // Generate 1 buffer for Index Buffer
    glGenBuffers(1, &m_RendererID);

    // Bind buffer to add data
    Bind();

    // adding data to index buffer
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
}

OpenGLIndexBuffer::~OpenGLIndexBuffer()
{
    // deleting 1 buffer
    glDeleteBuffers(1, &m_RendererID);
}

void OpenGLIndexBuffer::Bind() const
{
    // GL_ELEMENT_ARRAY_BUFFER refers to index buffers
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
}

void OpenGLIndexBuffer::Unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

unsigned int OpenGLIndexBuffer::GetCount() const 
{ 
    return m_Count;
}
