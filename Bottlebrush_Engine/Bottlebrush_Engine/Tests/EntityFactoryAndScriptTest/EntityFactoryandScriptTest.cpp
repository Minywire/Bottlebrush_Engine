//
// Created by Marco on 08/04/24.
//

#include <gtest/gtest.h>

#include <EntityFactory.h>
#include <BBScript.h>
#include <ECS.h>
#include <Scene.h>

TEST(EntityFactoryandScriptTest, EntityGrabTransformFromScript) {
    ECS ecs;
    EntityFactory entityFactorio;
    BBScript luaStateWrapper;

    Entity bruh = entityFactorio.create_from_file(ecs, luaStateWrapper.getLuaState(), "EntityFactoryTest.lua");

    TransformComponent& transformComponent = bruh.GetComponent<TransformComponent>(ecs.getReg());

    EXPECT_EQ(transformComponent.position, glm::vec3(1,2,3)) << transformComponent.position.x << " " << transformComponent.position.y << " " << transformComponent.position.z;
    EXPECT_EQ(transformComponent.rotation, glm::vec3(5,4,3)) << transformComponent.rotation.x << " " << transformComponent.rotation.y << " " << transformComponent.rotation.z;
    EXPECT_EQ(transformComponent.scale, glm::vec3(1000,0,23.1)) << transformComponent.scale.x << " " << transformComponent.scale.y << " " << transformComponent.scale.z;
}

TEST(EntityFactoryandScriptTest, EntityGrabModelFromScript) {
    ECS ecs2;
    EntityFactory entityFactorio2;
    BBScript luaStateWrapper2;

    Entity bruh2 = entityFactorio2.create_from_file(ecs2, luaStateWrapper2.getLuaState(), "EntityFactoryTest.lua");

    ModelComponent& modelComponent = bruh2.GetComponent<ModelComponent>(ecs2.getReg());

    EXPECT_EQ(modelComponent.model_path, "cube.obj") << modelComponent.model_path;
}

TEST(EntityFactoryandScriptTest, MasterFileStorageTest)
{
    Scene testScene("MasterFileTest.lua");

    EXPECT_EQ(testScene.getMasterFile(), "MasterFileTest.lua") << "Lua File: " << testScene.getMasterFile();
}

TEST(EntityFactoryandScriptTest, LuaFunctionRegTest)
{
    Scene testScene("MasterFileTest.lua");

    testScene.init();



}
TEST(EntityFactoryandScriptTest, MasterFileCreationTest)
{

}

