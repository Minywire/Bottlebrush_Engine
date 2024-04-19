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
    /// @brief glClearColor()
    void Clear() const override;

    /// @author Alan
    /// @brief This needs to be called within the draw loop. Uses member
    /// pointers to bind a Vertex Array (which has a Vertex Buffer, its layout
    /// and Index Buffer bound) and Shader and then uses the GraphicAPI to draw
    /// from the data bound to them.
    void Draw(ShaderType shaderType, const VertexArray& va, const unsigned int indexCount) override;

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
    /// @brief Initialise the Shader and creates a shader program
    /// from each shader source. Each param besides shaderType does not need an entry if we are not
    /// using them.
    /// @param shaderType is the unordered map to manage the amount of different Shaders
    /// @param vertexsource filename for a Vertex Shader Program. The file path
    /// is not required
    /// @param fragmentsource filename for a Fragment Shader Program. The file
    /// path is not required
    /// @param computesource filename for a Compute Shader Program. The file
    /// path is not required
    /// @param geometrysource filename for a Geometry Shader Program. The file
    /// path is not required
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
