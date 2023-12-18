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
#include "renderer/Model.hpp"
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
                        .scale = 0.1f
                    }
                );
                _coordinator->addComponent(
                    *_entities.rbegin(),
                    Model {
                        .model = std::make_shared<RL::ZModel>("./client/resources/models/boom.glb"),
                    }
                );
                _coordinator->addComponent(
                    *_entities.rbegin(),
                    Projectile {
                        .direction = ECS::Direction::LEFT,
                        .trajectory = [](tls::Vec3 pos, std::shared_ptr<float> t) {
                            return tls::Vec3{pos._x + 0.1, pos._y, pos._z};
                        },
                        .damage = 1,
                        .speed = 0.5f
                    }
                );
                _coordinator->addComponent(
                    *_entities.rbegin(),
                    ECS::Particles {
                        .particles = std::vector<ECS::Particle>(20000),
                        .texture = std::make_shared<RL::ZTexture>("./client/resources/images/particle.png"),
                        .type = ECS::ParticleType::CONE,
                        .direction = ECS::Direction::LEFT,
                        .speed = 400.0f,
                        .scaleOffset = 0.5f,
                        .positionOffset = {-0.5, 0, 0},
                        .lifeTime = 2,
                        .spawnRate = 50,
                        .spawnTimer = 0,
                        .surviveChance = 35
                    }
                );
            }

            static void testShot(std::shared_ptr<Coordinator> _coordinator, std::set<Entity> _entities, tls::Vec3 _pos) {
                _entities.insert(_entities.end(), _coordinator->createEntity());
                _coordinator->addComponent(
                    *_entities.rbegin(),
                    Transform {
                        .position = _pos,
                        .rotation = {0, 0, 1, -90},
                        .scale = 0.1f
                    }
                );
//                 _coordinator->addComponent(
//                     *_entities.rbegin(),
//                     Model {
//                         .model = std::make_shared<RL::ZModel>("./client/resources/models/boom.glb"),
//                     }
//                 );

                _coordinator->addComponent(
                    *_entities.rbegin(),
                    Projectile {
                        .direction = ECS::Direction::LEFT,
                        .trajectory = [](tls::Vec3 pos, std::shared_ptr<float> t) {
                            std::cout << *t << std::endl;
                            *t += 0.01f;
                            return tls::Vec3{ pos._x + 0.5f, 10 * std::sin((*t) * 5), pos._z };
                        },
                        .damage = 1,
                        .speed = 0.5f
                    }
                );
                _coordinator->addComponent(
                    *_entities.rbegin(),
                    ECS::Particles {
                        .particles = std::vector<ECS::Particle>(20000),
                        .texture = std::make_shared<RL::ZTexture>("./client/resources/images/particle.png"),
                        .type = ECS::ParticleType::CONE,
                        .direction = ECS::Direction::LEFT,
                        .speed = 10000.0f,
                        .scaleOffset = 2.0f,
                        .positionOffset = {-0.5, 0, 0},
                        .lifeTime = 12,
                        .spawnRate = 1,
                        .spawnTimer = 0,
                        .surviveChance = 0
                    }
                );
            }

            static void tripleShot(std::shared_ptr<Coordinator> _coordinator, std::set<Entity> _entities, tls::Vec3 _pos) {
                std::vector<std::function<tls::Vec3(tls::Vec3, std::shared_ptr<float>)>> trajectories = {
                    [](tls::Vec3 pos, std::shared_ptr<float> f) {
                        return tls::Vec3{pos._x + 0.1, pos._y, pos._z};
                    },
                    [](tls::Vec3 pos, std::shared_ptr<float> f) {
                        return tls::Vec3{pos._x + 0.1, pos._y + 0.1, pos._z};
                    },
                    [](tls::Vec3 pos, std::shared_ptr<float> f) {
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
                        Model {
                            .model = std::make_shared<RL::ZModel>("./client/resources/models/boom.glb"),
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
                        ECS::Particles {
                            .particles = std::vector<ECS::Particle>(20000),
                            .texture = std::make_shared<RL::ZTexture>("./client/resources/images/particle.png"),
                            .type = ECS::ParticleType::EXPLOSION,
                            .direction = ECS::Direction::LEFT,
                            .speed = 400.0f,
                            .scaleOffset = 0.5f,
                            .positionOffset = {0, 0, 0},
                            .lifeTime = 2,
                            .spawnRate = 50,
                            .spawnTimer = 0,
                            .surviveChance = 35
                        }
                    );
                }
            }

            void update(std::shared_ptr<RL::IEvent> _event) {
                auto coordinatorPtr = _coordinator.lock();
                if (!coordinatorPtr) {
                    return;
                }

                for (auto const &entity : _entities) {
                    auto &transform = coordinatorPtr->getComponent<Transform>(entity);
                    auto &weapon = coordinatorPtr->getComponent<Weapon>(entity);

                    if (_event->isKeyPressed(KEY_F))
                        weapon.create_projectile(std::shared_ptr<Coordinator>(_coordinator), _entities, transform.position + tls::Vec3{1, 2, 0});
                }
            }
    };
}

#endif //RTYPE_SHOOT_HPP
