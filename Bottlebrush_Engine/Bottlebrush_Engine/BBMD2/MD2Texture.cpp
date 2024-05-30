#include "MD2Texture.h"

#include <stb/stb_image.h>
#include <glad/glad.h>
#include <iostream>

MD2Texture::MD2Texture()
	:
	m_Filepath(""),
	m_LocalBuffer(nullptr),
	m_Width(0),
	m_Height(0),
	m_BPP(0)
{
	
}

MD2Texture::~MD2Texture()
{
	glDeleteTextures(1, &m_RendererID);
}

void MD2Texture::CreateTexture(const std::string& path)
{
	// will Assimp load texture files aswell? instead of using stb_image?
	// OpenGL expects image to start at bottom left, instead of top left
	stbi_set_flip_vertically_on_load(false);
	// 4 = RGBA (desired channels)
	m_LocalBuffer = stbi_load(path.c_str(), &m_Width, &m_Height, &m_BPP, 0);

	glGenTextures(1, &m_RendererID);
	glBindTexture(GL_TEXTURE_2D, m_RendererID);

	// how the texture will be resampled down if it needs to be rendered smaller
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	// how the texture will be resampled up if it needs to be rendered larger
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// clamp the wrap modes, S & T is like x and y
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	GLenum format = GL_RGBA;
	if (m_BPP == 1)
		format = GL_RED;
	else if (m_BPP == 2)
		format = GL_RG;
	else if (m_BPP == 3)
		format = GL_RGB;
	else if (m_BPP == 4)
		format = GL_RGBA;

	// RGBA8 how you want opengl to format the data
	// RGBA is the format we are supplying
	glTexImage2D(GL_TEXTURE_2D, 0, format, m_Width, m_Height, 0, format, GL_UNSIGNED_BYTE, m_LocalBuffer);
	glGenerateMipmap(GL_TEXTURE_2D);
	// Unbind texture
	glBindTexture(GL_TEXTURE_2D, 0);

	if (m_LocalBuffer)
	{
		stbi_image_free(m_LocalBuffer);
		//std::cout << "Loaded Texture of size " << m_Width << " x " << m_Height << std::endl;
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}

	
}

void MD2Texture::Bind(unsigned int slot) const
{
	// can bind to a different texture slot
	// 32 maximum texture slots
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, m_RendererID);
}

void MD2Texture::Unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
