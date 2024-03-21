//
// Created by Niamh Wilson on 14/3/2024.
//

#ifndef BOTTLEBRUSH_ENGINE_BOTTLEBRUSH_ENGINE_BOTTLEBRUSH_ENGINE_BBASSETIMPORTER_MESH_H_
#define BOTTLEBRUSH_ENGINE_BOTTLEBRUSH_ENGINE_BOTTLEBRUSH_ENGINE_BBASSETIMPORTER_MESH_H_

#pragma once


#include <Vector3D.h>
#include <Vector2D.h>

#include "glad/glad.h"

#include <string>
#include <vector>
#include <utility>
#include <cassert>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

struct Vertex {
  BBMaths::Vector3D Position;
  BBMaths::Vector3D Normal;
  BBMaths::Vector2D TexCoords;
};

struct Texture {
  unsigned int id;
  std::string type;
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

  std::vector<std::unique_ptr<Mesh>> mSubMeshes;
  std::vector<unsigned int> mIndices;
  std::vector<Vertex> mVertices;
  std::vector<Texture> mTextures;

  GLuint mVertexArray;
  GLuint mVertexBuffer;
  GLuint mElementBuffer;
};


#endif //BOTTLEBRUSH_ENGINE_BOTTLEBRUSH_ENGINE_BOTTLEBRUSH_ENGINE_BBASSETIMPORTER_MESH_H_
