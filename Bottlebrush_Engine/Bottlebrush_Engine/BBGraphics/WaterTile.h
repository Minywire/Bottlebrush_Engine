//
// Created by niamh on 1/06/2024.
//

#ifndef BOTTLEBRUSH_ENGINE_WATERTILE_H
#define BOTTLEBRUSH_ENGINE_WATERTILE_H

#include <glm/glm.hpp>

class WaterTile {

public:
    WaterTile(glm::vec3 waterPosition, int waterWidth, int waterHeight);
private:
    glm::vec3 position;
    int width, height;
};


#endif //BOTTLEBRUSH_ENGINE_WATERTILE_H
