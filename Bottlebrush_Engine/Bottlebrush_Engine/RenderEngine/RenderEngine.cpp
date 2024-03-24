//
// Created by Marco Garzon Lara on 27/11/2023.
// Edited by Alan Brunet on 16/03/24
//
#pragma once

#include "RenderEngine.h"
#include "GraphicsFactory.h"

#include <iostream>

void hello_world() {
    std::cout << "Hello, World" << std::endl;
}

void RenderEngine::TestSetupValues()
{
    /********************************************************************************************************************
    *
    *  THIS IS AN EXAMPLE OF HOW TO SETUP AND DRAW AN OBJECT. INSTANTIATION SHOULD HAPPEN OUTSIDE THE MAIN LOOP.
    *  ONLY THE DRAW CALL NEEDS TO BE WITHIN THE MAIN LOOP I.E., RENDERENGINE::DRAW();
    *
    *********************************************************************************************************************
  
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

    // vertex array object
    std::unique_ptr<VertexArray> vertex_array = GraphicsFactory<GraphicsAPI::OpenGL>::CreateVertexArray();
    //OpenGLVertexArray vao;
    
    // 4 vertex and 2 points (2D)
    std::unique_ptr<VertexBuffer> vertex_buffer = GraphicsFactory<GraphicsAPI::OpenGL>::CreateVertexBuffer(positions, 4 * 2 * sizeof(float));
    
    // define the format of each vertex data 
    // i.e., 2 = 2 points of positions for each vertex (can use different numbers for different attributes)
    std::unique_ptr<VertexBufferLayout> vbLayout = GraphicsFactory<GraphicsAPI::OpenGL>::CreateVertexBufferLayout();
    //OpenGLVertexBufferLayout* vbLayout;
    
    //@TODO This template belongs in the child class, how to access?
    vbLayout->Push(2, DataType::FLOAT);
    
    // add current buffer with its layout specs to the vertex array
    vertex_array->AddBuffer(*vertex_buffer, *vbLayout);

    // 6 = the count of elements in indices
    std::unique_ptr<IndexBuffer> ib = GraphicsFactory<GraphicsAPI::OpenGL>::CreateIndexBuffer(indices, 6);

    // setup source shader files locations
    ShaderSourceFiles ssf;
    ssf.VertexSource = "Basic.vert";
    ssf.FragmentSource = "Basic.frag";

    // calling the constructor will read the files within ssf and apply them
    std::unique_ptr<Shader> shader = std::make_unique<OpenGLShader>(ssf);

    // basic.frag has a uniform declaration
    shader->Bind();
    shader->SetUniform4f("u_Color", 0.2f, 0.3f, 0.8f, 1.0f);

    // clearing all buffer bindings
    vertex_array->Unbind();
    shader->Unbind();
    vertex_buffer->UnBind();
    ib->UnBind();

    std::unique_ptr<RenderEngine> r = std::make_unique<OpenGLRenderer>();

    // this needs to be called within the main draw loop
    r->Draw(*vertex_array, *ib, *shader);

    */
    
    
}
