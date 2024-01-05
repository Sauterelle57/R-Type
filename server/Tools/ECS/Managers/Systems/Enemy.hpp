/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** EnemySystem.hpp
*/

#ifndef RTYPE_ENEMY_HPP
#define RTYPE_ENEMY_HPP

#include "System.hpp"
#include "Coordinator.hpp"
#include "ComponentStructs.hpp"
#include <random>

namespace ECS {
    class EnemySystem : public System {
        public:
            void init() {
                rng = std::mt19937(dev());
                dist1 = std::uniform_int_distribution<std::mt19937::result_type>(1, 50);
            }

            void update() {
                auto coordinatorPtr = _coordinator.lock();
                if (!coordinatorPtr) {
                    return;
                }


                for (auto const &entity : _entities) {
                    auto &transform = coordinatorPtr->getComponent<Transform>(entity);
                    auto &collider = coordinatorPtr->getComponent<Collider>(entity);
                    auto &enemy = coordinatorPtr->getComponent<Enemy>(entity);
                    auto &shooter = coordinatorPtr->getComponent<Shooter>(entity);
                    float rdm = static_cast<float>(dist1(rng));
                    float rdm2 = static_cast<float>(dist1(rng));
                    if (rdm > 49)
                        enemy.isGoingUp = !enemy.isGoingUp;
                    if (rdm > 49)
                        enemy.isTurningLeft = !enemy.isTurningLeft;
                    if ((enemy.isGoingUp || transform.position._y < -15) && transform.position._y <= 30.0) {
                        enemy.isGoingUp = true;
                        transform.position._y += 0.1;
                    } else {
                        enemy.isGoingUp = false;
                        transform.position._y -= 0.1;
                    }
                    if ((enemy.isTurningLeft || transform.rotation._a < -15) && transform.rotation._a <= 15.0) {
                        enemy.isTurningLeft = true;
                        transform.rotation._a += 0.2;
                    } else {
                        enemy.isTurningLeft = false;
                        transform.rotation._a -= 0.2;
                    }
                    if (enemy.clock.isTimeElapsed()) {
                        shooter.isShooting = true;
                    }
                    transform.rotation._x = 1;
                }
            }

            std::random_device dev;
            std::mt19937 rng;
            std::uniform_int_distribution<std::mt19937::result_type> dist1;
    };
}

#endif //RTYPE_ENEMY_HPP
