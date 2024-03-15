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

struct ShaderSourceFiles
{
    std::string VertexSource;
    std::string FragmentSource;
    std::string ComputeSource;
    std::string GeometrySource;
};

class Shader {
public:
    Shader(ShaderSourceFiles ssf);
    virtual ~Shader() = default;

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
    ShaderSourceFiles mSSF;
    int mStatus;
    int mLength;
    // caching for uniforms
    std::unordered_map<std::string, int> mUniformLocationCache;

    std::string ParseFile(const std::string& filename);
    bool CheckSSFValid(std::string source);
};


#endif //BOTTLEBRUSH_ENGINE_SHADER_H
