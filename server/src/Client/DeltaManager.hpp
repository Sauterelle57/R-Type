/*
** EPITECH PROJECT, 2024
** B-CPP-500-STG-5-2-rtype-noah.gosciniak
** File description:
** DeltaManager
*/

#ifndef DELTAMANAGER_HPP_
#define DELTAMANAGER_HPP_
#include <map>
#include <bitset>
#include "EntityData.hpp"

namespace rt
{
    class DeltaManager
    {
        public:
            DeltaManager() = default;
            ~DeltaManager() = default;

            void addEntity(std::uint32_t ECSId, unsigned long msgId, rt::Entity entity) {
                _clients[ECSId] = entity;
            }

            rt::Entity getAcknowledge(std::uint32_t ECSId, rt::Entity entityNow) {
                if (_clients.find(ECSId) == _clients.end()) {
                    entityNow.signature = std::bitset<9>(0b111111111);
                    return entityNow;
                }

                rt::Entity& diff = _clients[ECSId];
                diff.signature[0] = diff.position._x != entityNow.position._x;
                diff.signature[1] = diff.position._y != entityNow.position._y;
                diff.signature[2] = diff.position._z != entityNow.position._z;

                diff.signature[3] = diff.rotation._x != entityNow.rotation._x;
                diff.signature[4] = diff.rotation._y != entityNow.rotation._y;
                diff.signature[5] = diff.rotation._z != entityNow.rotation._z;
                diff.signature[6] = diff.rotation._a != entityNow.rotation._a;

                diff.signature[7] = diff.scale != entityNow.scale;
                diff.signature[8] = diff.entityType != entityNow.entityType;

                entityNow.signature = diff.signature;

                return entityNow;
            }

            void deleteEntity(std::uint32_t ECSId) {
                if (_clients.find(ECSId) != _clients.end())
                    _clients.erase(ECSId);
            }
        private:
            std::map<std::uint32_t, rt::Entity> _clients;

            float _calculDelta(tls::Vec3 position, tls::Vec4 rotation, float scale, ENTITY_TYPE type, rt::Entity& diff) {
                float finalDelta = position._x + position._y + position._z + rotation._x + rotation._y + rotation._z + rotation._a + scale + static_cast<int>(type);
                float base = diff.position._x + diff.position._y + diff.position._z + diff.rotation._x + diff.rotation._y + diff.rotation._z + diff.rotation._a + diff.scale + static_cast<int>(diff.entityType);
                float delta = finalDelta - base;
                return delta;
            }
    };
}

#endif /* !DELTAMANAGER_HPP_ */
