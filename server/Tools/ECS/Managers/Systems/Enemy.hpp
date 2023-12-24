/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** EnemySystem.hpp
*/

#ifndef RTYPE_ENEMY_HPP
#define RTYPE_ENEMY_HPP

#include "System.hpp"
#include "Coordinator.hpp"
#include "ComponentStructs.hpp"

namespace ECS {
    class EnemySystem : public System {
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

#endif //RTYPE_ENEMY_HPP
