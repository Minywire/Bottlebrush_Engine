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

/// Contains the filenames of each shader type
/// These only need to specify the filename and not the full directory path
struct ShaderSourceFiles
{
    std::string VertexSource;
    std::string FragmentSource;
    std::string ComputeSource;
    std::string GeometrySource;
};

/// The program that will run on the GPU.
/// Needs Shader files to construct.
class Shader {
public:
    /// Constructor that gets full path name and registers it to member variable m_SSF
    Shader(ShaderSourceFiles ssf);
    /// Deconstructor
    virtual ~Shader() = default;

    /// Binds the Shader to use / add
    virtual void Bind() const = 0;
    /// Unbinds the Shader
    virtual void Unbind() const = 0;

    /// Sets uniforms found in shader files to values passed in
    virtual void SetUniform1f(const std::string& name, float value) = 0;
    virtual void SetUniform3f(const std::string& name, float v0, float v1, float v2) = 0;
    virtual void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3) = 0;

    // Disable Copying and Assignment
    Shader(Shader const &) = delete;
    Shader & operator=(Shader const &) = delete;

protected:
    /// protected member variables

    /// Unique ID for graphics API
    unsigned int m_Program;
    /// Shader file names
    ShaderSourceFiles m_SSF;
    /// Used to check if shader loads correctly
    int m_Status;
    /// For checking errors
    int m_Length;
    /// caching for uniforms
    std::unordered_map<std::string, int> m_UniformLocationCache;

    /// Returns the full path name
    std::string ParseFile(const std::string& filename);
    /// Validity check on path name
    bool CheckSSFValid(std::string source);
};


#endif //BOTTLEBRUSH_ENGINE_SHADER_H
