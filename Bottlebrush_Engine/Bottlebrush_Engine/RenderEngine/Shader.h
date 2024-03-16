//
// Created by niamh on 26/12/2023.
// Edited by Alan Brunet on 16/03/24 
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
    unsigned int m_Program;
    ShaderSourceFiles m_SSF;
    int m_Status;
    int m_Length;
    // caching for uniforms
    std::unordered_map<std::string, int> m_UniformLocationCache;

    std::string ParseFile(const std::string& filename);
    bool CheckSSFValid(std::string source);
};


#endif //BOTTLEBRUSH_ENGINE_SHADER_H
