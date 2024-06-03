//
// Created by niamh on 26/04/2024.
//

#ifndef BOTTLEBRUSH_ENGINE_LIGHT_H
#define BOTTLEBRUSH_ENGINE_LIGHT_H

#include <glm/glm.hpp>

class Light {
public:
    Light();

    glm::vec3 colour;
    float ambientIntensity;
};


#endif //BOTTLEBRUSH_ENGINE_LIGHT_H
