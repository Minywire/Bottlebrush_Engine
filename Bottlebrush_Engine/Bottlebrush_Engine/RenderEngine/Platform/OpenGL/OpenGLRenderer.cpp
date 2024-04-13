//
//  Created by Alan Brunet 12/03/2024
//
#include "OpenGLRenderer.h"
#include "GraphicsFactory.h"

#include <iostream>

OpenGLRenderer::OpenGLRenderer() 
{

}

OpenGLRenderer::~OpenGLRenderer()
{

}

void OpenGLRenderer::Clear() const 
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


void OpenGLRenderer::Draw(ShaderType shaderType, const VertexArray& va, const unsigned int indexCount)
{
    if (m_ShaderManager.find(shaderType) != m_ShaderManager.end()) {
        m_ShaderManager[shaderType]->Bind();
        va.Bind();
        glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);
    } 
    else {
      std::cout << "Warning: ShaderType not set yet" << std::endl;
    }
}

void OpenGLRenderer::DisplayGPUInfo() const 
{
    std::cout << "GL Version - " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GL Vender - " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "GL Renderer - " << glGetString(GL_RENDERER) << std::endl;
}

void OpenGLRenderer::SetShaderSource(
    ShaderType shaderType,
    std::filesystem::path vertexsource,
    std::filesystem::path fragmentsource,
    std::filesystem::path computesource,
    std::filesystem::path geometrysource)
{
    // setup source shader files locations
    ShaderSourceFiles ssf;
    ssf.VertexSource = vertexsource;
    ssf.FragmentSource = fragmentsource;
    ssf.ComputeSource = computesource;
    ssf.GeometrySource = geometrysource;

    // calling the constructor will read the files within ssf and apply them
    m_ShaderManager[shaderType] =
        GraphicsFactory<GraphicsAPI::OpenGL>::CreateShaderBuffer(ssf);
}

void OpenGLRenderer::SetColour(ShaderType shaderType, float r, float g, float b, float a) {
    if (m_ShaderManager.find(shaderType) != m_ShaderManager.end()) {
        m_ShaderManager[shaderType]->Bind();
        m_ShaderManager[shaderType]->SetUniform4f("u_Color", r, g, b, a);
    } 
    else {
        std::cout << "Warning: ShaderType not set yet" << std::endl;
    }
    
}

void OpenGLRenderer::UnbindShader(ShaderType shaderType) { 
    // clearing all buffer bindings
    if (m_ShaderManager.find(shaderType) != m_ShaderManager.end()) {
        m_ShaderManager[shaderType]->Unbind();
    }
}
