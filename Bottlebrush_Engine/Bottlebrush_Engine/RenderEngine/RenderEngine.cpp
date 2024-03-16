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


    /// @TODO provide this with some Casting methods to child classes for buffers, shader, arrays.
    
    // an idea for using macro
    // macro for using what Graphics API is being used
    // this is an example of a setup.
    // possibly needs to be put into a struct?
    if (GRAPHICS_API == "OpenGL")
    {
        // vertex array object
        OpenGLVertexArray vao;
        // 4 vertex and 2 points (2D)
        OpenGLVertexBuffer vb(positions, 4 * 2 * sizeof(float));

        // define the format of each vertex data 
        // i.e., 2 = 2 points of positions for each vertex (can use different numbers for different attributes)
        OpenGLVertexBufferLayout vbLayout;
        vbLayout.Push<float>(2);
        // add current buffer with its layout specs to the vertex array
        vao.AddBuffer(vb, vbLayout);

        // 6 = the count of elements in indices
        OpenGLIndexBuffer ib(indices, 6);

        // setup source shader files locations
        ShaderSourceFiles ssf;
        ssf.VertexSource = "Basic.vert";
        ssf.FragmentSource = "Basic.frag";

        // calling the constructor will read the files within ssf and apply them
        OpenGLShader shader(ssf);

        // basic.frag has a uniform declaration
        shader.Bind();
        shader.SetUniform4f("u_Color", 0.2f, 0.3f, 0.8f, 1.0f);

        // clearing all buffer bindings
        vao.Unbind();
        shader.Unbind();
        vb.UnBind();
        ib.UnBind();

        OpenGLRenderer r;

        // this needs to be called within the main draw loop
        r.Draw(vao, ib, shader);
    }
}
