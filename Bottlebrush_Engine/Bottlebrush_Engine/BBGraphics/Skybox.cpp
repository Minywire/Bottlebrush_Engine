#include "Skybox.h"

Skybox::Skybox(std::filesystem::path model) {
	InitMesh(model);
}

Skybox::~Skybox() {

}

void Skybox::InitMesh(std::filesystem::path model) {
	m_Model = GraphicsFactory<GraphicsAPI::OpenGL>::CreateModel(model.string());
	// @TODO set textures as cubemap
	// BPP = 3 for RGB
	m_Texture =
		GraphicsFactory<GraphicsAPI::OpenGL>::CreateTextureBuffer(2048, 2048, 3);

	m_Texture->InitCubeMap();

	/*
	for (int i = 0; i < 6; i++) {
	m_Texture->CreateCubemap(data, i);
	}
	*/
}

void Skybox::ActiveTexture() { 
	m_Texture->Bind(); 
}
