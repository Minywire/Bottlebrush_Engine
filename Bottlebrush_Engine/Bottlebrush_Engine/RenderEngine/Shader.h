//
// Created by niamh on 26/12/2023.
//

#ifndef BOTTLEBRUSH_ENGINE_SHADER_H
#define BOTTLEBRUSH_ENGINE_SHADER_H

#define SHADER_SOURCE_DIR "Bottlebrush_Engine/Bottlebrush_Engine/Shaders/"

#include <string>
#include <iostream>
#include <fstream>
#include <memory>
#include <cassert>
#include <unordered_map>

#include <glad/glad.h>

class Shader {
public:
    Shader(const std::string& filename);
    virtual ~Shader() = 0;

    // is this needed?
    unsigned int GetShaderProgram() const { return mProgram; }

    // 
    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;

    virtual void SetUniform1f(const std::string& name, float value) = 0;
    virtual void SetUniform3f(const std::string& name, float v0, float v1, float v2) = 0;
    virtual void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3) = 0;

    // Disable Copying and Assignment
    Shader(Shader const &) = delete;
    Shader & operator=(Shader const &) = delete;

protected:
    // protected member variables
    unsigned int mProgram;
    std::string mFilePath;
    int mStatus;
    int mLength;
    // caching for uniforms
    std::unordered_map<std::string, int> mUniformLocationCache;

    std::string ParseFile(const std::string& filename);
    std::string LoadShader(const std::string& filepath);
};


#endif //BOTTLEBRUSH_ENGINE_SHADER_H
