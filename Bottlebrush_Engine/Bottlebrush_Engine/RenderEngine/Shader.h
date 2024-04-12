//
// Created by niamh on 26/12/2023.
// Edited by Alan Brunet on 16/03/24 
//

#ifndef BOTTLEBRUSH_ENGINE_SHADER_H
#define BOTTLEBRUSH_ENGINE_SHADER_H

#include <string>
#include <iostream>
#include <fstream>
#include <memory>
#include <cassert>
#include <unordered_map>
#include <filesystem>

/// @author Alan Brunet
/// @brief Contains the filenames of each shader type.
/// These only need to specify the filename and not the full directory path.
/// They also do not need to be all initialised
struct ShaderSourceFiles
{
    std::string VertexSource;
    std::string FragmentSource;
    std::string ComputeSource;
    std::string GeometrySource;
};

/// @author Alan Brunet
/// @brief Creates a program for the GPU from shader program source files.
/// Needs Shader source files to construct as it loads files within Shader/ directory.
class Shader {
public:
    Shader(){};
    /// Deconstructor
    virtual ~Shader() = default;

    /// @author Alan Brunet
    /// @brief Binds the Shader to use / add
    virtual void Bind() const = 0;

    /// @author Alan Brunet
    /// @brief Unbinds the Shader
    virtual void Unbind() const = 0;

    /// @author Alan Brunet
    /// @brief Sets uniforms found in shader files to values passed in
    /// @param name is the uniform name within the Shader Program source file. E.g., "u_Color"
    virtual void SetUniform1i(const std::string& name, int value) = 0;

    /// @author Alan Brunet
    /// @brief Sets uniforms found in shader files to values passed in
    /// @param name is the uniform name within the Shader Program source file.
    /// E.g., "u_Color"
    virtual void SetUniform1f(const std::string& name, float value) = 0;

    /// @author Alan Brunet
    /// @brief Sets uniforms found in shader files to values passed in
    /// @param name is the uniform name within the Shader Program source file.
    /// E.g., "u_Color"
    virtual void SetUniform3f(const std::string& name, float v0, float v1, float v2) = 0;

    /// @author Alan Brunet
    /// @brief Sets uniforms found in shader files to values passed in
    /// @param name is the uniform name within the Shader Program source file.
    /// E.g., "u_Color"
    virtual void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3) = 0;

    // Disable Copying and Assignment
    Shader(Shader const &) = delete;
    Shader & operator=(Shader const &) = delete;

protected:

    /// @author Alan Brunet
    /// @brief Used to find which shader type failed compiling
	/// @param type takes in a Graphic API shader type
	/// @see CompileShader()
	/// @return the string of what Shader type has failed
    virtual std::string ShaderTypeToString(unsigned int type) = 0;

	/// @author Alan Brunet
    /// @brief Compiles a Shader, using a source shader file
	/// @param type Shader Type (vert, frag, comp, geo)
	/// @see DetermineShaderType()
	/// @param source the whole string from a shader program file source
	/// @see LoadShaderType()
	/// @return a compiled Shader ready to be attached
	virtual unsigned int CompileShader(unsigned int type, const std::string& source) = 0;

	/// @author Alan Brunet
    /// @brief Determines what Graphic API type the filename is from the extension
	/// @param filename Is the Shader Program source filename
	/// @return a Shader Type in Graphic API format
	virtual unsigned int DetermineShaderType(const std::string& filename) = 0;

	/// @author Alan Brunet
	/// @brief Takes in a filepath that will be loaded
    /// @param full filepath of the shader program source
    /// @see GenFilePath()
    /// @return a string containing all within a Shader file
	virtual std::string LoadShaderType(const std::filesystem::path& filepath) = 0;

	/// @author Alan Brunet
    /// @brief Links a shader, performs a check after link process
    /// @param program is what will be linked to the shader
    /// @see https://docs.gl/gl4/glLinkProgram
	virtual void LinkShader(unsigned int& program) = 0;

	/// @author Alan Brunet
    /// @brief Attaches shader to a program object
	/// @param shadersource is the full string from a shader program file
	/// @see LoadShaderType()
	/// @param program is a modifiable int to attach shaders to
	virtual void AttachShader(const std::string& shadersource, unsigned int& program) = 0;

    /// @author Alan Brunet
    /// @brief using member struct ShaderSourceFiles, it checks their validity, 
    /// then attached the shader to a program object
	/// @return a fully loaded Shader Program
	virtual unsigned int CreateShader() = 0;

	/// @author Alan Brunet
    /// @brief Finds the declared Uniform name within the shader files. E.g., "u_Color"
    /// @return the position of the uniform
	virtual int GetUniformLocation(const std::string& name) = 0;

    /// @author Alan Brunet
    /// @brief Takes in a filename and returns the full path directory
    /// @param filename Just a filename to be used as a Shader Program. e.g., "Basic.vert"
    /// @return Returns the full path name
    virtual std::filesystem::path GenFilePath(const std::string& filename) = 0;

    /// @author Alan Brunet
    /// @brief Validity check on path name
    /// @param source is the ShaderSourceFile filename
    /// @see CreateShader()
    /// @return True or False on valid filepath
    virtual bool CheckSSFValid(const std::string& source) = 0;
};


#endif //BOTTLEBRUSH_ENGINE_SHADER_H
