//
//  Created by Alan Brunet 22/03/2024
//
#pragma once

#include "OpenGLShader.h"
#include "OpenGLVertexArray.h"
#include "OpenGLVertexBuffer.h"
#include "OpenGLIndexBuffer.h"
#include "OpenGLVertexBufferLayout.h"
#include "OpenGLTexture.h"

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
    static std::unique_ptr<Shader> CreateShaderBuffer(ShaderSourceFiles ssf);
};
