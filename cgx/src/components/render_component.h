// jacob curlin
// render_component.h
// 01/29/2024

#ifndef RENDERCOMPONENT_H
#define RENDERCOMPONENT_H

#include <glm/glm.hpp>
#include "../render/model.h"
#include "../render/shader.h"

struct RenderComponent
{
    std::shared_ptr<cgx::graphics::Model> model;
    std::shared_ptr<cgx::graphics::Shader> shader;
};



#endif // RENDERCOMPONENT_H