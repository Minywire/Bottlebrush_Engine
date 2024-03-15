#include "Shader.h"
//
// Created by niamh on 26/12/2023.
//

#include "Shader.h"

Shader::Shader(ShaderSourceFiles ssf)
{
    mSSF.VertexSource = ParseFile(ssf.VertexSource);
    mSSF.FragmentSource = ParseFile(ssf.FragmentSource);
    mSSF.ComputeSource = ParseFile(ssf.ComputeSource);
    mSSF.GeometrySource = ParseFile(ssf.GeometrySource);
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
