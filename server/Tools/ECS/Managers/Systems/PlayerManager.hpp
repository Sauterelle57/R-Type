/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** PlayerManager.hpp
*/

#ifndef RTYPE_PLAYERMANAGER_HPP
#define RTYPE_PLAYERMANAGER_HPP

#include "System.hpp"
#include "Coordinator.hpp"
#include "ComponentStructs.hpp"
#include "Protocol.hpp"

namespace ECS {
    class PlayerManager : public System {
        public:
            void update(const rt::Protocol &data, const std::string &ip, const int port, int wave) {
                auto coordinatorPtr = _coordinator.lock();
                if (!coordinatorPtr) {
                    return;
                }

                for (auto const &entity : _entities) {
                    auto &player = coordinatorPtr->getComponent<Player>(entity);
                    auto &transform = coordinatorPtr->getComponent<Transform>(entity);
                    // auto &shooter = coordinatorPtr->getComponent<Shooter>(entity);
                    auto &updater = coordinatorPtr->getComponent<ClientUpdater>(entity);
                    auto &weapon = coordinatorPtr->getComponent<Weapon>(entity);
                    auto &type = coordinatorPtr->getComponent<Type>(entity);
                    if (wave == 4) {
                        weapon.create_projectile = Shoot::sinShot;
                    }
                    if (wave == 6) {
                        weapon.create_projectile = Shoot::doubleSinShot;
                    }
                    if (wave == 8) {
                        weapon.create_projectile = Shoot::tripleShot;
                    }

                    if (type.ip == ip && type.port == port) {
                        if (data.protocol == rt::PROTOCOL_TYPE::MOVE || data.protocol == rt::PROTOCOL_TYPE::MOVE_AND_SHOOT) {
                            int x, y, z;
                            x = data.client.move._x / _entities.size();
                            y = data.client.move._y / _entities.size();
                            z = data.client.move._z / _entities.size();

                            player.mooving._x = x * 0.25f;
                            player.mooving._y = y * 0.25f;
                            player.mooving._z = z * 0.25f;
                        } else if (data.protocol == rt::PROTOCOL_TYPE::SHOOT) {
                            shooter.isShooting = true;
                        }
                        if (data.protocol == rt::PROTOCOL_TYPE::MOVE_AND_SHOOT) {
                            shooter.isShooting = true;
                        }
                    }
                }
            }
        };
    }

#endif //RTYPE_PLAYERMANAGER_HPP
