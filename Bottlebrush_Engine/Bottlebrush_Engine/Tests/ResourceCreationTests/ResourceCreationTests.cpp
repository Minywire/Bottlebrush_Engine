//
// Created by Marco on 17/04/24.
//
#include <gtest/gtest.h>

#include <Scene.h>
#include <BBResourceManager.hpp>
#include <ECS.h>

TEST(ResourceCreationTests, GenerateFromComponentTest)
{
    BBResourceManager resourceMan;
    const ModelComponent testComponent = { "cube.obj" };

    resourceMan.generateModelFromComponent(testComponent);

}