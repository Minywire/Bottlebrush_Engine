//
// Created by Marco Garzon Lara on 27/11/2023.
// Edited by Alan Brunet on 16/03/24
//
#define OPENGL

#ifdef OPENGL
    #define GRAPHICS_API "OpenGL"
    #include "OpenGLRenderer.h"
    #include "OpenGLShader.h"
    #include "OpenGLVertexArray.h"
    #include "OpenGLVertexBuffer.h"
    #include "OpenGLIndexBuffer.h"
    #include "OpenGLVertexBufferLayout.h"
#endif // OPENGL

#include "RenderEngine.h"

#include <iostream>

void hello_world() {
    std::cout << "Hello, World" << std::endl;
}

void RenderEngine::TestSetupValues()
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

    
    // macro for using what Graphics API is being used
    if (GRAPHICS_API == "OpenGL")
    {
        // vertex array object
        OpenGLVertexArray vao;
        // 4 vertex and 2 points (2D)
        OpenGLVertexBuffer vb(positions, 4 * 2 * sizeof(float));

        OpenGLVertexBufferLayout vbLayout;
        vbLayout.Push<float>(2);
        vao.AddBuffer(vb, vbLayout);

        OpenGLIndexBuffer ib(indices, 6);

        ShaderSourceFiles ssf;
        ssf.VertexSource = "Basic.vert";
        ssf.FragmentSource = "Basic.frag";
        OpenGLShader shader(ssf);
        // load frag aswell
        shader.Bind();
        shader.SetUniform4f("u_Color", 0.2f, 0.3f, 0.8f, 1.0f);

        vao.Unbind();
        shader.Unbind();
        vb.UnBind();
        ib.UnBind();
    }
}
