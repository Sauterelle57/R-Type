/*
** EPITECH PROJECT, 2023
** B-CPP-500-STG-5-2-rtype-noah.gosciniak
** File description:
** Particle System
*/

#ifndef RTYPE_PARTICLE_HPP
#define RTYPE_PARTICLE_HPP

#include "System.hpp"
#include "Coordinator.hpp"
#include "renderer/Utils.hpp"
#include "renderer/Camera.hpp"
#include "renderer/Texture.hpp"
#include "renderer/Shader.hpp"
#include "renderer/Mode.hpp"
#include "Vec3.hpp"

namespace ECS {
    class ParticleSystem : public System {
        public:
            void initParticle(Entity entity, Particle &particle) {
                auto coordinatorPtr = _coordinator.lock();
                if (!coordinatorPtr) {
                    return;
                }

                auto &particles = coordinatorPtr->getComponent<Particles>(entity);
                auto &transform = coordinatorPtr->getComponent<Transform>(entity);

                particle.position = transform.position + particles.positionOffset;
                if (particles.direction == ECS::UP)
                    particle.speed = (tls::Vec3){ RL::Utils::getRandomValue(-10, 10) / particles.speed, RL::Utils::getRandomValue(100, 200) / (particles.speed * 10), RL::Utils::getRandomValue(-10, 10) / particles.speed };
                else if (particles.direction == ECS::DOWN)
                    particle.speed = (tls::Vec3){ RL::Utils::getRandomValue(-10, 10) / particles.speed, RL::Utils::getRandomValue(-200, -100) / (particles.speed * 10), RL::Utils::getRandomValue(-10, 10) / particles.speed };
                else if (particles.direction == ECS::LEFT)
                    particle.speed = (tls::Vec3){ RL::Utils::getRandomValue(-200, -100) / (particles.speed * 10), RL::Utils::getRandomValue(-10, 10) / particles.speed, RL::Utils::getRandomValue(-10, 10) / particles.speed };
                else if (particles.direction == ECS::RIGHT)
                    particle.speed = (tls::Vec3){ RL::Utils::getRandomValue(100, 200) / (particles.speed * 10), RL::Utils::getRandomValue(-10, 10) / particles.speed, RL::Utils::getRandomValue(-10, 10) / particles.speed };
                particle.alpha = particles.lifeTime;
                particle.active = true;
            }

            void updateParticles(Entity entity) {
                auto coordinatorPtr = _coordinator.lock();
                if (!coordinatorPtr) {
                    return;
                }

                auto &particles = coordinatorPtr->getComponent<Particles>(entity);
                auto &transform = coordinatorPtr->getComponent<Transform>(entity);

                for (auto &particle : particles.particles) {
                    if (particle.active) {
                        particle.position._x += particle.speed._x;
                        particle.position._y += particle.speed._y;
                        particle.position._z += particle.speed._z;
                        particle.alpha -= 1.0f - (RL::Utils::getRandomValue(0, 100) < particles.surviveChance ? particles.lifeTime : 0.0f);

                        if (particle.alpha <= 0.0f)
                            particle.active = false;
                    }
                }
            }

            void emitParticles (Entity entity) {
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
                for (auto const &entity: _entities) {
                    updateParticles(entity);
                    emitParticles(entity);
                }
                drawParticles(_camera, _shader);
            }
    };
}

#endif //RTYPE_PARTICLE_HPP
