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
    std::unique_ptr<OpenGLTexture> m_Texture;
 public:
    OpenGLMesh();
    ~OpenGLMesh() override;

    /// @author Alan Brunet
    /// @brief Creates the mesh using OpenGL's Vertex Buffer,
    /// Vertex buffer layout and Index buffer. It then binds it to an array
    /// @param vertices vertex data, i.e., positions, texcoords, normals
    /// @param indices index buffer data. Indexing the drawing of vertexes
    /// @param layout vertex buffer layout. Defines the size of each element in
    /// the vertex buffer
    void CreateMesh(std::vector<float> vertices, std::vector<unsigned int> indices, std::vector<float> textureCoords, const std::filesystem::path& textureFilePath, std::vector<unsigned int> layout) override;

    /// @author Alan Brunet
    /// @brief Creates a texture from a given image, and an assigned slot
    /// which is defaulted to zero
    /// @param width is image width
    /// @param height is image height
    /// @param bpp is bytes per pixel
    /// @param imagedata is the raw data from an image
    /// @param slot for overlapping image textures if not 0.
    /// Defaulted to zero
//    void SetTexture(int width, int height, int bpp, unsigned char* imagedata,
//                    unsigned int slot = 0) override;


    /// @author Alan Brunet
    /// @brief unbinds all buffers to this mesh
    void UnbindMesh() override;

    inline std::unique_ptr<VertexArray>& GetVertexArray() override {return m_VertexArray;}
    inline unsigned int GetIndexCount() override {return m_IndexBuffer->GetCount();}
};
