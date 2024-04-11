#include "Mesh.h"

#include "OpenGLVertexArray.h"
#include "OpenGLVertexBuffer.h"
#include "OpenGLIndexBuffer.h"
#include "OpenGLVertexBufferLayout.h"
#include "OpenGLTexture.h"

class OpenGLMesh : public Mesh {
private:
	/// Vertex Array pointer
	std::unique_ptr<VertexArray> m_VertexArray;

	/// Texture Buffer pointer
    std::unique_ptr<Texture> m_Texture;
 public:
    OpenGLMesh();
	~OpenGLMesh() override;
};
