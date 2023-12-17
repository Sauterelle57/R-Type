//
// Created by noahg on 17/12/2023.
//

#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP
#include "ComponentStructs.hpp"
#include "Coordinator.hpp"
#include "System.hpp"

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
            if (projectiles.direction == ECS::UP)
                transform.rotation = (tls::Vec4){ 0, 0, 1, 0 };
            else if (projectiles.direction == ECS::DOWN)
                transform.rotation = (tls::Vec4){ 0, 0, 1, 180 };
            else if (projectiles.direction == ECS::LEFT)
                transform.rotation = (tls::Vec4){ 0, 0, 1, -90 };
            else if (projectiles.direction == ECS::LEFT_DOWN)
                transform.rotation = (tls::Vec4){ 0, 0, 1, -135 };
            else if (projectiles.direction == ECS::LEFT_UP)
                transform.rotation = (tls::Vec4){ 0, 0, 1, -45 };
            else if (projectiles.direction == ECS::RIGHT)
                transform.rotation = (tls::Vec4){ 0, 0, 1, 90 };
            else if (projectiles.direction == ECS::RIGHT_DOWN)
                transform.rotation = (tls::Vec4){ 0, 0, 1, 135 };
            else if (projectiles.direction == ECS::RIGHT_UP)
                transform.rotation = (tls::Vec4){ 0, 0, 1, 45 };
        }

        void update() {
            auto coordinatorPtr = _coordinator.lock();
            if (!coordinatorPtr) {
                return;
            }

            for (auto const &entity : _entities) {
                auto &projectile = coordinatorPtr->getComponent<Projectile>(entity);
                auto &transform = coordinatorPtr->getComponent<Transform>(entity);
                static Direction previous_direction = projectile.direction;
                static tls::Vec3 previous_position = transform.position;

                transform.position = projectile.trajectory(transform.position, projectile.t);

                if (transform.position._y > previous_position._y)
                    projectile.direction = ECS::LEFT_UP;
                else if (transform.position._y < previous_position._y)
                    projectile.direction = ECS::LEFT_DOWN;
                previous_position = transform.position;

                if (previous_direction != projectile.direction) {
                    initProjectile(entity, coordinatorPtr->getComponent<Weapon>(entity));
                    previous_direction = projectile.direction;
                }
            }
        }
    };
}

#endif //PROJECTILE_HPP
