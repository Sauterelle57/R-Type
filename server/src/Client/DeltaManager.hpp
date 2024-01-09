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

            rt::Entity addEntity(std::uint32_t ECSId, tls::Vec3 position, tls::Vec4 rotation, float scale, ENTITY_TYPE type) {
                std::bitset<9> signature;
                rt::Entity ent = {ECSId, signature, position, rotation, scale, type};

                if (_clients.find(ECSId) == _clients.end()) {
                    ent.signature = std::bitset<9>(0b111111111);
                    _clients.insert({ECSId, ent});
                    return ent;
                }

                rt::Entity& diff = _clients[ECSId];
                diff.signature[0] = diff.position._x != position._x;
                diff.signature[1] = diff.position._y != position._y;
                diff.signature[2] = diff.position._z != position._z;

                diff.signature[3] = diff.rotation._x != rotation._x;
                diff.signature[4] = diff.rotation._y != rotation._y;
                diff.signature[5] = diff.rotation._z != rotation._z;
                diff.signature[6] = diff.rotation._a != rotation._a;

                diff.signature[7] = diff.scale != scale;
                diff.signature[8] = diff.entityType != type;


                
                ent.signature = diff.signature;
                float delta = _calculDelta(position, rotation, scale, type, diff);
                _clients[ECSId] = ent;
                return ent;
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
