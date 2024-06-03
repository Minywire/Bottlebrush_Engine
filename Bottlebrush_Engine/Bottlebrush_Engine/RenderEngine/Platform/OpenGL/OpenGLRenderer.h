//
//  Created by Alan 12/03/2024
//
#pragma once

#include "RenderEngine.h"

#include <glad/glad.h>
#include <filesystem>
#include <unordered_map>
#include <memory>

/// @author Alan
/// @brief Base class for rendering objects. It contains member pointers to a
/// Vertex Array, Vertex Buffer, Index Buffer, and a Shader
class OpenGLRenderer : public RenderEngine
{
private:
    /// Shader pointer
    //std::unique_ptr<Shader> m_Shader;
    std::unordered_map<ShaderType, std::unique_ptr<Shader>> m_ShaderManager;

 public:
    OpenGLRenderer();
    ~OpenGLRenderer() override;

    /// @author Alan
    /// @brief called at the start of the render loop to clear colour and depth buffers
    void Clear() const override;

    /// @author Alan
    /// @brief Draws a model with triangle polygons
    /// This needs to be called within the draw loop.
    /// @param shaderType is the shader program to be used
    /// @param va is the Vertex Array to bind and use
    /// @param indexCount is the total count of indices in that Vertex array
    void Draw(ShaderType shaderType, const VertexArray& va, const unsigned int indexCount) override;

    /// @author Marco
    /// @brief Draws a model with a vao (no index buffer)
    /// This needs to be called within the draw loop.
    /// @param shaderType is the shader program to be used
    /// @param va is the bound Vertex Array
    /// @param size is the data size of the specified VAO
    void Draw(ShaderType shaderType, unsigned int va, unsigned int vertexCount) override;

    /// @author Alan
    /// @brief Draws using TriangleStrips.
    /// e.g, for Terrain
    /// @param shaderType the shader program to be used
    /// @param va is the Vertex Array to bind and use
    /// @param numStrips is the number of strips that needs to be drawn
    /// @param numTriangles is the number of triangles that will be drawn
    void DrawTriangleStrips(
        ShaderType shaderType,
        const VertexArray& va,
        const int numStrips,
        const int numTriangles) override;
    
    /// @author Alan
    /// @brief This just display current graphics API - version, vendor, and
    /// renderer
    void DisplayGPUInfo() const override;

    /// @author Alan
    /// @brief Initialise the Shader and creates a shader program from each shader source. 
    /// Each param besides shaderType does not need an entry if we are not using them.
    /// @param shaderType is the unordered map to manage the amount of different Shaders
    /// Each param does not need an entry if we are not using them.
    /// @param vertexsource filename for a Vertex Shader Program. The file path is not required
    /// @param fragmentsource filename for a Fragment Shader Program. The file path is not required
    /// @param computesource filename for a Compute Shader Program. The file path is not required
    /// @param geometrysource filename for a Geometry Shader Program. The file path is not required
    void SetShaderSource(
        ShaderType shaderType,
        std::filesystem::path vertexsource = std::filesystem::path(),
        std::filesystem::path fragmentsource = std::filesystem::path(),
        std::filesystem::path computesource = std::filesystem::path(),
        std::filesystem::path geometrysource = std::filesystem::path()) override;

    
    /// @author Alan
    /// @brief Must be called last to unbind all data. So it does not flow data
    /// into the next buffers.
    void UnbindShader(ShaderType shaderType) override;

    /// @author Alan
    /// @brief Manually set the colour of an object with "u_Color" variable
    /// within a basic.frag file.
    ///	all elements must be normalised. i.e., between 0.0f and 1.0f
    /// @param r Red channel
    /// @param g Green channel
    /// @param b Blue channel
    /// @param a Alpha channel / transparency
    void SetColour(ShaderType shaderType, float r, float g, float b, float a) override;

    inline std::unique_ptr<Shader>& GetShader(ShaderType shaderType) { return m_ShaderManager[shaderType]; }
};
