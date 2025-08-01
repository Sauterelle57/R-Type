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

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

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
                particle.scale._x = transform.scale._x * particles.scaleOffset._x;
                particle.scale._y = transform.scale._y * particles.scaleOffset._y;
                particle.scale._z = transform.scale._z * particles.scaleOffset._z;
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
                particle.scale._x = transform.scale._x * particles.scaleOffset._x;
                particle.scale._y = transform.scale._y * particles.scaleOffset._y;
                particle.scale._z = transform.scale._z * particles.scaleOffset._z;
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

                particle.scale._x = transform.scale._x * particles.scaleOffset._x;
                particle.scale._y = transform.scale._y * particles.scaleOffset._y;
                particle.scale._z = transform.scale._z * particles.scaleOffset._z;
                particle.alpha = particles.lifeTime;
                particle.active = true;
            }

            static void initParticleExplosion(std::shared_ptr<Coordinator> coordinator, Entity entity, Particle &particle) {
                if (!coordinator) {
                    return;
                }

                auto &particles = coordinator->getComponent<Particles>(entity);
                auto &transform = coordinator->getComponent<Transform>(entity);

                particle.position = transform.position + particles.positionOffset;
                particle.scale._x = transform.scale._x * particles.scaleOffset._x;
                particle.scale._y = transform.scale._y * particles.scaleOffset._y;
                particle.scale._z = transform.scale._z * particles.scaleOffset._z;
                float angleRadians = RL::Utils::getRandomValue(0, 360) * (M_PI / 180);

                particle.speed = {
                        cos(angleRadians) * 0.1,
                        sin(angleRadians) * 0.1,
                        0
                };

                particle.id = RL::Utils::getRandomValue(1, 9);
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
                particle.scale._x = transform.scale._x * particles.scaleOffset._x;
                particle.scale._y = transform.scale._y * particles.scaleOffset._y;
                particle.scale._z = transform.scale._z * particles.scaleOffset._z;
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
                particle.scale._x = transform.scale._x * particles.scaleOffset._x;
                particle.scale._y = transform.scale._y * particles.scaleOffset._y;
                particle.scale._z = transform.scale._z * particles.scaleOffset._z;
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
                particle.scale._x = transform.scale._x * particles.scaleOffset._x;
                particle.scale._y = transform.scale._y * particles.scaleOffset._y;
                particle.scale._z = transform.scale._z * particles.scaleOffset._z;
            }

            static void initParticleLineRight(std::shared_ptr<Coordinator> coordinator, Entity entity, Particle &particle) {
                if (!coordinator) {
                    return;
                }

                auto &particles = coordinator->getComponent<Particles>(entity);
                auto &transform = coordinator->getComponent<Transform>(entity);

                particle.position = transform.position + particles.positionOffset;
                particle.speed = {RL::Utils::getRandomValue(200, 100) / (particles.speed * 10), 0, 0};
                particle.alpha = particles.lifeTime;
                particle.active = true;
                particle.scale._x = transform.scale._x * particles.scaleOffset._x;
                particle.scale._y = transform.scale._y * particles.scaleOffset._y;
                particle.scale._z = transform.scale._z * particles.scaleOffset._z;
            }

            static void initParticleField(std::shared_ptr<Coordinator> coordinator, Entity entity, Particle &particle) {
                if (!coordinator) {
                    return;
                }

                auto &particles = coordinator->getComponent<Particles>(entity);
                auto &transform = coordinator->getComponent<Transform>(entity);

                float a = 5.0f;
                float b = 3.0f;
                float c = 2.0f;

                float theta = RL::Utils::getRandomValue(0, 360) * (M_PI / 180);
                float phi = acos(1 - 2 * RL::Utils::getRandomValue(0, 100) / 100.0f);

                particle.position = tls::Vec3{
                        a * sin(phi) * cos(theta),
                        b * sin(phi) * sin(theta),
                        c * cos(phi)
                } + transform.position + particles.positionOffset;

                tls::Vec3 velocityDirection = tls::Vec3{-b * cos(phi) * sin(theta), a * cos(phi) * cos(theta), 0};
                particle.speed = velocityDirection.normalized() * (particles.speed / (a + b + c));

                particle.alpha = particles.lifeTime;
                particle.active = true;
                particle.scale = particles.scaleOffset;
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

            static void drawParticlesDefault(std::shared_ptr<Coordinator> coordinator, Entity entity ,std::shared_ptr<RL::ICamera> camera) {
                RL::ZMode mode;

                auto &particles = coordinator->getComponent<Particles>(entity);

                particles.shader->beginMode();
                mode.beginBlend(BLEND_ADDITIVE);
                auto &transform = coordinator->getComponent<Transform>(entity);

                for (auto &particle : particles.particles) {
                    if (particle.active) {
                        if (particles.texture.size() > 0)
                            camera->drawBillboard(*particles.texture[0]->getTexture(), particle.position, particle.scale._x, RL::Utils::fade(WHITE, particle.alpha));
                    }
                }
                mode.endBlend();
                particles.shader->endMode();
            }

            static void drawParticlesStarfieldBackground(std::shared_ptr<Coordinator> coordinator, Entity entity ,std::shared_ptr<RL::ICamera> camera) {

                auto &particles = coordinator->getComponent<Particles>(entity);
                auto &transform = coordinator->getComponent<Transform>(entity);

                std::vector<Color> colors = {SKYBLUE, MAGENTA, PINK, SKYBLUE};

                for (auto &particle : particles.particles) {
                    if (particle.active) {
                        if (particles.texture.size() > 1) {
                            if (RL::Utils::getRandomValue(0, 100) < 2) {
                                if (particle.id != 0) {
                                    camera->drawBillboard(*particles.texture[0]->getTexture(), particle.position, particle.scale._x, colors[particle.id]);
                                } else {
                                    camera->drawBillboard(*particles.texture[0]->getTexture(), particle.position, particle.scale._x, WHITE);
                                }
                            } else {
                                if (particle.id != 0) {
                                    camera->drawBillboard(*particles.texture[0]->getTexture(), particle.position, particle.scale._x, colors[particle.id]);
                                } else {
                                    camera->drawBillboard(*particles.texture[0]->getTexture(), particle.position, particle.scale._x, WHITE);
                                }
                            }
                        }
                    }
                }
            }

            static void drawParticlesExplosion(std::shared_ptr<Coordinator> coordinator, Entity entity ,std::shared_ptr<RL::ICamera> camera) {
                RL::ZMode mode;
                auto &particles = coordinator->getComponent<Particles>(entity);

                particles.shader->beginMode();
                mode.beginBlend(BLEND_ADDITIVE);
                auto &transform = coordinator->getComponent<Transform>(entity);


                for (auto &particle : particles.particles) {
                    if (particle.active) {
                        if (particles.texture.size() > 8) {
                            if (particle.id > 0) {
                                particle.scale._x += 0.3;
                                particle.scale._y += 0.3;
                                particle.scale._z += 0.3;
                                if (particle.scale._x > 2.5 && particle.scale._y > 2.5 && particle.scale._z > 2.5) {
                                    particle.id *= -1;
                                }
                            } else if (particle.id < 0) {
                                particle.speed -= particle.speed * 0.05;
                                particle.scale._x -= 0.2;
                                particle.scale._y -= 0.2;
                                particle.scale._z -= 0.2;
                            }
                            if (particle.scale._x < 0.1 && particle.scale._y < 0.1 && particle.scale._z < 0.1) {
                                particle.scale = {0.1, 0.1, 0.1};
                            }
                            camera->drawBillboard(*particles.texture[std::abs(particle.id) -1]->getTexture(), particle.position, particle.scale._x,  RL::Utils::fade(WHITE, particle.alpha));
                        }
                    }
                }
                mode.endBlend();
                particles.shader->endMode();
            }

            static void drawParticleField(std::shared_ptr<Coordinator> coordinator, Entity entity, std::shared_ptr<RL::ICamera> camera) {
                if (!coordinator) {
                    return;
                }

                auto &particles = coordinator->getComponent<Particles>(entity);
                auto &velocity = coordinator->getComponent<Velocity>(entity);
                RL::ZMode mode;
                mode.beginBlend(BLEND_ADDITIVE);
                auto &transform = coordinator->getComponent<Transform>(entity);

                float a = 5.0f;
                float b = 3.0f;
                float c = 2.0f;

                for (auto &particle : particles.particles) {
                    if (particle.active) {
                        particle.position += velocity.speed;

                        tls::Vec3 offset = particle.position - (transform.position + particles.positionOffset);
                        float distanceSquared = (offset._x * offset._x) / (a * a) +
                                                (offset._y * offset._y) / (b * b) +
                                                (offset._z * offset._z) / (c * c);
                        if (distanceSquared > 2.0f) {
                            particle.active = false;
                        } else {
                            float distance = sqrt(distanceSquared);
                            float alpha = 2.0f - (distance * 1.5);
                            camera->drawBillboard(*particles.texture[0]->getTexture(), particle.position, particle.scale._x, RL::Utils::fade(WHITE, alpha));
                        }
                    }
                }
                mode.endBlend();
            }

            void update(std::shared_ptr<RL::ICamera> _camera) {
                auto coordinatorPtr = _coordinator.lock();

                for (auto const &entity: _entities) {
                    auto &particles = coordinatorPtr->getComponent<Particles>(entity);
                    if (particles.spawnTimer.isTimeElapsed() || particles.hasStarted) {
                        updateParticles(entity);
                        emitParticles(entity);
                        particles.hasStarted = true;
                    }
                    particles.drawParticle(coordinatorPtr, entity, _camera);
                }
            }
    };
}

#endif //RTYPE_PARTICLE_HPP
