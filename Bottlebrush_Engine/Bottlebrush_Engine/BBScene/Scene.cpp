//
// Created by Marco Garzon Lara on 12/3/2024.
//

#include "Scene.h"
#include "BBGUI.h"

void FramebufferSizeCallback(Window::WindowContext window, int width,  int height) 
{
    glViewport(0, 0, width, height);
}

void KeyCallback(Window::WindowContext window, int key, int scancode, int action, int mods) 
{
    auto* data = glfwGetWindowUserPointer(window);
    auto* scene = reinterpret_cast<Scene*>(data);

    if (scene->getExitScreenFlag()) return;

    if (key == GLFW_KEY_C && action == GLFW_PRESS) scene->setWireFrameFlag(!scene->getWireframeFlag());
    
    if (key == GLFW_KEY_R && action == GLFW_PRESS) scene->setCameraRestrictionFlag(!scene->getCameraRestrictionFlag());

    if (action == GLFW_PRESS && key == GLFW_KEY_LEFT_SHIFT)
      scene->getCamera().SetSpeed(scene->getCamera().GetSpeed() * 2.0f);
    if (action == GLFW_RELEASE && key == GLFW_KEY_LEFT_SHIFT)
      scene->getCamera().SetSpeed(scene->getCamera().GetSpeed() / 2.0f);
    if(action == GLFW_PRESS && key == GLFW_KEY_ESCAPE)
        scene->toggleMenuActive();
}

void MouseCallback(Window::WindowContext window, double pos_x, double pos_y) 
{
    auto* data = glfwGetWindowUserPointer(window);
    auto* scene = reinterpret_cast<Scene*>(data);

    if (scene->getExitScreenFlag() || scene->getMenuActive()) return;

    if (scene->getFirstMouseFlag()) 
    {
        scene->setLastX(pos_x);
        scene->setLastY(pos_y);
        scene->setFirstMouseFlag(false);
    }

    float x_offset = pos_x - scene->getLastX(), y_offset = scene->getLastY() - pos_y;

    scene->setLastX(pos_x);
    scene->setLastY(pos_y);

    scene->getCamera().ProcessMouseMovement(x_offset, y_offset);
}

void ScrollCallback(Window::WindowContext window, double x_offset, double y_offset) \
{
    auto* data = glfwGetWindowUserPointer(window);
    auto* scene = reinterpret_cast<Scene*>(data);

    if (scene->getExitScreenFlag() || scene->getMenuActive()) return;
    scene->getCamera().ProcessMouseScroll(static_cast<float>(y_offset));
}

void Scene::ProcessInput(float deltaTime) {
    if (exitScreen) {
        if (glfwGetMouseButton(window.GetContext(), GLFW_MOUSE_BUTTON_LEFT == GLFW_PRESS)) 
        {
            window.SetShouldClose(true);
        }
        return;
    }

    if(menuActive) return;

    if (glfwGetKey(window.GetContext(), GLFW_KEY_W) == GLFW_PRESS)
        mainCamera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window.GetContext(), GLFW_KEY_S) == GLFW_PRESS)
        mainCamera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window.GetContext(), GLFW_KEY_A) == GLFW_PRESS)
        mainCamera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window.GetContext(), GLFW_KEY_D) == GLFW_PRESS)
        mainCamera.ProcessKeyboard(RIGHT, deltaTime);
    if (glfwGetKey(window.GetContext(), GLFW_KEY_SPACE) == GLFW_PRESS)
        mainCamera.ProcessKeyboard(UP, deltaTime);
    if (glfwGetKey(window.GetContext(), GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        mainCamera.ProcessKeyboard(DOWN, deltaTime);
}

void Scene::createEntity(const std::string & lua_file) //provides a user-friendly function that you only need to specify the script entity to.
{
    entityFactory.create_from_file(bbECS, lua.getLuaState(), lua_file);
}

void Scene::createEntityAndTransform(const std::string & lua_file, float xPos, float yPos, float zPos)
{
    entityFactory.create_from_file(bbECS, lua.getLuaState(), lua_file, xPos, yPos, zPos);
}

Scene::Scene(const std::string& lua_master, float screenwidth, float screenheight)
    : accumulatedFrameTime(0), UpdateAIInterval(0.2f), screen_width(screenwidth), screen_height(screenheight)
{
    window = Window(Window::CURSOR, Window::CURSOR_DISABLED, "BOTTLE BRUSH", screen_width, screen_height);

    window.Create();

    renderEngine = GraphicsFactory<GraphicsAPI::OpenGL>::CreateRenderer();
    masterLuaFile = lua_master;
    lua.getLuaState().set_function("create_entity", &Scene::createEntity, this); //register create entity function into lua state of this instance
    lua.getLuaState().set_function("create_entityTR", &Scene::createEntityAndTransform, this);

    init();

    const ShaderType defaultShaderType = ShaderType::Default;
    const ShaderType terrainShaderType = ShaderType::Terrain;
    const ShaderType skyboxShaderType = ShaderType::Skybox;

    setRendererShaderSource(defaultShaderType,
                        "Resources/Shaders/Vertex/BasicTex.vert",
                        "Resources/Shaders/Fragment/BasicTex.frag");

    setRendererShaderSource(terrainShaderType, 
                        "Resources/Shaders/Vertex/Heightmap.vert",
                        "Resources/Shaders/Fragment/Heightmap.frag");

    setRendererShaderSource(skyboxShaderType,
                        "Resources/Shaders/Vertex/Skybox.vert",
                        "Resources/Shaders/Fragment/Skybox.frag");
    
    setRendererShaderSource(ShaderType::MD2,
                            "Resources/Shaders/Vertex/MD2Model.vert",
                            "Resources/Shaders/Fragment/MD2Model.frag");

    const std::vector<std::filesystem::path> skyboxTextures {
        std::filesystem::path("Resources/Textures/Skybox/right.jpg"),
        std::filesystem::path("Resources/Textures/Skybox/left.jpg"),
        std::filesystem::path("Resources/Textures/Skybox/top.jpg"),
        std::filesystem::path("Resources/Textures/Skybox/bottom.jpg"),
        std::filesystem::path("Resources/Textures/Skybox/front.jpg"),
        std::filesystem::path("Resources/Textures/Skybox/back.jpg"),
    };

    skybox = Skybox("Resources/Models/Skybox.obj", skyboxTextures);
}

void Scene::setProjectionMatrix(glm::mat4 projMatrix)
{
    projectionMatrix = projMatrix;
}

void Scene::setViewMatrix(glm::mat4 vMatrix)
{
    viewMatrix = vMatrix;
}

void Scene::init()
{
    glfwSetWindowUserPointer(window.GetContext(), this);

    glfwSetFramebufferSizeCallback(window.GetContext(), FramebufferSizeCallback);
    glfwSetKeyCallback(window.GetContext(), KeyCallback);
    glfwSetCursorPosCallback(window.GetContext(), MouseCallback);
    glfwSetScrollCallback(window.GetContext(), ScrollCallback);

   
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
      std::cerr << "ERROR: Failed to initialize GLAD!" << std::endl;
      return;
    }

    glEnable(GL_DEPTH_TEST);

    mainCamera.SetPosition(1000.0f, 100.0f, 1000.0f);
    mainCamera.SetSensitivity(0.05f);
    mainCamera.SetSpeed(100.0f);
    mainCamera.SetZoom(30.0f);

    bbSystems.RegisterAIFunctions(bbECS, lua.getLuaState(), mainCamera); // register functions before running scripts
    if(!lua.getLuaState().do_file(masterLuaFile).valid())
    {
        std::cout << "Could not load master game script file\n";
        return;
    }//load the master lua scene script containing all entities

    bbSystems.createTerrainComponents(bbECS, resources.getSceneTerrain());
    bbSystems.createModelComponents(bbECS, resources.getSceneModels());
    bbSystems.createMD2ModelComponents(bbECS, resources.getSceneMD2Models());
    initBBGUI(window.GetContext());
}

void Scene::update()
{
    while (!window.GetShouldClose()) {
        if(menuActive) {
            updateBBGUIFrameStart();
            if(ImGui::CollapsingHeader("Controls")) {
                if(ImGui::TreeNode("Movement")) {
                    ImGui::Text("Forward: W");
                    ImGui::Text("Left: A");
                    ImGui::Text("Backwards: S");
                    ImGui::Text("Right: D");
                    ImGui::Text("Up: Spacebar");
                    ImGui::Text("Down: Left Control");
                    ImGui::Text("Zoom (speedy): Left Shift");
                    ImGui::TreePop();
                }

                if(ImGui::TreeNode("Scene")) {
                    ImGui::Text("Toggle wireframe: C");
                    ImGui::TreePop();
                }

                ImGui::Text("Exit: Escape");
            }

            if(ImGui::CollapsingHeader("Credits")) {
                ImGui::Text("Alan Brunet");
                ImGui::Text("Jaiden di Lanzo");
                ImGui::Text("Marco Garzon Lara");
                ImGui::Text("Niamh Wilson");
            }

            if(ImGui::Button("Exit")) {
                exitScreen = true;
            }
        }

        auto current_frame = static_cast<float>(glfwGetTime());
        float deltaTime = current_frame - last_frame;
        last_frame = current_frame;
        accumulatedFrameTime += deltaTime;

        // Process user input
        ProcessInput(deltaTime);

        // Clear colours and buffers
        clearRenderEngine();

        // Toggle wireframe (via key callback)
        if (wireframe)
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        else
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        glm::mat4 projection = glm::perspective(
            glm::radians(mainCamera.GetZoom()),
            (float)screen_width / (float)screen_height, 0.1f, 100000.0f);

        glm::mat4 view = mainCamera.GetViewMatrix();

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
        model = glm::rotate(model, glm::radians(0.0f), glm::vec3(1.0f, 0.3f, 0.5f));

        // MY SCENE
        setProjectionMatrix(projection);
        setViewMatrix(view);
        
        bbSystems.setLight(*renderEngine, ShaderType::Default, viewMatrix);

        Systems::drawMD2Models(bbECS, 
                               ShaderType::MD2, 
                               *renderEngine, 
                                resources.getSceneMD2Models(), 
                                projectionMatrix, viewMatrix);

        Systems::updateMD2Interpolation(bbECS, resources.getSceneMD2Models(), deltaTime);


        Systems::drawTerrain(bbECS, ShaderType::Terrain, *renderEngine,
                             resources.getSceneTerrain(), false,
                             projectionMatrix, viewMatrix);

        Systems::updateCameraTerrainHeight(bbECS, 
                                           resources.getSceneTerrain(), 
                                           mainCamera,  
                                           restrictCamera,
                                           5.0f);

        Systems::drawModels(bbECS, ShaderType::Default, *renderEngine,
                            resources.getSceneModels(), projectionMatrix,
                            viewMatrix);
        Systems::updateAIMovements(bbECS, deltaTime, resources.getSceneTerrain());
        while (accumulatedFrameTime >= UpdateAIInterval) {
            Systems::updateAI(bbECS, lua.getLuaState(), accumulatedFrameTime);
            accumulatedFrameTime -= UpdateAIInterval;
        }

        if (exitScreen) {
            glm::vec3 position = {-4825, 0, -5000}, front = {-5000, 0, 0},
                    up = {0, 1, 0};
            mainCamera.SetSpeed(0);
            mainCamera.SetZoom(55);
            mainCamera.SetViewMatrix(position, front, up);
        }

        // SKYBOX
        //  change depth function so depth test passes when
        //  values are equal to depth buffer's content
        glDepthFunc(GL_LEQUAL);
        // draw skybox as last
        // draw skybox as last
        view =
            glm::mat4(glm::mat3(view));  // remove translation from the view matrix

        renderEngine->GetShader(ShaderType::Skybox)
            ->SetUniformMatrix4fv("view", view);
        renderEngine->GetShader(ShaderType::Skybox)
            ->SetUniformMatrix4fv("projection", projection);
        renderEngine->GetShader(ShaderType::Skybox)->SetUniform1i("skybox", 0);

        // Draw the Skybox
        skybox.ActiveTexture();
        for (unsigned int i = 0; i < skybox.getModel()->GetSubMeshes().size();
                i++) {
            renderEngine->Draw(
                ShaderType::Skybox,
                *skybox.getModel()->GetSubMeshes()[i]->GetVertexArray(),
                skybox.getModel()->GetSubMeshes()[i]->GetIndexCount());
        }

        glDepthFunc(GL_LESS);  // set depth function back to default

        if(menuActive) {
            updateBBGUIFrameEnd();
        }

        window.Swap();
        window.Poll();
    }

    shutDownBBGUI();
    window.Remove();
}

void Scene::setRendererShaderSource(ShaderType shaderType, const std::string & vertexSource, const std::string & fragSource)
{
    renderEngine->SetShaderSource(shaderType, vertexSource, fragSource);
}

void Scene::clearRenderEngine()
{
    renderEngine->Clear();
}

const Camera& Scene::getCamera() const
{ 
    return mainCamera; 
}

Camera& Scene::getCamera()
{ 
    return mainCamera; 
}

bool Scene::getWireframeFlag() const
{ 
    return wireframe; 
}

void Scene::setWireFrameFlag(bool flag) 
{ 
    wireframe = flag; 
}

bool Scene::getExitScreenFlag() const
{ 
    return exitScreen; 
}

void Scene::setExitFlag(bool flag)
{ 
    exitScreen = flag; 
}

bool Scene::getFirstMouseFlag() const
{ 
    return first_mouse_click; 
}

void Scene::setFirstMouseFlag(bool flag)
{ 
    first_mouse_click = flag; 
}

float Scene::getLastX() const
{ 
    return last_x;
}

float Scene::getLastY() const
{ 
    return last_y;
}

void Scene::setLastX(float lX) 
{ 
    last_x = lX; 
}

void Scene::setLastY(float lY)
{ 
    last_y = lY; 
}

void Scene::toggleMenuActive() {
    this->menuActive = !this->menuActive;

    if(menuActive) {
        window.SetCursorMode(Window::CURSOR_NORMAL);
    } else {
        window.SetCursorMode(Window::CURSOR_DISABLED);
    }
}

bool Scene::getMenuActive() const {
    return menuActive;
}

void Scene::setCameraRestrictionFlag(bool flag)
{
    restrictCamera = flag;
}

bool Scene::getCameraRestrictionFlag() const
{
    return restrictCamera;
}
