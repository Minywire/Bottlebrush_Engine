#include "OpenGLIndexBuffer.h"

#include "OpenGLRenderer.h"

OpenGLIndexBuffer::OpenGLIndexBuffer(const unsigned int* data, unsigned int count)
    : m_Count(count)
{
    // make sure GLuint is the same as commonly used unsigned int
    ASSERT(sizeof(unsigned int) == sizeof(GLuint));

    // Generate 1 buffer for Index Buffer
    GLCall(glGenBuffers(1, &m_RendererID));

    // Bind buffer to add data
    Bind();
    // old call
    //GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));

    // adding data to index buffer
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
}

OpenGLIndexBuffer::~OpenGLIndexBuffer()
{
    // deleting 1 buffer
    GLCall(glDeleteBuffers(1, &m_RendererID));
}

void OpenGLIndexBuffer::Bind() const
{
    // GL_ELEMENT_ARRAY_BUFFER refers to index buffers
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
}

void OpenGLIndexBuffer::UnBind() const
{
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
