#include "OpenGLTexture.h"

OpenGLTexture::OpenGLTexture(const std::string& path) : m_Filepath(path),
      m_LocalBuffer(nullptr),
      m_Width(0),
      m_Height(0),
      m_BPP(0) 
{
  /* 
  * @TODO find an alternative to stbi.h for loading files
  * 
  // will Assimp load texture files aswell? instead of using stb_image?
  // OpenGL expects image to start at bottom left, instead of top left
  stbi_set_flip_vertically_on_load(1);
  // 4 = RGBA (desired channels)
  m_LocalBuffer = stbi_load(path.c_str(), &m_Width, &m_Height, &m_BPP, 4);
  */

  GLCall(glGenTextures(1, &m_RendererID));
  GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));

  // how the texture will be resampled down if it needs to be rendered smaller
  GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
  // how the texture will be resampled up if it needs to be rendered larger
  GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
  // clamp the wrap modes, S & T is like x and y
  GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
  GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

  // RGBA8 how you want opengl to format the data
  // RGBA is the format we are supplying
  GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA,
                      GL_UNSIGNED_BYTE, m_LocalBuffer));
  // Unbind texture
  GLCall(glBindTexture(GL_TEXTURE_2D, 0));

  // will find an alternative to stbi.h for loading files
  //if (m_LocalBuffer) stbi_image_free(m_LocalBuffer);
}

OpenGLTexture::~OpenGLTexture() 
{ 
    GLCall(glDeleteTextures(1, &m_RendererID)); 
}

void OpenGLTexture::Bind(unsigned int slot) const 
{
  // can bind to a different texture slot
  // 32 maximum texture slots
  GLCall(glActiveTexture(GL_TEXTURE0 + slot));
  GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));
}

void OpenGLTexture::Unbind() const 
{
    GLCall(glBindTexture(GL_TEXTURE_2D, 0)); 
}
