//
//  Created by Alan Brunet 22/03/2024
//
#pragma once

#include "Platform/OpenGL/OpenGLShader.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"
#include "Platform/OpenGL/OpenGLVertexBuffer.h"
#include "Platform/OpenGL/OpenGLIndexBuffer.h"
#include "Platform/OpenGL/OpenGLVertexBufferLayout.h"
#include "Platform/OpenGL/OpenGLTexture.h"
#include "Platform/OpenGL/OpenGLRenderer.h"
#include "Platform/OpenGL/OpenGLModel.h"
#include "Platform/OpenGL/OpenGLMesh.h"

/// @author Alan Brunet
/// @brief Enum class to define which Graphics API to be used
enum class GraphicsAPI {
	OpenGL, Vulkan
};

/// @author Alan Brunet, Niamh Wilson
/// @brief Factory class to determine which Rendering API to be point to. 
/// Each Create function will return a unique pointer to the specified Graphics API component
template <GraphicsAPI>
class GraphicsFactory {
public:
    static std::unique_ptr<RenderEngine> CreateRenderer();
    static std::unique_ptr<VertexBuffer> CreateVertexBuffer(const void* vertices, unsigned int size);
    static std::unique_ptr<VertexArray> CreateVertexArray();    
    static std::unique_ptr<VertexBufferLayout> CreateVertexBufferLayout();
    static std::unique_ptr<IndexBuffer> CreateIndexBuffer(const unsigned int* data, unsigned int count);
    static std::unique_ptr<Texture> CreateTextureBuffer(int width, int height, int bbp);
    static std::unique_ptr<Shader> CreateShaderBuffer(const ShaderSourceFiles& ssf);
    static std::unique_ptr<Model> CreateModel(const std::string& filePath);
    static std::unique_ptr<Mesh> CreateMesh();
};

template<>
class GraphicsFactory<GraphicsAPI::OpenGL> {
public:
    static std::unique_ptr<RenderEngine> CreateRenderer() {
        return std::make_unique<OpenGLRenderer>();
    }
    static std::unique_ptr<VertexBuffer> CreateVertexBuffer(const void* vertices, unsigned int size) {
        return std::make_unique<OpenGLVertexBuffer>(vertices, size);
    }
    static std::unique_ptr<VertexArray> CreateVertexArray() {
        return std::make_unique<OpenGLVertexArray>();
    }
    static std::unique_ptr<VertexBufferLayout> CreateVertexBufferLayout() {
        return std::make_unique<OpenGLVertexBufferLayout>();
    }
    static std::unique_ptr<IndexBuffer> CreateIndexBuffer(const unsigned int* data, unsigned int count) {
        return std::make_unique<OpenGLIndexBuffer>(data, count);
    }
    static std::unique_ptr<Texture> CreateTextureBuffer(int width, int height, int bpp) {
        return std::make_unique<OpenGLTexture>(width, height, bpp);
    }
    static std::unique_ptr<Shader> CreateShaderBuffer(const ShaderSourceFiles& ssf) {
        return std::make_unique<OpenGLShader>(ssf);
    }
    static std::unique_ptr<Model> CreateModel(const std::string& filePath) {
        return std::make_unique<OpenGLModel>(filePath);
    }
    static std::unique_ptr<Mesh> CreateMesh(){
        return std::make_unique<OpenGLMesh>();
    };
};
