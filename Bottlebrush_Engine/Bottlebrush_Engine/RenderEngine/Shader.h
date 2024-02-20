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

#include <glad/glad.h>

class Shader {
public:
    Shader();
    ~Shader();

    // Public member functions
    Shader & Activate();
    Shader & Attach(std::string const & filepath);
    static GLuint Create(std::string const & filename);
    GLuint GetShaderProgram() const;
    Shader & Link();

    // Wrap calls to glUniform
    void Bind(int location, float value);

    // Disable Copying and Assignment
    Shader(Shader const &) = delete;
    Shader & operator=(Shader const &) = delete;

private:
    // private member variables
    GLuint mProgram;
    GLint mStatus{};
    GLint mLength{};
};


#endif //BOTTLEBRUSH_ENGINE_SHADER_H
