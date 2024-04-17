#include "OpenGLTexture.h"

#include "OpenGLRenderer.h"

OpenGLTexture::OpenGLTexture(int width, int height, int bpp)
    : m_LocalBuffer(nullptr), m_Width(width), m_Height(height), m_BPP(bpp)
{
    glGenTextures(1, &m_RendererID);
}

OpenGLTexture::~OpenGLTexture() 
{ 
    glDeleteTextures(1, &m_RendererID); 
}

void OpenGLTexture::CreateTexture(unsigned char* data) {

    /* 
    * @TODO find an alternative to stbi.h for loading files
    * 
    // will Assimp load texture files aswell? instead of using stb_image?
    // OpenGL expects image to start at bottom left, instead of top left
    stbi_set_flip_vertically_on_load(1);
    // 4 = RGBA (desired channels)
    m_LocalBuffer = stbi_load(path.c_str(), &m_Width, &m_Height, &m_BPP, 4);

    // will find an alternative to stbi.h for loading files
    //if (m_LocalBuffer) stbi_image_free(m_LocalBuffer);
    */

    m_LocalBuffer = data; 
    
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
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer);

    // Unbind texture
    glBindTexture(GL_TEXTURE_2D, 0);
}

void OpenGLTexture::InitCubeMap() {
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}

void OpenGLTexture::CreateCubemap(unsigned char* data, unsigned int index) {
    glGenTextures(1, &m_RendererID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_RendererID);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + index, 0, GL_RGB, m_Width, m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
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
