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

#include "Shader.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexBufferLayout.h"
#include "Texture.h"

enum class GraphicsAPI {
	OpenGL, Vulkan
};

template <GraphicsAPI>
class GraphicsFactory {
public:
	static std::unique_ptr<VertexBuffer> CreateVertexBuffer(float* vertices, unsigned int size);
	static std::unique_ptr<VertexArray> CreateVertexArray();
    static std::unique_ptr<VertexBufferLayout> CreateVertexBufferLayout();
    static std::unique_ptr<IndexBuffer> CreateIndexBuffer(const unsigned int* data, unsigned int count);
    static std::unique_ptr<Texture> CreateTextureBuffer(const std::string& path);
    static std::unique_ptr<Shader> CreateShaderBuffer(const ShaderSourceFiles& ssf);
};

template<>
class GraphicsFactory<GraphicsAPI::OpenGL> {
public:
    static std::unique_ptr<VertexBuffer> CreateVertexBuffer(float* vertices, unsigned int size) {
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
    static std::unique_ptr<Texture> CreateTextureBuffer(const std::string& path) {
        return std::make_unique<OpenGLTexture>(path);
    }
    static std::unique_ptr<Shader> CreateShaderBuffer(const ShaderSourceFiles& ssf) {
        return std::make_unique<OpenGLShader>(ssf);
    }
};