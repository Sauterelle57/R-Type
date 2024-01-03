/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** ClientUpdater.hpp
*/

#ifndef RTYPE_CLIENTUPDATER_HPP
#define RTYPE_CLIENTUPDATER_HPP

#include "System.hpp"
#include "Coordinator.hpp"
#include "../Components/ComponentStructs.hpp"
#include "Protocol.hpp"

namespace ECS {
    class ClientUpdaterSystem : public System {
        public:
            void update() {
                auto coordinatorPtr = _coordinator.lock();
                if (!coordinatorPtr) {
                    std::cout << "ClientUpdaterSystem: coordinatorPtr is null" << std::endl;
                    return;
                }

                //TODO: Enable this to enable serialization
                // rt::ProtocolController pc;
                // pc.setSender(rt::SENDER_TYPE::SERVER);
                // pc.setProtocol(rt::PROTOCOL_TYPE::ENTITIES);

                ClientUpdater clu;
                bool clu_available = false;

                for (auto const &entity : _entities) {
                    auto &transform = coordinatorPtr->getComponent<Transform>(entity);
                    auto &type = coordinatorPtr->getComponent<Type>(entity);
                    auto &clientUpdater = coordinatorPtr->getComponent<ClientUpdater>(entity);
                    clu = clientUpdater;
                    clu_available = true;

                    std::ostringstream responseStream;
                    responseStream << entity << " TRANSFORM " << std::fixed << std::setprecision(2)
                                   << transform.position._x << " " << transform.position._y << " " << transform.position._z << " "
                                   << transform.rotation._x << " " << transform.rotation._y << " " << transform.rotation._z << " "
                                   << transform.rotation._a << " " << transform.scale << " " << type.name;

                    std::cout << "ENTITY : " << entity << " " << transform.position._x << ", " << transform.position._y << ", " << transform.position._z  << "," <<  std::endl;

                    clientUpdater._pc->addEntity(entity, transform.position, transform.rotation, transform.scale, rt::ENTITY_TYPE::PLAYER);
                    // auto clients = clientUpdater.clientController->getClients();
                    // for (auto &clt : clients) {
                    //     std::string response = responseStream.str();
                    //     if (type.different && (type.ip != clt->getIpAdress() || type.port != clt->getPort()))
                    //         response += "_NY";
                    //     clientUpdater.wrapper->sendTo(response, clt->getIpAdress(), clt->getPort());
                    // }
                }

                if (!clu_available)
                    return;
                auto proto = clu._pc->getProtocol();

                for (auto &clt : clu.clientController->getClients()) {
                    auto ents = proto.server.entities;

                    for (auto &ent : ents) {
                        auto id = rt::ProtocolController::getECSIdFromBitset(ent);
                        auto &type = coordinatorPtr->getComponent<Type>(id);

                        if (type.different && (type.ip != clt->getIpAdress() || type.port != clt->getPort())) {
                            std::cout << "ENTITY : " << id << " is different" << std::endl;
                            clu._pc->changeEntityTypeInBitset(ent, rt::ENTITY_TYPE::ENEMY);
                        }
                        // clu.wrapper->sendTo(response, clt->getIpAdress(), clt->getPort());
                    }
                    auto response = clu._pc->serialize();
                    clu.wrapper->sendTo(response, clt->getIpAdress(), clt->getPort());
                }

                // for (auto &x : proto.server.entities) {
                //     auto id = rt::ProtocolController::getECSIdFromBitset(x);
                //     std::cout << "ENTITY : " << id << std::endl;

                // }

                clu._pc->init();
                

                // auto clients = clientUpdater.clientController->getClients();

                // for (auto &clt : clients) {
                //     auto protocol = pc.getProtocol();
                //     auto ip = clt->getIpAdress();
                //     auto port = clt->getPort();
                //     for (auto &entity : protocol.server.entities)
                //         if (type.different && (type.ip != ip || type.port != port))
                //             entity.entityType = rt::ENTITY_TYPE::ENEMY;
                    
                // }
            }

            void send() {
                auto coordinatorPtr = _coordinator.lock();
                if (!coordinatorPtr) {
                    std::cout << "ClientUpdaterSystem: coordinatorPtr is null" << std::endl;
                    return;
                }

                for (auto const &entity : _entities) {
                    auto &transform = coordinatorPtr->getComponent<Transform>(entity);
                    auto &type = coordinatorPtr->getComponent<Type>(entity);
                    auto &clientUpdater = coordinatorPtr->getComponent<ClientUpdater>(entity);
                    break;
                } 
                
            }
    };
}

#endif //RTYPE_CLIENTUPDATER_HPP
