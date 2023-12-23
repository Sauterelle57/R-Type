/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** PlayerManager.hpp
*/

#ifndef RTYPE_PLAYERMANAGER_HPP
#define RTYPE_PLAYERMANAGER_HPP

#include "System.hpp"
#include "Coordinator.hpp"
#include "ComponentStructs.hpp"

namespace ECS {
    class PlayerManager : public System {
        public:
            void update() {
                auto coordinatorPtr = _coordinator.lock();
                if (!coordinatorPtr) {
                    return;
                }

                for (auto const &entity : _entities) {
                    auto &player = coordinatorPtr->getComponent<Player>(entity);


                }
            }
    };
}

#endif //RTYPE_PLAYERMANAGER_HPP
