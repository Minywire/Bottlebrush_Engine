//
// Created by niamh on 26/12/2023.
// Edited by Alan on 16/03/24 
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

#include "glm/glm.hpp"

/// @author Alan
/// @brief Contains the filenames of each shader type.
/// These only need to specify the filename and not the full directory path.
/// They also do not need to be all initialised
struct ShaderSourceFiles
{
	std::filesystem::path VertexSource;
	std::filesystem::path FragmentSource;
	std::filesystem::path ComputeSource;
	std::filesystem::path GeometrySource;
};

/// @author Alan
/// @brief Creates a program for the GPU from shader program source files.
/// Needs Shader source files to construct as it loads files within Resources/Shader/ directory.
class Shader {
public:
	Shader(){};
	/// Deconstructor
	virtual ~Shader() = default;

	/// @author Alan
	/// @brief Binds the Shader to use / add
	virtual void Bind() const = 0;

	/// @author Alan
	/// @brief Unbinds the Shader
	virtual void Unbind() const = 0;

	/// @author Alan
	/// @brief Sets uniforms found in shader files to values passed in
	/// @param name is the uniform name within the Shader Program source file.
	/// e.g., "skybox" in the skybox shader files .vert/.frag
	virtual void SetUniform1i(const std::string& name, int value) = 0;

	/// @author Alan
	/// @brief Sets uniforms found in shader files to values passed in
	/// @param name is the uniform name within the Shader Program source file.
	virtual void SetUniform1f(const std::string& name, float value) = 0;

	/// @author Alan
	/// @brief Sets uniforms found in shader files to values passed in
	/// @param name is the uniform name within the Shader Program source file.
	virtual void SetUniform3f(const std::string& name, float v0, float v1, float v2) = 0;

	
	virtual void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3) = 0;

	/// @author Jaiden
	/// @brief Sets uniforms found in shader files to values passed in
	/// @param name is the uniform name within the Shader Program source file.
	/// E.g., "model", "view", "projection"
	virtual void SetUniformMatrix4fv(const std::string& name,
									 const glm::mat4& mat) = 0;

	// Disable Copying and Assignment
	Shader(Shader const &) = delete;
	Shader & operator=(Shader const &) = delete;

protected:

	/// @author Alan
	/// @brief Used to find which shader type failed compiling
	/// @param type takes in a Graphic API shader type
	/// @see CompileShader()
	/// @return the string of what Shader type has failed
	virtual std::string ShaderTypeToString(unsigned int type) = 0;

	/// @author Alan
	/// @brief Compiles a Shader, using a source shader file
	/// @param type Shader Type (vert, frag, comp, geo)
	/// @see DetermineShaderType()
	/// @param source the whole string from a shader program file source
	/// @see LoadShaderType()
	/// @return a compiled Shader ready to be attached
	virtual unsigned int CompileShader(unsigned int type, const std::string& source) = 0;

	/// @author Alan
	/// @brief Determines what Graphic API type the filename is from the extension
	/// @param filename Is the Shader Program source filename
	/// @return a Shader Type in Graphic API format
	virtual unsigned int DetermineShaderType(const std::filesystem::path& filename) = 0;

	/// @author Alan
	/// @brief Takes in a filepath that will be loaded
	/// @param full filepath of the shader program source
	/// @see GenFilePath()
	/// @return a string containing all within a Shader file
	virtual std::string LoadShaderType(const std::filesystem::path& filepath) = 0;

	/// @author Alan
	/// @brief Links a shader, performs a check after link process
	/// @param program is what will be linked to the shader
	/// @see https://docs.gl/gl4/glLinkProgram
	virtual void LinkShader(unsigned int& program) = 0;

	/// @author Alan
	/// @brief Attaches shader to a program object
	/// @param shadersource is the full string from a shader program file
	/// @see LoadShaderType()
	/// @param program is a modifiable int to attach shaders to
	virtual void AttachShader(const std::filesystem::path& shadersource, 
		unsigned int& program) = 0;

	/// @author Alan
	/// @brief using member struct ShaderSourceFiles, it checks their validity, 
	/// then attached the shader to a program object
	/// @return a fully loaded Shader Program
	virtual unsigned int CreateShader() = 0;

	/// @author Alan
	/// @brief Finds the declared Uniform name within the shader files. E.g., "u_Color"
	/// @return the position of the uniform
	virtual int GetUniformLocation(const std::string& name) = 0;
};


#endif //BOTTLEBRUSH_ENGINE_SHADER_H
