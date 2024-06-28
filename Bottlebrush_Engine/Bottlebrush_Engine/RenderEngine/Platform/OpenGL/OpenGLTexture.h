//
//  Created by Alan, Niamh 12/03/2024
//
#pragma once

#include "Texture.h"
#include <string>
#include <filesystem>
#include "Image.h"
#include "OpenGLFrameBuffer.h"

class OpenGLTexture : public Texture
{
private:
	unsigned int m_RendererID;

 public:
	/// @author Alan
    /// @brief Constructor that generates a texture buffer
	OpenGLTexture();
	~OpenGLTexture() override;

	/// @author Alan, Niamh Wilson
    /// @brief Creates a texture from a given texture image data.
    /// OpenGL expects image to start at bottom left, instead of top left. 
    /// May need to flip image data before passing.
    /// @param data is the image data
	void CreateTexture(const std::filesystem::path& imageFilePath, bool flip = true);

	/// @author Alan
    /// @brief Sets up the tex parameters for a cubemap.
	void InitCubeMap() override;

	/// @author Alan
    /// @brief Creates a tex 2D image for a cubemap
    /// @param data is the stream of data from the image
	/// @param index is which face the texture will be put against
	void CreateCubemap(const std::filesystem::path& imageFilePath, unsigned int index) override;

	/// @author Alan
    /// @brief Binds the CubeMap Texture to use / add
    /// @param slot can be different texture slots, maximum of 32 slots
	void BindCubeMap(unsigned int slot = 0) const override;

	/// @author Alan
    /// @brief Binds the Texture to use / add
    /// @param slot can be different texture slots, maximum of 32 slots
	void Bind(unsigned int slot = 0) const override;

	/// @author Alan
    /// @brief unbinds texture
	void Unbind() const override;
};
