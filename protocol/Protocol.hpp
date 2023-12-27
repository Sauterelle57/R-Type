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

    struct Entity
    {
        std::uint32_t ECSEntity;
        tls::Vec3 position;
        tls::Vec4 rotation;
        float scale;
        std::string type;
    };

    struct Protocol
    {
        SENDER_TYPE sender;
        PROTOCOL_TYPE protocol;
        std::vector<Entity> entities;
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

        ProtocolController& addEntity(std::uint32_t ECSId, tls::Vec3 position, tls::Vec4 rotation, float scale, std::string type)
        {
            Entity entity;
            entity.ECSEntity = ECSId;
            entity.position = position;
            entity.rotation = rotation;
            entity.scale = scale;
            entity.type = type;
            _protocol->entities.push_back(entity);
            return *this;
        }

        std::string serialize() const
        {
            std::ostringstream oss;
            oss.write(reinterpret_cast<const char*>(&_protocol->sender), sizeof(_protocol->sender));
            oss.write(reinterpret_cast<const char*>(&_protocol->protocol), sizeof(_protocol->protocol));

            for (const auto& entity : _protocol->entities)
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

            for (const auto& entity : protocol.entities)
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
                deserializedData.entities.push_back(entity);
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

            std::size_t typeSize = entity.type.size();
            oss.write(reinterpret_cast<const char*>(&typeSize), sizeof(typeSize));
            oss.write(entity.type.c_str(), typeSize);
        }

        static void deserializeEntity(std::istringstream& iss, Entity& entity)
        {
            iss.read(reinterpret_cast<char*>(&entity.ECSEntity), sizeof(entity.ECSEntity));
            iss.read(reinterpret_cast<char*>(&entity.position), sizeof(entity.position));
            iss.read(reinterpret_cast<char*>(&entity.rotation), sizeof(entity.rotation));
            iss.read(reinterpret_cast<char*>(&entity.scale), sizeof(entity.scale));

            std::size_t typeSize;
            iss.read(reinterpret_cast<char*>(&typeSize), sizeof(typeSize));
            entity.type.resize(typeSize);
            iss.read(&entity.type[0], typeSize);
        }
    };

} // namespace rt

#endif /* !PROTOCOL_HPP_ */
