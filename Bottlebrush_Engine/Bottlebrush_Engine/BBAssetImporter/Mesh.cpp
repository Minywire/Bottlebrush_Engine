//
// Created by Niamh Wilson on 14/3/2024.
//

#include "Mesh.h"
Mesh::Mesh(std::vector<Vertex> verts, std::vector<unsigned int> ind, std::vector<Texture> tex) {
  this->vertices = std::move(verts);
  this->indices = std::move(ind);
  this->textures = std::move(tex);
}
