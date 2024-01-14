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
#include "Clock.hpp"
#include "Protocol.hpp"
#include <algorithm>

namespace rt
{
    class DeltaManager
    {
        public:
            DeltaManager() = default;
            ~DeltaManager() = default;

            bool validatePacket(unsigned long packetId) {
                if (_packets.find(packetId) == _packets.end())
                    return false;
                
                auto protocol = _packets[packetId];

                for (auto x : protocol.server.entities) {
                    _entities[x.ECSEntity] = x;
                }

                //std::vector<std::uint32_t> _toDelete
                std::vector<std::pair<std::uint32_t, long long>> destroyedEntities = protocol.server.destroyedEntities;
                // do : _toDelete = _toDelete - protocol.server.destroyedEntities;
                _toDelete.erase(std::remove_if(_toDelete.begin(), _toDelete.end(),
                [&destroyedEntities](std::pair<std::uint32_t, long long> id) {
                    return std::find(destroyedEntities.begin(), destroyedEntities.end(), id) != destroyedEntities.end();
                }), _toDelete.end());

                

                // _toDelete.insert(_toDelete.end(), protocol.server.destroyedEntities.begin(), protocol.server.destroyedEntities.end());

                // std::cout << "Protocol in stock : " << _packets.size() << std::endl;

                _packets.erase(packetId);
                return true;
            }

            void setPacket(rt::Protocol &protocol) {
                protocol.packetId = tls::Clock::getTimeStamp();
                _packets[protocol.packetId] = protocol;
            }

            rt::Entity getAcknowledge(std::uint32_t ECSId, rt::Entity entityNow) {
                if (_entities.find(ECSId) == _entities.end()) {
                    entityNow.signature = std::bitset<15>(0b111111111111111);
                    return entityNow;
                }

                rt::Entity& diff = _entities[ECSId];
                diff.signature[0] = diff.position._x != entityNow.position._x;
                diff.signature[1] = diff.position._y != entityNow.position._y;
                diff.signature[2] = diff.position._z != entityNow.position._z;

                diff.signature[3] = diff.rotation._x != entityNow.rotation._x;
                diff.signature[4] = diff.rotation._y != entityNow.rotation._y;
                diff.signature[5] = diff.rotation._z != entityNow.rotation._z;
                diff.signature[6] = diff.rotation._a != entityNow.rotation._a;

                // diff.signature[7] = diff.scale != entityNow.scale;
                diff.signature[7] = diff.scale._x != entityNow.scale._x;
                diff.signature[8] = diff.scale._y != entityNow.scale._y;
                diff.signature[9] = diff.scale._z != entityNow.scale._z;

                diff.signature[10] = diff.entityType != entityNow.entityType;

                entityNow.signature = diff.signature;

                return entityNow;
            }

            void deleteEntity(std::pair<std::uint32_t, long long> ECSId) {
                if (_entities.find(ECSId.first) != _entities.end())
                    _entities.erase(ECSId.first);
            }

            std::vector<std::pair<std::uint32_t, long long>> getDeletedEntities(std::vector<std::pair<std::uint32_t, long long>> toDelete) {

                toDelete.insert(toDelete.end(), _toDelete.begin(), _toDelete.end());

                _toDelete = toDelete;

                return toDelete;
            }   

            void setDeletedEntities(std::vector<std::pair<std::uint32_t, long long>> entities) {
                _toDelete = entities;
            }
        private:
            std::map<std::uint32_t, rt::Entity> _entities;
            std::vector<std::pair<std::uint32_t, long long>> _toDelete;
            std::map<long long, rt::Protocol> _packets;

            float _calculDelta(tls::Vec3 position, tls::Vec4 rotation, tls::Vec3 scale, ENTITY_TYPE type, rt::Entity& diff) {
                float finalDelta = position._x + position._y + position._z + rotation._x + rotation._y + rotation._z + rotation._a + scale._x + scale._y + scale._z + static_cast<int>(type);
                float base = diff.position._x + diff.position._y + diff.position._z + diff.rotation._x + diff.rotation._y + diff.rotation._z + diff.rotation._a + diff.scale._x + diff.scale._y + diff.scale._z + static_cast<int>(diff.entityType);
                float delta = finalDelta - base;
                return delta;
            }
    };
}

#endif /* !DELTAMANAGER_HPP_ */
