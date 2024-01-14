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
            static void basicShot(std::shared_ptr<Coordinator> _coordinator, std::set<Entity> _entities, tls::Vec3 _pos, std::shared_ptr<rt::ClientController> _clientController, std::shared_ptr<rt::IWrapper> _wrapper, std::shared_ptr<rt::ProtocolController> _pc) {
                static tls::Matrix rotationMatrix = tls::MatrixRotateX(180 * DEG2RAD);
                static tls::Matrix rotation2Matrix = tls::MatrixRotateY(90 * DEG2RAD);
                static tls::Matrix finalTransformation = MatrixMultiply(rotation2Matrix, rotationMatrix);

                static tls::BoundingBox boundingBox = tls::loadModelAndGetBoundingBox("./client/resources/models/missile.glb");
                static bool first = true;
                if (first) {
                    boundingBox.applyMatrix(finalTransformation);
                    first = false;
                }

                _entities.insert(_entities.end(), _coordinator->createEntity());
                _coordinator->addComponent(
                    *_entities.rbegin(),
                    Transform {
                        .position = _pos,
                        .rotation = {0, 0, 0, 0},
                        .scale = {.1f, .1f, .1f}
                    }
                );
                _coordinator->addComponent(
                    *_entities.rbegin(),
                    Projectile {
                        .damage = 1,
                        .speed = 0.2f
                    }
                );
                _coordinator->addComponent(
                    *_entities.rbegin(),
                    Trajectory {
                        .trajectory = [](tls::Vec3 pos, std::shared_ptr<float> t) {
                            return tls::Vec3{pos._x + 1, pos._y, pos._z};
                        },
                        .oriented = true
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
                        ._pc = _pc,
                        .wrapper = _wrapper,
                        .clientController = _clientController
                    }
                );
            }

            static void basicEnemyShot(std::shared_ptr<Coordinator> _coordinator, std::set<Entity> _entities, tls::Vec3 _pos, std::shared_ptr<rt::ClientController> _clientController, std::shared_ptr<rt::IWrapper> _wrapper, std::shared_ptr<rt::ProtocolController> _pc) {
                static tls::Matrix matr = tls::MatrixMultiply(tls::MatrixIdentity(), tls::MatrixRotateZ(90 * DEG2RAD));
                static tls::BoundingBox boundingBox = tls::loadModelAndGetBoundingBox("./client/resources/models/boom.glb");
                static bool first = true;
                if (first) {
                    boundingBox.applyMatrix(matr);
                    first = false;
                }

                _entities.insert(_entities.end(), _coordinator->createEntity());
                _coordinator->addComponent(
                    *_entities.rbegin(),
                    Transform {
                        .position = _pos,
                        .rotation = {0, 0, 1, 90},
                        .scale = {0.15f, 0.15f, 0.15f}
                    }
                );
                static float speed = 0.2f;
                _coordinator->addComponent(
                    *_entities.rbegin(),
                    Projectile {
                        .damage = 1,
                        .speed = speed
                    }
                );
                _coordinator->addComponent(
                    *_entities.rbegin(),
                    Trajectory {
                        .trajectory = [](tls::Vec3 pos, std::shared_ptr<float> t) {
                            return tls::Vec3{pos._x - speed, pos._y, pos._z};
                        },
                        .oriented = true
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
                        ._pc = _pc,
                        .wrapper = _wrapper,
                        .clientController = _clientController
                    }
                );
            }

            static void doubleSinShot(std::shared_ptr<Coordinator> _coordinator, std::set<Entity> _entities, tls::Vec3 _pos, std::shared_ptr<rt::ClientController> _clientController, std::shared_ptr<rt::IWrapper> _wrapper, std::shared_ptr<rt::ProtocolController> _pc) {
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
                            .scale = {0.15f, 0.15f, 0.15f}
                        }
                    );
                    _coordinator->addComponent(
                        *_entities.rbegin(),
                        Projectile {
                            .damage = 1,
                            .speed = 0.5f
                        }
                    );
                    _coordinator->addComponent(
                        *_entities.rbegin(),
                        Trajectory {
                            .t = std::make_shared<float>(start[i]),
                            .trajectory = trajectories[i],
                            .oriented = true
                        }
                    );
                    _coordinator->addComponent(
                        *_entities.rbegin(),
                        ECS::Collider {
                            .bounds = {
                                    .min = {-2, -2, -2},
                                    .max = {2, 2, 2}
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
                            ._pc = _pc,
                            .wrapper = _wrapper,
                            .clientController = _clientController
                        }
                    );
                }
            }

            static void sinShot(std::shared_ptr<Coordinator> _coordinator, std::set<Entity> _entities, tls::Vec3 _pos, std::shared_ptr<rt::ClientController> _clientController, std::shared_ptr<rt::IWrapper> _wrapper, std::shared_ptr<rt::ProtocolController> _pc) {
                _entities.insert(_entities.end(), _coordinator->createEntity());
                _coordinator->addComponent(
                    *_entities.rbegin(),
                    Transform {
                        .position = _pos,
                        .rotation = {0, 0, 1, -90},
                        .scale = {0.15f, 0.15f, 0.15f}
                    }
                );
                _coordinator->addComponent(
                    *_entities.rbegin(),
                    Projectile {
                        .damage = 1, // HERE CHANGE DAMAGE FOR SAME AS WEAPON
                        .speed = 0.5f
                    }
                );
                _coordinator->addComponent(
                    *_entities.rbegin(),
                    Trajectory {
                        .trajectory = [](tls::Vec3 pos, std::shared_ptr<float> t) {
                            *t += 0.01f;
                            return tls::Vec3{ pos._x + 0.5f, .5 * std::sin((*t) * 10) + pos._y, pos._z };
                        },
                        .oriented = true
                    }
                );
                _coordinator->addComponent(
                    *_entities.rbegin(),
                    ECS::Collider {
                        .bounds = {
                            .min = {-2, -2, -2},
                            .max = {2, 2, 2}
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
                        ._pc = _pc,
                        .wrapper = _wrapper,
                        .clientController = _clientController
                    }
                );
            }

            static void tripleShot(std::shared_ptr<Coordinator> _coordinator, std::set<Entity> _entities, tls::Vec3 _pos, std::shared_ptr<rt::ClientController> _clientController, std::shared_ptr<rt::IWrapper> _wrapper, std::shared_ptr<rt::ProtocolController> _pc) {
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
                static tls::Matrix matr0 = tls::MatrixMultiply(tls::MatrixIdentity(), tls::MatrixRotateZ(90 * DEG2RAD));
                static tls::BoundingBox boundingBox0 = tls::loadModelAndGetBoundingBox("./client/resources/models/boom.glb");
                static tls::Matrix matr1 = tls::MatrixMultiply(tls::MatrixIdentity(), tls::MatrixRotateZ((90 + 45) * DEG2RAD));
                static tls::BoundingBox boundingBox1 = tls::loadModelAndGetBoundingBox("./client/resources/models/boom.glb");
                static tls::Matrix matr2 = tls::MatrixMultiply(tls::MatrixIdentity(), tls::MatrixRotateZ((90 - 45) * DEG2RAD));
                static tls::BoundingBox boundingBox2 = tls::loadModelAndGetBoundingBox("./client/resources/models/boom.glb");
                static bool first = true;
                if (first) {
                    boundingBox0.applyMatrix(matr0);
                    boundingBox1.applyMatrix(matr1);
                    boundingBox2.applyMatrix(matr2);
                    first = false;
                }
                static std::vector<tls::BoundingBox> boundingBoxes = {boundingBox0, boundingBox1, boundingBox2};

                for (int i = 0; i < 3; i++) {
                    _entities.insert(_entities.end(), _coordinator->createEntity());
                    _coordinator->addComponent(
                        *_entities.rbegin(),
                        Transform {
                            .position = _pos,
                            .rotation = rotations[i],
                            .scale = {0.15f, 0.15f, 0.15f}
                        }
                    );
                    _coordinator->addComponent(
                        *_entities.rbegin(),
                        ECS::Collider {
                            .team = 0,
                            .bounds = boundingBoxes[i]
                        }
                    );
                    _coordinator->addComponent(
                        *_entities.rbegin(),
                        Projectile {
                            .damage = 1,
                            .speed = 0.5f
                        }
                    );
                    _coordinator->addComponent(
                        *_entities.rbegin(),
                        Trajectory {
                            .trajectory = trajectories[i],
                            .oriented = true
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
                            ._pc = _pc,
                            .wrapper = _wrapper,
                            .clientController = _clientController
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

                    if (weapon.autoShoot && weapon.shootFrequency.isTimeElapsed()) {
                        weapon.create_projectile(std::shared_ptr<Coordinator>(_coordinator), _entities, transform.position + tls::Vec3{-1, 0, 0}, updater.clientController, updater.wrapper, updater._pc);
                    }
                }
            }
    };
}

#endif //RTYPE_SHOOT_HPP
