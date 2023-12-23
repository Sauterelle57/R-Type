/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** Collider.hpp
*/

#ifndef RTYPE_COLLIDER_HPP
#define RTYPE_COLLIDER_HPP
#include "System.hpp"
#include "Coordinator.hpp"
#include "ComponentStructs.hpp"

namespace ECS {
    class ColliderSystem : public System {
        public:
            void update(rt::ClientController &clientCtrl, rt::IWrapper *wrapper) {
                auto coordinatorPtr = _coordinator.lock();
                if (!coordinatorPtr) {
                    return;
                }

                auto clientIDS = clientCtrl.getClients();

                for (auto const &entity : _entities) {
                    auto &transform = coordinatorPtr->getComponent<Transform>(entity);
                    auto &team = coordinatorPtr->getComponent<Collider>(entity).team;

                    for (auto const &entity2 : _entities) {
                        if (entity == entity2) {
                            continue;
                        }
                        auto &transform2 = coordinatorPtr->getComponent<Transform>(entity2);
                        auto &team2 = coordinatorPtr->getComponent<Collider>(entity2).team;

//                        if (transform.bounds.min.x < transform2.bounds.max.x && transform.bounds.max.x > transform2.bounds.min.x &&
//                            transform.bounds.min.y < transform2.bounds.max.y && transform.bounds.max.y > transform2.bounds.min.y) {
//                            std::cout << "Collision" << std::endl;
//                        }
                        if (transform.position._x > transform2.position._x - 2 && transform.position._x < transform2.position._x + 2 &&
                            transform.position._y > transform2.position._y - 2 && transform.position._y < transform2.position._y + 2 && team != team2) {
                            for (auto const &clientID : clientIDS) {
                                std::ostringstream responseStream;
                                responseStream << entity << " DESTROY";
                                std::string response = responseStream.str();
                                wrapper->sendTo(response, clientID->getIpAdress(), clientID->getPort());
                            }
                            for (auto const &clientID : clientIDS) {
                                std::ostringstream responseStream;
                                responseStream << entity2 << " DESTROY";
                                std::string response = responseStream.str();
                                wrapper->sendTo(response, clientID->getIpAdress(), clientID->getPort());
                            }
                            coordinatorPtr->destroyEntity(entity);
                            coordinatorPtr->destroyEntity(entity2);
                            return;
                        }
                    }
                }
            }
    };
}
#endif //RTYPE_COLLIDER_HPP
