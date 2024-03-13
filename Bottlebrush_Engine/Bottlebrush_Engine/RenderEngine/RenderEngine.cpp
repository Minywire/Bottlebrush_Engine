//
// Created by Marco Garzon Lara on 27/11/2023.
//

#include "RenderEngine.h"

#include <iostream>

#include "Platform/OpenGL/OpenGLRenderer.h"
#include "Platform/OpenGL/OpenGLVertexBufferLayout.h"

void hello_world() {
    std::cout << "Hello, World" << std::endl;
}

void RenderEngine::Test()
{
    // drawing a square, 4 vertex positions
    float positions[] = {
            -0.5f, -0.5f, // 0
             0.5f, -0.5f, // 1
             0.5f, 0.5f,  // 2
            -0.5f, 0.5f,  // 3
    };

    // index buffer for vertex positions
    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    /*

    // vertex array object
    OpenGLVertexArray vao;
    // 4 vertex and 2 points (2D)
    OpenGLVertexBuffer vb(positions, 4 * 2 * sizeof(float));

    OpenGLVertexBufferLayout vbLayout;
    vbLayout.Push<float>(2);
    vao.AddBuffer(vb, vbLayout);

    OpenGLIndexBuffer ib(indices, 6);

    OpenGLShader shader("Bottlebrush_Engine/Bottlebrush_Engine/Shaders/Vertex/test.vert");
    shader.Bind();
    shader.SetUniform4f("u_Color", 0.2f, 0.3f, 0.8f, 1.0f);

    vao.Unbind();
    shader.Unbind();
    vb.UnBind();
    ib.UnBind();

    OpenGLRenderer renderer;

    */
}

void RenderEngine::Draw() const
{

}
