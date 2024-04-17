#include "Skybox.h"

Skybox::Skybox(std::filesystem::path model) {
  InitMesh(model);
}

Skybox::~Skybox() {

}

void Skybox::InitMesh(std::filesystem::path model) {
  m_Model = GraphicsFactory<GraphicsAPI::OpenGL>::CreateModel(
      model.string());
  // @TODO set textures as cubemap
}
