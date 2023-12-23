//
// Created by noahg on 17/12/2023.
//

#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP
#include "ComponentStructs.hpp"
#include "Coordinator.hpp"
#include "System.hpp"
#define M_PI_ 3.14159265358979323846
#include <string>
#include <iostream>
#include <iomanip>
#include "IWrapper.hpp"
#include "Vec3.hpp"

namespace ECS {

    class ProjectileSystem : public System {
    public:
        void initProjectile(Entity entity, Weapon &weapon) {
            auto coordinatorPtr = _coordinator.lock();
            if (!coordinatorPtr) {
                return;
            }

            auto &projectiles = coordinatorPtr->getComponent<Projectile>(entity);
            auto &transform = coordinatorPtr->getComponent<Transform>(entity);

            projectiles.damage = weapon.damage;
            projectiles.speed = weapon.speed;
        }

        void update(ECS::Entity cameraEntity, rt::ClientController &clientCtrl, rt::IWrapper *wrapper) {
            auto coordinatorPtr = _coordinator.lock();
            if (!coordinatorPtr) {
                return;
            }

            auto clientIDS = clientCtrl.getClients();
            auto camTransform = coordinatorPtr->getComponent<Transform>(cameraEntity);

            for (auto const &entity : _entities) {
                auto &projectile = coordinatorPtr->getComponent<Projectile>(entity);
                auto &transform = coordinatorPtr->getComponent<Transform>(entity);
                tls::Vec3 position = transform.position;

                transform.position = projectile.trajectory(transform.position, projectile.t);

                tls::Vec3 newPosition = transform.position;

                float angle = std::atan2(newPosition._y - position._y, newPosition._x - position._x) * 180 / M_PI_;

                transform.rotation = {0, 0, 1, angle - 90};

                if (std::abs(camTransform.position._x - transform.position._x) > 100 || std::abs(camTransform.position._y - transform.position._y) > 100) {
                    for (auto const &clientID : clientIDS) {
                        std::ostringstream responseStream;
                        responseStream << entity << " DESTROY";
                        std::string response = responseStream.str();
                        wrapper->sendTo(response, clientID->getIpAdress(), clientID->getPort());
                    }
                    std::cout << "before destroy" << std::endl;
                    std::cout << entity << std::endl;
                    coordinatorPtr->destroyEntity(entity);
                    std::cout << "after destroy" << std::endl;
                    return;
                }

                std::ostringstream responseStream;
                responseStream << entity << " TRANSFORM " << std::fixed << std::setprecision(2)
                            << transform.position._x << " " << transform.position._y << " " << transform.position._z << " "
                            << transform.rotation._x << " " << transform.rotation._y << " " << transform.rotation._z << " "
                            << transform.rotation._a << " " << transform.scale << " BASIC_SHOT";

                std::string response = responseStream.str();

                for (auto const &clientID : clientIDS) {
                    //std::cout << "send info to client " << clientID->getIpAdress() << ", " << clientID->getPort() << std::endl;
                    //std::cout << response << std::endl;
                    wrapper->sendTo(response, clientID->getIpAdress(), clientID->getPort());
                }

//                initProjectile(entity, coordinatorPtr->getComponent<Weapon>(entity));
            }
        }
    };
}

#endif //PROJECTILE_HPP
