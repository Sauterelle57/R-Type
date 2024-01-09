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
            void update() {
                auto coordinatorPtr = _coordinator.lock();
                if (!coordinatorPtr) {
                    return;
                }

                for (auto const &entity : _entities) {
                    auto &transform = coordinatorPtr->getComponent<Transform>(entity);
                    auto &collider = coordinatorPtr->getComponent<Collider>(entity);
                    auto &clientUpdater = coordinatorPtr->getComponent<ClientUpdater>(entity);
                    auto clientIDS = clientUpdater.clientController->getClients();

                    for (auto const &entity2 : _entities) {
                        if (entity == entity2) {
                            continue;
                        }
                        auto &transform2 = coordinatorPtr->getComponent<Transform>(entity2);
                        auto &collider2 = coordinatorPtr->getComponent<Collider>(entity2);

//                        if (transform.bounds.min.x < transform2.bounds.max.x && transform.bounds.max.x > transform2.bounds.min.x &&
//                            transform.bounds.min.y < transform2.bounds.max.y && transform.bounds.max.y > transform2.bounds.min.y) {
//                            std::cout << "Collision" << std::endl;
//                        }
                        if (collider.bounds.transform(transform.position, {transform.scale, transform.scale, transform.scale}).intersects(collider2.bounds.transform(transform2.position, {transform2.scale, transform2.scale, transform2.scale}))) {
                            if (collider.breakable && collider2.breakable && collider.team != collider2.team) {
                                {
                                    // std::ostringstream responseStream;
                                    // responseStream << entity << " DESTROY";
                                    clientUpdater._pc->deleteEntity(entity);
                                    // std::string response = responseStream.str();
                                    // clientUpdater.wrapper->sendTo(response, clientID->getIpAdress(), clientID->getPort());
                                }
                                {
                                    // std::ostringstream responseStream;
                                    // responseStream << entity2 << " DESTROY";
                                    clientUpdater._pc->deleteEntity(entity2);
                                    // std::string response = responseStream.str();
                                    // clientUpdater.wrapper->sendTo(response, clientID->getIpAdress(), clientID->getPort());
                                }
                                coordinatorPtr->destroyEntity(entity);
                                coordinatorPtr->destroyEntity(entity2);
                                return;
                            } else if (collider.movable) {
                                transform.position -= collider.velocity + (!collider2.movable ? collider2.velocity : tls::Vec3(0, 0, 0));
                            } else if (collider2.movable) {
                                transform2.position -= collider2.velocity + (!collider.movable ? collider.velocity : tls::Vec3(0, 0, 0));
                            }
                        }
                    }
                }
            }
    };
}
#endif //RTYPE_COLLIDER_HPP
