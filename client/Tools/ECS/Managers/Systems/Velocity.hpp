/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** Velocity.hpp
*/

#ifndef RTYPE_VELOCITY_HPP
#define RTYPE_VELOCITY_HPP
#include "System.hpp"
#include "Coordinator.hpp"
#include "ComponentStructs.hpp"

namespace ECS {
    class VelocitySystem : public System {
        public:
            void getOldPosition() {
                auto coordinatorPtr = _coordinator.lock();
                if (!coordinatorPtr) {
                    return;
                }

                for (auto const &entity : _entities) {
                    auto &transform = coordinatorPtr->getComponent<Transform>(entity);
                    auto &velocity = coordinatorPtr->getComponent<Velocity>(entity);

                    velocity.oldPosition = transform.position;
                }
            }

            void update() {
                auto coordinatorPtr = _coordinator.lock();
                if (!coordinatorPtr) {
                    return;
                }

                for (auto const &entity : _entities) {
                    auto &transform = coordinatorPtr->getComponent<Transform>(entity);
                    auto &velocity = coordinatorPtr->getComponent<Velocity>(entity);

                    velocity.speed = transform.position - velocity.oldPosition;
                }
            }
    };
}
#endif //RTYPE_VELOCITY_HPP
