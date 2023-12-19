/*
** EPITECH PROJECT, 2023
** B-CPP-500-STG-5-2-rtype-noah.gosciniak
** File description:
** DrawModel
*/

#ifndef RTYPE_PLAY_HPP
#define RTYPE_PLAY_HPP

#include "System.hpp"
#include "Coordinator.hpp"
#include "renderer/IEvent.hpp"

namespace ECS {
    class Play : public System {
        public:
            void update(std::shared_ptr<RL::IEvent> _event) {
                auto coordinatorPtr = _coordinator.lock();
                if (!coordinatorPtr) {
                    return;
                }

                int count = 0;
                for (auto const &entity : _entities) {
                    count++;
                    auto &controle = coordinatorPtr->getComponent<Player>(entity);
                    auto &transform = coordinatorPtr->getComponent<Transform>(entity);

                    if (_event->isKeyDown(controle.key_up)) transform.position._y -= 1;
                    if (_event->isKeyDown(controle.key_down)) transform.position._y += 1;
                    if (_event->isKeyDown(controle.key_left)) transform.position._x -= 1;
                    if (_event->isKeyDown(controle.key_right)) transform.position._x += 1;
                    if (_event->isKeyDown(controle.key_shoot)) std::cout << "shoot" << std::endl;
                    if (_event->isKeyDown(controle.key_validate)) std::cout << "validate" << std::endl;
                    if (_event->isKeyDown(controle.key_cancel)) std::cout << "cancel" << std::endl;
                    if (_event->isKeyDown(controle.key_settings)) std::cout << "settings" << std::endl;
                }
                // std::cout << "Play: " << count << std::endl;
            }
    };
}

#endif //RTYPE_PLAY_HPP
