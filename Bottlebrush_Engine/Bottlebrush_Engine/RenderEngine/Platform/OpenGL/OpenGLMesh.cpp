#include "OpenGLMesh.h"
//
//  Created by Alan Brunet 11/04/2024
//

#include "OpenGLMesh.h"

OpenGLMesh::OpenGLMesh() {

}

OpenGLMesh::~OpenGLMesh() {

}

void OpenGLMesh::CreateMesh(std::vector<float> vertices, std::vector<unsigned int> indices, std::vector<float> textureCoords, std::vector<unsigned int> layout) {
    // create a vertex buffer, vector data, vertices
    m_VertexBuffer = std::make_unique<OpenGLVertexBuffer>(vertices.data(), vertices.size() * sizeof(float)) ;

    // define the format of each vertex data
    // i.e., 2 = 2 points of positions for each vertex (can use different
    // numbers for different attributes)
    m_VertexBufferLayout = std::make_unique<OpenGLVertexBufferLayout>();

    m_VertexArray = std::make_unique<OpenGLVertexArray>();

    for (unsigned int i = 0; i < layout.size(); i++) {
      //@TODO DataType is hard coded currently.
      m_VertexBufferLayout->Push(layout[i], DataType::FLOAT);
    }

    // add current buffer with its layout specs to the vertex array
    m_VertexArray->AddBuffer(*m_VertexBuffer, *m_VertexBufferLayout);

    // create an index buffer and bind it, must be done after layout binding
    m_IndexBuffer = std::make_unique<OpenGLIndexBuffer>(indices.data(), indices.size());
}

void OpenGLMesh::SetTexture(int width, int height, int bpp,
                                unsigned char* imagedata, unsigned int slot) {
  m_Texture = std::make_unique<OpenGLTexture>(width, height, bpp);

  m_Texture->CreateTexture(imagedata);
  m_Texture->Bind(slot);
}

void OpenGLMesh::UnbindMesh() {
  // clearing all buffer bindings
  if (m_VertexArray) m_VertexArray->Unbind();
  if (m_IndexBuffer) m_IndexBuffer->Unbind();
  if (m_VertexBuffer) m_VertexBuffer->Unbind();
  if (m_Texture) m_Texture->Unbind();
}
