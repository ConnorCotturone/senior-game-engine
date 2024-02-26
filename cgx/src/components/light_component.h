// jacob curlin
// light_component.h
// 02/25/2024

#ifndef LIGHTCOMPONENT_H
#define LIGHTCOMPONENT_H

#include <glm/glm.hpp>

struct LightComponent
{
    glm::vec3 position;
    glm::vec3 color;
    float intensity;
};



#endif // LIGHTCOMPONENT_H