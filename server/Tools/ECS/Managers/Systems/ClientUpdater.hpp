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
#include <map>
#include "Clock.hpp"

namespace ECS {
    class ClientUpdaterSystem : public System {
        public:
            void update(bool debug) {
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
                    auto &colliderStruct = coordinatorPtr->getComponent<Collider>(entity);
                    auto collider = colliderStruct.bounds.transform(transform.position, transform.scale);
                    auto &clientUpdater = coordinatorPtr->getComponent<ClientUpdater>(entity);
                    clu = clientUpdater;
                    clu_available = true;

                    // std::ostringstream responseStream;
                    // responseStream << entity << " TRANSFORM " << std::fixed << std::setprecision(2)
                    //                << transform.position._x << " " << transform.position._y << " " << transform.position._z << " "
                    //                << transform.rotation._x << " " << transform.rotation._y << " " << transform.rotation._z << " "
                    //                << transform.rotation._a << " " << transform.scale << " " << type.name;

                    static std::map<std::string, rt::ENTITY_TYPE> nameToId = {
                        {"CAMERA", rt::ENTITY_TYPE::CAMERA},
                        {"PLAYER", rt::ENTITY_TYPE::PLAYER},
                        {"ENEMY", rt::ENTITY_TYPE::ENEMY},
                        {"BOSS", rt::ENTITY_TYPE::BOSS},
                        {"CHILD", rt::ENTITY_TYPE::CHILD},
                        {"TILE", rt::ENTITY_TYPE::TILE},
                        {"TILE_BREAKABLE", rt::ENTITY_TYPE::TILE_BREAKABLE},
                        {"BASIC_SHOT", rt::ENTITY_TYPE::BASIC_SHOT},
                        {"BASIC_ENEMY_SHOT", rt::ENTITY_TYPE::BASIC_ENEMY_SHOT},
                        {"SIN_SHOT", rt::ENTITY_TYPE::SIN_SHOT},
                    };

                    clientUpdater._pc->addEntity(entity, transform.position, transform.rotation, transform.scale, nameToId[type.name], collider);
                    // auto clients = clientUpdater.clientController->getClients();
                    // for (auto &clt : clients) {
                    //     std::string response = responseStream.str();
                    //     if (type.different && (type.ip != clt->getIpAdress() || type.port != clt->getPort()))
                    //         response += "_NY";di
                    //     clientUpdater.wrapper->sendTo(response, clt->getIpAdress(), clt->getPort());
                    // }
                }

                if (!clu_available)
                    return;
                auto proto = clu._pc->getProtocol();

                for (auto &clt : clu.clientController->getClients()) {
                    auto ents = proto.server.entities;
                    std::vector<rt::Entity> newEnts;

                    for (auto &ent : ents) {
                        auto id = ent.ECSEntity;
                        auto &type = coordinatorPtr->getComponent<Type>(id);
                        if (type.different && (type.ip != clt->getIpAdress() || type.port != clt->getPort())) {
                            ent.entityType = rt::ENTITY_TYPE::PLAYER_NY;
                        }
                        auto acknowledge = clt->getDeltaManager()->getAcknowledge(id, ent);
                        if (acknowledge.signature[0] || acknowledge.signature[1] || acknowledge.signature[2] || acknowledge.signature[3] || acknowledge.signature[4] || acknowledge.signature[5] || acknowledge.signature[6] || acknowledge.signature[7] || acknowledge.signature[8] || acknowledge.signature[9] || acknowledge.signature[10] || acknowledge.signature[11] || acknowledge.signature[12] || acknowledge.signature[13] || acknowledge.signature[14])
                            newEnts.push_back(acknowledge);
                    }
                    auto newProto = proto;
                    newProto.server.destroyedEntities = clt->getDeltaManager()->getDeletedEntities(proto.server.destroyedEntities);

                    for (auto x : newProto.server.destroyedEntities) {
                        clt->getDeltaManager()->deleteEntity(x);
                    }
                    clt->getDeltaManager()->setPacket(newProto);
                    auto response = clu._pc->serialize(newProto, debug);
                    clu.wrapper->sendTo(response, clt->getIpAdress(), clt->getPort());
                }

                clu._pc->init();
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
