/*
** EPITECH PROJECT, 2023
** B-CPP-500-STG-5-2-rtype-noah.gosciniak
** File description:
** AutoMove
*/

#ifndef RTYPE_AutoMove_HPP
#define RTYPE_AutoMove_HPP

#include "System.hpp"
#include "Coordinator.hpp"
#include "ComponentStructs.hpp"

namespace ECS {
    class AutoMove : public System {
        public:
            void update() {
                auto coordinatorPtr = _coordinator.lock();
                if (!coordinatorPtr) {
                    return;
                }

                // for (auto const &entity : _entities) {
                //     auto &transform = coordinatorPtr->getComponent<Transform>(entity);
                //     auto &trajectory = coordinatorPtr->getComponent<Trajectory>(entity);

                //     transform.position = trajectory.trajectory(transform.position, trajectory.t);
                // }
            }
    };
}

#endif //RTYPE_AutoMove_HPP
