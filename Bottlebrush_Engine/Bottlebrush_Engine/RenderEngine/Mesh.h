//
//  Created by Alan Brunet 11/04/2024
//

#pragma once

#include <memory>
#include <filesystem>
#include "VertexArray.h"

class Mesh {
protected:

public:
    Mesh(){};
    virtual ~Mesh() = default;

    /// @author Alan Brunet
    /// @brief Creates the mesh using OpenGL's Vertex Buffer, 
    /// Vertex buffer layout and Index buffer. It then binds it to an array
    /// @param vertices vertex data, i.e., positions, texcoords, normals
    /// @param vertDataSize how many elements are part of the vertex as a whole
    /// 3 positions, 2 texcoords, 3 normals = 8;
    /// @param indices index buffer data. Indexing the drawing of vertexes
    /// @param layout vertex buffer layout. Defines the size of each element in
    /// the vertex buffer
    virtual void CreateMesh(std::vector<float> vertices, std::vector<unsigned int> indices, const std::filesystem::path& textureFilePath, int textureSlot, std::vector<unsigned int> layout) = 0;

    /// @author Alan Brunet
    /// @brief Creates a texture from a given image, and an assigned slot
    /// which is defaulted to zero
    /// @param width is image width
    /// @param height is image height
    /// @param bpp is bytes per pixel
    /// @param imagedata is the raw data from an image
    /// @param slot for overlapping image textures if not 0.
    /// Defaulted to zero
    virtual void SetTexture(unsigned int slot = 0) = 0;

    virtual void UnbindMesh() = 0;

    virtual inline std::unique_ptr<VertexArray>& GetVertexArray() = 0;
    virtual inline unsigned int GetIndexCount() =0;
};
