//
//  Created by Alan 11/04/2024
//

#pragma once

#include "Mesh.h"

#include "OpenGLVertexArray.h"
#include "OpenGLVertexBuffer.h"
#include "OpenGLIndexBuffer.h"
#include "OpenGLVertexBufferLayout.h"
#include "OpenGLTexture.h"
#include <filesystem>

/// @author Alan
/// @brief Mesh class that holds all vertex data, including its texture
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
    OpenGLMesh(
        std::vector<float> vertices, 
        std::vector<unsigned int> indices,
        const std::filesystem::path& textureFilePath, 
        int textureSlot,
        std::vector<unsigned int> layout);
    ~OpenGLMesh() override;

    /// @author Alan
    /// @brief Creates the mesh using OpenGL's Vertex Buffer,
    /// Vertex buffer layout and Index buffer. It then binds it to an array
    /// @param vertices vertex data, i.e., positions, texcoords, normals
    /// @param indices index buffer data. Indexing the drawing of vertexes
    /// @param layout vertex buffer layout. Defines the size of each element in
    /// the vertex buffer
    void CreateMesh(
        std::vector<float> vertices, 
        std::vector<unsigned int> indices, 
        const std::filesystem::path& textureFilePath, 
        int textureSlot, 
        std::vector<unsigned int> layout) override;

    /// @author Alan
    /// @brief Creates a texture from a given image, and an assigned slot
    /// which is defaulted to zero
    /// @param width is image width
    /// @param height is image height
    /// @param bpp is bytes per pixel
    /// @param imagedata is the raw data from an image
    /// @param slot for overlapping image textures if not 0.
    /// Defaulted to zero
    void SetTexture(unsigned int slot = 0) override;


    /// @author Alan
    /// @brief unbinds mesh buffers
    void UnbindMesh() override;

    inline std::unique_ptr<VertexArray>& GetVertexArray() override {return m_VertexArray;}
    inline unsigned int GetIndexCount() override {return m_IndexBuffer->GetCount();}
};
