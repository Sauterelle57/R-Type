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
        void update() {
            auto coordinatorPtr = _coordinator.lock();
            if (!coordinatorPtr) {
                return;
            }

            for (auto const &entity : _entities) {

                auto &projectile = coordinatorPtr->getComponent<Projectile>(entity);
                auto &transform = coordinatorPtr->getComponent<Transform>(entity);

                transform.position = projectile.trajectory(transform.position);
            }
        }
    };
}

#endif //PROJECTILE_HPP
