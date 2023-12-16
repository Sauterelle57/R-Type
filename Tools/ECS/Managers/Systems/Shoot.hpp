/*
** EPITECH PROJECT, 2023
** B-CPP-500-STG-5-2-rtype-noah.gosciniak
** File description:
** DrawModel
*/

#ifndef RTYPE_SHOOT_HPP
#define RTYPE_SHOOT_HPP

#include "System.hpp"
#include "Coordinator.hpp"
#include "renderer/IEvent.hpp"
#include "ComponentStructs.hpp"
#include "ProjectileFunctions.hpp"

namespace ECS {
    class Shoot : public System {
        public:
            void update() {
                auto coordinatorPtr = _coordinator.lock();
                if (!coordinatorPtr) {
                    return;
                }

                BasicShot(_entities, coordinatorPtr);

                int count = 0;
                for (auto const &entity : _entities) {
                    count++;
                    auto &transform = coordinatorPtr->getComponent<Transform>(entity);
                    auto &projectile = coordinatorPtr->getComponent<Projectile>(entity);

                    transform.position = projectile.trajectory(transform.position);
                }
                // std::cout << "Shoot: " << count << std::endl;
            }
    };
}

#endif //RTYPE_SHOOT_HPP
