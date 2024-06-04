//
//  Created by Alan 12/03/2024
//

#include "OpenGLShader.h"
#include "OpenGLRenderer.h"

OpenGLShader::OpenGLShader(ShaderSourceFiles ssf) 
    : m_SSF(ssf)
{
    m_Program = CreateShader();
}

OpenGLShader::~OpenGLShader()
{
    glDeleteProgram(m_Program);
}

void OpenGLShader::Bind() const
{
    glUseProgram(m_Program);
}

void OpenGLShader::Unbind() const
{
    glUseProgram(0);
}

std::string OpenGLShader::ShaderTypeToString(unsigned int type)
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
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    //@TODO delete after debugging
    //std::cout << "Shader Source:\n" << source << std::endl;

    // error checking
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (!result)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        std::string message;
        glGetShaderInfoLog(id, length, &length, message.data());

        std::cout << "failed to compile: " <<
            ShaderTypeToString(type)
            << " shader" << std::endl;
        std::cout << message << std::endl;

        glDeleteShader(id);
        return 0;
    }

    return id;
}

unsigned int OpenGLShader::DetermineShaderType(const std::filesystem::path& filename)
{
    std::filesystem::path ext = filename.extension();

    if      (ext == ".comp") return GL_COMPUTE_SHADER;
    else if (ext == ".frag") return GL_FRAGMENT_SHADER;
    else if (ext == ".geom") return GL_GEOMETRY_SHADER;
    else if (ext == ".vert") return GL_VERTEX_SHADER;
    return false;
}

void OpenGLShader::LinkShader(unsigned int& program)
{
    glLinkProgram(program);

    // verify linking success
    glGetProgramiv(program, GL_LINK_STATUS, &m_Status);
    if (m_Status == false) {
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &m_Length);
        // @TODO: Do i need to do memory management stuff with this unique ptr?
        std::unique_ptr<char[]> buffer(new char[m_Length]);
        glGetProgramInfoLog(program, m_Length, nullptr, buffer.get());
        fprintf(stderr, "Link unsuccessful: %s", buffer.get());
    }
    // @TODO this m_Status gets set to a negative value, causing assert to be called
    //assert(m_Status == true);
}

void OpenGLShader::AttachShader(const std::filesystem::path& shadersource, unsigned int& program)
{
    unsigned int shader = CompileShader(DetermineShaderType(shadersource), LoadShaderType(shadersource));

    glAttachShader(program, shader);
    LinkShader(program);
    glValidateProgram(program);

    glDeleteShader(shader);
}

std::string OpenGLShader::LoadShaderType(const std::filesystem::path& filepath)
{
    //@TODO delete after debugging
    std::cout << "Path: " << filepath << std::endl;

    // Load GLSL shader source from file
    std::ifstream file_stream(filepath);
    auto shader_file_contents = std::string(std::istreambuf_iterator<char>(file_stream),
        std::istreambuf_iterator<char>());

//    //@TODO delete after debugging
//    std::cout << "Load: \n" << shader_file_contents << std::endl;

    return shader_file_contents;
}

unsigned int OpenGLShader::CreateShader()
{
    // needs to be modifiable for glAttachShader
    unsigned int program = glCreateProgram();

    // check if source is valid, then attach the shader
    if (!m_SSF.VertexSource.empty()) 
    { 
      AttachShader(m_SSF.VertexSource, program); 
    }
    if (!m_SSF.FragmentSource.empty()) 
    {
      AttachShader(m_SSF.FragmentSource, program); 
    }
    if (!m_SSF.ComputeSource.empty()) 
    { 
      AttachShader(m_SSF.ComputeSource, program); 
    }
    if (!m_SSF.GeometrySource.empty()) 
    { 
      AttachShader(m_SSF.GeometrySource, program); 
    }

    return program;
}


void OpenGLShader::SetUniform1i(const std::string& name, int value)
{
    Bind();
    glUniform1i(GetUniformLocation(name), value);
}

void OpenGLShader::SetUniform1f(const std::string& name, float value)
{
    Bind();
    glUniform1f(GetUniformLocation(name), value);
}

void OpenGLShader::SetUniform3f(const std::string& name, float v0, float v1, float v2)
{
    Bind();
    glUniform3f(GetUniformLocation(name), v0, v1, v2);
}

void OpenGLShader::SetUniform3fv(const std::string& name,
                                 const glm::vec3& value) {
  Bind();
  glUniform3fv(GetUniformLocation(name), 1, &value[0]);
}

void OpenGLShader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
    Bind();
    glUniform4f(GetUniformLocation(name), v0, v1, v2, v3);
}

void OpenGLShader::SetUniformMatrix4fv(const std::string& name,
                                       const glm::mat4& mat) {
    Bind();
    glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &mat[0][0]);
}

int OpenGLShader::GetUniformLocation(const std::string& name)
{
    // see if it exists within our map first, else add it
    if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
        return m_UniformLocationCache[name];
    int location = 0;
    // find the location
    location = glGetUniformLocation(m_Program, name.c_str());
    if (location == -1)
        std::cout << "Warning: uniform '" << name << "' doesn't exist!" << std::endl;

    // assign the location to the map
    m_UniformLocationCache[name] = location;
         
    return location;
}

void OpenGLShader::SetUniformArray1fv(const std::string &name, int arrayLength, float *array) {
    Bind();
    glUniform1fv(GetUniformLocation(name), arrayLength, array);
}
