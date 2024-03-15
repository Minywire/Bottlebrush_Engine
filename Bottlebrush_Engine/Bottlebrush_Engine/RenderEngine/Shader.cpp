//
// Created by niamh on 26/12/2023.
//

#include "Shader.h"

Shader::Shader(const std::string& filename)
{
    mFilePath = ParseFile(filename);
}

std::string Shader::ParseFile(const std::string& filename)
{
    std::string path;
    std::string extension;

    // Get file extension (should be its own function)
    auto index = filename.rfind('.');
    auto ext = filename.substr(index + 1);

    if      (ext == "vert") path = SHADER_SOURCE_DIR "Vertex/";
    else if (ext == "frag") path = SHADER_SOURCE_DIR "Fragment/";
    else if (ext == "geom") path = SHADER_SOURCE_DIR "Geometry/";
    else if (ext == "comp") path = SHADER_SOURCE_DIR "Compute/";

    return (path + filename);
}

std::string Shader::LoadShader(const std::string& filepath)
{
    // Load GLSL shader source from file
    std::ifstream file_stream(filepath);
    auto shader_file_contents = std::string(std::istreambuf_iterator<char>(file_stream),
        std::istreambuf_iterator<char>());

    return shader_file_contents;
}
