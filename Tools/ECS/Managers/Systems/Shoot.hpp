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

namespace ECS {

    class Shoot : public System {
        public:
            void basicShot(std::set<Entity> _entities, std::shared_ptr<Coordinator> _coordinator) {
                _entities.insert(_entities.end(), _coordinator->createEntity());
                _coordinator->addComponent(
                    *_entities.rbegin(),
                    Transform {
                        .position = {0, 0, 0},
                        .rotation = {0, 0, 1, -90},
                        .scale = 1.f
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
                        .trajectory = [](tls::Vec3 pos) {
                            return tls::Vec3{pos._x + 2, pos._y, pos._z};
                        },
                        .damage = 1,
                        .speed = 0.5f
                    }
                );
                _coordinator->addComponent(
                    *_entities.rbegin(),
                    ECS::Particles {
                        .particles = std::vector<ECS::Particle>(1000),
                        .texture = std::make_shared<RL::ZTexture>("./client/resources/images/particle.png"),
                        .type = ECS::ParticleType::CONE,
                        .direction = ECS::Direction::UP,
                        .speed = 300.0f,
                        .scaleOffset = 0.0001f,
                        .positionOffset = {0, 0, 0},
                        .lifeTime = 1000,
                        .spawnRate = 10,
                        .spawnTimer = 0
                    }
                );
            }
            void update(std::shared_ptr<RL::IEvent> _event) {
                auto coordinatorPtr = _coordinator.lock();
                if (!coordinatorPtr) {
                    return;
                }
                if (_event->isKeyPressed(KEY_F))
                    basicShot(_entities, coordinatorPtr);

                int count = 0;
                for (auto const &entity : _entities) {
                    count++;
                    auto &transform = coordinatorPtr->getComponent<Transform>(entity);
                    auto &projectile = coordinatorPtr->getComponent<Projectile>(entity);

                    transform.position = projectile.trajectory(transform.position);
                }
                 std::cout << "Shoot: " << count << std::endl;
            }
    };
}

#endif //RTYPE_SHOOT_HPP
