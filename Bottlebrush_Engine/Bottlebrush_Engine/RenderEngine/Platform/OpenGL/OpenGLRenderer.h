//
//  Created by Alan Brunet 12/03/2024
//
#pragma once

#include <glad/glad.h>

#include "OpenGLVertexArray.h"
#include "OpenGLIndexBuffer.h"
#include "OpenGLShader.h"
#include "OpenGLLogCall.h"

#include "../../RenderEngine.h"

class OpenGLRenderer : RenderEngine
{
private:

public:
    void Clear() const;
    void Draw(const VertexArray& va, const IndexBuffer& ib, const OpenGLShader& shader) const;
};
