// jacob curlin
// model.h
// 02/08/2024


#ifndef MODEL_H
#define MODEL_H

#include "mesh.h"
#include "shader.h"
#include "model.h"

#include <memory>
#include <string>

namespace cgx::graphics
{

    class Model
    {
    public:
        Model(std::vector<std::shared_ptr<Mesh>> meshes);

        void draw(Shader& shader);

    private:
        std::vector<std::shared_ptr<Mesh>> m_meshes;
    };

}

#endif // MODEL_H