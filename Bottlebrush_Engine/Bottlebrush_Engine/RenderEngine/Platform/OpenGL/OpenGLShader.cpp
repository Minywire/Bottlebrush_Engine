//
//  Created by Alan Brunet 12/03/2024
//
#define NUMSHADERTYPES 4

#include "OpenGLShader.h"
#include "OpenGLRenderer.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>


OpenGLShader::OpenGLShader(ShaderSourceFiles ssf) : Shader(ssf)
{
    m_Program = CreateShader();
}

OpenGLShader::~OpenGLShader()
{
    GLCall(glDeleteProgram(m_Program));
}

void OpenGLShader::Bind() const
{
    GLCall(glUseProgram(m_Program));
}

void OpenGLShader::Unbind() const
{
    GLCall(glUseProgram(0));
}

std::string OpenGLShader::FindFailedCompiler(unsigned int type)
{
    switch (type) 
    {
        case GL_VERTEX_SHADER:      return "vertex";
        case GL_FRAGMENT_SHADER:    return "fragment";
        case GL_COMPUTE_SHADER:     return "compute";
        case GL_GEOMETRY_SHADER:    return "geometry";
        default:                    return "unknown";
    }
}

unsigned int OpenGLShader::CompileShader(unsigned int type, const std::string& source)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    GLCall(glShaderSource(id, 1, &src, nullptr));
    GLCall(glCompileShader(id));

    // error checking
    int result;
    GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
    if (!result)
    {
        int length;
        GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
        char* message = (char*) malloc(length * sizeof(char)); //MARCO: Changed this to malloc since it's just a message string that can be cleared in this scope
        GLCall(glGetShaderInfoLog(id, length, &length, message));

        std::cout << "failed to compile" <<
            FindFailedCompiler(type)
            << " shader" << std::endl;
        std::cout << message << std::endl;

        free(message); //clear the string
        GLCall(glDeleteShader(id));

        free(message);
        return 0;
    }

    return id;
}

unsigned int OpenGLShader::DetermineShaderType(const std::string& filename)
{
    auto index = filename.rfind('.');
    auto ext = filename.substr(index + 1);

    if      (ext == "comp") return glCreateShader(GL_COMPUTE_SHADER);
    else if (ext == "frag") return glCreateShader(GL_FRAGMENT_SHADER);
    else if (ext == "geom") return glCreateShader(GL_GEOMETRY_SHADER);
    else if (ext == "vert") return glCreateShader(GL_VERTEX_SHADER);
    else                    assert(false);   
    return false;
}

void OpenGLShader::LinkShader()
{
    GLCall(glLinkProgram(m_Program));

    // verify linking success
    GLCall(glGetProgramiv(m_Program, GL_LINK_STATUS, &m_Status));
    if (m_Status == false) {
        GLCall(glGetProgramiv(m_Program, GL_INFO_LOG_LENGTH, &m_Length));
        // TODO: Do i need to do memory management stuff with this unique ptr?
        std::unique_ptr<char[]> buffer(new char[m_Length]);
        GLCall(glGetProgramInfoLog(m_Program, m_Length, nullptr, buffer.get()));
        fprintf(stderr, "%s", buffer.get());
    }
    assert(m_Status == true);
}

void OpenGLShader::AttachShader(std::string shadersource, unsigned int& program)
{
    unsigned int shader = CompileShader(DetermineShaderType(shadersource), LoadShaderType(shadersource));

    GLCall(glAttachShader(program, shader));
    LinkShader();
    GLCall(glValidateProgram(program));

    GLCall(glDeleteShader(shader));
}

std::string OpenGLShader::LoadShaderType(const std::string& filepath)
{
    // Load GLSL shader source from file
    std::ifstream file_stream(filepath);
    auto shader_file_contents = std::string(std::istreambuf_iterator<char>(file_stream),
        std::istreambuf_iterator<char>());

    return shader_file_contents;
}

unsigned int OpenGLShader::CreateShader()
{
    // needs to be modifiable for glAttachShader
    GLCall(unsigned int program = glCreateProgram());

    // check if source is valid, then attach the shader
    if (CheckSSFValid(m_SSF.VertexSource)) { AttachShader(m_SSF.VertexSource, m_Program); }
    if (CheckSSFValid(m_SSF.FragmentSource)) { AttachShader(m_SSF.FragmentSource, m_Program); }
    if (CheckSSFValid(m_SSF.ComputeSource)) { AttachShader(m_SSF.ComputeSource, m_Program); }
    if (CheckSSFValid(m_SSF.GeometrySource)) { AttachShader(m_SSF.GeometrySource, m_Program); }

    return m_Program;
}


void OpenGLShader::SetUniform1i(const std::string& name, int value)
{
    GLCall(glUniform1i(GetUniformLocation(name), value));
}

void OpenGLShader::SetUniform1f(const std::string& name, float value)
{
    GLCall(glUniform1f(GetUniformLocation(name), value));
}

void OpenGLShader::SetUniform3f(const std::string& name, float v0, float v1, float v2)
{
    GLCall(glUniform3f(GetUniformLocation(name), v0, v1, v2));
}

void OpenGLShader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
    GLCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
}


int OpenGLShader::GetUniformLocation(const std::string& name)
{
    // see if it exists within our map first, else add it
    if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
        return m_UniformLocationCache[name];
    int location = 0;
    // find the location
    GLCall(location = glGetUniformLocation(m_Program, name.c_str()));
    if (location == -1)
        std::cout << "Warning: uniform '" << name << "' doesn't exist!" << std::endl;

    // assign the location to the map
    m_UniformLocationCache[name] = location;
         
    return location;
}


