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

        void update() {
            auto coordinatorPtr = _coordinator.lock();
            if (!coordinatorPtr) {
                return;
            }

            for (auto const &entity : _entities) {
                auto &projectile = coordinatorPtr->getComponent<Projectile>(entity);
                auto &transform = coordinatorPtr->getComponent<Transform>(entity);
                tls::Vec3 position = transform.position;

                // transform.position = projectile.trajectory(transform.position, projectile.t);

                // tls::Vec3 newPosition = transform.position;

                // float angle = std::atan2(newPosition._y - position._y, newPosition._x - position._x) * 180 / M_PI;

                // transform.rotation = {0, 0, 1, angle - 90};

//                initProjectile(entity, coordinatorPtr->getComponent<Weapon>(entity));
            }
        }
    };
}

#endif //PROJECTILE_HPP
