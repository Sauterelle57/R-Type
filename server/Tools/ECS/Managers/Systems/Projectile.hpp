//
// Created by noahg on 17/12/2023.
//

#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP
#include "ComponentStructs.hpp"
#include "Coordinator.hpp"
#include "System.hpp"
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
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
            auto &collider = coordinatorPtr->getComponent<Collider>(entity);

            collider.damage = weapon.damage;
            collider.life = 1.0f;
            collider.maxLife = 1.0f;
            projectiles.speed = weapon.speed;
        }

        void update(ECS::Entity cameraEntity) {
            auto coordinatorPtr = _coordinator.lock();
            if (!coordinatorPtr) {
                return;
            }

            auto camTransform = coordinatorPtr->getComponent<Transform>(cameraEntity);

            for (auto const &entity : _entities) {
                auto &projectile = coordinatorPtr->getComponent<Projectile>(entity);
                auto &transform = coordinatorPtr->getComponent<Transform>(entity);
                auto &clientUpdater = coordinatorPtr->getComponent<ClientUpdater>(entity);
                auto clientIDS = clientUpdater.clientController->getClients();

                // tls::Vec3 position = transform.position;

                // transform.position = projectile.trajectory(transform.position, projectile.t);

                // tls::Vec3 newPosition = transform.position;

                // float angle = std::atan2(newPosition._y - position._y, newPosition._x - position._x) * 180 / M_PI;

                // transform.rotation = {0, 0, 1, angle - 90};

                if (std::abs(camTransform.position._x - transform.position._x) > 75 || std::abs(camTransform.position._y - transform.position._y) > 75 ||
                    std::abs(camTransform.position._x - transform.position._x) < -75 || std::abs(camTransform.position._y - transform.position._y) < -75) {
//                    for (auto const &clientID : clientIDS) {
                        // std::ostringstream responseStream;
                        // responseStream << entity << " DESTROY";
//                        std::cout << "DESTROY " << entity << std::endl;
                        clientUpdater._pc->deleteEntity(entity, tls::Clock::getTimeStamp());
                        // std::string response = responseStream.str();
                        // clientUpdater.wrapper->sendTo(response, clientID->getIpAdress(), clientID->getPort());
//                    }
                    coordinatorPtr->destroyEntity(entity);
                    return;
                }
            }
        }
    };
}

#endif //PROJECTILE_HPP
