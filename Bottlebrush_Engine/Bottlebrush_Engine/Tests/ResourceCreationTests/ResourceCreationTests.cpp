//
// Created by Marco on 17/04/24.
//
#include <gtest/gtest.h>

#include "Scene.h"
#include <BBResourceManager.hpp>
#include "ECS.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"


TEST(ResourceCreationTests, GenerateFromComponentTest)
{
    //GLAD AND GLFW INIT STUFF
    const unsigned int screen_width = 800, screen_height = 600;

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
    }
    glfwMakeContextCurrent(window);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "ERROR: Failed to initialize GLAD!" << std::endl;
    }

    //TESTING MODEL GENERATION HERE
    BBResourceManager resourceMan;
    const ModelComponent testComponent = { "cube.obj", "Disabled_Pokemon_Go_-_Eevee___Zubat_0-3_screenshot.png" };

    resourceMan.generateModelFromComponent(testComponent);

    EXPECT_EQ(resourceMan.getSceneModels().count("cube.obj"), 1); //testing if the object itself is actually in the map using the count func, which should return 1 if the cube entry is in there.
}