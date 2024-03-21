#pragma once

#include "Texture.h"

class OpenGLTexture : public Texture
{
private:

public:
	OpenGLTexture(const std::string& path);
	virtual ~OpenGLTexture() override;

	virtual void Bind(unsigned int slot = 0) const override;
	virtual void Unbind() const override;
};
