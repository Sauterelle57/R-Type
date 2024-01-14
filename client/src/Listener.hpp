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
#include <unordered_map>
#include "IListener.hpp"
#include "renderer/Sound.hpp"
#include "Protocol.hpp"
#include "UdpClient.hpp"
#include "renderer/Mesh.hpp"
#include "renderer/Music.hpp"

namespace RT {
    class Listener : public IListener {
        public:
            Listener(std::shared_ptr<ECS::Coordinator> &coordinator, std::shared_ptr<std::set<Entity>> entities, std::shared_ptr<RL::ICamera> cam, std::shared_ptr<rt::UdpClient> udpClient) : _coordinator(coordinator), _entities(entities), _cam(cam), _udpClient(udpClient) {
                {
                    _playerModel = std::vector<std::shared_ptr<RL::ZModel>>();
                    _playerModel.push_back(std::make_shared<RL::ZModel>("./client/resources/models/player1.glb"));
                    _playerModel.push_back(std::make_shared<RL::ZModel>("./client/resources/models/player2.glb"));
                    _playerModel.push_back(std::make_shared<RL::ZModel>("./client/resources/models/player3.glb"));
                    _playerModel.push_back(std::make_shared<RL::ZModel>("./client/resources/models/player4.glb"));
                    _playerModel.push_back(std::make_shared<RL::ZModel>("./client/resources/models/player5.glb"));
                    Matrix matr = MatrixIdentity();
                    matr = MatrixMultiply(matr, MatrixRotateY(90 * DEG2RAD));
                    matr = MatrixMultiply(matr, MatrixRotateZ(-90 * DEG2RAD));
                    for (int i = 0 ; i < _playerModel.size() ; i++)
                        _playerModel[i]->_model->transform = matr;
                }
                {
                    _tileBMmodel = std::make_shared<RL::ZModel>("./client/resources/models/obstacle.glb");
                }
                {
                    _tileModel = std::make_shared<RL::ZModel>("./client/resources/models/obstacle.glb");
                }
                {
                    _modelEnemy = std::make_shared<RL::ZModel>("./client/resources/models/spaceship2.glb");
                    Matrix matr = MatrixIdentity();
                    matr = MatrixMultiply(matr, MatrixRotateX(180 * DEG2RAD));
                    matr = MatrixMultiply(matr, MatrixRotateZ(180 * DEG2RAD));
                    _modelEnemy->_model->transform = matr;
                }
                {
                    _modelEnemy2 = std::make_shared<RL::ZModel>("./client/resources/models/mob3.glb");
                    Matrix matr = MatrixIdentity();
                    matr = MatrixMultiply(matr, MatrixRotateZ(-20 * DEG2RAD));
                    matr = MatrixMultiply(matr, MatrixRotateY(155 * DEG2RAD));
                    _modelEnemy2->_model->transform = matr;
                }
                {
                    _modelFloorEnemy = std::make_shared<RL::ZModel>("./client/resources/models/mob5.glb");
                }
                {
                    _modelFloorEnemyAnimation = std::make_shared<RL::ZModelAnimation>("./client/resources/models/mob5.glb", &_modelFloorEnemyAnimationCount);
                }
                {
                    _modelBoss = std::make_shared<RL::ZModel>("./client/resources/models/boss2.glb");
                }
                {
                    _modelChild = std::make_shared<RL::ZModel>("./client/resources/models/boss_body2.glb");
                }
                {
                    _modelShot = std::make_shared<RL::ZModel>("./client/resources/models/missile.glb");
                    Matrix rotationMatrix = MatrixRotateX(-90 * DEG2RAD);
                    Matrix rotation2Matrix = MatrixRotateZ(-90 * DEG2RAD);
                    Matrix finalTransformation = MatrixMultiply(rotationMatrix, rotation2Matrix);
                    _modelShot->_model->transform = finalTransformation;
                }
                {
                    _modelEnemyShot = std::make_shared<RL::ZModel>("./client/resources/models/boom.glb");
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

            
            void onEvent(bool &shouldClose, bool &debug) {
                while (!_queue.empty()) {
                    std::string front = _queue.front();
                    _queue.pop();

                    rt::ProtocolController pc;

                    auto receivedData = pc.deserialize(front);

                    if (receivedData.sender == rt::SENDER_TYPE::SERVER && receivedData.protocol == rt::PROTOCOL_TYPE::ENTITIES) {

                        for (auto &x : receivedData.server.entities) {
                            std::uint32_t ecsID = x.ECSEntity;
                            tls::Vec3 position = x.position;
                            tls::Vec4 rotation = x.rotation;
                            tls::BoundingBox bounds = x.bounds;
                            tls::Vec3 scale = x.scale;
                            int type = x.entityType;
                            _interpreterCreateEntity(ecsID, x.signature, position, rotation, scale, type, bounds, shouldClose, debug);
                        }

                        for (auto &ecsID : receivedData.server.destroyedEntities) {
                            if (!_deletedIDAlreadyRemoved.contains(ecsID.second)) {
                                auto transform = _coordinator->getComponent<ECS::Transform>(_serverToClient[ecsID.first]);
                                _coordinator->destroyEntity(_serverToClient[ecsID.first]);
                                _deletedIDAlreadyRemoved.insert(ecsID.second);



                                _entities->insert(_entities->end(), _coordinator->createEntity());
                                transform.scale = {1, 1, 1};
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
                                                .scaleOffset = {.3f, .3f, .3f},
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
                                        ECS::Velocity{}
                                );
                                _coordinator->addComponent(
                                        *_entities->rbegin(),
                                        ECS::SelfDestruct{
                                                .timer = tls::Clock(.4)
                                        }
                                );
                            }
                        }

                        pc.actionId(receivedData.packetId);
                        auto toSend = pc.getProtocol();
                        _udpClient->sendStruct(toSend);
                    }
                }
            }

            void addEvent(const std::string &event) {
                _queue.push(event);
            }


            void _interpreterCreateEntity(std::uint32_t ecsID, std::bitset<15> signature, tls::Vec3 position, tls::Vec4 rotation, tls::Vec3 scale, int type, tls::BoundingBox bounds, bool &shouldCLose, bool &debug) {
                if (_serverToClient.find(ecsID) == _serverToClient.end()) {
                    ECS::Entity entity = _coordinator->createEntity();

                    _entities->insert(_entities->end(), entity);
                    _serverToClient[ecsID] = entity;

                    _coordinator->addComponent(
                        *_entities->rbegin(),
                        ECS::Transform{
                                {position._x, position._y, position._z},
                                {rotation._x, rotation._y, rotation._z, rotation._a},
                                {scale._x, scale._y, scale._z}
                        }
                    );
                    // DBD
                    _coordinator->addComponent(
                        *_entities->rbegin(),
                        ECS::Bdb{
                            .bounds = {
                                .min = {static_cast<float>(bounds.min._x), static_cast<float>(bounds.min._y), static_cast<float>(bounds.min._z)},
                                .max = {static_cast<float>(bounds.max._x), static_cast<float>(bounds.max._y), static_cast<float>(bounds.max._z)}
                            }
                        }
                    );
//                    std::cout << "Create entity with [" << ecsID << "] and type : " << type << std::endl;
                    if (type == rt::ENTITY_TYPE::PLAYER) {
                        static int i = 0;
                        std::cout << "Create player ! with [" << ecsID << "]" << std::endl;
                        _coordinator->addComponent(
                            *_entities->rbegin(),
                            ECS::Model{
                                .model = _playerModel[i++ % _playerModel.size()],
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
                                .particles = std::vector<ECS::Particle>(5000),
                                .texture = _particleBlueTexture,
                                .speed = .1f,
                                .scaleOffset = {.1f, .1f, .1f},
                                .positionOffset = {0, 0, 0},
                                .lifeTime = 50,
                                .spawnRate = 60,
                                .surviveChance = 0,
                                .initParticle = ECS::ParticleSystem::initParticleField,
                                .drawParticle = ECS::ParticleSystem::drawParticleField,
                                .shader = _shaderParticles
                            }
                        );
                        _coordinator->addComponent(
                                *_entities->rbegin(),
                                ECS::Velocity{}
                        );
                    } else if (type == rt::ENTITY_TYPE::PLAYER_NY) {
                        static int i = 1;
                        // std::vector<Color> colors = {RED, GREEN, YELLOW, PURPLE, ORANGE, PINK};
                        _coordinator->addComponent(
                            *_entities->rbegin(),
                            ECS::Model{
                                .model = _playerModel[i % _playerModel.size()],
                                // .color = colors[i % colors.size()]
                            }
                        );
                        _coordinator->addComponent(
                                *_entities->rbegin(),
                                ECS::ShaderComponent{
                                        .shader = _lightShader,
                                }
                        );
                    } else if (type == rt::ENTITY_TYPE::CAMERA) {
                        _coordinator->addComponent(
                            *_entities->rbegin(),
                            ECS::Cam{
                                .camera = _cam
                            }
                        );
                        _coordinator->addComponent(
                            *_entities->rbegin(),
                            ECS::Music {
                                .music = std::make_shared<RL::ZMusic>("./client/resources/sounds/stage1.mp3")
                            }
                        );
                        _coordinator->addComponent(
                                *_entities->rbegin(),
                                ECS::Particles{
                                        .particles = std::vector<ECS::Particle>(1000),
                                        .texture = _starTexture,
                                        .speed = 60.0f,
                                        .scaleOffset = {1.2f, 1.2f, 1.2f},
                                        .positionOffset = {95, 0, -120},
                                        .lifeTime = 550,
                                        .spawnRate = 1,
                                        .surviveChance = 0,
                                        .initParticle = ECS::ParticleSystem::initParticleStarfieldBackground,
                                        .drawParticle = ECS::ParticleSystem::drawParticlesStarfieldBackground,
                                        .shader = _shaderParticles
                                }
                        );
                        _coordinator->addComponent(
                                *_entities->rbegin(),
                                ECS::Velocity{}
                        );

                        std::vector<ECS::SlideBar> sliderBars;
                        std::vector<ECS::CheckBox> checkBoxes;
                        std::vector<ECS::Button> buttons;

                        sliderBars.push_back(
                            ECS::SlideBar{
                                {1920 / 2 - 200, 1080 / 2 - 200, 400, 20},
                                "Master volume",
                                "",
                                50,
                                0,
                                100,
                                [](float value) {
                                    RL::Utils::setMasterVolume(value / 100);
                                }
                            }
                        );

                        buttons.push_back(
                            ECS::Button{
                                {1920 / 2 - 50, 1080 / 2 + 300, 100, 25},
                                "Disconnect",
                                [&]() {
                                    shouldCLose = true;
                                }
                            }
                        );

                        checkBoxes.push_back(
                            ECS::CheckBox{
                                {1920 / 2 - 200, 1080 / 2 -100, 20, 20},
                                "Debeug mode",
                                false,
                                [&](bool value) {
                                    debug = value;
                                }
                            }
                        );

                        _coordinator->addComponent(
                            *_entities->rbegin(),
                            ECS::Modal {
                                .width = 1920 - 1920 / 4,
                                .height = 1080 - 1080 / 4,
                                .title = "Options",
                                .titleWidth = 20,
                                .color = {0, 0, 0, 250},
                                .openClose = [](bool &active) {
                                    if (RL::Utils::isKeyPressed(KEY_ESCAPE)) {
                                        active = !active;
                                    }
                                },
                                .slideBars = sliderBars,
                                .checkBoxes = checkBoxes,
                                .buttons = buttons
                            }
                        );

                        const int nbLights = 4;

                        float _x[nbLights] = { -20.0f, -20.0f, 40.0f, 40.0f };
                        float _y[nbLights] = { -10.0f, 35.0f, -10.0f, 35.0f };
                        float _z[nbLights] = { 5, 5, 5, 5 };
                        Color _colors[nbLights] = { PURPLE, BLUE, RED, PINK };

                        for (int i = 0 ; i < nbLights ; i++) {
                            float x, y, z, rx, ry, rz, ra, sx, sy, sz;
                            x = y = z = rx = ry = rz = ra = 0;
                            sx = sy = sz = 1;
                            Color color = _colors[i];

                            x = _x[i];
                            y = _y[i];
                            z = _z[i];

                            _entities->insert(_entities->end(), _coordinator->createEntity());
                            _coordinator->addComponent(
                                    *_entities->rbegin(),
                                    ECS::LightComponent{
                                            .light = CreateLight(LIGHT_POINT, { x, y, z }, {x, y, z - 1}, color, *_lightShader->getShader())
                                    }
                            );

                            _coordinator->addComponent(
                                    *_entities->rbegin(),
                                    ECS::Transform{
                                            {x, y, z},
                                            {rx, ry, rz, ra},
                                            {sx, sy, sz}
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
                        }
                    } else if (type == rt::ENTITY_TYPE::TILE_BREAKABLE) {
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
                    } else if (type == rt::ENTITY_TYPE::TILE) {
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
                    } else if (type == rt::ENTITY_TYPE::ENEMY) {
                        _coordinator->addComponent(
                            *_entities->rbegin(),
                            ECS::Model{
                                .model = _modelEnemy,
                            }
                        );
                        _coordinator->addComponent(
                            *_entities->rbegin(),
                            ECS::ShaderComponent{
                                .shader = _lightShader,
                            }
                        );
                    } else if (type == rt::ENTITY_TYPE::ENEMY2) {
                        _coordinator->addComponent(
                            *_entities->rbegin(),
                            ECS::Model{
                                .model = _modelEnemy2,
                            }
                        );
                        _coordinator->addComponent(
                            *_entities->rbegin(),
                            ECS::ShaderComponent{
                                .shader = _lightShader,
                            }
                        );
                    }  else if (type == rt::ENTITY_TYPE::FLOOR_ENEMY) {
                        _coordinator->addComponent(
                            *_entities->rbegin(),
                            ECS::Model{
                                .model = _modelFloorEnemy,
                            }
                        );
                        _coordinator->addComponent(
                            *_entities->rbegin(),
                            ECS::ShaderComponent{
                                .shader = _lightShader,
                            }
                        );
                    }  else if (type == rt::ENTITY_TYPE::BOSS) {
                        _coordinator->addComponent(
                            *_entities->rbegin(),
                            ECS::Model{
                                .model = _modelBoss,
                            }
                        );
                        _coordinator->addComponent(
                            *_entities->rbegin(),
                            ECS::ShaderComponent{
                                .shader = _lightShader,
                            }
                        );
                    } else if (type == rt::ENTITY_TYPE::CHILD) {
                        _coordinator->addComponent(
                            *_entities->rbegin(),
                            ECS::Model{
                                .model = _modelChild,
                            }
                        );
                        _coordinator->addComponent(
                            *_entities->rbegin(),
                            ECS::ShaderComponent{
                                .shader = _lightShader,
                            }
                        );
                    } else if (type == rt::ENTITY_TYPE::BASIC_SHOT) {
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
                                .scaleOffset = {3, 3, 3},
                                .positionOffset = {-0.5, 0, 0},
                                .lifeTime = 2,
                                .spawnRate = 10,
                                .surviveChance = 5,
                                .initParticle = ECS::ParticleSystem::initParticleConeLeft,
                                .drawParticle = ECS::ParticleSystem::drawParticlesDefault,
                                .shader = _shaderParticles
                            }
                        );
                        _coordinator->addComponent(
                            *_entities->rbegin(),
                            ECS::Velocity{}
                        );
                        _coordinator->addComponent(
                            *_entities->rbegin(),
                            ECS::Sound{
                                .sound = sd,
                            }
                        );
                    } else if (type == rt::ENTITY_TYPE::SIN_SHOT) {
                        std::shared_ptr<RL::ZSound> sd = std::make_shared<RL::ZSound>("./client/resources/sounds/pew.mp3");
                        sd->setSoundVolume(0.5f);
                        _coordinator->addComponent(
                            *_entities->rbegin(),
                            ECS::Particles{
                                .particles = std::vector<ECS::Particle>(500),
                                .texture = _particleTexture,
                                .speed = 500.0f,
                                .scaleOffset = {3.f, 3.f, 3.f},
                                .positionOffset = {0, 0, 0},
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
                            ECS::Velocity{}
                        );
                        _coordinator->addComponent(
                            *_entities->rbegin(),
                            ECS::Sound{
                                .sound = sd,
                            }
                        );
                    } else if (type == rt::BASIC_ENEMY_SHOT) {
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
                                .scaleOffset = {3.f, 3.f, 3.f},
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
                            ECS::Velocity{}
                        );
                        _coordinator->addComponent(
                            *_entities->rbegin(),
                            ECS::Sound{
                                .sound = sd,
                            }
                        );
                    }
                } else {
                    auto &transform = _coordinator->getComponent<ECS::Transform>(_serverToClient[ecsID]);

                    transform.position._x = (signature[0] ? position._x : transform.position._x);
                    transform.position._y = (signature[1] ? position._y : transform.position._y);
                    transform.position._z = (signature[2] ? position._z : transform.position._z);

                    transform.rotation._x = (signature[3] ? rotation._x : transform.rotation._x);
                    transform.rotation._y = (signature[4] ? rotation._y : transform.rotation._y);
                    transform.rotation._z = (signature[5] ? rotation._z : transform.rotation._z);
                    transform.rotation._a = (signature[6] ? rotation._a : transform.rotation._a);

                    transform.scale._x = (signature[7] ? scale._x : transform.scale._x);
                    transform.scale._y = (signature[8] ? scale._y : transform.scale._y);
                    transform.scale._z = (signature[9] ? scale._z : transform.scale._z);

                    auto &bdb = _coordinator->getComponent<ECS::Bdb>(
                        _serverToClient[ecsID]);


                    bdb = ECS::Bdb{
                        .bounds = {
                            .min = {static_cast<float>(bounds.min._x), static_cast<float>(bounds.min._y), static_cast<float>(bounds.min._z)},
                            .max = {static_cast<float>(bounds.max._x), static_cast<float>(bounds.max._y), static_cast<float>(bounds.max._z)}
                        }
                    };
                }
            }

            std::shared_ptr<rt::UdpClient> _udpClient;
            std::queue<std::string> _queue;
            std::shared_ptr<ECS::Coordinator> _coordinator;
            std::shared_ptr<std::set<Entity>> _entities;
            std::unordered_map<Entity, Entity> _serverToClient;
            std::shared_ptr<RL::ICamera> _cam;
            std::vector<std::shared_ptr<RL::ZModel>> _playerModel;
            std::shared_ptr<RL::ZModel> _tileBMmodel;
            std::shared_ptr<RL::ZModel> _tileModel;
            std::shared_ptr<RL::ZModel> _modelEnemy;
            std::shared_ptr<RL::ZModel> _modelEnemy2;
            std::shared_ptr<RL::ZModel> _modelFloorEnemy;
            std::shared_ptr<RL::ZModel> _modelBoss;
            std::shared_ptr<RL::ZModel> _modelChild;
            std::shared_ptr<RL::ZModel> _modelShot;
            std::shared_ptr<RL::ZModel> _modelEnemyShot;
            std::shared_ptr<RL::ZTexture> _textureEnemy;
            std::vector<std::shared_ptr<RL::ZTexture>> _particleTexture;
            std::vector<std::shared_ptr<RL::ZTexture>> _particleBlueTexture;
            std::vector<std::shared_ptr<RL::ZTexture>> _starTexture;
            std::vector<std::shared_ptr<RL::ZTexture>> _explosionTexture;
            std::vector<std::shared_ptr<RL::ZTexture>> _playerTexture;
            std::shared_ptr<RL::IShader> _lightShader;
            std::shared_ptr<RL::IShader> _shaderParticles;
            std::shared_ptr<RL::ZModel> _sphereModel;
            std::set<long long> _deletedIDAlreadyRemoved;
            std::shared_ptr<RL::ZModelAnimation> _modelFloorEnemyAnimation;
            int _modelFloorEnemyAnimationCount = 0;
    };
}

#endif //RTYPE_LISTENER_HPP