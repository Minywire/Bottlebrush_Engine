//#include "RenderEngine.h"
#include "GraphicsFactory.h"
#include "BBGUI/BBGUI.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Bottlebrush Engine", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    initBBGUI(window);
    
//    // drawing a square, 4 vertex positions,
//    float positions[] = {
//        0.5f,  0.5f,  0.5f,  // 0
//        0.0f,  0.5f,  0.5f,  // 1
//        0.0f,  0.0f,  0.5f,   // 2
//        0.5f,  0.0f,  0.5f,  // 3
//    };
//
//    float positions2[] = {
//        -0.5f, -0.5f,  0.5f,  // 0
//         0.0f, -0.5f,  0.5f,  // 1
//         0.0f,  0.0f,  0.5f,  // 2
//        -0.5f,  0.0f,  0.5f,  // 3
//    };
//
//    unsigned int layoutsizes[] = {3};
//
//    // index buffer for vertex positions
//    unsigned int indices[] = {0, 1, 2, 2, 3, 0};
//
//    //@TODO Implement and test Texture.h
    const GraphicsAPI s_API = GraphicsAPI::OpenGL;
//
//    std::unique_ptr<RenderEngine> r = GraphicsFactory<s_API>::CreateRenderer();
//
    std::unique_ptr<Model> testCube = GraphicsFactory<s_API>::CreateModel("Resources/Models/cube.obj");
//
//    r->SetShaderSource("Basic.vert", "Basic.frag");
//    r->SetColour(0.2f, 0.3f, 0.8f, 1.0f);
//    r->SetVertexBuffer(positions, 4, 3);
//    r->PushLayout(1, layoutsizes);
//    r->SetIndexBuffer(indices, 6);
//    r->ClearBuffers();
//
//    std::unique_ptr<RenderEngine> r2 = GraphicsFactory<s_API>::CreateRenderer();
//
//    r2->SetVertexBuffer(positions2, 4, 3);
//    r2->PushLayout(1, layoutsizes);
//    r2->SetIndexBuffer(indices, 6);
//    r2->SetShaderSource("Basic.vert", "Basic.frag");
//    r2->SetColour(0.8f, 0.3f, 0.8f, 1.0f);
//    r2->ClearBuffers();

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // this needs to be called within the main draw loop
        //r->Draw(*vertex_array, *ib, *shader);
//        r->Draw();
//        r2->Draw();

        testCube->Draw();
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwPollEvents();
        updateBBGUIFrameStart(); //start of frame rendering for GUI

        updateBBGUIFrameEnd(); //end of frame render for GUI
        glfwSwapBuffers(window);
    }

    shutDownBBGUI(); //shut down the GUI

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}
