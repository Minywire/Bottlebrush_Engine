#include "Skybox.h"

Skybox::Skybox() {
  m_Model = GraphicsFactory<GraphicsAPI::OpenGL>::CreateModel(
	  "Resources/Models/cube.obj");
  InitMesh();
}

void Skybox::InitMesh() {
  
}
