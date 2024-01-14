/*
** EPITECH PROJECT, 2023
** B-CPP-500-STG-5-2-rtype-noah.gosciniak
** File description:
** DrawModel
*/

#ifndef RTYPE_PARENT_HPP
#define RTYPE_PARENT_HPP

#include "System.hpp"
#include "Coordinator.hpp"
#include "ComponentStructs.hpp"
#include <cmath>
#include "ClientController.hpp"

namespace ECS {

    class ParentManager : public System {
        public:
            static void bossChild(std::shared_ptr<Coordinator> _coordinator, std::set<Entity> _entities, Entity parent) {
                _entities.insert(_entities.end(), _coordinator->createEntity());
                auto &traveling = _coordinator->getComponent<ECS::Traveling>(parent);
                auto &transform = _coordinator->getComponent<ECS::Transform>(parent);
                auto &weapon = _coordinator->getComponent<ECS::Weapon>(parent);
                auto &collider = _coordinator->getComponent<ECS::Collider>(parent);
                auto &clientUpdater = _coordinator->getComponent<ECS::ClientUpdater>(parent);
                // auto &enemy = _coordinator->getComponent<ECS::Enemy>(parent);
                // auto &shooter = _coordinator->getComponent<ECS::Shooter>(parent);
                static int offset = 1;

                _coordinator->addComponent(*_entities.rbegin(), traveling);
                transform.position._x += offset;
                offset += 1;
                _coordinator->addComponent(*_entities.rbegin(), transform);
                weapon.damage /= 2;
                weapon.speed *= 2;
                _coordinator->addComponent(*_entities.rbegin(), weapon);

                static tls::BoundingBox bdb = tls::loadModelAndGetBoundingBox("./client/resources/models/boss_body.glb");
                static tls::Matrix matr = tls::MatrixIdentity();
                static bool first = true;
                if (first) {
                    matr = tls::MatrixMultiply(matr, tls::MatrixRotateX(-180 * DEG2RAD));
                    bdb.applyMatrix(matr);
                    first = false;
                }

                _coordinator->addComponent(*_entities.rbegin(), collider);
                _coordinator->addComponent(
                    *_entities.rbegin(),
                    ECS::Type {
                        .name = "CHILD"
                    }
                );
                _coordinator->addComponent(*_entities.rbegin(), clientUpdater);
                // _coordinator->addComponent(*_entities.rbegin(), enemy);
                // _coordinator->addComponent(*_entities.rbegin(), shooter);
            }

            void update() {
                auto coordinatorPtr = _coordinator.lock();
                if (!coordinatorPtr) {
                    return;
                }

                for (auto const &entity : _entities) {
                    auto &transform = coordinatorPtr->getComponent<Transform>(entity);
                    auto &parent = coordinatorPtr->getComponent<Parent>(entity);

                    if (parent.spawnFrequency.isTimeElapsed() && parent.nbChildren > 0) {
                        parent.create_child(coordinatorPtr, _entities, entity);
                        parent.nbChildren--;
                    }
                }
            }
    };
}

#endif //RTYPE_PARENT_HPP
