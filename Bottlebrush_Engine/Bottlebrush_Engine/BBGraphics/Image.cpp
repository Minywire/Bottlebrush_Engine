//
// Created by niamh on 17/04/2024.
//

#include "Image.h"

Image::Image(const std::filesystem::path& imagePath, bool flip) {
    
    if (flip)
        stbi_set_flip_vertically_on_load(true);
    else
        stbi_set_flip_vertically_on_load(false);

    m_imageData = stbi_load(imagePath.string().c_str(), &m_width, &m_height, &m_imgChannels, 0);

    if(m_imageData) {
        std::cout << "Image loaded successfully" << std::endl;
    } else {
        std::cout << "Failed to load image" << std::endl;
    }
}

Image::~Image() {
    free(m_imageData);
}

unsigned char *Image::getImageData() {
    return m_imageData;
}

int Image::getImageWidth() const {
    return m_width;
}

int Image::getImageHeight() const {
    return m_height;
}

int Image::getChannels() const {
    return m_imgChannels;
}
