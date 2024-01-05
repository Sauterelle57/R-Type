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
//#include "ComponentStructs.hpp"
#include "../Components/ComponentStructs.hpp"
#include "../../../../src/renderer/Shader.hpp"
#include "../../../../src/renderer/Window.hpp"

namespace ECS {
    class LightSystem : public System {
        public:
            void update(const std::shared_ptr<RL::IWindow>& window, const std::shared_ptr<RL::ZShader>& shader) {
                auto coordinatorPtr = _coordinator.lock();
                if (!coordinatorPtr) {
                    return;
                }

                static bool drawHitbox = false;

                if (IsKeyPressed(KEY_H))
                    drawHitbox = !drawHitbox;
                for (auto const &entity : _entities) {
                    auto &transform = coordinatorPtr->getComponent<Transform>(entity);
                    auto &light = coordinatorPtr->getComponent<LightComponent>(entity);

                    light.light.position = transform.position;

                    UpdateLightValues(*shader->getShader(), light.light);

                    if (drawHitbox)
                        window->drawSphereWires(transform.position, transform.scale, 5, 5, light.light.color);
                }
            }
    };
}

#endif //RTYPE_LIGHTS_HPP
