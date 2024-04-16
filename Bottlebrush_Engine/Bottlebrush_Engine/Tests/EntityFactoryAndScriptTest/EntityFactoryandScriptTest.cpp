//
// Created by Marco on 08/04/24.
//

#include <gtest/gtest.h>

#include <EntityFactory.h>
#include <BBScript.h>
#include <ECS.h>
#include <Scene.h>

TEST(EntityFactoryandScriptTest, EntityGrabTransformFromScript) { //This tests whether the EntityFactory is capable of creating entities containing transform components directly from scripts
    ECS ecs;
    EntityFactory entityFactorio;
    BBScript luaStateWrapper;

    Entity bruh = entityFactorio.create_from_file(ecs, luaStateWrapper.getLuaState(), "EntityFactoryTest.lua");

    TransformComponent& transformComponent = bruh.GetComponent<TransformComponent>(ecs.getReg());

    EXPECT_EQ(transformComponent.position, glm::vec3(1,2,3)) << transformComponent.position.x << " " << transformComponent.position.y << " " << transformComponent.position.z;
    EXPECT_EQ(transformComponent.rotation, glm::vec3(5,4,3)) << transformComponent.rotation.x << " " << transformComponent.rotation.y << " " << transformComponent.rotation.z;
    EXPECT_EQ(transformComponent.scale, glm::vec3(1000,0,23.1)) << transformComponent.scale.x << " " << transformComponent.scale.y << " " << transformComponent.scale.z;
}

TEST(EntityFactoryandScriptTest, EntityGrabModelFromScript) { //This tests whether the EntityFactory is capable of creating entities containing model components directly from scripts
    ECS ecs2;
    EntityFactory entityFactorio2;
    BBScript luaStateWrapper2;

    Entity bruh2 = entityFactorio2.create_from_file(ecs2, luaStateWrapper2.getLuaState(), "EntityFactoryTest.lua");

    ModelComponent& modelComponent = bruh2.GetComponent<ModelComponent>(ecs2.getReg()); //get a reference to the component that has been stored in the entity from file

    EXPECT_EQ(modelComponent.model_path, "cube.obj") << modelComponent.model_path;
}

TEST(EntityFactoryandScriptTest, MasterFileStorageTest)
{
    Scene testScene("MasterFileTest.lua");

    EXPECT_EQ(testScene.getMasterFile(), "MasterFileTest.lua") << "Lua File: " << testScene.getMasterFile(); //lets me know if the actual file stored in the master file script is good.
}

TEST(EntityFactoryandScriptTest, LuaFunctionRegTest)
{
    Scene testScene("MasterFileTest.lua");

    testScene.init();

    auto group = testScene.getECS().GetAllEntitiesWith<ModelComponent>(); //the container with all the matching entities

    for(auto entity : group)
    {
        auto& currentModelComponent = group.get<ModelComponent>(entity); //get the current component from the group entities

        std::cout << "Current model path from current entity component: " << currentModelComponent.model_path << "\n";
        //trying to see if the lua script entities actually get created as ECS entities. Paths should be able to be retrieved from ECS registry if this is the case
    }
}