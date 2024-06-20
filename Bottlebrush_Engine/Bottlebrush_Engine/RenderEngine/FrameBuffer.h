//
// Created by niamh on 20/06/2024.
//

#ifndef BOTTLEBRUSH_ENGINE_FRAMEBUFFER_H
#define BOTTLEBRUSH_ENGINE_FRAMEBUFFER_H
#include <vector>

/**
 * @author Niamh
 * @brief
 */
class FrameBuffer {
public:
    FrameBuffer(){};
    virtual ~FrameBuffer() = default;

    /**
     * @author Niamh
     * @brief Binds a buffer to draw / manipulate
     */
    virtual void Bind() const = 0;

    /**
     * @author Niamh
     * @brief Unbinds the buffer
     */
    virtual void Unbind() const = 0;
};

#endif //BOTTLEBRUSH_ENGINE_FRAMEBUFFER_H
