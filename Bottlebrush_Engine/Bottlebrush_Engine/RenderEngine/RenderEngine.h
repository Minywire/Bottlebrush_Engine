//
// Created by Marco Garzon Lara on 27/11/2023.
// Edited by Alan on 16/03/24
//
#pragma once

#include "VertexArray.h"
#include "Shader.h"

enum class ShaderType { Default, Pixelated, Water, Shadowmap, Skybox, Terrain };

/// @author Alan
/// @brief Base class for rendering objects. It contains member pointers to a Vertex Array,
/// Vertex Buffer, Index Buffer, and a Shader
class RenderEngine
{
protected:
	
public:
    RenderEngine(){};
    virtual ~RenderEngine() = default;

    /// @author Alan
    /// @brief glClearColor()
    virtual void Clear() const = 0;

    /// @author Alan
    /// @brief This needs to be called within the draw loop. Uses member pointers to bind a Vertex Array (which has a Vertex Buffer, its layout and Index Buffer bound)
    /// and index count of how many indices there is
    virtual void Draw(ShaderType shaderType, const VertexArray& va, const unsigned int indexCount) = 0;

    virtual void DrawTriangleStrips(
        ShaderType shaderType,
        const VertexArray& va,
        const int numStrips,
        const int numTriangles) = 0;

    /// @author Alan
    /// @brief This just display current graphics API - version, vendor, and
    /// renderer
    virtual void DisplayGPUInfo() const = 0;

    /// @author Alan
    /// @brief Called fourth, Initialise the Shader and creates a shader program from each shader source. Each param does not need an entry if we are not using them.
    /// @param vertexsource filename for a Vertex Shader Program. The file path is not required
    /// @param fragmentsource filename for a Fragment Shader Program. The file path is not required
    /// @param computesource filename for a Compute Shader Program. The file path is not required
    /// @param geometrysource filename for a Geometry Shader Program. The file path is not required
    virtual void SetShaderSource(
        ShaderType shaderType,
        std::filesystem::path vertexsource = std::filesystem::path(),
        std::filesystem::path fragmentsource = std::filesystem::path(),
        std::filesystem::path computesource = std::filesystem::path(),
        std::filesystem::path geometrysource = std::filesystem::path()) = 0;

    /// @author Alan
    /// @brief Must be called last to unbind all data. So it does not flow data into the next buffers.
    virtual void UnbindShader(ShaderType shaderType) = 0;

    /// @author Alan
    /// @brief Manually set the colour of an object with "u_Color" variable within a basic.frag file.
    ///	all elements must be normalised. i.e., between 0.0f and 1.0f
    /// @param r Red channel
    /// @param g Green channel
    /// @param b Blue channel
    /// @param a Alpha channel / transparency
    virtual void SetColour(ShaderType shaderType, float r, float g, float b, float a) = 0;

    virtual inline std::unique_ptr<Shader>& GetShader(ShaderType shaderType) = 0;
};
