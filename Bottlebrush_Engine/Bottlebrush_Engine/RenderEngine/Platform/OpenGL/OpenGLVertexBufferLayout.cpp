//
// Created by Marco on 22/03/24.
//
#include "OpenGLVertexBufferLayout.h"

template<>
void OpenGLVertexBufferLayout::Push<float>(unsigned int count)
{
    // float is normalised
    m_Elements.push_back({ count, GL_FLOAT, GL_FALSE });
    m_Stride += count * GetSizeOfType(GL_FLOAT);
}

template<>
void OpenGLVertexBufferLayout::Push<unsigned int>(unsigned int count)
{
    // unsigned int is normalised
    m_Elements.push_back({ count, GL_UNSIGNED_INT, GL_FALSE });
    m_Stride += count * GetSizeOfType(GL_UNSIGNED_INT);
}

template<>
void OpenGLVertexBufferLayout::Push<unsigned char>(unsigned int count)
{
    // chars are not normalised
    m_Elements.push_back({ count, GL_UNSIGNED_BYTE, GL_TRUE });
    m_Stride += count * GetSizeOfType(GL_BYTE);
}

inline std::vector<VertexBufferElement> OpenGLVertexBufferLayout::GetElements() const &
{
    return m_Elements;
}

inline unsigned int OpenGLVertexBufferLayout::GetStride() const
{
    return m_Stride;
}