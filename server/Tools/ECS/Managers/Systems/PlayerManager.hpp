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
            void update(const std::string &data, const std::string &ip, const int port) {
                auto coordinatorPtr = _coordinator.lock();
                if (!coordinatorPtr) {
                    return;
                }

                for (auto const &entity : _entities) {
                    auto &player = coordinatorPtr->getComponent<Player>(entity);
                    auto &type = coordinatorPtr->getComponent<Type>(entity);
                    auto &clientUpdater = coordinatorPtr->getComponent<ClientUpdater>(entity);
                    auto &transform = coordinatorPtr->getComponent<ECS::Transform>(entity);
                    auto &collider = coordinatorPtr->getComponent<ECS::Collider>(entity);


                    if (type.ip == ip && type.port == port) {
                        std::istringstream iss(data);
                        std::string command;
                        iss >> command;

                        if (command == "MOVE") {
                            int x, y, z;
                            if (iss >> x >> y >> z) {
                                if ((x >= -1 && x <= 1) && (y >= -1 && y <= 1) && (z >= -1 && z <= 1)) {
                                    std::cout << "Command: " << command << ", x: " << x << ", y: " << y << ", z: " << z << std::endl;

                                    player.mooving._x = x * 0.25f;
                                    player.mooving._y = y * 0.25f;
                                    player.mooving._z = z * 0.25f;
                                }
                            } else {
                                std::cerr << "Error extracting values from the string." << std::endl;
                            }
                        } else if (command == "SHOOT") {
                            player.isShooting = true;
                        }
                    }
                }
            }
    };
}

#endif //RTYPE_PLAYERMANAGER_HPP
