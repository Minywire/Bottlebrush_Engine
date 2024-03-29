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
    glClear(GL_COLOR_BUFFER_BIT);
}

/*
void OpenGLRenderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
    shader.Bind();
    va.Bind();
    glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);
}
*/

void OpenGLRenderer::Draw() const 
{
    m_SH->Bind();
    m_VA->Bind();
    glDrawElements(GL_TRIANGLES, m_IB->GetCount(), GL_UNSIGNED_INT, nullptr);
}

void OpenGLRenderer::DisplayGPUInfo() const 
{
    std::cout << "GL Version - " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GL Vender - " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "GL Renderer - " << glGetString(GL_RENDERER) << std::endl;
}


void OpenGLRenderer::SetVertexBuffer(const void* vertData, unsigned int vertexCount, unsigned int vertDataSize) 
{
    // vertex array object
    m_VA = GraphicsFactory<GraphicsAPI::OpenGL>::CreateVertexArray();

    // 4 vertex and 2 points (2D)
    m_VB = GraphicsFactory<GraphicsAPI::OpenGL>::CreateVertexBuffer(vertData, vertexCount * vertDataSize * sizeof(float));
}

void OpenGLRenderer::PushLayout(unsigned int count, unsigned int sizes[]) 
{
    // define the format of each vertex data
    // i.e., 2 = 2 points of positions for each vertex (can use different numbers
    // for different attributes)
    m_VBL = GraphicsFactory<GraphicsAPI::OpenGL>::CreateVertexBufferLayout();

    for (unsigned int i = 0; i < count; i++) 
    {
        //@TODO DataType is hard coded currently.
        m_VBL->Push(sizes[i], DataType::FLOAT);
    }

    // add current buffer with its layout specs to the vertex array
    m_VA->AddBuffer(*m_VB, *m_VBL);
}

void OpenGLRenderer::SetIndexBuffer(unsigned int indices[], unsigned int count)
{
    // 6 = the count of elements in indices
    m_IB = GraphicsFactory<GraphicsAPI::OpenGL>::CreateIndexBuffer(indices, count);
}

void OpenGLRenderer::SetShaderSource(
    std::string vertexsource,
    std::string fragmentsource,
    std::string computesource,
    std::string geometrysource)
{
    // setup source shader files locations
    ShaderSourceFiles ssf;
    ssf.VertexSource = vertexsource;
    ssf.FragmentSource = fragmentsource;
    ssf.ComputeSource = computesource;
    ssf.GeometrySource = geometrysource;

    // calling the constructor will read the files within ssf and apply them
    m_SH = GraphicsFactory<GraphicsAPI::OpenGL>::CreateShaderBuffer(ssf);
}

void OpenGLRenderer::SetTexture(int width, int height, int bpp, unsigned char* imagedata, unsigned int slot)
{
  m_TX = GraphicsFactory<GraphicsAPI::OpenGL>::CreateTextureBuffer(width, height, bpp);

  m_TX->CreateTexture(imagedata);
  m_TX->Bind(slot);
}

void OpenGLRenderer::SetColour(float r, float g, float b, float a) {
    // basic.frag has a uniform declaration
    m_SH->Bind();
    m_SH->SetUniform4f("u_Color", r, g, b, a);
}

void OpenGLRenderer::ClearBuffers() 
{ 
    // clearing all buffer bindings
    if(m_VA) m_VA->Unbind();
    if(m_SH) m_SH->Unbind();
    if(m_IB) m_IB->Unbind();
    if(m_VB) m_VB->Unbind();
    if(m_TX) m_TX->Unbind();
}

