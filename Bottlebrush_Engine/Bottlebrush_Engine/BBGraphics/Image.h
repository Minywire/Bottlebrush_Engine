//
// Created by niamh on 17/04/2024.
//

#ifndef BOTTLEBRUSH_ENGINE_IMAGE_H
#define BOTTLEBRUSH_ENGINE_IMAGE_H

struct image {
    int m_width = 0;
    int m_height = 0;
    int m_BytesPerPixel = 0;
    unsigned char* m_LocalBuffer;
};

#endif //BOTTLEBRUSH_ENGINE_IMAGE_H
