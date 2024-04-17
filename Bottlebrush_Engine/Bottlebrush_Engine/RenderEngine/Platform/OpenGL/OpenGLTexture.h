#pragma once

#include "Texture.h"
#include <string>
#include <filesystem>
#include "Image.h"

class OpenGLTexture : public Texture
{
private:
	unsigned int m_RendererID;

 public:
	/// @author Alan Brunet
    /// @brief Constructor that generates a texture buffer
	OpenGLTexture(const std::filesystem::path& imageFilePath);
	~OpenGLTexture() override;

	/// @author Alan Brunet, Niamh Wilson
    /// @brief Creates a texture from a given texture image data.
    /// OpenGL expects image to start at bottom left, instead of top left. 
    /// May need to flip image data before passing.
    /// @param data is the image data
	void CreateTexture(const std::filesystem::path& imageFilePath);

	/// @author Alan Brunet
    /// @brief Binds the Texture to use / add
    /// @param slot can be different texture slots, maximum of 32 slots
	void Bind(unsigned int slot = 0) const override;

	/// @author Alan Brunet
    /// @brief unbinds texture
	void Unbind() const override;
};
