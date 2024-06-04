//
//  Created by Alan 12/03/2024
//
#pragma once

#include "Shader.h"
#include "glm/glm.hpp"

/// @author Alan
/// @brief Creates a program for the GPU from shader program source files.
/// Needs Shader source files to construct as it loads files within
/// Resources/Shader/ directory.
class OpenGLShader : public Shader
{
public:
	/// Constructor that gets full path name and registers it to member variable m_SSF
	OpenGLShader(ShaderSourceFiles ssf);
	/// Deconstructor
	~OpenGLShader() override;

	/// @author Alan
	/// @brief Binds the Shader to use / add
	void Bind() const override;

	/// @author Alan
	/// @brief Unbinds the Shader
	void Unbind() const override;

	/// @author Alan
	/// @brief Sets uniforms found in shader files to values passed in
	/// @param name is the uniform name within the Shader Program source file. E.g., "u_Color"
	void SetUniform1i(const std::string& name, int value) override;

	/// @author Alan
	/// @brief Sets uniforms found in shader files to values passed in
	/// @param name is the uniform name within the Shader Program source file.
	/// E.g., "u_Color"
	void SetUniform1f(const std::string& name, float value) override;

	/// @author Alan
	/// @brief Sets uniforms found in shader files to values passed in
	/// @param name is the uniform name within the Shader Program source file.
	/// E.g., "u_Color"
	void SetUniform3f(const std::string& name, float v0, float v1, float v2) override;

        void SetUniform3fv(const std::string& name,
                           const glm::vec3& value) override;

        /// @author Alan
	/// @brief Sets uniforms found in shader files to values passed in
	/// @param name is the uniform name within the Shader Program source file.
	/// E.g., "u_Color"
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3) override;

	/// @author Jaiden
	/// @brief Sets uniforms found in shader files to values passed in
	/// @param name is the uniform name within the Shader Program source file.
	/// E.g., "model", "view", "projection"
	void SetUniformMatrix4fv(const std::string& name,
								const glm::mat4& mat) override;

    /**
     * @author Niamh
     * @brief Sets uniforms found in shader files to values passed in
     * @param name The uniform name within the Shader Program source file. E.g. "model", "view", "projection".
     * @param arrayLength The number of elements in the array.
     * @param array The array values.
     */
    void SetUniformArray1fv(const std::string& name, int arrayLength, float array[]) override;
private:
	/// Struct for carrying file locations
	ShaderSourceFiles m_SSF;

	/// Unique ID for graphics API
	unsigned int m_Program;

	/// Used to check if shader loads correctly
	int m_Status;
	/// For checking errors
	int m_Length;
	/// caching for uniforms
	std::unordered_map<std::string, int> m_UniformLocationCache;

	/// @author Alan
	/// @brief Used to find which shader type failed compiling
	/// @param type takes in a Graphic API shader type
	/// @see CompileShader()
	/// @return the string of what Shader type has failed
	std::string ShaderTypeToString(unsigned int type) override;

	/// @author Alan
	/// @brief Compiles a Shader, using a source shader file
	/// @param type Shader Type (vert, frag, comp, geo)
	/// @see DetermineShaderType()
	/// @param source the whole string from a shader program file source
	/// @see LoadShaderType()
	/// @return a compiled Shader ready to be attached
	unsigned int CompileShader(unsigned int type, const std::string& source) override;

	/// @author Alan
	/// @brief Determines what Graphic API type the filename is from the extension
	/// @param filename Is the Shader Program source filename
	/// @return a Shader Type in Graphic API format
	unsigned int DetermineShaderType(const std::filesystem::path& filename);

	/// @author Alan
	/// @brief Takes in a filepath that will be loaded
	/// @param full filepath of the shader program source
	/// @see GenFilePath()
	/// @return a string containing all within a Shader file
	std::string LoadShaderType(const std::filesystem::path& filepath) override;

	/// @author Alan
	/// @brief Links a shader, performs a check after link process
	/// @param program is what will be linked to the shader
	/// @see https://docs.gl/gl4/glLinkProgram
	void LinkShader(unsigned int& program) override;

	/// @author Alan
	/// @brief Attaches shader to a program object
	/// @param shadersource is the full string from a shader program file
	/// @see LoadShaderType()
	/// @param program is a modifiable int to attach shaders to
	void AttachShader(const std::filesystem::path& shadersource, 
		unsigned int& program) override;

	/// @author Alan
	/// @brief using member struct ShaderSourceFiles, it checks their validity, 
	/// then attached the shader to a program object
	/// @return a fully loaded Shader Program
	unsigned int CreateShader()override;

	/// @author Alan
	/// @brief Finds the declared Uniform name within the shader files. 
	/// E.g., "model", "view", "projection", "skybox"
	/// @return the position of the uniform
	int GetUniformLocation(const std::string& name)override;
};
