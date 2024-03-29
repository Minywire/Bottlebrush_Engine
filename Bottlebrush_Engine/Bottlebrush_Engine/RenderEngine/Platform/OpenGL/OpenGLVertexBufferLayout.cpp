//
// Created by Marco on 22/03/24.
//
#include <glad/glad.h>
#include "OpenGLVertexBufferLayout.h"
#include <cassert>

OpenGLVertexBufferLayout::OpenGLVertexBufferLayout() : m_Stride(0) {

}

OpenGLVertexBufferLayout::~OpenGLVertexBufferLayout() {

}
// manually setting the byte count of GL types
unsigned int OpenGLVertexBufferLayout::GetSizeOfType(unsigned int type) {
  switch (type) {
    case GL_FLOAT:
      return 4;
    case GL_UNSIGNED_INT:
      return 4;
    case GL_UNSIGNED_BYTE:
      return 1;
  }
  assert(false && "This is false.");
  return 0;
}

void OpenGLVertexBufferLayout::Push(unsigned int count, DataType dt) {
    switch (dt) { 
    case DataType::FLOAT:
        // float is normalised
        m_Elements.push_back({count, GL_FLOAT, GL_FALSE});
        m_Stride += count * GetSizeOfType(GL_FLOAT);
        break;
    case DataType::UINT:
        // unsigned int is normalised
        m_Elements.push_back({count, GL_UNSIGNED_INT, GL_FALSE});
        m_Stride += count * GetSizeOfType(GL_UNSIGNED_INT);
        break;
    case DataType::UCHAR:
        // chars are not normalised
        m_Elements.push_back({count, GL_UNSIGNED_BYTE, GL_TRUE});
        m_Stride += count * GetSizeOfType(GL_BYTE);
        break;
    default:
        // float is normalised
        m_Elements.push_back({count, GL_FLOAT, GL_FALSE});
        m_Stride += count * GetSizeOfType(GL_FLOAT);
        break;
    }
}

std::vector<VertexBufferElement> OpenGLVertexBufferLayout::GetElements() const &
{
    return m_Elements;
}

unsigned int OpenGLVertexBufferLayout::GetStride() const
{
    return m_Stride;
}