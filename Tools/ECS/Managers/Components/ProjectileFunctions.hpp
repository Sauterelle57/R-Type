///*
//** EPITECH PROJECT, 2023
//** B-CPP-500-STG-5-2-rtype-noah.gosciniak
//** File description:
//** ProjectileFunctions
//*/
//
//#ifndef PROJECTILEFUNCTIONS_HPP_
//#define PROJECTILEFUNCTIONS_HPP_
//
//
////#include <memory>
////#include "Entity.hpp"
////#include "Coordinator.hpp"
////#include "renderer/Model.hpp"
//
//namespace ECS {
//
//    void basicShot() {
////        _entities.insert(_entities.end(), _coordinator->createEntity());
////        _coordinator->addComponent(
////            _entities.extract(_entities.end()).value(),
////            Transform {
////                .position = {0, 0, 0},
////                .rotation = {0, 0, 0, 0},
////                .scale = 0.1f
////            }
////        );
////        _coordinator->addComponent(
////            _entities.extract(_entities.end()).value(),
////            Model {
////                .model = std::make_shared<RL::ZModel>("./client/resources/models/boom.glb"),
////            }
////        );
////        _coordinator->addComponent(
////            _entities.extract(_entities.end()).value(),
////            Projectile {
////                .trajectory = [](tls::Vec3 pos) {
////                    return tls::Vec3{pos._x + 2, pos._y, pos._z};
////                },
////                .damage = 1,
////                .speed = 0.5f
////            }
////        );
////        _coordinator->addComponent(
////            _entities.extract(_entities.end()).value(),
////            ECS::Particles {
////                .particles = std::vector<ECS::Particle>(1000),
////                .texture = std::make_shared<RL::ZTexture>("./client/resources/images/particle.png"),
////                .type = ECS::ParticleType::CONE,
////                .direction = ECS::Direction::UP,
////                .speed = 300.0f,
////                .scaleOffset = 0.1f,
////                .positionOffset = {0, 0, 0},
////                .lifeTime = 1000,
////                .spawnRate = 10,
////                .spawnTimer = 0
////            }
////        );
//    }
//
//};
//
//#endif /* !PROJECTILEFUNCTIONS_HPP_ */
