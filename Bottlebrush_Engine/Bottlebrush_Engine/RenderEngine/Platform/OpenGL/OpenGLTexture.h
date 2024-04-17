#pragma once

#include "Texture.h"
#include <string>
#include <filesystem>

class OpenGLTexture : public Texture
{
private:
	unsigned int m_RendererID;
	unsigned char* m_LocalBuffer;
	// BPP = bytes per pixel
	int m_Width = 0, m_Height = 0, m_BPP = 0;

 public:
	/// @author Alan Brunet
    /// @brief Constructor that generates a texture buffer
	OpenGLTexture(int width, int height, int bpp);
	~OpenGLTexture() override;

	/// @author Alan Brunet
    /// @brief Creates a texture from a given texture image data.
    /// OpenGL expects image to start at bottom left, instead of top left. 
    /// May need to flip image data before passing.
    /// @param data is the image data
	void CreateTexture(unsigned char* data) override;

	/// @author Alan Brunet
    /// @brief Binds the Texture to use / add
    /// @param slot can be different texture slots, maximum of 32 slots
	void Bind(unsigned int slot = 0) const override;

	/// @author Alan Brunet
    /// @brief unbinds texture
	void Unbind() const override;

	/// @author Alan Brunet
    /// @return member width
	int GetWidth() const override;

	/// @author Alan Brunet
    /// @return member height
    int GetHeight() const override;

    std::filesystem::path GetFilePath();
    void SetFilePath(const std::filesystem::path& texturePath) override;
};
