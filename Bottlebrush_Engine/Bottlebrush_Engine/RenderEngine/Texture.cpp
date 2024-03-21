//
//  Created by Alan Brunet 21/03/2024
//
#include "Texture.h"

Texture::Texture(const std::string& path)
    : m_Filepath(path),
      m_LocalBuffer(nullptr),
      m_Width(0),
      m_Height(0),
      m_BPP(0)
{}
