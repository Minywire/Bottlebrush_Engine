//
// Created by niamh on 26/12/2023.
// Edited by Alan Brunet on 16/03/24
//

#include "Shader.h"

Shader::Shader(ShaderSourceFiles ssf)
{
    m_SSF.VertexSource = ParseFile(ssf.VertexSource);
    m_SSF.FragmentSource = ParseFile(ssf.FragmentSource);
    m_SSF.ComputeSource = ParseFile(ssf.ComputeSource);
    m_SSF.GeometrySource = ParseFile(ssf.GeometrySource);
}

std::string Shader::ParseFile(const std::string& filename)
{
    std::string path;
    std::string extension;

    // Get file extension (should be its own function)
    auto index = filename.rfind('.');
    if (index == std::string::npos)
    {
        return "nullptr";
    }
    auto ext = filename.substr(index + 1);

    if      (ext == "vert") path = SHADER_SOURCE_DIR "Vertex/";
    else if (ext == "frag") path = SHADER_SOURCE_DIR "Fragment/";
    else if (ext == "geom") path = SHADER_SOURCE_DIR "Geometry/";
    else if (ext == "comp") path = SHADER_SOURCE_DIR "Compute/";

    return (path + filename);
}

bool Shader::CheckSSFValid(std::string filename)
{
    if (filename == "nullptr") return false;
    return true;
}
