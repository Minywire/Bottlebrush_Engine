//
// Created by Niamh Wilson on 14/3/2024.
//

#ifndef BOTTLEBRUSH_ENGINE_BOTTLEBRUSH_ENGINE_BOTTLEBRUSH_ENGINE_BBASSETIMPORTER_MESH_H_
#define BOTTLEBRUSH_ENGINE_BOTTLEBRUSH_ENGINE_BOTTLEBRUSH_ENGINE_BBASSETIMPORTER_MESH_H_

#pragma once

#include <../include/engine/maths/Vector3D.h>
#include <../include/engine/maths/Vector2D.h>
#include <string>
#include <vector>
#include <utility>

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
  Mesh(std::vector<Vertex> verts, std::vector<unsigned int> ind, std::vector<Texture> tex);
 private:
  // Mesh data
  std::vector<Vertex> vertices;
  std::vector<unsigned int> indices;
  std::vector<Texture> textures;
};

#endif //BOTTLEBRUSH_ENGINE_BOTTLEBRUSH_ENGINE_BOTTLEBRUSH_ENGINE_BBASSETIMPORTER_MESH_H_
