//
//  Created by Alan 11/04/2024
//

#include "OpenGLMesh.h"
OpenGLMesh::OpenGLMesh(
    std::vector<float> vertices,
    std::vector<unsigned int> indices,
    const std::filesystem::path& textureFilePath,
    int textureSlot, 
    std::vector<unsigned int> layout) 
{
    CreateMesh(vertices, indices, textureFilePath, textureSlot, layout);
}

OpenGLMesh::~OpenGLMesh() {

}

void OpenGLMesh::CreateMesh(
    std::vector<float> vertices, 
    std::vector<unsigned int> indices, 
    const std::filesystem::path& textureFilePath, 
    int textureSlot, 
    std::vector<unsigned int> layout) 
{
    // create a vertex buffer with vertices data
    m_VertexBuffer = std::make_unique<OpenGLVertexBuffer>(vertices.data(), vertices.size() * sizeof(float));

    // create a vertex buffer layout, this defines the format of each vertex data
    m_VertexBufferLayout = std::make_unique<OpenGLVertexBufferLayout>();
    
    // create a vertex array, container for Vertex, Index Buffer, and its layout
    m_VertexArray = std::make_unique<OpenGLVertexArray>();

    // define the format of each vertex
    for (unsigned int i : layout) {
      m_VertexBufferLayout->Push(i, DataType::FLOAT);
    }

    // add current buffer with its layout specs to the vertex array
    m_VertexArray->AddBuffer(*m_VertexBuffer, *m_VertexBufferLayout);

    // create an index buffer and bind it, must be done after adding a buffer to the vertex array
    m_IndexBuffer = std::make_unique<OpenGLIndexBuffer>(indices.data(), indices.size());

    // create a texture buffer
    m_Texture = std::make_unique<OpenGLTexture>();
    // loads texture and creates in openGL format
    m_Texture->CreateTexture(textureFilePath);
}

void OpenGLMesh::SetTexture(unsigned int slot) {
    m_Texture->Bind(slot);
}

void OpenGLMesh::UnbindMesh() {
  // clearing all buffer bindings
  if (m_VertexArray) m_VertexArray->Unbind();
  if (m_IndexBuffer) m_IndexBuffer->Unbind();
  if (m_VertexBuffer) m_VertexBuffer->Unbind();
  if (m_Texture) m_Texture->Unbind();
}
