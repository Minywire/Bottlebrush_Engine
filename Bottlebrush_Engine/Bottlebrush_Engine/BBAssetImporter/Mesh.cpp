//
// Created by Niamh Wilson on 14/3/2024.
//

#include "Mesh.h"

#include <utility>

Mesh::Mesh(std::vector<float> vertices, std::vector<unsigned int> indices) {
    mVertices = std::move(vertices);
    mIndices = std::move(indices);
}
