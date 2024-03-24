#pragma once

#include "Texture.h"
#include <string>

class OpenGLTexture : public Texture
{
private:
	unsigned int m_RendererID;
	std::string m_Filepath;
	unsigned char* m_LocalBuffer;
	// BPP = bytes per pixel
	int m_Width, m_Height, m_BPP;

 public:
	OpenGLTexture(const std::string& path);
	~OpenGLTexture() override;

	void Bind(unsigned int slot = 0) const override;
	void Unbind() const override;

	int GetWidth() const override;
    int GetHeight() const override;
};
