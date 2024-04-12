//
// Created by Marco Garzon Lara on 27/11/2023.
// Edited by Alan Brunet on 16/03/24
//
#pragma once

#include "VertexArray.h"
#include "Shader.h"

/// @author Alan Brunet
/// @brief Base class for rendering objects. It contains member pointers to a Vertex Array,
/// Vertex Buffer, Index Buffer, and a Shader
class RenderEngine
{
protected:
	
public:
    RenderEngine(){};
    virtual ~RenderEngine() = default;

    /// @author Alan Brunet
    /// @brief glClearColor()
    virtual void Clear() const = 0;

    /// @author Alan Brunet
    /// @brief This needs to be called within the draw loop. Uses member pointers to bind a Vertex Array (which has a Vertex Buffer, its layout and Index Buffer bound)
    /// and index count of how many indices there is
    virtual void Draw(const VertexArray& va, const unsigned int indexCount) const = 0;

    /// @author Alan Brunet
    /// @brief This just display current graphics API - version, vendor, and
    /// renderer
    virtual void DisplayGPUInfo() const = 0;

    /// @author Alan Brunet
    /// @brief Called fourth, Initialise the Shader and creates a shader program from each shader source. Each param does not need an entry if we are not using them.
    /// @param vertexsource filename for a Vertex Shader Program. The file path is not required
    /// @param fragmentsource filename for a Fragment Shader Program. The file path is not required
    /// @param computesource filename for a Compute Shader Program. The file path is not required
    /// @param geometrysource filename for a Geometry Shader Program. The file path is not required
    virtual void SetShaderSource(
		std::string vertexsource = "nullptr",
		std::string fragmentsource = "nullptr",
		std::string computesource = "nullptr",
                std::string geometrysource = "nullptr") = 0;

    /// @author Alan Brunet
    /// @brief Must be called last to unbind all data. So it does not flow data into the next buffers.
    virtual void UnbindBuffers() = 0;

    /// @author Alan Brunet
    /// @brief Manually set the colour of an object with "u_Color" variable within a basic.frag file.
    ///	all elements must be normalised. i.e., between 0.0f and 1.0f
    /// @param r Red channel
    /// @param g Green channel
    /// @param b Blue channel
    /// @param a Alpha channel / transparency
    virtual void SetColour(float r, float g, float b, float a) = 0;

    virtual inline std::unique_ptr<Shader>& GetShader() = 0;
};
