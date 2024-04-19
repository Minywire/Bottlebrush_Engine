#include "Skybox.h"

Skybox::Skybox(std::filesystem::path model, std::vector<std::filesystem::path> texPaths) {
	InitMesh(model, texPaths);
}

Skybox::~Skybox() {

}

void Skybox::InitMesh(std::filesystem::path model,
                      std::vector<std::filesystem::path> texPaths) {

    // This will cause an image failing to load. But it is intended
    // alternatively we can pass an image that will load, but it will be not used
    m_Model = GraphicsFactory<GraphicsAPI::OpenGL>::CreateModel(
        model, 
        "");

	// values will be changed on load
	m_Texture =
		GraphicsFactory<GraphicsAPI::OpenGL>::CreateTextureBuffer();

    // sets up the texture parameters before creating the texture
	m_Texture->InitCubeMap();

    // loads a cubemap texture from 6 individual texture faces
    // order:
    // +X (right)
    // -X (left)
    // +Y (top)
    // -Y (bottom)
    // +Z (front)
    // -Z (back)
    // -------------------------------------------------------
    for (unsigned int i = 0; i < texPaths.size(); i++) {
        unsigned char* data = stbi_load(
            texPaths[i].string().c_str(), &m_Texture->GetWidth(),
                    &m_Texture->GetHeight(), &m_Texture->GetBPP(), 0);

        if (data) {
            m_Texture->CreateCubemap(data, i);

            stbi_image_free(data);
        } else {
            std::cout << "Cubemap texture failed to load at path: " << texPaths[i]
                    << std::endl;
            stbi_image_free(data);
        }
        m_Texture->CreateCubemap(texPaths[i], i);
    }
}

void Skybox::ActiveTexture() { 
	m_Texture->BindCubeMap(); 
}
