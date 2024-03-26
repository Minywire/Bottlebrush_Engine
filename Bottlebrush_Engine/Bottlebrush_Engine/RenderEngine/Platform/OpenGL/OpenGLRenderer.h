//
//  Created by Alan Brunet 12/03/2024
//
#pragma once

#include "RenderEngine.h"

#include <glad/glad.h>

/// @author Alan Brunet
/// @brief Base class for rendering objects. It contains member pointers to a
/// Vertex Array, Vertex Buffer, Index Buffer, and a Shader
class OpenGLRenderer : public RenderEngine
{
private:
    /// Vertex Array pointer
    std::unique_ptr<VertexArray> m_VA;
    /// Vertex Buffer pointer
    std::unique_ptr<VertexBuffer> m_VB;
    /// Index Buffer pointer
    std::unique_ptr<IndexBuffer> m_IB;
    /// Vertex Buffer Layout pointer
    std::unique_ptr<VertexBufferLayout> m_VBL;
    /// Shader pointer
    std::unique_ptr<Shader> m_SH;
    /// Texture Buffer pointer
    std::unique_ptr<Texture> m_TX;

 public:
    OpenGLRenderer();
    ~OpenGLRenderer();

    /// @author Alan Brunet
    /// @brief glClearColor()
    void Clear() const override;

    /// @author Alan Brunet
    /// @brief This needs to be called within the draw loop. Uses member
    /// pointers to bind a Vertex Array (which has a Vertex Buffer, its layout
    /// and Index Buffer bound) and Shader and then uses the GraphicAPI to draw
    /// from the data bound to them.
    void Draw() const override;
    
    /// @author Alan Brunet
    /// @brief This just display current graphics API - version, vendor, and
    /// renderer
    void DisplayGPUInfo() const override;

    /// @author Alan Brunet
    /// @brief Called first to initialise Vertex Buffers. Also initialises a
    /// Vertex Array
    /// @param vertData is the stream of data for all vertex data (i.e.,
    /// position, normal, texture coords
    /// @param vertexcount is the count of how many vertex the object has
    /// @param vertDataSize is the total amount of elements for that vertex
    /// (e.g., vec3 position, vec2 texcoord = 5 in total)
    void SetVertexBuffer(float vertData[], unsigned int vertexCount,unsigned int vertDataSize) override;

    /// @author Alan Brunet
    /// @brief Called second, Initialises a Vertex Buffer Layout, and inserts as
    /// many as count is and adds this to the Vertex Buffer
    /// @param count equals the amount of attributes to be push, 1 = position, 2
    /// = position and texture coords / colour, 3 = position, tex coords /
    /// colour, and normals
    /// @param sizes[] needs to specify how many elements are part of that
    /// attribute. i.e., vec3 pos = 3, vec2 pos = 2. Next element the size of
    /// texcoord = 2. Next element the size normal = 3
    /// @TODO DataType is hard coded currently in implementation.
    void PushLayout(unsigned int count, unsigned int sizes[]) override;

    /// @author Alan Brunet
    /// @brief Called third, Initialises the Index Buffer and binds it.
    /// @param indices each element points to which vertex is being drawn for
    /// the triangles.
    /// @param count the amount of element in indices
    void SetIndexBuffer(unsigned int indices[],unsigned int count)override;

    /// @author Alan Brunet
    /// @brief Called fourth, Initialise the Shader and creates a shader program
    /// from each shader source. Each param does not need an entry if we are not
    /// using them.
    /// @param vertexsource filename for a Vertex Shader Program. The file path
    /// is not required
    /// @param fragmentsource filename for a Fragment Shader Program. The file
    /// path is not required
    /// @param computesource filename for a Compute Shader Program. The file
    /// path is not required
    /// @param geometrysource filename for a Geometry Shader Program. The file
    /// path is not required
    void SetShaderSource(std::string vertexsource = "nullptr",
                         std::string fragmentsource = "nullptr",
                         std::string computesource = "nullptr",
                         std::string geometrysource = "nullptr") override;

    /// @author Alan Brunet
    /// @brief Creates a texture from a given image, and an assigned slot
    /// which is defaulted to zero
    /// @param width is image width
    /// @param height is image height
    /// @param bpp is bytes per pixel
    /// @param imagedata is the raw data from an image
    /// @param slot for overlapping image textures if not 0.
    /// Defaulted to zero
    void SetTexture(int width, int height, int bpp, unsigned char* imagedata,
                    unsigned int slot = 0) override;

    /// @author Alan Brunet
    /// @brief Must be called last to unbind all data. So it does not flow data
    /// into the next buffers.
    void ClearBuffers() override;

    /// @author Alan Brunet
    /// @brief Manually set the colour of an object with "u_Color" variable
    /// within a basic.frag file.
    ///	all elements must be normalised. i.e., between 0.0f and 1.0f
    /// @param r Red channel
    /// @param g Green channel
    /// @param b Blue channel
    /// @param a Alpha channel / transparency
    void SetColour(float r, float g, float b, float a) override;
};
