//
// Created by niamh on 20/06/2024.
//

#include "OpenGLFrameBuffer.h"
#include "OpenGLRenderer.h"

OpenGLFrameBuffer::OpenGLFrameBuffer() {
    glGenFramebuffers(1, &m_FramebufferID);
}

OpenGLFrameBuffer::~OpenGLFrameBuffer() {
    glDeleteFramebuffers(1, &m_FramebufferID);
}
