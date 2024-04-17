#pragma once


#include <filesystem> //@TODO maybe delete?

/// @author Alan Brunet
/// @brief Class to create and store textures, this can hold up to 32 different texture slots
class Texture
{
protected:

public:
    Texture(){};
    virtual ~Texture() = default;

    /// @author Alan Brunet
    /// @brief Creates a texture from a given texture image data.
    /// OpenGL expects image to start at bottom left, instead of top left. 
    /// May need to flip image data before passing.
    /// @param data is the image data
    virtual void CreateTexture(unsigned char* data) = 0;

    virtual void InitCubeMap() = 0;
    virtual void CreateCubemap(unsigned char* data, unsigned int index) = 0;

    virtual void BindCubeMap(unsigned int slot = 0) const = 0;

    /// @author Alan Brunet
    /// @brief Binds the Texture to use / add
    /// @param slot can be different texture slots, maximum of 32 slots. defaulted to 1 (0)
    virtual void Bind(unsigned int slot = 0) const = 0;
    
    /// @author Alan Brunet
    /// @brief unbinds texture
    virtual void Unbind() const = 0;

    /// @author Alan Brunet
    /// @return member width
    virtual int GetWidth() const = 0;

	/// @author Alan Brunet
    /// @return member height
    virtual int GetHeight() const = 0;
};
