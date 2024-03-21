//
//  Created by Alan Brunet 21/03/2024
//
#include "Texture.h"
#include "OpenGLTexture.h"

Texture* Texture::Create(const std::string& path) 
{
  return new OpenGLTexture(path);
}

int Texture::GetWidth() const {

}


int Texture::GetHieght() const {

}
