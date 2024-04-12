//
//  Created by Alan Brunet 11/04/2024
//

#pragma once

#include <memory>

#include "VertexArray.h"

class Mesh {
protected:

public:
    Mesh(){};
    virtual ~Mesh() = default;

    virtual void CreateMesh(std::vector<float> vertices, unsigned int vertDataSize, std::vector<unsigned int> indices, std::vector<unsigned int> layout) = 0;

    virtual inline std::unique_ptr<VertexArray>& GetVertexArray() = 0;
    virtual inline unsigned int GetIndexCount() =0;
};
