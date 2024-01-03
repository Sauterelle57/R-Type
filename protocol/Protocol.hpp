#ifndef PROTOCOL_HPP_
#define PROTOCOL_HPP_

#include <iostream>
#include <sstream>
#include <string>
#include <memory>
#include <vector>
#include <array>
#include <cstdint>
#include <bitset>
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
        std::vector<std::bitset<578>> entities; // List entities from server to client
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
            std::cout << "1" << std::endl;
            // std::cout << "addr : " << _protocol << std::endl;
            _protocol->sender = rt::SENDER_TYPE::SERVER;
            std::cout << "2" << std::endl;

            // auto bits = ProtocolController::convertEntityToBitset(ECSId, {true, true}, position, rotation, scale, type);
            // std::cout << bits << std::endl;
            // _protocol.server.entities.push_back(bits);
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
                std::bitset<578> entity;
                deserializeEntity(iss, entity);
                deserializedData.server.entities.push_back(entity);
            }

            return deserializedData;
        }

        std::bitset<578> convertEntityToBitset(std::uint32_t ecsId, std::array<bool, 2> signature, tls::Vec3 pos, tls::Vec4 rotation, float scale, int type)
        {
            std::bitset<32> ecsIdBits(ecsId);
            std::bitset<2> signatureBits((signature[0] << 1) | signature[1]);

            std::bitset<64> posXBits(*reinterpret_cast<uint64_t*>(&pos._x));
            std::bitset<64> posYBits(*reinterpret_cast<uint64_t*>(&pos._y));
            std::bitset<64> posZBits(*reinterpret_cast<uint64_t*>(&pos._z));

            std::bitset<64> rotationXBits(*reinterpret_cast<uint64_t*>(&rotation._x));
            std::bitset<64> rotationYBits(*reinterpret_cast<uint64_t*>(&rotation._y));
            std::bitset<64> rotationZBits(*reinterpret_cast<uint64_t*>(&rotation._z));
            std::bitset<64> rotationABits(*reinterpret_cast<uint64_t*>(&rotation._a));

            std::bitset<64> scaleBits(*reinterpret_cast<uint64_t*>(&scale));

            std::bitset<32> typeBits(type);

            std::bitset<578> result;

            // Setting bits individually
            for (int i = 0; i < 32; ++i)
                result.set(i, ecsIdBits[i]);

            for (int i = 0; i < 2; ++i)
                result.set(i + 32, signatureBits[i]);

            for (int i = 0; i < 64; ++i)
            {
                result.set(i + 34, posXBits[i]);
                result.set(i + 98, posYBits[i]);
                result.set(i + 162, posZBits[i]);
                result.set(i + 226, rotationXBits[i]);
                result.set(i + 290, rotationYBits[i]);
                result.set(i + 354, rotationZBits[i]);
                result.set(i + 418, rotationABits[i]);
                result.set(i + 482, scaleBits[i]);
            }

            for (int i = 0; i < 32; ++i)
                result.set(i + 546, typeBits[i]);

            return result;
        }

        void changeEntityTypeInBitset(std::bitset<578> &x, rt::ENTITY_TYPE type)
        {
            std::bitset<32> typeBits(type);

            for (int i = 0; i < 32; ++i)
                x.set(i + 546, typeBits[i]);
        }

        static std::uint32_t getECSIdFromBitset(std::bitset<578> x)
        {
            std::bitset<32> ecsIdBits;
            std::uint32_t ecsID;

            for (int i = 0; i < 32; ++i)
                ecsIdBits[i] = x[i];
        
            return ecsID;
        }

        static void convertBitsetToEntity(std::bitset<578> x, std::uint32_t &ecsID, tls::Vec3 &pos, tls::Vec4 &rotation, float &scale, int &type)
        {
            std::bitset<32> ecsIdBits;
            std::array<bool, 2> signatureBits;

            // Extracting bits individually
            for (int i = 0; i < 32; ++i)
                ecsIdBits[i] = x[i];

            for (int i = 0; i < 2; ++i)
                signatureBits[i] = x[i + 32];

            std::bitset<64> posXBits, posYBits, posZBits;
            std::bitset<64> rotationXBits, rotationYBits, rotationZBits, rotationABits;
            std::bitset<64> scaleBits;

            for (int i = 0; i < 64; ++i)
            {
                posXBits[i] = x[i + 34];
                posYBits[i] = x[i + 98];
                posZBits[i] = x[i + 162];
                rotationXBits[i] = x[i + 226];
                rotationYBits[i] = x[i + 290];
                rotationZBits[i] = x[i + 354];
                rotationABits[i] = x[i + 418];
                scaleBits[i] = x[i + 482];
            }

            std::bitset<32> typeBits;

            for (int i = 0; i < 32; ++i)
                typeBits[i] = x[i + 546];

            // Converting back to original types
            ecsID = static_cast<std::uint32_t>(ecsIdBits.to_ulong());
            signatureBits[0] = signatureBits[1] = false;
            signatureBits[0] = x[33];
            signatureBits[1] = x[32];

            pos._x = *reinterpret_cast<double*>(&posXBits);
            pos._y = *reinterpret_cast<double*>(&posYBits);
            pos._z = *reinterpret_cast<double*>(&posZBits);

            rotation._x = *reinterpret_cast<double*>(&rotationXBits);
            rotation._y = *reinterpret_cast<double*>(&rotationYBits);
            rotation._z = *reinterpret_cast<double*>(&rotationZBits);
            rotation._a = *reinterpret_cast<double*>(&rotationABits);

            scale = *reinterpret_cast<float*>(&scaleBits);

            type = static_cast<int>(typeBits.to_ulong());
        }

        Protocol getProtocol() const { return *_protocol.get(); }

    private:
        std::shared_ptr<Protocol> _protocol;

        void serializeEntity(std::ostringstream& oss, const std::bitset<578>& entity) const
        {
            oss.write(reinterpret_cast<const char*>(&entity), entity.size() / 8);
        }

        static void deserializeEntity(std::istringstream& iss, std::bitset<578>& entity)
        {
            iss.read(reinterpret_cast<char*>(&entity), entity.size() / 8);
        }

    };

} // namespace rt

#endif /* !PROTOCOL_HPP_ */
