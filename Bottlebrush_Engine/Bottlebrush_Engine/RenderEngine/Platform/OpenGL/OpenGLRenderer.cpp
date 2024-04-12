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


void OpenGLRenderer::Draw(const VertexArray& va, const unsigned int indexCount) const
{
    m_Shader->Bind();
    va.Bind();
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);
}

void OpenGLRenderer::Draw() const 
{
    if (m_Shader) m_Shader->Bind();
    if (m_VertexArray) 
    {
        m_VertexArray->Bind();
        glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);
    } 
    else 
    {
        assert(false && "VertexArray is not bound on an object");
    }
        
}

void OpenGLRenderer::DisplayGPUInfo() const 
{
    std::cout << "GL Version - " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GL Vender - " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "GL Renderer - " << glGetString(GL_RENDERER) << std::endl;
}


void OpenGLRenderer::SetVertexBuffer(const void* vertData, unsigned int vertexCount, unsigned int vertDataSize) 
{
    // 4 vertex and 2 points (2D)
    m_VertexBuffer = GraphicsFactory<GraphicsAPI::OpenGL>::CreateVertexBuffer(vertData, vertexCount * vertDataSize * sizeof(float));
}

void OpenGLRenderer::PushLayout(unsigned int count, unsigned int sizes[]) 
{
    // define the format of each vertex data
    // i.e., 2 = 2 points of positions for each vertex (can use different numbers
    // for different attributes)
    m_VertexBufferLayout = GraphicsFactory<GraphicsAPI::OpenGL>::CreateVertexBufferLayout();

    // vertex array object
    m_VertexArray = GraphicsFactory<GraphicsAPI::OpenGL>::CreateVertexArray();

    for (unsigned int i = 0; i < count; i++) 
    {
        //@TODO DataType is hard coded currently.
        m_VertexBufferLayout->Push(sizes[i], DataType::FLOAT);
    }

    // add current buffer with its layout specs to the vertex array
    m_VertexArray->AddBuffer(*m_VertexBuffer, *m_VertexBufferLayout);
}

void OpenGLRenderer::SetIndexBuffer(unsigned int indices[], unsigned int count)
{
    // 6 = the count of elements in indices
    m_IndexBuffer = GraphicsFactory<GraphicsAPI::OpenGL>::CreateIndexBuffer(indices, count);
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
    m_Shader = GraphicsFactory<GraphicsAPI::OpenGL>::CreateShaderBuffer(ssf);
}

void OpenGLRenderer::SetTexture(int width, int height, int bpp, unsigned char* imagedata, unsigned int slot)
{
    m_Texture = GraphicsFactory<GraphicsAPI::OpenGL>::CreateTextureBuffer(width, height, bpp);

    m_Texture->CreateTexture(imagedata);
    m_Texture->Bind(slot);
}

void OpenGLRenderer::SetColour(float r, float g, float b, float a) {
    // basic.frag has a uniform declaration
    if (m_Shader) 
    {
        m_Shader->Bind();
        m_Shader->SetUniform4f("u_Color", r, g, b, a);
    }
    else
    {
        std::cout << "Warning: Shader is not bound" << std::endl;
    }
}

void OpenGLRenderer::ClearBuffers() 
{ 
    // clearing all buffer bindings
    if(m_VertexArray) m_VertexArray->Unbind();
    if(m_Shader) m_Shader->Unbind();
    if(m_IndexBuffer) m_IndexBuffer->Unbind();
    if(m_VertexBuffer) m_VertexBuffer->Unbind();
    if(m_Texture) m_Texture->Unbind();
}

