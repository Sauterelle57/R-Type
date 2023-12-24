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

                for (auto const &entity : _entities) {
                    auto &transform = coordinatorPtr->getComponent<Transform>(entity);
                    auto &player = coordinatorPtr->getComponent<Player>(entity);
                    auto &coll = coordinatorPtr->getComponent<Collider>(entity);
                    auto &trav = coordinatorPtr->getComponent<Traveling>(entity);

                    transform.position += player.mooving;
                    coll.velocity = trav.speed + player.mooving;
                    player.mooving = {0, 0, 0};
                }
            }
    };
}

#endif //RTYPE_MOVE_HPP
