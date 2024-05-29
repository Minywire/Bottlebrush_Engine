//
// Created by Marco Garzon Lara on 12/3/2024.
//

#include "Scene.h"

void Scene::createEntity(const std::string & lua_file) //provides a user-friendly function that you only need to specify the script entity to.
{
    entityFactory.create_from_file(bbECS, lua.getLuaState(), lua_file);
}

void Scene::createEntityAndTransform(const std::string & lua_file, float xPos, float yPos, float zPos)
{
    entityFactory.create_from_file(bbECS, lua.getLuaState(), lua_file, xPos, yPos, zPos);
}

Scene::Scene(const std::string& lua_master, unsigned int screen_width, unsigned int screen_height)
    : accumulatedFrameTime(0), UpdateAIInterval(2.f), screenWidth(screen_width), screenHeight(screen_height) {
    renderEngine = GraphicsFactory<GraphicsAPI::OpenGL>::CreateRenderer();
    masterLuaFile = lua_master;
    lua.getLuaState().set_function("create_entity", &Scene::createEntity, this); //register create entity function into lua state of this instance
    lua.getLuaState().set_function("create_entityTR", &Scene::createEntityAndTransform, this);

    const ShaderType defaultShaderType = ShaderType::Default;
    const ShaderType terrainShaderType = ShaderType::Terrain;

    setRendererShaderSource(defaultShaderType, 
                        "Resources/Shaders/Vertex/BasicTex.vert",
                        "Resources/Shaders/Fragment/BasicTex.frag");

    setRendererShaderSource(terrainShaderType, 
                        "Resources/Shaders/Vertex/Heightmap.vert",
                        "Resources/Shaders/Fragment/Heightmap.frag");
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
    if(!lua.getLuaState().do_file(masterLuaFile).valid())
    {
        std::cout << "Could not load master game script file\n";
        return;
    }//load the master lua scene script containing all entities

    bbSystems.createTerrainComponents(bbECS, resources.getSceneTerrain());
    bbSystems.createModelComponents(bbECS, resources.getSceneModels());
    bbSystems.ReadAIScripts(bbECS, lua.getLuaState());

    mainCamera.SetPosition(1000.0f, 100.0f, 1000.0f);
    mainCamera.SetSensitivity(0.05f);
    mainCamera.SetSpeed(100.0f);
    mainCamera.SetZoom(30.0f);
}

void Scene::update(float deltaTime)
{
    accumulatedFrameTime += deltaTime;
    
    projectionMat = glm::perspective(
        glm::radians(mainCamera.GetZoom()),
        (float)screenWidth / (float)screenHeight, 0.1f, 100000.0f);

    viewMat = mainCamera.GetViewMatrix();

    bbSystems.setLight(*renderEngine, ShaderType::Default, viewMatrix);
    Systems::drawTerrain(bbECS, ShaderType::Terrain, *renderEngine, resources.getSceneTerrain(), false, projectionMat, viewMat);
    Systems::drawModels(bbECS, ShaderType::Default, *renderEngine, resources.getSceneModels(), projectionMat, viewMat);

    while (accumulatedFrameTime >= UpdateAIInterval) 
    {
        std::cout << "update all AI call" << std::endl;
        Systems::updateAI(bbECS, lua.getLuaState());
        accumulatedFrameTime -= UpdateAIInterval;
    }
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

Camera& Scene::fetchCamera()
{
    return mainCamera;
}

const glm::mat4& Scene::getProjMat() const 
{
    return projectionMat;
}

const glm::mat4& Scene::getViewMat() const
{
    return viewMat;
}