//
// Created by Niamh Wilson on 14/3/2024.
//

#ifndef BOTTLEBRUSH_ENGINE_BOTTLEBRUSH_ENGINE_BOTTLEBRUSH_ENGINE_BBASSETIMPORTER_MESH_H_
#define BOTTLEBRUSH_ENGINE_BOTTLEBRUSH_ENGINE_BOTTLEBRUSH_ENGINE_BBASSETIMPORTER_MESH_H_

#pragma once

#include <RenderEngine.h>
#include <GraphicsFactory.h>

#include "glad/glad.h"

#include <string>
#include <vector>
#include <utility>
#include <cassert>

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>


class Mesh {
 public:
  Mesh(std::vector<float> vertices, std::vector<unsigned int> indices);
  ~Mesh() = default;

 private:
  std::vector<unsigned int> mIndices;
  std::vector<float> mVertices;
};


#endif //BOTTLEBRUSH_ENGINE_BOTTLEBRUSH_ENGINE_BOTTLEBRUSH_ENGINE_BBASSETIMPORTER_MESH_H_
