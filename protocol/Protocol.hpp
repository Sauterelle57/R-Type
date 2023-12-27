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
            // Server Part Server => Client
            PING,
            CONNECTION_REQUEST,
            MOVE,
            SHOOT,

            // Client Part Client => Server
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
            // Variables
            SENDER_TYPE sender;
            PROTOCOL_TYPE protocol;

            std::vector<Entity> entities;
        };

        class ProtocolController
        {
            public:
                ProtocolController() {
                    init();
                };

                ~ProtocolController() = default;

                ProtocolController& init() {
                    _protocol = std::make_shared<Protocol>();
                    return *this;
                }

                ProtocolController& setSender(rt::SENDER_TYPE sender) {
                    _protocol->sender = sender;
                    return *this;
                }

                ProtocolController& setProtocol(rt::PROTOCOL_TYPE protocol) {
                    _protocol->protocol = protocol;
                    return *this;
                }

                ProtocolController& addEntity(std::uint32_t ECSId, tls::Vec3 position, tls::Vec4 rotation, float scale, std::string type) {
                    Entity entity;

                    entity.ECSEntity = ECSId;
                    entity.position = position;
                    entity.rotation = rotation;
                    entity.scale = scale;
                    entity.type = type;

                    _protocol->entities.push_back(entity);
                    return *this;
                }

                std::string serialize() const {
                    rt::Protocol pt = *_protocol.get();
                    return _serializeStruct(pt);
                }

                std::string serialize(const Protocol &protocol) const {
                    return _serializeStruct(protocol);
                }

                static Protocol deserialize(const std::string& data) {
                    std::istringstream iss(data);
                    Protocol deserializedData;

                    iss.read(reinterpret_cast<char*>(&deserializedData.sender), sizeof(deserializedData.sender));
                    iss.read(reinterpret_cast<char*>(&deserializedData.protocol), sizeof(deserializedData.protocol));
                    iss.read(reinterpret_cast<char*>(&deserializedData.entities), sizeof(deserializedData.entities));

                    return deserializedData;
                }

                rt::Protocol getProtocol() const {
                    return *_protocol.get();
                }

            private:
                std::shared_ptr<Protocol> _protocol;

                std::string _serializeStruct(const Protocol& protocol) const {
                    std::ostringstream oss;

                    oss.write(reinterpret_cast<const char*>(&protocol.sender), sizeof(protocol.sender));
                    oss.write(reinterpret_cast<const char*>(&protocol.protocol), sizeof(protocol.protocol));
                    oss.write(reinterpret_cast<const char*>(&protocol.entities), sizeof(protocol.entities));
                    return oss.str();
                }
        };
    }

#endif /* !PROTOCOL_HPP_ */