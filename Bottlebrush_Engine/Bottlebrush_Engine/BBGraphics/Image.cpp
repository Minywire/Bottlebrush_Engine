//
// Created by niamh on 17/04/2024.
//

#include "Image.h"

Image::Image(std::filesystem::path imagePath) {
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
