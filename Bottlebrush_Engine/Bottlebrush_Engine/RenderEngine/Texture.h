#pragma once

#include "OpenGLRenderer.h"

class Texture
{
protected:
	unsigned int m_RendererID;
	std::string m_Filepath;
	unsigned char* m_LocalBuffer;
	// BPP = bytes per pixel
	int m_Width, m_Height, m_BPP;

public:
	virtual ~Texture() = 0;

	virtual void Bind(unsigned int slot = 0) const = 0;
	virtual void Unbind() const = 0;

	virtual int GetWidth() const = 0;
    virtual int GetHeight() const = 0;
};
