#ifndef PROTOCOL_HPP_
#define PROTOCOL_HPP_

#include <iostream>
#include <sstream>
#include <string>
#include <memory>
#include <vector>
#include <cstdint>
#include "Vec3.hpp"
#include "Vec4.hpp"

namespace rt
{
    enum SENDER_TYPE
    {
        CLIENT,
        SERVER
    };

    enum PROTOCOL_TYPE
    {
        PING,
        CONNECTION_REQUEST,
        MOVE,
        SHOOT,
        CONNECTION_ACCEPTED,
        CONNECTION_REFUSED,
        OK,
        ENTITIES
    };

    enum ENTITY_TYPE
    {
        PLAYER,
        ENEMY,
    };

    struct Entity
    {
        std::uint32_t ECSEntity;
        
        tls::Vec3 position;
        tls::Vec4 rotation;
        float scale;
        ENTITY_TYPE entityType;
    };

    // Client
    struct p_client {
        tls::Vec3 move = {0, 0, 0};
    };

    // Server
    struct p_server {
        std::vector<Entity> entities; // List entities from server to client
    };

    struct Protocol
    {
        SENDER_TYPE sender;
        PROTOCOL_TYPE protocol;

        p_client client;
        p_server server;
    };

    class ProtocolController
    {
    public:
        ProtocolController() { init(); };
        ~ProtocolController() = default;

        ProtocolController& init()
        {
            _protocol = std::make_shared<Protocol>();
            return *this;
        }

        ProtocolController& setSender(rt::SENDER_TYPE sender)
        {
            _protocol->sender = sender;
            return *this;
        }

        ProtocolController& setProtocol(rt::PROTOCOL_TYPE protocol)
        {
            _protocol->protocol = protocol;
            return *this;
        }

        // Actions :

        ProtocolController& actionPing()
        {
            _protocol->sender = CLIENT;
            _protocol->protocol = rt::PROTOCOL_TYPE::PING;
            return *this;
        }

        ProtocolController& actionMove(tls::Vec3 move)
        {
            _protocol->sender = rt::SENDER_TYPE::CLIENT;
            _protocol->protocol = rt::PROTOCOL_TYPE::MOVE;

            _protocol->client.move = move;
            return *this;
        }

        // Events Server Part :

        ProtocolController& addEntity(std::uint32_t ECSId, tls::Vec3 position, tls::Vec4 rotation, float scale, ENTITY_TYPE type)
        {
            _protocol->sender = rt::SENDER_TYPE::SERVER;
            _protocol->protocol = rt::PROTOCOL_TYPE::ENTITIES;

            Entity entity;
            entity.ECSEntity = ECSId;
            entity.position = position;
            entity.rotation = rotation;
            entity.scale = scale;
            entity.entityType = type;
            _protocol->server.entities.push_back(entity);
            return *this;
        }

        // Functions : 

        std::string serialize() const
        {
            std::ostringstream oss;
            oss.write(reinterpret_cast<const char*>(&_protocol->sender), sizeof(_protocol->sender));
            oss.write(reinterpret_cast<const char*>(&_protocol->protocol), sizeof(_protocol->protocol));

            for (const auto& entity : _protocol->server.entities)
            {
                serializeEntity(oss, entity);
            }

            return oss.str();
        }

        std::string serialize(const Protocol &protocol) const
        {
            std::ostringstream oss;
            oss.write(reinterpret_cast<const char*>(&protocol.sender), sizeof(protocol.sender));
            oss.write(reinterpret_cast<const char*>(&protocol.protocol), sizeof(protocol.protocol));

            for (const auto& entity : protocol.server.entities)
            {
                serializeEntity(oss, entity);
            }

            return oss.str();
        }

        static Protocol deserialize(const std::string& data)
        {
            std::istringstream iss(data);
            Protocol deserializedData;

            iss.read(reinterpret_cast<char*>(&deserializedData.sender), sizeof(deserializedData.sender));
            iss.read(reinterpret_cast<char*>(&deserializedData.protocol), sizeof(deserializedData.protocol));

            while (iss.peek() != EOF)
            {
                Entity entity;
                deserializeEntity(iss, entity);
                deserializedData.server.entities.push_back(entity);
            }

            return deserializedData;
        }

        Protocol getProtocol() const { return *_protocol.get(); }

    private:
        std::shared_ptr<Protocol> _protocol;

        void serializeEntity(std::ostringstream& oss, const Entity& entity) const
        {
            oss.write(reinterpret_cast<const char*>(&entity.ECSEntity), sizeof(entity.ECSEntity));
            oss.write(reinterpret_cast<const char*>(&entity.position), sizeof(entity.position));
            oss.write(reinterpret_cast<const char*>(&entity.rotation), sizeof(entity.rotation));
            oss.write(reinterpret_cast<const char*>(&entity.scale), sizeof(entity.scale));
            oss.write(reinterpret_cast<const char*>(&entity.entityType), sizeof(entity.entityType));
        }

        static void deserializeEntity(std::istringstream& iss, Entity& entity)
        {
            iss.read(reinterpret_cast<char*>(&entity.ECSEntity), sizeof(entity.ECSEntity));
            iss.read(reinterpret_cast<char*>(&entity.position), sizeof(entity.position));
            iss.read(reinterpret_cast<char*>(&entity.rotation), sizeof(entity.rotation));
            iss.read(reinterpret_cast<char*>(&entity.scale), sizeof(entity.scale));
            iss.read(reinterpret_cast<char*>(&entity.entityType), sizeof(entity.ECSEntity));
        }
    };

} // namespace rt

#endif /* !PROTOCOL_HPP_ */
