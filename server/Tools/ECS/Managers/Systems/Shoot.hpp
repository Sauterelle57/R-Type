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
#include "ClientController.hpp"
#define AMPLITUDE 0.5f

namespace ECS {

    class Shoot : public System {
        public:
            static void basicShot(std::shared_ptr<Coordinator> _coordinator, std::set<Entity> _entities, tls::Vec3 _pos, std::shared_ptr<rt::ClientController> _clientController, std::shared_ptr<rt::IWrapper> _wrapper) {
                Matrix matr = MatrixMultiply(MatrixIdentity(), MatrixRotateZ(90 * DEG2RAD));
                tls::BoundingBox boundingBox = tls::loadModelAndGetBoundingBox("./client/resources/models/boom.glb");
                boundingBox.applyMatrix(matr);

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
                _coordinator->addComponent(
                    *_entities.rbegin(),
                    ECS::Collider {
                        .team = 0,
                        .bounds = boundingBox
                    }
                );
                _coordinator->addComponent(
                    *_entities.rbegin(),
                    ECS::Type {
                        .name = "BASIC_SHOT"
                    }
                );
                _coordinator->addComponent(
                    *_entities.rbegin(),
                    ECS::ClientUpdater {
                        .wrapper = _wrapper,
                        .clientController = _clientController
                    }
                );
            }
            static void basicEnemyShot(std::shared_ptr<Coordinator> _coordinator, std::set<Entity> _entities, tls::Vec3 _pos, std::shared_ptr<rt::ClientController> _clientController, std::shared_ptr<rt::IWrapper> _wrapper) {
                Matrix matr = MatrixMultiply(MatrixIdentity(), MatrixRotateZ(90 * DEG2RAD));
                tls::BoundingBox boundingBox = tls::loadModelAndGetBoundingBox("./client/resources/models/boom.glb");
                boundingBox.applyMatrix(matr);

                _entities.insert(_entities.end(), _coordinator->createEntity());
                _coordinator->addComponent(
                    *_entities.rbegin(),
                    Transform {
                        .position = _pos,
                        .rotation = {0, 0, 1, 90},
                        .scale = 0.15f
                    }
                );
                _coordinator->addComponent(
                    *_entities.rbegin(),
                    Projectile {
                        .trajectory = [](tls::Vec3 pos, std::shared_ptr<float> t) {
                            return tls::Vec3{pos._x - 0.2, pos._y, pos._z};
                        },
                        .damage = 1,
                        .speed = 0.2f
                    }
                );
                _coordinator->addComponent(
                    *_entities.rbegin(),
                    ECS::Collider {
                        .team = 1,
                        .bounds = boundingBox
                    }
                );
                _coordinator->addComponent(
                    *_entities.rbegin(),
                    ECS::Type {
                        .name = "BASIC_ENEMY_SHOT"
                    }
                );
                _coordinator->addComponent(
                    *_entities.rbegin(),
                    ECS::ClientUpdater {
                        .wrapper = _wrapper,
                        .clientController = _clientController
                    }
                );
            }

            static void doubleSinShot(std::shared_ptr<Coordinator> _coordinator, std::set<Entity> _entities, tls::Vec3 _pos, std::shared_ptr<rt::ClientController> _clientController, std::shared_ptr<rt::IWrapper> _wrapper) {
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
                    _coordinator->addComponent(
                        *_entities.rbegin(),
                        ECS::Collider {
                            .bounds = {
                                    .min = {-1, -1, -1},
                                    .max = {1, 1, 1}
                            }
                        }
                    );
                    _coordinator->addComponent(
                        *_entities.rbegin(),
                        ECS::Type {
                            .name = "SIN_SHOT"
                        }
                    );
                    _coordinator->addComponent(
                        *_entities.rbegin(),
                        ECS::ClientUpdater {
                            .wrapper = _wrapper,
                            .clientController = _clientController
                        }
                    );
                }
            }

            static void sinShot(std::shared_ptr<Coordinator> _coordinator, std::set<Entity> _entities, tls::Vec3 _pos, std::shared_ptr<rt::ClientController> _clientController, std::shared_ptr<rt::IWrapper> _wrapper) {
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
                _coordinator->addComponent(
                    *_entities.rbegin(),
                    ECS::Collider {
                        .bounds = {
                                .min = {-1, -1, -1},
                                .max = {1, 1, 1}
                        }
                    }
                );
                _coordinator->addComponent(
                    *_entities.rbegin(),
                    ECS::Type {
                        .name = "SIN_SHOT"
                    }
                );
                _coordinator->addComponent(
                    *_entities.rbegin(),
                    ECS::ClientUpdater {
                        .wrapper = _wrapper,
                        .clientController = _clientController
                    }
                );
            }

            static void tripleShot(std::shared_ptr<Coordinator> _coordinator, std::set<Entity> _entities, tls::Vec3 _pos, std::shared_ptr<rt::ClientController> _clientController, std::shared_ptr<rt::IWrapper> _wrapper) {
                std::vector<std::function<tls::Vec3(tls::Vec3, std::shared_ptr<float>)>> trajectories = {
                    [](tls::Vec3 pos, std::shared_ptr<float> t) {
                        return tls::Vec3{pos._x + 1, pos._y, pos._z};
                    },
                    [](tls::Vec3 pos, std::shared_ptr<float> t) {
                        return tls::Vec3{pos._x + 0.5, pos._y + 0.5, pos._z};
                    },
                    [](tls::Vec3 pos, std::shared_ptr<float> t) {
                        return tls::Vec3{pos._x + 0.5, pos._y - 0.5, pos._z};
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
                    _coordinator->addComponent(
                        *_entities.rbegin(),
                        ECS::Type {
                            .name = "BASIC_SHOT"
                        }
                    );
                    _coordinator->addComponent(
                        *_entities.rbegin(),
                        ECS::ClientUpdater {
                            .wrapper = _wrapper,
                            .clientController = _clientController
                        }
                    );
                    _coordinator->addComponent(
                        *_entities.rbegin(),
                        ECS::Collider {
                            .bounds = {
                                .min = {-1, -1, -1},
                                .max = {1, 1, 1}
                            }
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
                    auto &updater = coordinatorPtr->getComponent<ClientUpdater>(entity);
                    auto &shooter = coordinatorPtr->getComponent<Shooter>(entity);

                    if (shooter.isShooting) {
                        weapon.create_projectile(std::shared_ptr<Coordinator>(_coordinator), _entities, transform.position + tls::Vec3{0, 0, 0}, updater.clientController, updater.wrapper);
                        shooter.isShooting = false;
                    }
                }
            }
    };
}

#endif //RTYPE_SHOOT_HPP
