/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** Listener.hpp
*/

#ifndef RTYPE_LISTENER_HPP
#define RTYPE_LISTENER_HPP

#include <queue>
#include <iostream>
#include <sstream>
#include "IListener.hpp"
#include "renderer/Sound.hpp"
#include "renderer/Mesh.hpp"
#include <vector>

namespace RT {
    class Listener : public IListener {
        public:
            Listener(std::shared_ptr<ECS::Coordinator> &coordinator, std::shared_ptr<std::set<Entity>> entities, std::shared_ptr<RL::ICamera> cam) : _coordinator(coordinator), _entities(entities), _cam(cam) {
                {
                    _playerModel = std::make_shared<RL::ZModel>(
                            "./client/resources/models/ship.glb");
                    Matrix matr = MatrixIdentity();
                    matr = MatrixMultiply(matr, MatrixRotateY(90 * DEG2RAD));
                    matr = MatrixMultiply(matr, MatrixRotateZ(90 * DEG2RAD));
                    _playerModel->_model->transform = matr;
                }
                {
                    _tileBMmodel = std::make_shared<RL::ZModel>("./client/resources/models/cube.glb");
                    Matrix matr = MatrixIdentity();
                    matr = MatrixMultiply(matr, MatrixTranslate(-20, 5 , 0));
                    _tileBMmodel->_model->transform = matr;
                }
                {
                    _tileModel = std::make_shared<RL::ZModel>("./client/resources/models/cube.glb");
                    Matrix matr = MatrixIdentity();
                    matr = MatrixMultiply(matr, MatrixTranslate(-20, 5 , 0));
                    _tileModel->_model->transform = matr;
                }
                {
                    _modelEnemy = std::make_shared<RL::ZModel>("./client/resources/models/spaceship2.glb");
                    Matrix matr = MatrixIdentity();
                    matr = MatrixMultiply(matr, MatrixRotateY(-180 * DEG2RAD));
//                    matr = MatrixMultiply(matr, MatrixTranslate(0, -2 , 0));
                    _modelEnemy->_model->transform = matr;
////                    _textureEnemy = std::make_shared<RL::ZTexture>(
//                    "./client/resources/images/duck_text.png");
                }
                {
                    _modelShot = std::make_shared<RL::ZModel>("./client/resources/models/boom.glb");
                }
                {
                    _modelEnemyShot = std::make_shared<RL::ZModel>("./client/resources/models/boom.glb");
                    Matrix matr = MatrixIdentity();
                    matr = MatrixMultiply(matr, MatrixRotateY(180 * DEG2RAD));
                    _modelEnemyShot->_model->transform = matr;
                }
                {
                    _particleTexture = std::vector<std::shared_ptr<RL::ZTexture>>();
                    _particleTexture.push_back(std::make_shared<RL::ZTexture>("./client/resources/images/particle.png"));
                }
                {
                    _particleBlueTexture = std::vector<std::shared_ptr<RL::ZTexture>>();
                    _particleBlueTexture.push_back(std::make_shared<RL::ZTexture>("./client/resources/images/particleBlue.png"));
                }
                {
                    _starTexture = std::vector<std::shared_ptr<RL::ZTexture>>();
                    _starTexture.push_back(std::make_shared<RL::ZTexture>("./client/resources/images/star.png"));
                    _starTexture.push_back(std::make_shared<RL::ZTexture>("./client/resources/images/planet.png"));
                }
                {
                    _explosionTexture = std::vector<std::shared_ptr<RL::ZTexture>>();
                    for (int i = 1; i <= 9; i++)
                        _explosionTexture.push_back(std::make_shared<RL::ZTexture>("./client/resources/images/explosion " + std::to_string(i) + ".png"));
                }
                {
                    _lightShader = std::make_shared<RL::ZShader>("./client/resources/shaders/lighting.vs", "./client/resources/shaders/lighting.fs");
                    _lightShader->getShader()->locs[SHADER_LOC_VECTOR_VIEW] = _lightShader->getLocation("viewPos");
                    float ambient[4] = { 0.1f, 0.1f, 0.1f, 1.0f };
                    _lightShader->setValue(_lightShader->getLocation("ambient"), &ambient, SHADER_UNIFORM_VEC4);
                }
                {
                    _shaderParticles = std::make_shared<RL::ZShader>("./client/resources/shaders/particle.vs", "./client/resources/shaders/particle.fs");
                    int glowIntensityLoc = _shaderParticles->getLocation("glowIntensity");
                    float glowIntensity = 3.0f;
                    _shaderParticles->setValue(glowIntensityLoc, &glowIntensity, SHADER_UNIFORM_FLOAT);
                }
                {
                    RL::ZMesh mesh = RL::ZMesh();
                    mesh.genSphere(1, 32, 32);
                    mesh.setCanUnload(false);
                    _sphereModel = std::make_shared<RL::ZModel>(mesh.getMesh());
                }
            };
            ~Listener() = default;
            void onEvent() {
                while (!_queue.empty()) {
                    std::string front = _queue.front();
                    _queue.pop();

                    std::stringstream ss(front);
                    std::string id;
                    ss >> id;
                    std::string token;
                    if (_serverToClient.find(std::stoi(id)) == _serverToClient.end()) {
                        Entity entity = _coordinator->createEntity();
                        _entities->insert(_entities->end(), entity);
                        _serverToClient[std::stoi(id)] = entity;

                        while (ss >> token) {
                            if (token == "TRANSFORM") {
                                float x, y, z, rx, ry, rz, ra, scale;
                                ss >> x >> y >> z >> rx >> ry >> rz >> ra >> scale;
                                _coordinator->addComponent(
                                    *_entities->rbegin(),
                                    ECS::Transform{
                                        {x, y, z},
                                        {rx, ry, rz, ra},
                                        scale
                                    }
                                );
                            } else if (token == "PLAYER") {
                                _coordinator->addComponent(
                                    *_entities->rbegin(),
                                    ECS::Model{
                                        .model = _playerModel,
                                    }
                                );
                                _coordinator->addComponent(
                                        *_entities->rbegin(),
                                        ECS::ShaderComponent{
                                                .shader = _lightShader,
                                        }
                                );
                                _coordinator->addComponent(
                                    *_entities->rbegin(),
                                    ECS::Player{
                                        .key_up = KEY_W,
                                        .key_down = KEY_S,
                                        .key_left = KEY_A,
                                        .key_right = KEY_D,
                                        .key_shoot = KEY_SPACE,
                                        .key_validate = KEY_ENTER,
                                        .key_cancel = KEY_ESCAPE,
                                        .key_settings = KEY_F1,
                                    }
                                );
                                _coordinator->addComponent(
                                        *_entities->rbegin(),
                                        ECS::Particles{
                                                .particles = std::vector<ECS::Particle>(50000),
                                                .texture = _particleBlueTexture,
                                                .speed = .5f,
                                                .scaleOffset = .1f,
                                                .positionOffset = {-5.5, 2.5, 0},
                                                .lifeTime = 20,
                                                .spawnRate = 50,
                                                .surviveChance = 0,
                                                .initParticle = ECS::ParticleSystem::initParticleField,
                                                .drawParticle = ECS::ParticleSystem::drawParticleField,
                                                .shader = _shaderParticles
                                        }
                                );
                            } else if (token == "PLAYER_NY") {
                                static int i = 0;
                                std::vector<Color> colors = {RED, GREEN, YELLOW, PURPLE, ORANGE, PINK};
                                _coordinator->addComponent(
                                    *_entities->rbegin(),
                                    ECS::Model{
                                        .model = _playerModel,
                                        .color = colors[i++ % colors.size()]
                                    }
                                );
                                _coordinator->addComponent(
                                        *_entities->rbegin(),
                                        ECS::ShaderComponent{
                                                .shader = _lightShader,
                                        }
                                );
                            } else if (token == "TILE_BREAKABLE") {
                                _coordinator->addComponent(
                                    *_entities->rbegin(),
                                    ECS::Model{
                                        .model = _tileBMmodel,
                                        .color = RED
                                    }
                                );
                                _coordinator->addComponent(
                                        *_entities->rbegin(),
                                        ECS::ShaderComponent{
                                                .shader = _lightShader,
                                        }
                                );
                            } else if (token == "TILE") {
                                _coordinator->addComponent(
                                    *_entities->rbegin(),
                                    ECS::Model{
                                        .model = _tileModel,
                                    }
                                );
                                _coordinator->addComponent(
                                        *_entities->rbegin(),
                                        ECS::ShaderComponent{
                                                .shader = _lightShader,
                                        }
                                );
                            } else if (token == "ENEMY") {
                                _coordinator->addComponent(
                                        *_entities->rbegin(),
                                        ECS::Model{
                                            .model = _modelEnemy,
//                                            .texture = _textureEnemy
                                        }
                                );
                                _coordinator->addComponent(
                                        *_entities->rbegin(),
                                        ECS::ShaderComponent{
                                                .shader = _lightShader,
                                        }
                                );
                            } else if (token == "BASIC_SHOT") {
                                std::shared_ptr<RL::ZSound> sd = std::make_shared<RL::ZSound>("./client/resources/sounds/pew.mp3");
                                sd->setSoundVolume(0.5f);
                                _coordinator->addComponent(
                                        *_entities->rbegin(),
                                        ECS::Model{
                                                .model = _modelShot
                                        }
                                );
                                _coordinator->addComponent(
                                        *_entities->rbegin(),
                                        ECS::ShaderComponent{
                                                .shader = _lightShader,
                                        }
                                );
                                _coordinator->addComponent(
                                        *_entities->rbegin(),
                                        ECS::Particles{
                                                .particles = std::vector<ECS::Particle>(500),
                                                .texture = _particleTexture,
                                                .speed = 75.0f,
                                                .scaleOffset = 3.0f,
                                                .positionOffset = {-0.5, 0, 0},
                                                .lifeTime = 2,
                                                .spawnRate = 35,
                                                .surviveChance = 5,
                                                .initParticle = ECS::ParticleSystem::initParticleConeLeft,
                                                .drawParticle = ECS::ParticleSystem::drawParticlesDefault,
                                                .shader = _shaderParticles
                                        }
                                );
                                _coordinator->addComponent(
                                    *_entities->rbegin(),
                                    ECS::Sound{
                                        .sound = sd,
                                    }
                                );
                            } else if (token == "SIN_SHOT") {
                                std::shared_ptr<RL::ZSound> sd = std::make_shared<RL::ZSound>("./client/resources/sounds/pew.mp3");
                                sd->setSoundVolume(0.5f);
                                _coordinator->addComponent(
                                    *_entities->rbegin(),
                                    ECS::Particles{
                                            .particles = std::vector<ECS::Particle>(500),
                                            .texture = _particleTexture,
                                            .speed = 500.0f,
                                            .scaleOffset = 3.0f,
                                            .positionOffset = {-0.5, 0, 0},
                                            .lifeTime = 10,
                                            .spawnRate = 2,
                                            .surviveChance = 0,
                                            .initParticle = ECS::ParticleSystem::initParticleLineLeft,
                                            .drawParticle = ECS::ParticleSystem::drawParticlesDefault,
                                            .shader = _shaderParticles
                                    }
                                );
                                _coordinator->addComponent(
                                    *_entities->rbegin(),
                                    ECS::Sound{
                                        .sound = sd,
                                    }
                                );
                            } else if (token == "BASIC_ENEMY_SHOT") {
                                std::shared_ptr<RL::ZSound> sd = std::make_shared<RL::ZSound>("./client/resources/sounds/pew.mp3");
                                sd->setSoundVolume(0.5f);
                                _coordinator->addComponent(
                                    *_entities->rbegin(),
                                    ECS::Model{
                                        .model = _modelEnemyShot,
                                    }
                                );
                                _coordinator->addComponent(
                                        *_entities->rbegin(),
                                        ECS::ShaderComponent{
                                                .shader = _lightShader,
                                        }
                                );
                                _coordinator->addComponent(
                                    *_entities->rbegin(),
                                    ECS::Particles{
                                        .particles = std::vector<ECS::Particle>(500),
                                        .texture = _particleTexture,
                                        .speed = 75.0f,
                                        .scaleOffset = 3.0f,
                                        .positionOffset = {0.5, 0, 0},
                                        .lifeTime = 2,
                                        .spawnRate = 35,
                                        .surviveChance = 5,
                                        .initParticle = ECS::ParticleSystem::initParticleConeRight,
                                        .drawParticle = ECS::ParticleSystem::drawParticlesDefault,
                                        .shader = _shaderParticles
                                    }
                                );
                                _coordinator->addComponent(
                                    *_entities->rbegin(),
                                    ECS::Sound{
                                        .sound = sd,
                                    }
                                );
                            } else if (token == "CAMERA") {
                                _coordinator->addComponent(
                                    *_entities->rbegin(),
                                    ECS::Cam{
                                        .camera = _cam
                                    }
                                );
                                _coordinator->addComponent(
                                    *_entities->rbegin(),
                                    ECS::Particles{
                                        .particles = std::vector<ECS::Particle>(1000),
                                        .texture = _starTexture,
                                        .speed = 60.0f,
                                        .scaleOffset = 1.2f,
                                        .positionOffset = {95, 0, -120},
                                        .lifeTime = 550,
                                        .spawnRate = 1,
                                        .surviveChance = 0,
                                        .initParticle = ECS::ParticleSystem::initParticleStarfieldBackground,
                                        .drawParticle = ECS::ParticleSystem::drawParticlesStarfieldBackground,
                                        .shader = _shaderParticles
                                    }
                                );


                                const int nbLights = 4;

                                float _x[nbLights] = { -20.0f, -20.0f, 40.0f, 40.0f };
                                float _y[nbLights] = { -10.0f, 35.0f, -10.0f, 35.0f };
                                float _z[nbLights] = { 5, 5, 5, 5 };
                                Color _colors[nbLights] = { PURPLE, BLUE, RED, PINK };

                                for (int i = 0 ; i < nbLights ; i++) {
                                    float x, y, z, rx, ry, rz, ra, scale;
                                    x = y = z = rx = ry = rz = ra = scale = 0;
                                    Color color = _colors[i];

                                    x = _x[i];
                                    y = _y[i];
                                    z = _z[i];

                                    _entities->insert(_entities->end(), _coordinator->createEntity());
                                    _coordinator->addComponent(
                                            *_entities->rbegin(),
                                            ECS::LightComponent{
                                                    .light = CreateLight(LIGHT_POINT, (Vector3){ x, y, z }, {x, y, z - 1}, color, *_lightShader->getShader())
                                            }
                                    );

                                    _coordinator->addComponent(
                                            *_entities->rbegin(),
                                            ECS::Transform{
                                                    {x, y, z},
                                                    {rx, ry, rz, ra},
                                                    1
                                            }
                                    );
                                    _coordinator->addComponent(
                                            *_entities->rbegin(),
                                            ECS::Traveling{
                                                    {0.0175, 0, 0},
                                            }
                                    );
                                    _coordinator->addComponent(
                                        *_entities->rbegin(),
                                        ECS::ShaderComponent{
                                            .shader = _lightShader
                                        }
                                    );
                                    _coordinator->addComponent(
                                        *_entities->rbegin(),
                                        ECS::Model{
                                            .model = _sphereModel,
                                            .color = color
                                        }
                                    );
                                }


                            } else {
                                std::cout << "Unknown token : " << token << std::endl;
                            }
                        }
                    } else {
                        while (ss >> token) {
                            if (token == "TRANSFORM") {
                                auto &transform = _coordinator->getComponent<ECS::Transform>(
                                        _serverToClient[std::stoi(id)]);
                                float x, y, z, rx, ry, rz, ra, scale;
                                ss >> x >> y >> z >> rx >> ry >> rz >> ra >> scale;
                                transform = ECS::Transform{
                                        {x, y, z},
                                        {rx, ry, rz, ra},
                                        scale
                                };
                            } else if (token == "DESTROY") {
                                auto transform = _coordinator->getComponent<ECS::Transform>(_serverToClient[std::stoi(id)]);
                                _coordinator->destroyEntity(_serverToClient[std::stoi(id)]);

                                _entities->insert(_entities->end(), _coordinator->createEntity());
                                transform.scale = 1;
                                _coordinator->addComponent(
                                    *_entities->rbegin(),
                                    transform
                                );
                                _coordinator->addComponent(
                                    *_entities->rbegin(),
                                    ECS::Particles{
                                        .particles = std::vector<ECS::Particle>(10),
                                        .texture = _explosionTexture,
                                        .speed = 400.0f,
                                        .scaleOffset = .3f,
                                        .positionOffset = {0, 0, 0},
                                        .lifeTime = 6000,
                                        .spawnRate = 1,
                                        .surviveChance = 30,
                                        .initParticle = ECS::ParticleSystem::initParticleExplosion,
                                        .drawParticle = ECS::ParticleSystem::drawParticlesExplosion,
                                        .shader = _shaderParticles
                                    }
                                );
                                _coordinator->addComponent(
                                    *_entities->rbegin(),
                                    ECS::SelfDestruct{
                                        .timer = tls::Clock(.4)
                                    }
                                );
                            } else {
//                                std::cout << "[UPDATE] Unknown token : " << token << std::endl;
                            }
                        }
                    }
                }
            }

            void addEvent(const std::string &event) {
                _queue.push(event);
            }

            std::queue<std::string> _queue;
            std::shared_ptr<ECS::Coordinator> _coordinator;
            std::shared_ptr<std::set<Entity>> _entities;
            std::unordered_map<Entity, Entity> _serverToClient;
            std::shared_ptr<RL::ICamera> _cam;
            std::shared_ptr<RL::ZModel> _playerModel;
            std::shared_ptr<RL::ZModel> _tileBMmodel;
            std::shared_ptr<RL::ZModel> _tileModel;
            std::shared_ptr<RL::ZModel> _modelEnemy;
            std::shared_ptr<RL::ZModel> _modelShot;
            std::shared_ptr<RL::ZModel> _modelEnemyShot;
            std::shared_ptr<RL::ZTexture> _textureEnemy;
            std::vector<std::shared_ptr<RL::ZTexture>> _particleTexture;
            std::vector<std::shared_ptr<RL::ZTexture>> _particleBlueTexture;
            std::vector<std::shared_ptr<RL::ZTexture>> _starTexture;
            std::vector<std::shared_ptr<RL::ZTexture>> _explosionTexture;
            std::shared_ptr<RL::IShader> _lightShader;
            std::shared_ptr<RL::IShader> _shaderParticles;
            std::shared_ptr<RL::ZModel> _sphereModel;
    };
}

#endif //RTYPE_LISTENER_HPP
