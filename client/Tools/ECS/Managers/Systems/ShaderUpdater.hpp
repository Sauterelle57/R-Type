/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** ShaderUpdater.hpp
*/

#ifndef RTYPE_SHADERUPDATER_HPP
#define RTYPE_SHADERUPDATER_HPP
#include "System.hpp"
#include "Coordinator.hpp"
#include "ComponentStructs.hpp"

namespace ECS {
    class ShaderUpdaterSystem : public System {
        public:
            void update(tls::Vec3 cameraPos) {
                auto coordinatorPtr = _coordinator.lock();
                if (!coordinatorPtr) {
                    return;
                }

                for (auto const &entity : _entities) {
                    auto &shader = coordinatorPtr->getComponent<ShaderComponent>(entity).shader;
                    auto &model = coordinatorPtr->getComponent<Model>(entity);

                    float camPos[3] = {static_cast<float>(cameraPos._x), static_cast<float>(cameraPos._y), static_cast<float>(cameraPos._z)};
                    shader->setValue(shader->getShader()->locs[SHADER_LOC_VECTOR_VIEW], camPos, SHADER_UNIFORM_VEC3);


                    for (int matIndex = 0; matIndex < model.model->getModel()->materialCount; matIndex++) {
                        if (model.model->getModel()->materials[matIndex].shader.locs[SHADER_LOC_MAP_DIFFUSE] != -1) {
                            model.model->getModel()->materials[matIndex].shader = *shader->getShader();
//                            model.model->getModel()->materials[matIndex].shader = *shader->getShader();
                        }
                    }
                }
            }
    };
}

#endif //RTYPE_SHADERUPDATER_HPP
