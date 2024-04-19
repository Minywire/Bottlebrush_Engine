//
//  Created by Alan 12/03/2024
//

#include "OpenGLVertexArray.h"

#include "OpenGLRenderer.h"

OpenGLVertexArray::OpenGLVertexArray()
{
	// generate 1 vertex array buffer
	glGenVertexArrays(1, &m_RendererID);
}

OpenGLVertexArray::~OpenGLVertexArray()
{
	// delete 1 vertex array buffer
	glDeleteVertexArrays(1, &m_RendererID);
}

void OpenGLVertexArray::AddBuffer(const VertexBuffer& vb, VertexBufferLayout& layout)
{
	// bind vertex array buffer first to add vertex buffers
	Bind();
	// bind vertex buffer
	vb.Bind();

	// get vertex buffer layouts
    const std::vector<VertexBufferElement>& elements = layout.GetElements();
	// pointer to next attribute in bytes
	unsigned int offset = 0;

	for (unsigned int i = 0; i < elements.size(); i++)
	{
		const VertexBufferElement& element = elements[i];

		// enabling the vertex attribute array
		glEnableVertexAttribArray(i);
		// Specify the layout of this attribute
		glVertexAttribPointer(
        i,
        element.count,
        element.type,
        element.normalised,
        layout.GetStride(),
		reinterpret_cast<void*>(offset)
        );

		// calc byte space taken up by this attribute
		offset += element.count * layout.GetSizeOfType(element.type);
	}
}

void OpenGLVertexArray::Bind() const
{
	// Binding this vertex array to draw / add
	glBindVertexArray(m_RendererID);
}

void OpenGLVertexArray::Unbind() const
{
	glBindVertexArray(0);
}
