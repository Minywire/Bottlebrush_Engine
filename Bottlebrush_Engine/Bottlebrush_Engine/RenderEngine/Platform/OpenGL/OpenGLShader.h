#pragma once

#include <string>
#include <unordered_map>

struct OpenGLShaderProgramSource
{
	std::string VertexSource;
	std::string FragmentSource;
};

class OpenGLShader
{
private:
	std::string m_FilePath;
	unsigned int m_RendererID;
	// caching for uniforms
	std::unordered_map<std::string, int> m_UniformLocationCache;
public:
	OpenGLShader(const std::string& filepath);
	~OpenGLShader();

	void Bind() const;
	void Unbind() const;

	// set uniforms
	void SetUniform1f(const std::string& name, float value);
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);

private:
	OpenGLShaderProgramSource ParseShader(const std::string& filepath);
	unsigned int CompileShader(unsigned int type, const std::string& source);
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
	int GetUniformLocation(const std::string& name);
};
