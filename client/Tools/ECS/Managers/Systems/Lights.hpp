/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** Lights.hpp
*/

#ifndef RTYPE_LIGHTS_HPP
#define RTYPE_LIGHTS_HPP

#include "System.hpp"
#include "Coordinator.hpp"
#include "ComponentStructs.hpp"
#include "renderer/Shader.hpp"

namespace ECS {
    class LightSystem : public System {
        public:
            void update() {
                auto coordinatorPtr = _coordinator.lock();
                if (!coordinatorPtr) {
                    return;
                }

                for (auto const &entity : _entities) {
                    auto &transform = coordinatorPtr->getComponent<Transform>(entity);
                    auto &light = coordinatorPtr->getComponent<LightComponent>(entity);
                    auto &shader = coordinatorPtr->getComponent<ShaderComponent>(entity).shader;

                    light.light.position = transform.position;

                    UpdateLightValues(*shader->getShader(), light.light);
                }
            }
    };
}

#endif //RTYPE_LIGHTS_HPP
