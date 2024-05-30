#pragma once

#include <string>

class MD2Texture
{
private:
	unsigned int m_RendererID;
	std::string m_Filepath;
	unsigned char* m_LocalBuffer;
	// BPP = bytes per pixel
	int m_Width, m_Height, m_BPP;
public:
	MD2Texture();
	~MD2Texture();

	void CreateTexture(const std::string& path);
	void Bind(unsigned int slot = 0) const;
	void Unbind() const;

	inline int GetWidth() const { return m_Width; }
	inline int GetHeight() const { return m_Height; }
};