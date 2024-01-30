// jacob curlin
// Transform.h
// 01/28/2024

#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <glm/glm.hpp>

struct TransformComponent
{
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;
};

#endif // TRANSFORM_H