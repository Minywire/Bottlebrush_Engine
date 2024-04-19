#define GLM_ENABLE_EXPERIMENTAL

#include <iostream>

#include "Camera.h"
#include "GraphicsFactory.h"
#include "Skybox.h"
#include "Terrain.h"
#include "glad/glad.h"
#include "glfw/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

// Settings
const unsigned int screen_width = 800, screen_height = 600;
bool wireframe = false, grayscale = false;
glm::vec3 terrain_scale = {5.0f, 0.25f, 5.0f},
          terrain_shift = {0.0f, 16.0f, 0.0f};

// Camera
Camera camera(glm::vec3(0.0f, 0.0f, 0.0f));
float last_x = screen_width / 2.0f, last_y = screen_height / 2.0f;
bool first_mouse_click = true;

// Timing
float delta = 0.0f, last_frame = 0.0f;

void ProcessInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);

  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    camera.ProcessKeyboard(FORWARD, delta);
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    camera.ProcessKeyboard(BACKWARD, delta);
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    camera.ProcessKeyboard(LEFT, delta);
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    camera.ProcessKeyboard(RIGHT, delta);
  if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    camera.ProcessKeyboard(UP, delta);
  if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
    camera.ProcessKeyboard(DOWN, delta);
}

void FramebufferSizeCallback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}

void KeyCallback(GLFWwindow *window, int key, int scancode, int action,
                 int mods) {
  if (key == GLFW_KEY_C && action == GLFW_PRESS) wireframe = !wireframe;
}

void MouseCallback(GLFWwindow *window, double pos_x, double pos_y) {
  auto x = static_cast<float>(pos_x), y = static_cast<float>(pos_y);

  if (first_mouse_click) {
    last_x = x;
    last_y = y;
    first_mouse_click = false;
  }

  float x_offset = x - last_x, y_offset = last_y - y;

  last_x = x;
  last_y = y;

  camera.ProcessMouseMovement(x_offset, y_offset);
}

void ScrollCallback(GLFWwindow *window, double x_offset, double y_offset) {
  camera.ProcessMouseScroll(static_cast<float>(y_offset));
}

int main() {
  glfwInit();

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  GLFWwindow *window = glfwCreateWindow(screen_width, screen_height,
                                        "Bottlebrush Engine", nullptr, nullptr);
  if (window == nullptr) {
    std::cerr << "ERROR: Failed to create GLFW window!" << std::endl;
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);
  glfwSetKeyCallback(window, KeyCallback);
  glfwSetCursorPosCallback(window, MouseCallback);
  glfwSetScrollCallback(window, ScrollCallback);

  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cerr << "ERROR: Failed to initialize GLAD!" << std::endl;
    return -1;
  }

  glEnable(GL_DEPTH_TEST);

  const GraphicsAPI s_API = GraphicsAPI::OpenGL;
  std::unique_ptr<RenderEngine> renderEngine =
      GraphicsFactory<s_API>::CreateRenderer();

  Terrain heightmap(
      std::filesystem::path("resources/heightmaps/iceland_heightmap.png")
          .string(),
      terrain_scale, terrain_shift);
  float terrain_height_init =
      heightmap.GetHeight(camera.position_.x, camera.position_.z);
  camera.position_ = heightmap.GetCentre();
  camera.movement_speed_ *= 100.0f;

  std::unique_ptr<Model> testCube = GraphicsFactory<s_API>::CreateModel(
      "Resources/Models/Cube_With_Pizazz.obj",
      "Resources/Models/"
      "Disabled_Pokemon_Go_-_Eevee___Zubat_0-3_screenshot.png");

  // loads a cubemap texture from 6 individual texture faces
  std::vector<std::filesystem::path> skyboxTextures{
      std::filesystem::path("Resources/Textures/Skybox/right.jpg"),
      std::filesystem::path("Resources/Textures/Skybox/left.jpg"),
      std::filesystem::path("Resources/Textures/Skybox/top.jpg"),
      std::filesystem::path("Resources/Textures/Skybox/bottom.jpg"),
      std::filesystem::path("Resources/Textures/Skybox/front.jpg"),
      std::filesystem::path("Resources/Textures/Skybox/back.jpg"),
  };
  Skybox skybox("Resources/Models/Skybox.obj", skyboxTextures);

  const ShaderType defaultShaderType = ShaderType::Default;
  const ShaderType skyboxShaderType = ShaderType::Skybox;
  const ShaderType terrainShaderType = ShaderType::Terrain;

  renderEngine->SetShaderSource(terrainShaderType,
                                "Resources/Shaders/Vertex/Heightmap.vert",
                                "Resources/Shaders/Fragment/Heightmap.frag");

  renderEngine->SetShaderSource(skyboxShaderType,
                                "Resources/Shaders/Vertex/Skybox.vert",
                                "Resources/Shaders/Fragment/Skybox.frag");

  renderEngine->SetShaderSource(defaultShaderType,
                                "Resources/Shaders/Vertex/Basic.vert",
                                "Resources/Shaders/Fragment/Basic.frag");

  // RENDER LOOP
  while (!glfwWindowShouldClose(window)) {
    auto current_frame = static_cast<float>(glfwGetTime());
    delta = current_frame - last_frame;
    last_frame = current_frame;

    // Process user input
    ProcessInput(window);

    // Clear colours and buffers
    renderEngine->Clear();

    // Toggle wireframe (via key callback)
    if (wireframe)
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    // Calculate camera projection matrix relative to current camera zoom and
    // screen dimensions
    glm::mat4 projection = glm::perspective(
        glm::radians(camera.zoom_), (float)screen_width / (float)screen_height,
        0.1f, 100000.0f);
    // Evaluate camera view matrix i.e. the camera LookAt matrix
    glm::mat4 view = camera.GetViewMatrix();
    // Evaluate the camera model matrix that 'positions' the models being drawn
    // in the scene
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(0.0f), glm::vec3(1.0f, 0.3f, 0.5f));

    glm::vec3 local_position =
        glm::inverse(model) * glm::vec4(camera.position_, 1);
    float terrain_height =
        heightmap.GetHeight(local_position.x, local_position.z);
    float terrain_height_diff = std::abs(terrain_height_init - terrain_height);
    if (terrain_height < terrain_height_init)
      terrain_height -= terrain_height_diff * delta;
    if (terrain_height > terrain_height_init)
      terrain_height += terrain_height_diff * delta;
    if (terrain_height < 0)
      camera.position_.y = -terrain_shift.y * terrain_scale.y;
    else
      camera.position_.y = terrain_height * terrain_scale.y;

    renderEngine->GetShader(defaultShaderType)
        ->SetUniformMatrix4fv("projection", projection);
    renderEngine->GetShader(defaultShaderType)
        ->SetUniformMatrix4fv("view", view);
    renderEngine->GetShader(defaultShaderType)
        ->SetUniformMatrix4fv("model", model);

    renderEngine->GetShader(terrainShaderType)
        ->SetUniformMatrix4fv("projection", projection);
    renderEngine->GetShader(terrainShaderType)
        ->SetUniformMatrix4fv("view", view);
    renderEngine->GetShader(terrainShaderType)
        ->SetUniformMatrix4fv("model", model);

    renderEngine->DrawTriangleStrips(
        terrainShaderType, *heightmap.GetMesh()->GetVertexArray(),
        heightmap.GetNumStrips(), heightmap.GetNumTriangles());

    // Draw the test cube
    for (unsigned int i = 0; i < testCube->GetSubMeshes().size(); i++) {
      testCube->GetSubMeshes()[i]->SetTexture();
      renderEngine->Draw(defaultShaderType,
                         *testCube->GetSubMeshes()[i]->GetVertexArray(),
                         testCube->GetSubMeshes()[i]->GetIndexCount());
    }

    // change depth function so depth test passes when
    // values are equal to depth buffer's content
    glDepthFunc(GL_LEQUAL);
    // draw skybox as last
    view = glm::mat4(glm::mat3(
        camera.GetViewMatrix()));  // remove translation from the view matrix
    renderEngine->GetShader(skyboxShaderType)
        ->SetUniformMatrix4fv("view", view);
    renderEngine->GetShader(skyboxShaderType)
        ->SetUniformMatrix4fv("projection", projection);
    renderEngine->GetShader(skyboxShaderType)->SetUniform1i("skybox", 0);

    // Draw the Skybox
    skybox.ActiveTexture();
    for (unsigned int i = 0; i < skybox.getModel()->GetSubMeshes().size();
         i++) {
      renderEngine->Draw(
          skyboxShaderType,
          *skybox.getModel()->GetSubMeshes()[i]->GetVertexArray(),
          skybox.getModel()->GetSubMeshes()[i]->GetIndexCount());
    }

    glDepthFunc(GL_LESS);  // set depth function back to default

    // Swap out buffers and poll for input events
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();

  return 0;
}
