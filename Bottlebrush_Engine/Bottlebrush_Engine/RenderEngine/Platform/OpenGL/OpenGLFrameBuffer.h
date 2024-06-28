//
// Created by niamh on 20/06/2024.
//

#ifndef BOTTLEBRUSH_ENGINE_OPENGLFRAMEBUFFER_H
#define BOTTLEBRUSH_ENGINE_OPENGLFRAMEBUFFER_H

#include "FrameBuffer.h"
#include "OpenGLTexture.h"
// opengl attachment struct?

class OpenGLFrameBuffer : public FrameBuffer{
public:
    OpenGLFrameBuffer();
    ~OpenGLFrameBuffer() override;

    /**
     * @author Niamh
     * @brief Binds a buffer to draw / manipulate
     */
    void Bind() const override;

    /**
     * @author Niamh
     * @brief Unbinds the buffer
     */
    void Unbind() const override;

    /*
     * TODO
     * - Create texture attachment method
     * - Create renderbuffer object attachment method
     * - Create get width method
     * - Create get height method
     * - Create get framebuffer id method
     * - Generate texture from framebuffer (glFrameBufferTexture2D)
     */
private:
    unsigned int m_FramebufferID;
    // store colour attachments
    // store depth attachments
    // store stencil attachments
    // store depth-stencil attachments
};


#endif //BOTTLEBRUSH_ENGINE_OPENGLFRAMEBUFFER_H
