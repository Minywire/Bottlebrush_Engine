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

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

struct Vertex {
  glm::vec3 Position;
  glm::vec3 Normal;
  glm::vec3 TexCoords;
};

class Mesh {
 public:
  Mesh();
  ~Mesh();

  Mesh(std::string const & fileName);

  // Disable Copying and Assignment
  Mesh(Mesh const &) = delete;
  Mesh & operator=(Mesh const &) = delete;



 private:
  //std::vector<std::unique_ptr<Mesh>> mSubMeshes;
  std::vector<unsigned int> mIndices;
  std::vector<Vertex> mVertices;
  std::vector<Texture> mTextures;

  std::unique_ptr<VertexArray> vertexArray;
  std::unique_ptr<VertexBuffer> vertexBuffer;
  std::unique_ptr<IndexBuffer> indexBuffer;
};


#endif //BOTTLEBRUSH_ENGINE_BOTTLEBRUSH_ENGINE_BOTTLEBRUSH_ENGINE_BBASSETIMPORTER_MESH_H_
