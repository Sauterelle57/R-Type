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

namespace RT {
    class Listener : public IListener {
        public:
            Listener(std::shared_ptr<ECS::Coordinator> &coordinator, std::shared_ptr<std::set<Entity>> entities, std::shared_ptr<RL::ICamera> cam) : _coordinator(coordinator), _entities(entities), _cam(cam) {};
            ~Listener() = default;
            void onEvent() {
                while (!_queue.empty()) {
                    std::string front = _queue.front();
//                    std::cout << "New event : " << front << std::endl;
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
                                    ECS::Transform {
                                        {x, y, z},
                                        {rx, ry, rz, ra},
                                        scale
                                    }
                                );
                            } else if (token == "PLAYER_1") {
                                std::shared_ptr<RL::ZModel> model = std::make_shared<RL::ZModel>("./client/resources/models/ship.glb");
                                Matrix matr = MatrixIdentity();
                                matr = MatrixMultiply(matr, MatrixRotateY(90 * DEG2RAD));
                                matr = MatrixMultiply(matr, MatrixRotateZ(90 * DEG2RAD));
                                model->_model->transform = matr;
                                _coordinator->addComponent(
                                    *_entities->rbegin(),
                                    ECS::Model {
                                        .model = model,
                                    }
                                );
                                _coordinator->addComponent(
                                    *_entities->rbegin(),
                                    ECS::Player {
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
                            } else if (token == "PLAYER_2") {
                                std::shared_ptr<RL::ZModel> model = std::make_shared<RL::ZModel>("./client/resources/models/ship.glb");
                                Matrix matr = MatrixIdentity();
                                matr = MatrixMultiply(matr, MatrixRotateY(90 * DEG2RAD));
                                matr = MatrixMultiply(matr, MatrixRotateZ(90 * DEG2RAD));
                                model->_model->transform = matr;
                                static int i = 0;
                                std::vector<Color> colors = {RED, GREEN, YELLOW, PURPLE, ORANGE, PINK};
                                _coordinator->addComponent(
                                    *_entities->rbegin(),
                                    ECS::Model {
                                        .model = model,
                                        .color = colors[i++ % colors.size()]
                                    }
                                );
                            } else if (token == "ENEMY") {
                                std::shared_ptr<RL::ZModel> model = std::make_shared<RL::ZModel>("./client/resources/models/duck.obj");
                                Matrix matr = MatrixIdentity();
//                                matr = MatrixMultiply(matr, MatrixRotateX(-90 * DEG2RAD));
                                matr = MatrixMultiply(matr, MatrixRotateY(-180 * DEG2RAD));
//                                matr = MatrixMultiply(matr, MatrixRotateZ(-90 * DEG2RAD));
                                model->_model->transform = matr;
                                _coordinator->addComponent(
                                    *_entities->rbegin(),
                                    ECS::Model {
                                        .model = model,
                                        .texture = std::make_shared<RL::ZTexture>("./client/resources/images/duck_text.png"),
                                    }
                                );
                            } else if (token == "BASIC_SHOT") {
                                _coordinator->addComponent(
                                    *_entities->rbegin(),
                                    ECS::Model {
                                        .model = std::make_shared<RL::ZModel>("./client/resources/models/boom.glb"),
                                    }
                                );
                                _coordinator->addComponent(
                                    *_entities->rbegin(),
                                    ECS::Particles {
                                        .particles = std::vector<ECS::Particle>(500),
                                        .texture = std::make_shared<RL::ZTexture>("./client/resources/images/particle.png"),
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
                                std::shared_ptr<RL::ZSound> sd = std::make_shared<RL::ZSound>("./client/resources/sounds/pew.mp3");
                                sd->setSoundVolume(0.1f);
                                _coordinator->addComponent(
                                    *_entities->rbegin(),
                                    ECS::Sound{
                                        .sound = sd,
                                    }
                                );
                            } else if (token == "CAMERA") {
                                _coordinator->addComponent(
                                    *_entities->rbegin(),
                                    ECS::Cam {
                                        .camera = _cam
                                    }
                                );

                            } else {
                                std::cout << "Unknown token : " << token << std::endl;
                            }
                        }
                    } else {
                        while (ss >> token) {
                            if (token == "TRANSFORM") {
                                auto &transform = _coordinator->getComponent<ECS::Transform>(_serverToClient[std::stoi(id)]);
                                float x, y, z, rx, ry, rz, ra, scale;
                                ss >> x >> y >> z >> rx >> ry >> rz >> ra >> scale;
                                transform = ECS::Transform {
                                    {x, y, z},
                                    {rx, ry, rz, ra},
                                    scale
                                };
                            } else if (token == "DESTROY") {
                                _coordinator->destroyEntity(_serverToClient[std::stoi(id)]);
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
    };
}

#endif //RTYPE_LISTENER_HPP
