//
//  Created by Alan Brunet 12/03/2024
//
#pragma once

#include <glad/glad.h>

#include "RenderEngine.h"
//#include "GraphicsFactory.h"
//#include "OpenGLVertexArray.h"
//#include "OpenGLIndexBuffer.h"
//#include "OpenGLShader.h"



/// child class that does the rendering of objects
/// @TODO provide this with some Casting methods to child classes for buffers, shader, arrays.
class OpenGLRenderer : public RenderEngine
{
private:

public:

    OpenGLRenderer();

    ~OpenGLRenderer() override;

    /// glClearColor()
    void Clear() const override;
    /// This needs to be called within the draw loop 
    //void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const override;
    void Draw() const override;
    /// This just display current graphics API - version, vendor, and renderer
    void DisplayGPUInfo() const override;
};
