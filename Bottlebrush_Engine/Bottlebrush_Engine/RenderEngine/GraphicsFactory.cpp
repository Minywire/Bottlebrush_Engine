//
//  Created by Alan Brunet 22/03/2024
//
#include "GraphicsFactory.h"

//template<>
//class GraphicsFactory<GraphicsAPI::OpenGL> {
//public:
//    static std::unique_ptr<VertexBuffer> CreateVertexBuffer(float* vertices, unsigned int size) {
//        return std::make_unique<OpenGLVertexBuffer>(vertices, size);
//    }
//    static std::unique_ptr<VertexArray> CreateVertexArray() {
//        return std::make_unique<OpenGLVertexArray>();
//    }
//    static std::unique_ptr<VertexBufferLayout> CreateVertexBufferLayout() {
//        return std::make_unique<OpenGLVertexBufferLayout>();
//    }
//    static std::unique_ptr<IndexBuffer> CreateIndexBuffer(const unsigned int* data, unsigned int count) {
//        return std::make_unique<OpenGLIndexBuffer>(data, count);
//    }
//    static std::unique_ptr<Texture> CreateTextureBuffer(const std::string& path) {
//        return std::make_unique<OpenGLTexture>(path);
//    }
//    static std::unique_ptr<Shader> CreateShaderBuffer(const ShaderSourceFiles& ssf) {
//        return std::make_unique<OpenGLShader>(ssf);
//    }
//};

/*
* To implement vulkan
* 
template <>
class GraphicsFactory<GraphicsAPI::Vulkan> {
public:
    static std::unique_ptr<VertexBuffer> CreateVertexBuffer(float* vertices,
                                                          unsigned int size) {
        return std::make_unique<VulkanVertexBuffer>(vertices, size);
  }
};
*/
