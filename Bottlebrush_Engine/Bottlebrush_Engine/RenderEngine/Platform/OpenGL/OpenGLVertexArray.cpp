//
//  Created by Alan Brunet 12/03/2024
//
#include "OpenGLVertexArray.h"
#include "OpenGLVertexArray.h"

#include "OpenGLVertexBufferLayout.h"
#include "OpenGLRenderer.h"

OpenGLVertexArray::OpenGLVertexArray()
{
	// generate 1 vertex array buffer
	GLCall(glGenVertexArrays(1, &m_RendererID));
}

OpenGLVertexArray::~OpenGLVertexArray()
{
	// delete 1 vertex array buffer
	GLCall(glDeleteVertexArrays(1, &m_RendererID));
}

void OpenGLVertexArray::AddBuffer(const OpenGLVertexBuffer& vb, OpenGLVertexBufferLayout& layout)
{
	// bind vertex array buffer first to add vertex buffers
	Bind();
	// bind vertex buffer
	vb.Bind();

	// get vertex buffer layouts
	const std::vector<OpenGLVertexBufferElement>& elements = layout.GetElements();
	// pointer to next attribute in bytes
	unsigned int offset = 0;

	for (unsigned int i = 0; i < elements.size(); i++)
	{
		const OpenGLVertexBufferElement& element = elements[i];

		// enabling the vertex attribute array
		GLCall(glEnableVertexAttribArray(i));
		// 
		GLCall(glVertexAttribPointer(i, 
			element.count, 
			element.type, 
			element.normalised, 
			layout.GetStride(), 
			(const void*)offset));

		// calc byte space taken up by this attribute
		offset += element.count * OpenGLVertexBufferElement::GetSizeOfType(element.type);
	}
}

void OpenGLVertexArray::Bind() const
{
	// Binding this vertex array to draw / add
	GLCall(glBindVertexArray(m_RendererID));
}

void OpenGLVertexArray::Unbind() const
{
	GLCall(glBindVertexArray(0));
}
