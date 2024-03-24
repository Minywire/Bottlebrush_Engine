#include "RenderEngine.h"
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
    hello_world(); //from the RenderEngine lib, just testing things out

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

    // drawing a square, 4 vertex positions
    float positions[] = {
        -0.5f, -0.5f,  // 0
        0.5f,  -0.5f,  // 1
        0.5f,  0.5f,   // 2
        -0.5f, 0.5f,   // 3
    };

    // index buffer for vertex positions
    unsigned int indices[] = {0, 1, 2, 2, 3, 0};

    // vertex array object
    std::unique_ptr<VertexArray> vertex_array =
        GraphicsFactory<GraphicsAPI::OpenGL>::CreateVertexArray();
    // OpenGLVertexArray vao;

    // 4 vertex and 2 points (2D)
    std::unique_ptr<VertexBuffer> vertex_buffer =
        GraphicsFactory<GraphicsAPI::OpenGL>::CreateVertexBuffer(
            positions, 4 * 2 * sizeof(float));

    // define the format of each vertex data
    // i.e., 2 = 2 points of positions for each vertex (can use different
    // numbers for different attributes)
    std::unique_ptr<VertexBufferLayout> vbLayout = GraphicsFactory<GraphicsAPI::OpenGL>::CreateVertexBufferLayout();
    //OpenGLVertexBufferLayout* vbLayout;

    //@TODO This template belongs in the child class, how to access?
    vbLayout->Push(2, DataType::FLOAT);

    // add current buffer with its layout specs to the vertex array
    vertex_array->AddBuffer(*vertex_buffer, *vbLayout);

    // 6 = the count of elements in indices
    std::unique_ptr<IndexBuffer> ib =
        GraphicsFactory<GraphicsAPI::OpenGL>::CreateIndexBuffer(indices, 6);

    // setup source shader files locations
    ShaderSourceFiles ssf;
    ssf.VertexSource = "Basic.vert";
    ssf.FragmentSource = "Basic.frag";

    // calling the constructor will read the files within ssf and apply them
    std::unique_ptr<Shader> shader = std::make_unique<OpenGLShader>(ssf);

    // basic.frag has a uniform declaration
    shader->Bind();
    shader->SetUniform4f("u_Color", 0.2f, 0.3f, 0.8f, 1.0f);

    // clearing all buffer bindings
    vertex_array->Unbind();
    shader->Unbind();
    vertex_buffer->UnBind();
    ib->UnBind();

    std::unique_ptr<RenderEngine> r = std::make_unique<OpenGLRenderer>();

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
        r->Draw(*vertex_array, *ib, *shader);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwPollEvents();
        updateBBGUIFrameStart(); //start of frame rendering for GUI


        std::vector<float> test_triagnel = {
                -0.5,-0.5,0.0,
                0.0,0.5,0,
                0.5,-0.5,0.0
        };

        std::unique_ptr<VertexArray> array_buffer = GraphicsFactory<GraphicsAPI::OpenGL>::CreateVertexArray();
        std::unique_ptr<VertexBuffer> vertex_buffer = GraphicsFactory<GraphicsAPI::OpenGL>::CreateVertexBuffer(test_triagnel.data(), test_triagnel.size());
        //do render stuff here

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