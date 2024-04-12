//
//  Created by Alan Brunet 11/04/2024
//

#pragma once

#include "Mesh.h"

#include "OpenGLVertexArray.h"
#include "OpenGLVertexBuffer.h"
#include "OpenGLIndexBuffer.h"
#include "OpenGLVertexBufferLayout.h"
#include "OpenGLTexture.h"

class OpenGLMesh : public Mesh {
private:
    /// Vertex Array pointer
    std::unique_ptr<VertexArray> m_VertexArray;
    /// Vertex Buffer pointer
    std::unique_ptr<VertexBuffer> m_VertexBuffer;
    /// Index Buffer pointer
    std::unique_ptr<IndexBuffer> m_IndexBuffer;
    /// Vertex Buffer Layout pointer
    std::unique_ptr<VertexBufferLayout> m_VertexBufferLayout;
    /// Texture Buffer pointer
    std::unique_ptr<Texture> m_Texture;
 public:
    OpenGLMesh();
    ~OpenGLMesh() override;

    void CreateMesh(std::vector<float> vertices, unsigned int vertDataSize, std::vector<unsigned int> indices, std::vector<unsigned int> layout) override;

    inline std::unique_ptr<VertexArray>& GetVertexArray() override {return m_VertexArray;}
    inline unsigned int GetIndexCount() override {return m_IndexBuffer->GetCount();}
};
