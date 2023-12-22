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

namespace RT {
    class Listener : public IListener {
        public:
            Listener(std::shared_ptr<ECS::Coordinator> &coordinator, std::shared_ptr<std::set<Entity>> entities) : _coordinator(coordinator), _entities(entities) {};
            ~Listener() = default;
            void onEvent() {
                while (!_queue.empty()) {
                    std::string front = _queue.front();
                    std::cout << "New event : " << front << std::endl;
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
                            }
                            if (token == "PLAYER_1") {
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
                            }
                            if (token == "CAMERA") {
                                std::shared_ptr<RL::ICamera> camera = std::make_shared<RL::ZCamera>();
                                camera->setPosition({ 0.0f, 10.0f, 100.0f });
                                camera->setTarget({ 0.0f, 10.0f, 0.0f });
                                camera->setUp({ 0.0f, 1.0f, 0.0f });
                                camera->setFovy(30.0f);
                                camera->setProjection(CAMERA_PERSPECTIVE);

                                _coordinator->addComponent(
                                    *_entities->rbegin(),
                                    ECS::Cam {
                                        .camera = camera
                                    }
                                );
                            }
                        }
                    } else {
                        while (ss >> token) {
                            if (token == "TRANSFORM") {
                                auto &transform = _coordinator->getComponent<ECS::Transform>(std::stoi(id));
                                float x, y, z, rx, ry, rz, ra, scale;
                                ss >> x >> y >> z >> rx >> ry >> rz >> ra >> scale;
                                transform = ECS::Transform {
                                    {x, y, z},
                                    {rx, ry, rz, ra},
                                    scale
                                };
                            } else {
                                std::cout << "token : " << token << std::endl;
                            }
                        }
                    }

                    std::cout << "end" << std::endl;
                }
            }

            void addEvent(const std::string &event) {
                _queue.push(event);
            }

            std::queue<std::string> _queue;
            std::shared_ptr<ECS::Coordinator> _coordinator;
            std::shared_ptr<std::set<Entity>> _entities;
            std::unordered_map<Entity, Entity> _serverToClient;
    };
}

#endif //RTYPE_LISTENER_HPP
