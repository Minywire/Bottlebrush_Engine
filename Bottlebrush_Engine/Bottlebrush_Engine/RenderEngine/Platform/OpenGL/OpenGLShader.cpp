//
//  Created by Alan Brunet 12/03/2024
//
#include "OpenGLShader.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "OpenGLRenderer.h"

OpenGLShader::OpenGLShader(const std::string& filename) 
    : Shader(filename)
{
    mProgram = CreateShader();
}

OpenGLShader::~OpenGLShader()
{
    GLCall(glDeleteProgram(mProgram));
}

void OpenGLShader::Bind() const
{
    GLCall(glUseProgram(mProgram));
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
        char* message = (char*)_malloca(length * sizeof(char));
        GLCall(glGetShaderInfoLog(id, length, &length, message));
        std::cout << "failed to compile" <<
            // TODO switch case on what shader
            FindFailedCompiler(type)
            << " shader" << std::endl;
        std::cout << message << std::endl;

        GLCall(glDeleteShader(id));
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
    GLCall(glLinkProgram(mProgram));

    // verify linking success
    GLCall(glGetProgramiv(mProgram, GL_LINK_STATUS, &mStatus));
    if (mStatus == false) {
        GLCall(glGetProgramiv(mProgram, GL_INFO_LOG_LENGTH, &mLength));
        // TODO: Do i need to do memory management stuff with this unique ptr?
        std::unique_ptr<char[]> buffer(new char[mLength]);
        GLCall(glGetProgramInfoLog(mProgram, mLength, nullptr, buffer.get()));
        fprintf(stderr, "%s", buffer.get());
    }
    assert(mStatus == true);
}

unsigned int OpenGLShader::CreateShader()
{
    GLCall(unsigned int program = glCreateProgram());
    unsigned int shader = CompileShader(DetermineShaderType(mFilePath),LoadShader(mFilePath));

    GLCall(glAttachShader(program, shader));
    LinkShader();
    GLCall(glValidateProgram(program));

    GLCall(glDeleteShader(shader));

    return program;
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
    if (mUniformLocationCache.find(name) != mUniformLocationCache.end())
        return mUniformLocationCache[name];

    GLCall(int location = glGetUniformLocation(mProgram, name.c_str()));
    if (location == -1)
        std::cout << "Warning: uniform '" << name << "' doesn't exist!" << std::endl;

    mUniformLocationCache[name] = location;
         
    return location;
}


