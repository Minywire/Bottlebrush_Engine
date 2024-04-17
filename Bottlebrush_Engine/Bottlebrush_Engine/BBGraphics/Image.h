//
// Created by niamh on 17/04/2024.
//

#ifndef BOTTLEBRUSH_ENGINE_IMAGE_H
#define BOTTLEBRUSH_ENGINE_IMAGE_H

#include <stb/stb_image.h>
#include <filesystem>
#include <iostream>

class Image {
public:
    Image(const std::filesystem::path& imagePath);
    ~Image();

    int getImageHeight();
    int getImageWidth();
    unsigned char* getImageData();
private:
    int m_width;
    int m_height;
    int m_imgChannels;
    unsigned char* m_imageData;
};

#endif //BOTTLEBRUSH_ENGINE_IMAGE_H
