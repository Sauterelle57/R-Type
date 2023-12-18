/*
** EPITECH PROJECT, 2023
** B-CPP-500-STG-5-2-rtype-noah.gosciniak
** File description:
** ParticleEmitter
*/

#ifndef RTYPE_PARTICLE_EMITTER_HPP_
#define RTYPE_PARTICLE_EMITTER_HPP_

#include <memory>
#include "System.hpp"
#include "Entity.hpp"
#include "Coordinator.hpp"
#include "ComponentStructs.hpp"

namespace ECS {
    class ParticlesEmitter : public System {
        public:
            static void basicParticule(std::shared_ptr<Coordinator> _coordinator, std::set<Entity> _entities, tls::Vec3 _pos) {
                _entities.insert(_entities.end(), _coordinator->createEntity());
                _coordinator->addComponent(
                    *_entities.rbegin(),
                    Transform {
                        .position = _pos,
                        .rotation = {0, 0, 0, 0},
                        .scale = 0.1f
                    }
                );
                _coordinator->addComponent(
                    *_entities.rbegin(),
                    ECS::Particle {
                        .position = _pos,
                        .speed = 400.0f,
                        .alpha = 2,
                        .active = false
                    }
                );
            }
            //     auto coordinatorPtr = _coordinator.lock();
            //     if (!coordinatorPtr) {
            //         return;
            //     }

            //     auto &particles = coordinatorPtr->getComponent<Particles>(entity);
            //     auto &transform = coordinatorPtr->getComponent<Transform>(entity);

            //     particle.position = transform.position + particles.positionOffset;
            //     particle.speed = (tls::Vec3){ RL::Utils::getRandomValue(-10, 10) / particles.speed, RL::Utils::getRandomValue(100, 200) / (particles.speed * 10), RL::Utils::getRandomValue(-10, 10) / particles.speed };
            //     particle.alpha = particles.lifeTime;
            //     particle.active = true;
            // }

            void emitParticles(Entity entity) {
                auto coordinatorPtr = _coordinator.lock();
                if (!coordinatorPtr) {
                    return;
                }

                auto &particles = coordinatorPtr->getComponent<Particles>(entity);

                int count = 0;
                for (auto &particle : particles.particles) {
                    if (!particle.active) {
                        initParticle(entity, particle);
                        if (++count >= particles.spawnRate)
                            break;
                    }
                }
            }

            void drawParticles(std::shared_ptr<RL::ICamera> camera, std::shared_ptr<RL::IShader> shader) {
                auto coordinatorPtr = _coordinator.lock();
                RL::ZMode mode;
                if (!coordinatorPtr) {
                    return;
                }

                shader->beginMode();
                mode.beginBlend(BLEND_ADDITIVE);
                for (auto const &entity: _entities) {
                    auto &particles = coordinatorPtr->getComponent<Particles>(entity);
                    auto &transform = coordinatorPtr->getComponent<Transform>(entity);

                    for (auto &particle : particles.particles) {
                        if (particle.active) {
                            camera->drawBillboard(*particles.texture->getTexture().get(), particle.position, transform.scale * particles.scaleOffset, RL::Utils::fade(WHITE, particle.alpha));
                        }
                    }
                }
                mode.endBlend();
                shader->endMode();
            }

            void update(std::shared_ptr<RL::ICamera> _camera, std::shared_ptr<RL::IShader> _shader) {
                auto coordinatorPtr = _coordinator.lock();
                if (!coordinatorPtr) {
                    return;
                }

                for (auto const &entity: _entities) {
                    auto &emitter = coordinatorPtr->getComponent<ParticlesEmitter>(entity);
                    // updateParticles(entity);
                    entity.createParticle()
                    emitParticles(entity);
                }
                drawParticles(_camera, _shader);

            };
    };
};

#endif /* !RTYPE_PARTICLE_EMITTER_HPP_ */
