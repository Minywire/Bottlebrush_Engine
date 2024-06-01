#define GLM_ENABLE_EXPERIMENTAL

#include <iostream>

#include "Camera.h"
#include "GraphicsFactory.h"
#include "Scene.h"
#include "Skybox.h"
#include "Terrain.h"
#include "Window.h"
#include "glad/glad.h"
#include "glfw/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

int main() {
    Scene gameScene("Game/master_file.lua", 1920, 1080);

    gameScene.update();

  return 0;
}
    