/*
** EPITECH PROJECT, 2023
** B-CPP-500-STG-5-2-rtype-noah.gosciniak
** File description:
** Move
*/

#ifndef RTYPE_MOVE_HPP
#define RTYPE_MOVE_HPP

#include "System.hpp"
#include "Coordinator.hpp"
#include "ComponentStructs.hpp"

namespace ECS {
    class Move : public System {
        public:
            void update() {
                auto coordinatorPtr = _coordinator.lock();
                if (!coordinatorPtr) {
                    return;
                }

                // for (auto const &entity : _entities) {
                //     auto &transform = coordinatorPtr->getComponent<Transform>(entity);

                //     transform.position._y -= 0.1;
                //     if (transform.position._y < 0) {
                //         transform.position._y = 20;
                //     }
                // }
            }
    };
}

#endif //RTYPE_MOVE_HPP
