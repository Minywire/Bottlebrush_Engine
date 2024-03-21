//
//  Created by Alan Brunet 12/03/2024
//
#pragma once

#define SHADER_SOURCE_DIR "Bottlebrush_Engine/Bottlebrush_Engine/Shaders/"

#include "Shader.h"

#include <string>

/// The program that will run on the GPU.
/// Needs Shader files to construct.
class OpenGLShader : public Shader
{
public:
	/// Constructor that gets full path name and registers it to member variable m_SSF
	OpenGLShader(ShaderSourceFiles ssf);
	/// Deconstructor
	virtual ~OpenGLShader() override;

	/// Binds the Shader to use / add
	virtual void Bind() const override;
	/// Unbinds the Shader
	virtual void Unbind() const override;

	/// Sets uniforms found in shader files to values passed in
	virtual void SetUniform1i(const std::string& name, int value) override;
	virtual void SetUniform1f(const std::string& name, float value) override;
	virtual void SetUniform3f(const std::string& name, float v0, float v1, float v2) override;
	virtual void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3) override;

private:
	/// protected member methods
	/// Used to find which shader type failed compiling
	std::string FindFailedCompiler(unsigned int type);

	/// Creates a Shader, using a source shader file
	/// @param type Shader Type (vert, frag, comp, geo)
	/// @see DetermineShaderType()
	/// @param source the whole string from a shader file source
	/// @see LoadShaderType()
	unsigned int CompileShader(unsigned int type, const std::string& source);

	/// Returns a Shader Type in OpenGL format
	/// @param filename Checks extension to see what file type it is
	unsigned int DetermineShaderType(const std::string& filename);

	/// Returns a string containing all within a Shader file
	std::string LoadShaderType(const std::string& filepath);
	
	/// Links a shader to m_Program
	void LinkShader();

	/// Attaches to a Shader program
	/// @param shadersource is the full string from a shader file
	/// @param program is a modifiable int to attach shaders to
	void AttachShader(std::string shadersource, unsigned int& program);

	/// Returns a Shader Program
	unsigned int CreateShader();

	/// Finds the declared Uniform name within the shader files
	int GetUniformLocation(const std::string& name);
};
