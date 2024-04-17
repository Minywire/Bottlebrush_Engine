//
// Created by niamh on 17/04/2024.
//

#ifndef BOTTLEBRUSH_ENGINE_IMAGE_H
#define BOTTLEBRUSH_ENGINE_IMAGE_H

#include <stb/stb_image.h>
#include <filesystem>

class Image {
public:
    Image(std::filesystem::path imagePath);
    ~Image();

    unsigned char* getImageData();
private:
    int m_width;
    int m_height;
    int m_imgChannels;
    unsigned char* m_imageData;
};

#endif //BOTTLEBRUSH_ENGINE_IMAGE_H
