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
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

namespace ECS {
    class AutoMove : public System {
        public:
            void update() {
                auto coordinatorPtr = _coordinator.lock();
                if (!coordinatorPtr) {
                    return;
                }

                for (auto const &entity : _entities) {
                    auto &transform = coordinatorPtr->getComponent<Transform>(entity);
                    auto &trajectory = coordinatorPtr->getComponent<Trajectory>(entity);

                    // tls::Vec3 position = transform.position;

                    transform.position = trajectory.trajectory(transform.position, trajectory.t);

                    // tls::Vec3 newPosition = transform.position;

                    // float angle = std::atan2(newPosition._y - position._y, newPosition._x - position._x) * 180 / M_PI;

                    // transform.rotation = {0, 0, 1, angle - 90};
                }
            }
    };
}

#endif //RTYPE_AutoMove_HPP
