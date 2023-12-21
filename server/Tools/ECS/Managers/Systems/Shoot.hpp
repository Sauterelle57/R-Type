/*
** EPITECH PROJECT, 2023
** B-CPP-500-STG-5-2-rtype-noah.gosciniak
** File description:
** DrawModel
*/

#ifndef RTYPE_SHOOT_HPP
#define RTYPE_SHOOT_HPP

#include "System.hpp"
#include "Coordinator.hpp"
#include "ComponentStructs.hpp"
#include <cmath>
#define AMPLITUDE 0.5f

namespace ECS {

    class Shoot : public System {
        public:
            static void basicShot(std::shared_ptr<Coordinator> _coordinator, std::set<Entity> _entities, tls::Vec3 _pos) {
                _entities.insert(_entities.end(), _coordinator->createEntity());
                _coordinator->addComponent(
                    *_entities.rbegin(),
                    Transform {
                        .position = _pos,
                        .rotation = {0, 0, 1, -90},
                        .scale = 0.15f
                    }
                );
                _coordinator->addComponent(
                    *_entities.rbegin(),
                    Projectile {
                        .trajectory = [](tls::Vec3 pos, std::shared_ptr<float> t) {
                            return tls::Vec3{pos._x + 1.5, pos._y, pos._z};
                        },
                        .damage = 1,
                        .speed = 0.5f
                    }
                );
            }

            static void doubleSinShot(std::shared_ptr<Coordinator> _coordinator, std::set<Entity> _entities, tls::Vec3 _pos) {
                std::vector<std::function<tls::Vec3(tls::Vec3, std::shared_ptr<float>)>> trajectories = {
                    [](tls::Vec3 pos, std::shared_ptr<float> t) {
                        *t += 0.01f;
                        return tls::Vec3{pos._x + 0.5f, .5 * std::cos((*t) * 10) + pos._y, pos._z };
                    },
                    [](tls::Vec3 pos, std::shared_ptr<float> t) {
                        *t += 0.01f;
                        return tls::Vec3{pos._x + 0.5f, .5 * std::sin((*t) * 10) + pos._y, pos._z };
                    }
                };
                std::vector<double> start = {_pos._y, 0.0};

                for (int i = 0; i < 2; i++) {
                    _entities.insert(_entities.end(), _coordinator->createEntity());
                    _coordinator->addComponent(
                        *_entities.rbegin(),
                        Transform {
                            .position = _pos,
                            .rotation = {0, 0, 1, -90},
                            .scale = 0.1f
                        }
                    );
                    _coordinator->addComponent(
                        *_entities.rbegin(),
                        Projectile {
                            .t = std::make_shared<float>(start[i]),
                            .trajectory = trajectories[i],
                            .damage = 1,
                            .speed = 0.5f
                        }
                    );
                }
            }

            static void sinShot(std::shared_ptr<Coordinator> _coordinator, std::set<Entity> _entities, tls::Vec3 _pos) {
                _entities.insert(_entities.end(), _coordinator->createEntity());
                _coordinator->addComponent(
                    *_entities.rbegin(),
                    Transform {
                        .position = _pos,
                        .rotation = {0, 0, 1, -90},
                        .scale = 0.1f
                    }
                );
                _coordinator->addComponent(
                    *_entities.rbegin(),
                    Projectile {
                        .trajectory = [](tls::Vec3 pos, std::shared_ptr<float> t) {
                            *t += 0.01f;
                            return tls::Vec3{ pos._x + 0.5f, .5 * std::sin((*t) * 10) + pos._y, pos._z };
                        },
                        .damage = 1,
                        .speed = 0.5f
                    }
                );
            }

            static void tripleShot(std::shared_ptr<Coordinator> _coordinator, std::set<Entity> _entities, tls::Vec3 _pos) {
                std::vector<std::function<tls::Vec3(tls::Vec3, std::shared_ptr<float>)>> trajectories = {
                    [](tls::Vec3 pos, std::shared_ptr<float> t) {
                        return tls::Vec3{pos._x + 0.1, pos._y, pos._z};
                    },
                    [](tls::Vec3 pos, std::shared_ptr<float> t) {
                        return tls::Vec3{pos._x + 0.1, pos._y + 0.1, pos._z};
                    },
                    [](tls::Vec3 pos, std::shared_ptr<float> t) {
                        return tls::Vec3{pos._x + 0.1, pos._y - 0.1, pos._z};
                    }
                };
                std::vector<tls::Vec4> rotations = {{0,0,1,-90}, {0,0,1,-45}, {0,0,1,-135}};
                std::vector<ECS::Direction> directions = {ECS::Direction::LEFT, ECS::Direction::LEFT_UP, ECS::Direction::LEFT_DOWN};

                for (int i = 0; i < 3; i++) {
                    _entities.insert(_entities.end(), _coordinator->createEntity());
                    _coordinator->addComponent(
                        *_entities.rbegin(),
                        Transform {
                            .position = _pos,
                            .rotation = rotations[i],
                            .scale = 0.1f
                        }
                    );
                    _coordinator->addComponent(
                        *_entities.rbegin(),
                        Projectile {
                            .direction = directions[i],
                            .trajectory = trajectories[i],
                            .damage = 1,
                            .speed = 0.5f
                        }
                    );
                }
            }

            void update() {
                auto coordinatorPtr = _coordinator.lock();
                if (!coordinatorPtr) {
                    return;
                }

                for (auto const &entity : _entities) {
                    auto &transform = coordinatorPtr->getComponent<Transform>(entity);
                    auto &weapon = coordinatorPtr->getComponent<Weapon>(entity);

                    if (1 == 0) // TODO: check if player is shooting (shoot)
                        weapon.create_projectile(std::shared_ptr<Coordinator>(_coordinator), _entities, transform.position + tls::Vec3{-2, 2.7, 0});
                }
            }
    };
}

#endif //RTYPE_SHOOT_HPP
