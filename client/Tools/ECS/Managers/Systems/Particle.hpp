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
            static void initParticleConeUp(std::shared_ptr<Coordinator> coordinator, Entity entity, Particle &particle) {
                if (!coordinator) {
                    return;
                }

                auto &particles = coordinator->getComponent<Particles>(entity);
                auto &transform = coordinator->getComponent<Transform>(entity);

                particle.position = transform.position + particles.positionOffset;
                particle.speed = { RL::Utils::getRandomValue(-10, 10) / particles.speed,
                                   RL::Utils::getRandomValue(100, 200) / (particles.speed * 10),
                                   RL::Utils::getRandomValue(-10, 10) / particles.speed };

                particle.alpha = particles.lifeTime;
                particle.active = true;
            }

            static void initParticleConeDown(std::shared_ptr<Coordinator> coordinator, Entity entity, Particle &particle) {
                if (!coordinator) {
                    return;
                }

                auto &particles = coordinator->getComponent<Particles>(entity);
                auto &transform = coordinator->getComponent<Transform>(entity);

                particle.position = transform.position + particles.positionOffset;
                particle.speed = {RL::Utils::getRandomValue(-10, 10) / particles.speed,
                                  RL::Utils::getRandomValue(-200, -100) / (particles.speed * 10),
                                  RL::Utils::getRandomValue(-10, 10) / particles.speed};

                particle.alpha = particles.lifeTime;
                particle.active = true;
            }

            static void initParticleConeLeft(std::shared_ptr<Coordinator> coordinator, Entity entity, Particle &particle) {
                if (!coordinator) {
                    return;
                }

                auto &particles = coordinator->getComponent<Particles>(entity);
                auto &transform = coordinator->getComponent<Transform>(entity);

                particle.position = transform.position + particles.positionOffset;
                particle.speed = {RL::Utils::getRandomValue(-200, -100) / (particles.speed * 10),
                                  RL::Utils::getRandomValue(-10, 10) / particles.speed,
                                  RL::Utils::getRandomValue(-10, 10) / particles.speed};

                particle.alpha = particles.lifeTime;
                particle.active = true;
            }

            static void initParticleStarfieldBackground(std::shared_ptr<Coordinator> coordinator, Entity entity, Particle &particle) {
                if (!coordinator) {
                    return;
                }

                auto &particles = coordinator->getComponent<Particles>(entity);
                auto &transform = coordinator->getComponent<Transform>(entity);

                particle.position = transform.position + particles.positionOffset;
                particle.speed = {RL::Utils::getRandomValue(-200, -100) / (particles.speed * 10),
                                  RL::Utils::getRandomValue(-10, 10) / particles.speed,
                                  RL::Utils::getRandomValue(-20, 0) / particles.speed};
                auto rdmValue = RL::Utils::getRandomValue(0, 100);
                if (rdmValue < 50) {
                    particle.id = rdmValue % 4;
                    particle.speed = {RL::Utils::getRandomValue(25, 35) / particles.speed,
                                      RL::Utils::getRandomValue(-10, 10) / particles.speed,
                                      RL::Utils::getRandomValue(-20, 0) / particles.speed};
                }
                if (particle.speed._x == 0)
                    particle.speed._x = .1;
                if (particle.speed._y == 0)
                    particle.speed._y = .1;
                if (particle.speed._z == 0)
                    particle.speed._z = .1;
                particle.alpha = particles.lifeTime;
                particle.active = true;
            }

            static void initParticleConeRight(std::shared_ptr<Coordinator> coordinator, Entity entity, Particle &particle) {
                if (!coordinator) {
                    return;
                }

                auto &particles = coordinator->getComponent<Particles>(entity);
                auto &transform = coordinator->getComponent<Transform>(entity);

                particle.position = transform.position + particles.positionOffset;
                particle.speed = { RL::Utils::getRandomValue(100, 200) / (particles.speed * 10),
                                   RL::Utils::getRandomValue(-10, 10) / particles.speed,
                                   RL::Utils::getRandomValue(-10, 10) / particles.speed };
                particle.alpha = particles.lifeTime;
                particle.active = true;
            }

            static void initParticleLineLeft(std::shared_ptr<Coordinator> coordinator, Entity entity, Particle &particle) {
                if (!coordinator) {
                    return;
                }

                auto &particles = coordinator->getComponent<Particles>(entity);
                auto &transform = coordinator->getComponent<Transform>(entity);

                particle.position = transform.position + particles.positionOffset;
                particle.speed = {RL::Utils::getRandomValue(-200, -100) / (particles.speed * 10),
                                  0,
                                  0};
                particle.alpha = particles.lifeTime;
                particle.active = true;
            }

            static void initParticleLineRight(std::shared_ptr<Coordinator> coordinator, Entity entity, Particle &particle) {
                if (!coordinator) {
                    return;
                }

                auto &particles = coordinator->getComponent<Particles>(entity);
                auto &transform = coordinator->getComponent<Transform>(entity);

                particle.position = transform.position + particles.positionOffset;
                particle.speed = {RL::Utils::getRandomValue(200, 100) / (particles.speed * 10),
                                  0,
                                  0};
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
                        particles.initParticle(coordinatorPtr, entity, particle);
                        if (++count >= particles.spawnRate)
                            break;
                    }
                }
            }

            static void drawParticlesDefault(std::shared_ptr<Coordinator> coordinator, Entity entity ,std::shared_ptr<RL::ICamera> camera, std::shared_ptr<RL::IShader> shader) {
                RL::ZMode mode;

                shader->beginMode();
                mode.beginBlend(BLEND_ADDITIVE);
                auto &particles = coordinator->getComponent<Particles>(entity);
                auto &transform = coordinator->getComponent<Transform>(entity);

                for (auto &particle : particles.particles) {
                    if (particle.active) {
                        if (particles.texture.size() > 0)
                            camera->drawBillboard(*particles.texture[0]->getTexture(), particle.position, transform.scale * particles.scaleOffset, RL::Utils::fade(WHITE, particle.alpha));
                    }
                }
                mode.endBlend();
                shader->endMode();
            }
            static void drawParticlesStarfieldBackground(std::shared_ptr<Coordinator> coordinator, Entity entity ,std::shared_ptr<RL::ICamera> camera, std::shared_ptr<RL::IShader> shader) {

                auto &particles = coordinator->getComponent<Particles>(entity);
                auto &transform = coordinator->getComponent<Transform>(entity);

                std::vector<Color> colors = {SKYBLUE, MAGENTA, PINK, SKYBLUE};

                for (auto &particle : particles.particles) {
                    if (particle.active) {
                        if (particles.texture.size() > 1) {
                            if (RL::Utils::getRandomValue(0, 100) < 2) {
                                if (particle.id != 0) {
                                    camera->drawBillboard(*particles.texture[0]->getTexture(), particle.position, transform.scale * (particles.scaleOffset) * 4, colors[particle.id]);
                                } else {
                                    camera->drawBillboard(*particles.texture[0]->getTexture(), particle.position, transform.scale * particles.scaleOffset * 4, WHITE);
                                }
                            } else {
                                if (particle.id != 0) {
                                    camera->drawBillboard(*particles.texture[0]->getTexture(), particle.position, transform.scale * (particles.scaleOffset), colors[particle.id]);
                                } else {
                                    camera->drawBillboard(*particles.texture[0]->getTexture(), particle.position, transform.scale * particles.scaleOffset, WHITE);
                                }
                            }
                        }
                    }
                }
            }

            void update(std::shared_ptr<RL::ICamera> _camera, std::shared_ptr<RL::IShader> _shader) {
                auto coordinatorPtr = _coordinator.lock();

                for (auto const &entity: _entities) {
                    auto &particles = coordinatorPtr->getComponent<Particles>(entity);
                    if (particles.spawnTimer.isTimeElapsed() || particles.hasStarted) {
                        updateParticles(entity);
                        emitParticles(entity);
                        particles.hasStarted = true;
                    }
                    particles.drawParticle(coordinatorPtr, entity, _camera, _shader);
                }
            }
    };
}

#endif //RTYPE_PARTICLE_HPP
