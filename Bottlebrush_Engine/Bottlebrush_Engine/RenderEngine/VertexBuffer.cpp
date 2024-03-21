//
//  Created by Alan Brunet 12/03/2024
//
#include "VertexBuffer.h"
#include "OpenGLVertexBuffer.h"

VertexBuffer* VertexBuffer::Create(float* vertices, unsigned int size) {
	return new OpenGLVertexBuffer(vertices, size);
}
