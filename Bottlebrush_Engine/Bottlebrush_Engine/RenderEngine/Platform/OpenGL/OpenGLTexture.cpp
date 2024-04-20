#include "OpenGLTexture.h"

#include "OpenGLRenderer.h"

OpenGLTexture::OpenGLTexture() {

    glGenTextures(1, &m_RendererID);
    //CreateTexture(imageFilePath);
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

    int channels = textureImage.getChannels();
    GLenum format = GL_RGBA;
    if (channels == 1)
      format = GL_RED;
    else if (channels == 2)
      format = GL_RG;
    else if (channels == 3)
      format = GL_RGB;
    else if (channels == 4)
      format = GL_RGBA;

    // RGBA8 how you want opengl to format the data
    // RGBA is the format we are supplying
    glTexImage2D(GL_TEXTURE_2D, 0, format, textureImage.getImageWidth(), textureImage.getImageHeight(), 0, format, GL_UNSIGNED_BYTE, textureImage.getImageData());

    // Unbind texture
    glBindTexture(GL_TEXTURE_2D, 0);
}

void OpenGLTexture::InitCubeMap() {
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_RendererID);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}

void OpenGLTexture::CreateCubemap(const std::filesystem::path& imageFilePath, unsigned int index) {
    Image cubemapImage(imageFilePath);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + index, 0, GL_RGB, cubemapImage.getImageWidth(), cubemapImage.getImageHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, cubemapImage.getImageData());
}

void OpenGLTexture::BindCubeMap(unsigned int slot) const {
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_RendererID);
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
