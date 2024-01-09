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

namespace RT {
    class Listener : public IListener {
        public:
            Listener(std::shared_ptr<ECS::Coordinator> &coordinator, std::shared_ptr<std::set<Entity>> entities, std::shared_ptr<RL::ICamera> cam) : _coordinator(coordinator), _entities(entities), _cam(cam) {
                {
                    _starTexture = std::make_shared<RL::ZTexture>("./client/resources/images/star.png");
                }
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
                    _modelEnemy = std::make_shared<RL::ZModel>("./client/resources/models/duck.obj");
                    Matrix matr = MatrixIdentity();
                    matr = MatrixMultiply(matr, MatrixRotateY(-180 * DEG2RAD));
                    matr = MatrixMultiply(matr, MatrixTranslate(0, -20 , 0));
                    _modelEnemy->_model->transform = matr;
                    _textureEnemy = std::make_shared<RL::ZTexture>(
                    "./client/resources/images/duck_text.png");
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
                    _particleTexture = std::make_shared<RL::ZTexture>("./client/resources/images/particle.png");
                }
            };

            ~Listener() = default;
            
            void onEvent() {
                while (!_queue.empty()) {
                    std::string front = _queue.front();
                    _queue.pop();

                    // std::cout << "new message arrived !" << std::endl;
                    // std::cout << "of size : " << front.size() << std::endl;

                    rt::ProtocolController pc;

                    auto receivedData = pc.deserialize(front);
                    // std::cout << "SENDER TYPE : " << receivedData.sender << std::endl;
                    // std::cout << "PROTOCOL TYPE : " << receivedData.protocol << std::endl;

                    if (receivedData.sender == rt::SENDER_TYPE::SERVER && receivedData.protocol == rt::PROTOCOL_TYPE::ENTITIES) {
                        // std::cout << "[EXEC]: ENTITIES" << std::endl;
                        float delta = 0;

                        for (auto &x : receivedData.server.entities) {
                            std::uint32_t ecsID = x.ECSEntity;
                            tls::Vec3 position = x.position;
                            tls::Vec4 rotation = x.rotation;
                            float scale = x.scale;
                            int type = x.entityType;
                            // rt::ProtocolController::convertBitsetToEntity(x, ecsID, position, rotation, scale, type);
                            _interpreterCreateEntity(delta, ecsID, x.signature, position, rotation, scale, type);
                        }

                        for (auto &ecsID : receivedData.server.destroyedEntities) {
                            _coordinator->destroyEntity(_serverToClient[ecsID]);
                        }

                        std::cout << "delta: " << delta << std::endl;
                    }

                    // std::stringstream ss(front);
                    // std::string id;
                    // ss >> id;
                    // std::string token;
////////////////
//                     if (_serverToClient.find(std::stoi(id)) == _serverToClient.end()) {
//                         Entity entity = _coordinator->createEntity();
//                         _entities->insert(_entities->end(), entity);
//                         _serverToClient[std::stoi(id)] = entity;

//                         while (ss >> token) {
//                             if (token == "TRANSFORM") {
//                                 float x, y, z, rx, ry, rz, ra, scale;
//                                 ss >> x >> y >> z >> rx >> ry >> rz >> ra >> scale;
//                                 _coordinator->addComponent(
//                                     *_entities->rbegin(),
//                                     ECS::Transform{
//                                         {x, y, z},
//                                         {rx, ry, rz, ra},
//                                         scale
//                                     }
//                                 );
//                             } else if (token == "PLAYER") {
//                                 _coordinator->addComponent(
//                                     *_entities->rbegin(),
//                                     ECS::Model{
//                                         .model = _playerModel,
//                                     }
//                                 );
//                                 _coordinator->addComponent(
//                                     *_entities->rbegin(),
//                                     ECS::Player{
//                                         .key_up = KEY_W,
//                                         .key_down = KEY_S,
//                                         .key_left = KEY_A,
//                                         .key_right = KEY_D,
//                                         .key_shoot = KEY_SPACE,
//                                         .key_validate = KEY_ENTER,
//                                         .key_cancel = KEY_ESCAPE,
//                                         .key_settings = KEY_F1,
//                                     }
//                                 );
//                             } else if (token == "PLAYER_NY") {
//                                 static int i = 0;
//                                 std::vector<Color> colors = {RED, GREEN, YELLOW, PURPLE, ORANGE, PINK};
//                                 _coordinator->addComponent(
//                                     *_entities->rbegin(),
//                                     ECS::Model{
//                                         .model = _playerModel,
//                                         .color = colors[i++ % colors.size()]
//                                     }
//                                 );
//                             } else if (token == "TILE_BREAKABLE") {
//                                 _coordinator->addComponent(
//                                     *_entities->rbegin(),
//                                     ECS::Model{
//                                         .model = _tileBMmodel,
//                                         .color = RED
//                                     }
//                                 );
//                             } else if (token == "TILE") {
//                                 _coordinator->addComponent(
//                                     *_entities->rbegin(),
//                                     ECS::Model{
//                                         .model = _tileModel,
//                                     }
//                                 );
//                             } else if (token == "ENEMY") {
//                                 _coordinator->addComponent(
//                                         *_entities->rbegin(),
//                                         ECS::Model{
//                                                 .model = _modelEnemy,
//                                                 .texture = _textureEnemy
//                                         }
//                                 );
//                             } else if (token == "BASIC_SHOT") {
//                                 std::shared_ptr<RL::ZSound> sd = std::make_shared<RL::ZSound>("./client/resources/sounds/pew.mp3");
//                                 sd->setSoundVolume(0.5f);
//                                 _coordinator->addComponent(
//                                         *_entities->rbegin(),
//                                         ECS::Model{
//                                                 .model = _modelShot
//                                         }
//                                 );
//                                 _coordinator->addComponent(
//                                         *_entities->rbegin(),
//                                         ECS::Particles{
//                                                 .particles = std::vector<ECS::Particle>(500),
//                                                 .texture = _particleTexture,
//                                                 .type = ECS::ParticleType::CONE,
//                                                 .direction = ECS::Direction::LEFT,
//                                                 .speed = 75.0f,
//                                                 .scaleOffset = 3.0f,
//                                                 .positionOffset = {-0.5, 0, 0},
//                                                 .lifeTime = 2,
//                                                 .spawnRate = 35,
//                                                 .spawnTimer = 0,
//                                                 .surviveChance = 5
//                                         }
//                                 );
//                                 _coordinator->addComponent(
//                                     *_entities->rbegin(),
//                                     ECS::Sound{
//                                         .sound = sd,
//                                     }
//                                 );
//                             } else if (token == "SIN_SHOT") {
//                                 std::shared_ptr<RL::ZSound> sd = std::make_shared<RL::ZSound>("./client/resources/sounds/pew.mp3");
//                                 sd->setSoundVolume(0.5f);
//                                 _coordinator->addComponent(
//                                     *_entities->rbegin(),
//                                     ECS::Particles{
//                                         .particles = std::vector<ECS::Particle>(500),
//                                         .texture = _particleTexture,
//                                         .type = ECS::ParticleType::CONE,
//                                         .direction = ECS::Direction::LEFT,
//                                         .speed = 500.0f,
//                                         .scaleOffset = 3.0f,
//                                         .positionOffset = {-0.5, 0, 0},
//                                         .lifeTime = 10,
//                                         .spawnRate = 2,
//                                         .spawnTimer = 0,
//                                         .surviveChance = 0
//                                     }
//                                 );
//                                 _coordinator->addComponent(
//                                     *_entities->rbegin(),
//                                     ECS::Sound{
//                                         .sound = sd,
//                                     }
//                                 );
//                             } else if (token == "BASIC_ENEMY_SHOT") {
//                                 std::shared_ptr<RL::ZSound> sd = std::make_shared<RL::ZSound>("./client/resources/sounds/pew.mp3");
//                                 sd->setSoundVolume(0.5f);
//                                 _coordinator->addComponent(
//                                     *_entities->rbegin(),
//                                     ECS::Model{
//                                         .model = _modelEnemyShot,
//                                     }
//                                 );
//                                 _coordinator->addComponent(
//                                     *_entities->rbegin(),
//                                     ECS::Particles{
//                                         .particles = std::vector<ECS::Particle>(500),
//                                         .texture = _particleTexture,
//                                         .type = ECS::ParticleType::CONE,
//                                         .direction = ECS::Direction::RIGHT,
//                                         .speed = 75.0f,
//                                         .scaleOffset = 3.0f,
//                                         .positionOffset = {0.5, 0, 0},
//                                         .lifeTime = 2,
//                                         .spawnRate = 35,
//                                         .spawnTimer = 0,
//                                         .surviveChance = 5
//                                     }
//                                 );
//                                 _coordinator->addComponent(
//                                     *_entities->rbegin(),
//                                     ECS::Sound{
//                                         .sound = sd,
//                                     }
//                                 );
//                             } else if (token == "CAMERA") {
//                                 _coordinator->addComponent(
//                                     *_entities->rbegin(),
//                                     ECS::Cam{
//                                         .camera = _cam
//                                     }
//                                 );
//                                 _coordinator->addComponent(
//                                     *_entities->rbegin(),
//                                     ECS::Particles{
//                                         .particles = std::vector<ECS::Particle>(1000),
//                                         .texture = _starTexture,
//                                         .type = ECS::ParticleType::CONE,
//                                         .direction = ECS::Direction::LEFT,
//                                         .speed = 40.0f,
//                                         .scaleOffset = .5f,
//                                         .positionOffset = {95, 0, -120},
//                                         .lifeTime = 360,
//                                         .spawnRate = 1,
//                                         .spawnTimer = 0,
//                                         .surviveChance = 0
//                                     }
//                                 );
//                             } else {
//                                 std::cout << "Unknown token : " << token << std::endl;
//                             }
//                         }
//                     } else {
//                         while (ss >> token) {
//                             if (token == "TRANSFORM") {
//                                 auto &transform = _coordinator->getComponent<ECS::Transform>(
//                                         _serverToClient[std::stoi(id)]);
//                                 float x, y, z, rx, ry, rz, ra, scale;
//                                 ss >> x >> y >> z >> rx >> ry >> rz >> ra >> scale;
//                                 transform = ECS::Transform{
//                                         {x, y, z},
//                                         {rx, ry, rz, ra},
//                                         scale
//                                 };
//                             } else if (token == "DESTROY") {
//                                 _coordinator->destroyEntity(_serverToClient[std::stoi(id)]);
//                             } else {
// //                                std::cout << "[UPDATE] Unknown token : " << token << std::endl;
//                             }
//                         }
//                     }
////////////////////////////////////////////////////////////////
                }
            }

            void addEvent(const std::string &event) {
                _queue.push(event);
            }

            void _interpreterCreateEntity(float &delta, std::uint32_t ecsID, std::bitset<9> signature, tls::Vec3 position, tls::Vec4 rotation, float scale, int type) {
                // std::cout << "interpreter" << std::endl;
                // std::cout << "entity: " << ecsID << std::endl;
                // std::cout << "position: " << position._x << ", " << position._y << ", " << position._z << std::endl;
                // std::cout << "rotation: " << rotation._x << ", " << rotation._y << ", " << rotation._z << ", " << rotation._a << std::endl;
                // std::cout << "scale: " << scale << std::endl;
                // std::cout << "type: " << type << std::endl;
                float finalDelta = 0;

                finalDelta += signature[0] ? position._x : 0.0;
                finalDelta += signature[1] ? position._y : 0.0;
                finalDelta += signature[2] ? position._z : 0.0;

                finalDelta += signature[3] ? rotation._x : 0.0;
                finalDelta += signature[4] ? rotation._y : 0.0;
                finalDelta += signature[5] ? rotation._z : 0.0;
                finalDelta += signature[6] ? rotation._a : 0.0;

                finalDelta += signature[7] ? scale : 0.0;
                finalDelta += signature[8] ? type : 0.0;

                if (_serverToClient.find(ecsID) == _serverToClient.end()) {
                    ECS::Entity entity = _coordinator->createEntity();

                    _entities->insert(_entities->end(), entity);
                    _serverToClient[ecsID] = entity;

                    _coordinator->addComponent(
                        *_entities->rbegin(),
                        ECS::Transform{
                                {position._x, position._y, position._z},
                                {rotation._x, rotation._y, rotation._z, rotation._a},
                                scale
                        }
                    );

                    if (type == rt::ENTITY_TYPE::PLAYER) {
                        std::cout << "Create player ! with [" << ecsID << "]" << std::endl;
                        _coordinator->addComponent(
                            *_entities->rbegin(),
                            ECS::Model{
                                .model = _playerModel,
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
                    } else if (type == rt::ENTITY_TYPE::PLAYER_NY) {
                        static int i = 0;
                        std::vector<Color> colors = {RED, GREEN, YELLOW, PURPLE, ORANGE, PINK};
                        _coordinator->addComponent(
                            *_entities->rbegin(),
                            ECS::Model{
                                .model = _playerModel,
                                .color = colors[i++ % colors.size()]
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
                            ECS::Particles{
                                .particles = std::vector<ECS::Particle>(1000),
                                .texture = _starTexture,
                                .type = ECS::ParticleType::CONE,
                                .direction = ECS::Direction::LEFT,
                                .speed = 40.0f,
                                .scaleOffset = .5f,
                                .positionOffset = {95, 0, -120},
                                .lifeTime = 360,
                                .spawnRate = 1,
                                .spawnTimer = 0,
                                .surviveChance = 0
                            }
                        );
                    } else if (type == rt::ENTITY_TYPE::TILE_BREAKABLE) {
                        _coordinator->addComponent(
                            *_entities->rbegin(),
                            ECS::Model{
                                .model = _tileBMmodel,
                                .color = RED
                            }
                        );
                    } else if (type == rt::ENTITY_TYPE::TILE) {
                        _coordinator->addComponent(
                            *_entities->rbegin(),
                            ECS::Model{
                                .model = _tileModel,
                            }
                        );
                    } else if (type == rt::ENTITY_TYPE::ENEMY) {
                        _coordinator->addComponent(
                                *_entities->rbegin(),
                                ECS::Model{
                                        .model = _modelEnemy,
                                        .texture = _textureEnemy
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
                                ECS::Particles{
                                        .particles = std::vector<ECS::Particle>(500),
                                        .texture = _particleTexture,
                                        .type = ECS::ParticleType::CONE,
                                        .direction = ECS::Direction::LEFT,
                                        .speed = 75.0f,
                                        .scaleOffset = 3.0f,
                                        .positionOffset = {-0.5, 0, 0},
                                        .lifeTime = 2,
                                        .spawnRate = 35,
                                        .spawnTimer = 0,
                                        .surviveChance = 5
                                }
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
                                .type = ECS::ParticleType::CONE,
                                .direction = ECS::Direction::LEFT,
                                .speed = 500.0f,
                                .scaleOffset = 3.0f,
                                .positionOffset = {-0.5, 0, 0},
                                .lifeTime = 10,
                                .spawnRate = 2,
                                .spawnTimer = 0,
                                .surviveChance = 0
                            }
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
                            ECS::Particles{
                                .particles = std::vector<ECS::Particle>(500),
                                .texture = _particleTexture,
                                .type = ECS::ParticleType::CONE,
                                .direction = ECS::Direction::RIGHT,
                                .speed = 75.0f,
                                .scaleOffset = 3.0f,
                                .positionOffset = {0.5, 0, 0},
                                .lifeTime = 2,
                                .spawnRate = 35,
                                .spawnTimer = 0,
                                .surviveChance = 5
                            }
                        );
                        _coordinator->addComponent(
                            *_entities->rbegin(),
                            ECS::Sound{
                                .sound = sd,
                            }
                        );
                    }
                } else {
                    // std::cout << "Changing pos of : " << _serverToClient[ecsID] << std::endl;
                    auto &transform = _coordinator->getComponent<ECS::Transform>(
                            _serverToClient[ecsID]);
                    
                    float oldDelta = 0;
                    oldDelta += transform.position._x + transform.position._y + transform.position._z;
                    oldDelta += transform.rotation._x + transform.rotation._y + transform.rotation._z + transform.rotation._a;
                    oldDelta += transform.scale;
                    
                    transform.position._x = (signature[0] ? position._x : transform.position._x);
                    transform.position._y = (signature[1] ? position._y : transform.position._y);
                    transform.position._z = (signature[2] ? position._z : transform.position._z);

                    transform.rotation._x = (signature[3] ? rotation._x : transform.rotation._x);
                    transform.rotation._y = (signature[4] ? rotation._y : transform.rotation._y);
                    transform.rotation._z = (signature[5] ? rotation._z : transform.rotation._z);
                    transform.rotation._a = (signature[6] ? rotation._a : transform.rotation._a);

                    transform.scale = (signature[7] ? scale : transform.scale);
                    // transform = ECS::Transform{
                    //         {position._x, position._y, position._z},
                    //         {rotation._x, rotation._y, rotation._z, rotation._a},
                    //         scale
                    // };
                    float newDelta = 0;
                    newDelta += transform.position._x + transform.position._y + transform.position._z;
                    newDelta += transform.rotation._x + transform.rotation._y + transform.rotation._z + transform.rotation._a;
                    newDelta += transform.scale;

                    delta += newDelta - oldDelta;

                    return;
                }
                delta += finalDelta;
            }

            std::queue<std::string> _queue;
            std::shared_ptr<ECS::Coordinator> _coordinator;
            std::shared_ptr<std::set<Entity>> _entities;
            std::unordered_map<Entity, Entity> _serverToClient;
            std::shared_ptr<RL::ICamera> _cam;
            std::shared_ptr<RL::ZTexture> _starTexture;
            std::shared_ptr<RL::ZModel> _playerModel;
            std::shared_ptr<RL::ZModel> _tileBMmodel;
            std::shared_ptr<RL::ZModel> _tileModel;
            std::shared_ptr<RL::ZModel> _modelEnemy;
            std::shared_ptr<RL::ZModel> _modelShot;
            std::shared_ptr<RL::ZModel> _modelEnemyShot;
            std::shared_ptr<RL::ZTexture> _textureEnemy;
            std::shared_ptr<RL::ZTexture> _particleTexture;
    };
}

#endif //RTYPE_LISTENER_HPP
