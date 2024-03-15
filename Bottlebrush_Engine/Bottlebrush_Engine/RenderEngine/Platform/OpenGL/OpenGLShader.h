//
//  Created by Alan Brunet 12/03/2024
//
#pragma once

#define SHADER_SOURCE_DIR "Bottlebrush_Engine/Bottlebrush_Engine/Shaders/"

#include "../../Shader.h"

#include <string>


enum class ShaderType
{
	NONE = -1, VERTEX = 0, FRAGMENT = 1
};

class OpenGLShader : public Shader
{
public:
	OpenGLShader(const std::string& filename);
	virtual ~OpenGLShader() override;

	virtual void Bind() const override;
	virtual void Unbind() const override;

	// set uniforms
	virtual void SetUniform1f(const std::string& name, float value) override;
	virtual void SetUniform3f(const std::string& name, float v0, float v1, float v2) override;
	virtual void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3) override;

private:
	std::string FindFailedCompiler(unsigned int type);
	unsigned int CompileShader(unsigned int type, const std::string& source);
	unsigned int DetermineShaderType(const std::string& filename);
	void LinkShader();
	unsigned int CreateShader();
	int GetUniformLocation(const std::string& name);
};
