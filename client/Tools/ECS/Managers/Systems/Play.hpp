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
#include "UdpClient.hpp"

namespace ECS {
    class Play : public System {
        public:
            void update(std::shared_ptr<RL::IEvent> _event, std::shared_ptr<rt::UdpClient> udpClient) {
                auto coordinatorPtr = _coordinator.lock();
                if (!coordinatorPtr) {
                    return;
                }

                for (auto const &entity : _entities) {
                    auto &controle = coordinatorPtr->getComponent<Player>(entity);

                    tls::Vec3 mooving = {0, 0, 0};

                    if (_event->isKeyDown(controle.key_up)) mooving._y += 1;
                    if (_event->isKeyDown(controle.key_down)) mooving._y -= 1;
                    if (_event->isKeyDown(controle.key_left)) mooving._x -= 1;
                    if (_event->isKeyDown(controle.key_right)) mooving._x += 1;
//                    std::cout << mooving._x << " " << mooving._y << " " << mooving._z << std::endl;
                    if (mooving._x != 0 || mooving._y != 0 || mooving._z != 0) {
                        std::string str = "MOVE " + std::to_string(static_cast<int>(mooving._x)) + " " + std::to_string(static_cast<int>(mooving._y)) + " " + std::to_string(static_cast<int>(mooving._z));
                        udpClient->send(str);
                    }
                    if (_event->isKeyPressed(controle.key_shoot)) {
                        std::cout << "shoot" << std::endl;
                        udpClient->send("SHOOT");
                    }
                    if (_event->isKeyDown(controle.key_validate)) std::cout << "validate" << std::endl;
                    if (_event->isKeyDown(controle.key_cancel)) {
                        std::cout << "cancel" << std::endl;
                    };
                    if (_event->isKeyDown(controle.key_settings)) std::cout << "settings" << std::endl;
                }
                // std::cout << "Play: " << count << std::endl;
            }
    };
}

#endif //RTYPE_PLAY_HPP
