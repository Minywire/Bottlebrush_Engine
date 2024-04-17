#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#endif

#include "Skybox.h"

Skybox::Skybox(std::filesystem::path model, std::vector<std::filesystem::path> texPaths) {
	InitMesh(model, texPaths);
}

Skybox::~Skybox() {

}

void Skybox::InitMesh(std::filesystem::path model,
                      std::vector<std::filesystem::path> texPaths) {
	m_Model = GraphicsFactory<GraphicsAPI::OpenGL>::CreateModel(model.string());
	// @TODO set textures as cubemap
	// BPP = 3 for RGB
	m_Texture =
		GraphicsFactory<GraphicsAPI::OpenGL>::CreateTextureBuffer(2048, 2048, 3);

	m_Texture->InitCubeMap();

	int width, height, nrComponents;
    for (unsigned int i = 0; i < texPaths.size(); i++) {
        unsigned char* data = stbi_load(texPaths[i].string().c_str(), &width,
                                    &height, &nrComponents, 0);

        if (data) {
            m_Texture->CreateCubemap(data, i);

            stbi_image_free(data);
        } else {
            std::cout << "Cubemap texture failed to load at path: " << texPaths[i]
                    << std::endl;
            stbi_image_free(data);
        }
    }
	
	
}

void Skybox::ActiveTexture() { 
	m_Texture->BindCubeMap(); 
}
