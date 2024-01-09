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

namespace ECS {
    class ClientUpdaterSystem : public System {
        public:
            void update() {
                auto coordinatorPtr = _coordinator.lock();
                if (!coordinatorPtr) {
                    std::cout << "ClientUpdaterSystem: coordinatorPtr is null" << std::endl;
                    return;
                }

                for (auto const &entity : _entities) {
                    auto &transform = coordinatorPtr->getComponent<Transform>(entity);
                    auto &type = coordinatorPtr->getComponent<Type>(entity);
                    auto &collider = coordinatorPtr->getComponent<Collider>(entity);
                    auto &clientUpdater = coordinatorPtr->getComponent<ClientUpdater>(entity);

                    std::ostringstream responseStream;
                    responseStream << entity << " TRANSFORM " << std::fixed << std::setprecision(2)
                                   << transform.position._x << " " << transform.position._y << " " << transform.position._z << " "
                                   << transform.rotation._x << " " << transform.rotation._y << " " << transform.rotation._z << " "
                                   << transform.rotation._a << " " << transform.scale << " " << "BDB " << collider.bounds.min._x << " " << collider.bounds.min._y << " " << collider.bounds.min._z << " " << collider.bounds.max._x << " " << collider.bounds.max._y << " " << collider.bounds.max._z << " " << type.name;

                    auto clients = clientUpdater.clientController->getClients();

                    for (auto &clt : clients) {
                        std::string response = responseStream.str();
                        if (type.different && (type.ip != clt->getIpAdress() || type.port != clt->getPort()))
                            response += "_NY";
                        clientUpdater.wrapper->sendTo(response, clt->getIpAdress(), clt->getPort());
                    }
                }
            }
    };
}

#endif //RTYPE_CLIENTUPDATER_HPP
