//
// Created by niamh on 26/12/2023.
//

#include "Shader.h"

Shader::Shader() {
    mProgram = glCreateProgram();
}

Shader::~Shader() {
    glDeleteProgram(mProgram);
}

Shader & Shader::Activate() {
    glUseProgram(mProgram);
    return *this;
}

// TODO extrapolate this function into several smaller ones
Shader & Shader::Attach(const std::string &filename) {
    std::string path;
    std::string extension;

    // Get file extension (should be its own function)
    auto index = filename.rfind('.');
    auto ext = filename.substr(index + 1);

    if (ext == "vert") path = SHADER_SOURCE_DIR "Vertex/";
    else if(ext == "frag") path = SHADER_SOURCE_DIR "Fragment/";
    else if(ext == "geom") path = SHADER_SOURCE_DIR "Geometry/";
    else if(ext == "comp") path = SHADER_SOURCE_DIR "Compute/";

    // Load GLSL shader source from file
    std::ifstream file_stream(path + filename);
    auto shader_file_contents = std::string(std::istreambuf_iterator<char>(file_stream),
            std::istreambuf_iterator<char>());

    // Create a shader object
    const char * source = shader_file_contents.c_str();
    auto shader = Create(filename);
    glShaderSource(shader, 1, & source, nullptr);
    glCompileShader(shader);

    // Validate shader creation (could be a separate function?)
    glGetShaderiv(shader, GL_COMPILE_STATUS, &mStatus);

    if(mStatus == false) {
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, & mLength);
        // TODO: Do i need to do memory management stuff with this unique ptr?
        std::unique_ptr<char[]> buffer(new char[mLength]);
        glGetShaderInfoLog(shader, mLength, nullptr, buffer.get());
        fprintf(stderr, "%s\n%s", filename.c_str(), buffer.get());
    }

    // Attach the shader and free allocated memory
    glAttachShader(mProgram, shader);
    glDeleteShader(shader);

    return *this;
}

GLuint Shader::Create(const std::string &filename) {
    auto index = filename.rfind('.');
    auto ext = filename.substr(index + 1);

    if(ext == "comp") return glCreateShader(GL_COMPUTE_SHADER);
    else if(ext == "frag") return glCreateShader(GL_FRAGMENT_SHADER);
    else if(ext == "geom") return glCreateShader(GL_GEOMETRY_SHADER);
    else if(ext == "vert") return glCreateShader(GL_VERTEX_SHADER);
    else                   return false;
}

GLuint Shader::GetShaderProgram() const {
    return mProgram;
}

Shader & Shader::Link() {
    glLinkProgram(mProgram);

    // verify linking success
    glGetProgramiv(mProgram, GL_LINK_STATUS, &mStatus);
    if(mStatus == false) {
        glGetProgramiv(mProgram, GL_INFO_LOG_LENGTH, & mLength);
        // TODO: Do i need to do memory management stuff with this unique ptr?
        std::unique_ptr<char[]> buffer(new char[mLength]);
        glGetProgramInfoLog(mProgram, mLength, nullptr, buffer.get());
        fprintf(stderr, "%s", buffer.get());
    }
    assert(mStatus == true);
    return *this;
}

void Shader::Bind(int location, float value) {
    glUniform1f(location, value);
}
