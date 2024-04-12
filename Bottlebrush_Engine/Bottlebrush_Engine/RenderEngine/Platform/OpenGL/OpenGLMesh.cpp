//
//  Created by Alan Brunet 11/04/2024
//

#include "OpenGLMesh.h"

OpenGLMesh::OpenGLMesh() {

}

OpenGLMesh::~OpenGLMesh() {

}

void OpenGLMesh::CreateMesh(std::vector<float> vertices, unsigned int vertDataSize, std::vector<unsigned int> indices, std::vector<unsigned int> layout) {
    // define the format of each vertex data
    // i.e., 2 = 2 points of positions for each vertex (can use different numbers
    // for different attributes)
    m_VertexBuffer = std::make_unique<OpenGLVertexBuffer>(vertices.data(), vertices.size() * vertDataSize * sizeof(float)) ;

    m_VertexBufferLayout = std::make_unique<OpenGLVertexBufferLayout>();

    m_VertexArray = std::make_unique<OpenGLVertexArray>();

    for (unsigned int i = 0; i < layout.size(); i++) {
      //@TODO DataType is hard coded currently.
      m_VertexBufferLayout->Push(layout[i], DataType::FLOAT);
    }

    // add current buffer with its layout specs to the vertex array
    m_VertexArray->AddBuffer(*m_VertexBuffer, *m_VertexBufferLayout);

    m_IndexBuffer = std::make_unique<OpenGLIndexBuffer>(indices.data(), indices.size());

}

