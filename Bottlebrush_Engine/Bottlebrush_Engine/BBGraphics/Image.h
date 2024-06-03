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
    /**
     * Image Constructer
     * @param imagePath
     * @param flip
     */
    Image(const std::filesystem::path& imagePath, bool flip = true);
    ~Image();

    /**
     * Get Image Height
     * @return
     */
    int getImageHeight() const;
    /**
     * Get Image Width
     * @return
     */
    int getImageWidth() const;
    /**
     * Get the number of channels in the image
     * @return
     */
    int getChannels() const;
    /**
     * Return the image data in unsigned char
     * @return
     */
    unsigned char* getImageData();
private:
    int m_width;
    int m_height;
    int m_imgChannels;
    unsigned char* m_imageData;
};

#endif //BOTTLEBRUSH_ENGINE_IMAGE_H
