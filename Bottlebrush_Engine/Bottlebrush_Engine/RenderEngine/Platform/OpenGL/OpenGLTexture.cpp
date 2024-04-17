#include "OpenGLTexture.h"

#include "OpenGLRenderer.h"

OpenGLTexture::OpenGLTexture(const std::filesystem::path& imageFilePath) {

    glGenTextures(1, &m_RendererID);
    CreateTexture(imageFilePath);
}

OpenGLTexture::~OpenGLTexture() 
{ 
    glDeleteTextures(1, &m_RendererID); 
}

void OpenGLTexture::CreateTexture(const std::filesystem::path& imageFilePath) {
    Image textureImage(imageFilePath);
    glBindTexture(GL_TEXTURE_2D, m_RendererID);

    // OpenGL expects image to start at bottom left, instead of top left
    
    // how the texture will be resampled down if it needs to be rendered smaller
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    // how the texture will be resampled up if it needs to be rendered larger
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // clamp the wrap modes, S & T is like x and y
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    // RGBA8 how you want opengl to format the data
    // RGBA is the format we are supplying
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, textureImage.getImageWidth(), textureImage.getImageHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, textureImage.getImageData());

    // Unbind texture
    glBindTexture(GL_TEXTURE_2D, 0);
}

void OpenGLTexture::Bind(unsigned int slot) const 
{
    // can bind to a different texture slot
    // 32 maximum texture slots
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, m_RendererID);
}

void OpenGLTexture::Unbind() const 
{
    glBindTexture(GL_TEXTURE_2D, 0); 
}

int OpenGLTexture::GetWidth() const 
{ 
    return m_Width; 
}

int OpenGLTexture::GetHeight() const 
{ 
    return m_Height; 
}

std::filesystem::path OpenGLTexture::GetFilePath() {
    return textureFilePath;
}

void OpenGLTexture::SetFilePath(const std::filesystem::path& texturePath) {
    textureFilePath = texturePath;
}
