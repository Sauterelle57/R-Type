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
#include <map>
#include "Vec3.hpp"
#include "Vec4.hpp"
#include "EntityData.hpp"

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

    // Client
    struct p_client {
        tls::Vec3 move = {0, 0, 0};
    };

    // Server
    struct p_server {
        int destroyedEntitiesSize = 0;
        std::vector<std::uint32_t> destroyedEntities; // List entities from server to client
        // std::vector<std::bitset<554>> entities; // List entities from server to client
        std::vector<rt::Entity> entities;
    };

    struct Protocol
    {
        SENDER_TYPE sender;
        PROTOCOL_TYPE protocol;
        long long packetId;

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

        ProtocolController& addEntity(std::uint32_t ECSId, tls::Vec3 position, tls::Vec4 rotation, tls::Vec3 scale, ENTITY_TYPE type, tls::BoundingBox bounds)
        {
            _protocol->sender = rt::SENDER_TYPE::SERVER;
            _protocol->protocol = rt::PROTOCOL_TYPE::ENTITIES;

            // auto bits = ProtocolController::convertEntityToBitset(ECSId, {true, true}, position, rotation, scale, type);
            rt::Entity ent = {ECSId, std::bitset<15>(0b111111111111111), position, rotation, scale, type, bounds};
            // std::cout << bits << std::endl;
            _protocol->server.entities.push_back(ent);
            return *this;
        }

        ProtocolController& deleteEntity(std::uint32_t ECSId)
        {
            _protocol->sender = rt::SENDER_TYPE::SERVER;
            _protocol->protocol = rt::PROTOCOL_TYPE::ENTITIES;

            _protocol->server.destroyedEntities.push_back(ECSId);
            return *this;
        }

        // Functions :

        std::string serialize() const
        {
            std::ostringstream oss;
            oss.write(reinterpret_cast<const char*>(&_protocol->sender), sizeof(_protocol->sender));
            oss.write(reinterpret_cast<const char*>(&_protocol->protocol), sizeof(_protocol->protocol));

            // Serialize destroyedEntitiesSize and destroyedEntities vector
            _protocol->server.destroyedEntitiesSize = _protocol->server.destroyedEntities.size();
            oss.write(reinterpret_cast<const char*>(&_protocol->server.destroyedEntitiesSize), sizeof(_protocol->server.destroyedEntitiesSize));
            oss.write(reinterpret_cast<const char*>(_protocol->server.destroyedEntities.data()), _protocol->server.destroyedEntities.size() * sizeof(std::uint32_t));


            for (const auto& entity : _protocol->server.entities)
            {
                serializeEntity(oss, entity);
            }

            return oss.str();
        }

        std::string serialize(Protocol &protocol) const
        {
            std::ostringstream oss;
            oss.write(reinterpret_cast<const char*>(&protocol.sender), sizeof(protocol.sender));
            oss.write(reinterpret_cast<const char*>(&protocol.protocol), sizeof(protocol.protocol));
            oss.write(reinterpret_cast<const char*>(&protocol.packetId), sizeof(protocol.packetId));

            // Serialize destroyedEntitiesSize and destroyedEntities vector
            protocol.server.destroyedEntitiesSize = protocol.server.destroyedEntities.size();
            oss.write(reinterpret_cast<const char*>(&protocol.server.destroyedEntitiesSize), sizeof(protocol.server.destroyedEntitiesSize));
            oss.write(reinterpret_cast<const char*>(protocol.server.destroyedEntities.data()), protocol.server.destroyedEntities.size() * sizeof(std::uint32_t));


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
            iss.read(reinterpret_cast<char*>(&deserializedData.packetId), sizeof(deserializedData.packetId));

            // Deserialize destroyedEntitiesSize and destroyedEntities vector
            iss.read(reinterpret_cast<char*>(&deserializedData.server.destroyedEntitiesSize), sizeof(deserializedData.server.destroyedEntitiesSize));
            deserializedData.server.destroyedEntities.resize(deserializedData.server.destroyedEntitiesSize);
            iss.read(reinterpret_cast<char*>(deserializedData.server.destroyedEntities.data()), deserializedData.server.destroyedEntities.size() * sizeof(std::uint32_t));


            while (iss.peek() != EOF)
            {
                rt::Entity entity;
                deserializeEntity(iss, entity);
                deserializedData.server.entities.push_back(entity);
            }

            return deserializedData;
        }

        static std::string convertEntityToBinaryString(std::uint32_t ecsId, std::array<bool, 3> signature, tls::Vec3 pos, tls::Vec4 rotation, tls::Vec3 scale, ENTITY_TYPE type)
        {
            std::ostringstream oss;

            // Writing binary data directly to the stream
            oss.write(reinterpret_cast<const char*>(&ecsId), sizeof(ecsId));
            for (const auto& value : signature) {
                oss.write(reinterpret_cast<const char*>(&value), sizeof(value));
            }
            oss.write(reinterpret_cast<const char*>(&pos), sizeof(pos));
            if (signature[0])
                oss.write(reinterpret_cast<const char*>(&rotation), sizeof(rotation));
            // oss.write(reinterpret_cast<const char*>(&rotation), sizeof(rotation));
            if (signature[1])
                oss.write(reinterpret_cast<const char*>(&scale), sizeof(scale));
            // oss.write(reinterpret_cast<const char*>(&scale), sizeof(scale));
            if (signature[2])
                oss.write(reinterpret_cast<const char*>(&type), sizeof(type));
            // oss.write(reinterpret_cast<const char*>(&type), sizeof(type));

            return oss.str();
        }

        static rt::Entity convertBinaryStringToEntity(const std::string& data)
        {
            std::istringstream iss(data);
            rt::Entity entity;

            // Reading binary data directly from the stream
            iss.read(reinterpret_cast<char*>(&entity.ECSEntity), sizeof(entity.ECSEntity));
            iss.read(reinterpret_cast<char*>(&entity.signature), sizeof(entity.signature));
            iss.read(reinterpret_cast<char*>(&entity.position), sizeof(entity.position));
            if (entity.signature[0])
                iss.read(reinterpret_cast<char*>(&entity.rotation), sizeof(entity.rotation));
            else
                entity.rotation = {-1, -1, -1, -1};
            if (entity.signature[1])
                iss.read(reinterpret_cast<char*>(&entity.scale), sizeof(entity.scale));
            else
                entity.scale = {-1.0, -1.0, -1.0};
            if (entity.signature[2])
                iss.read(reinterpret_cast<char*>(&entity.entityType), sizeof(entity.entityType));
            else
                entity.entityType = rt::ENTITY_TYPE::PLAYER;

            return entity;
        }


        std::bitset<554> convertEntityToBitset(std::uint32_t ecsId, std::array<bool, 3> signature, tls::Vec3 pos, tls::Vec4 rotation, tls::Vec3 scale, ENTITY_TYPE type)
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

            std::bitset<64> scaleXBits(*reinterpret_cast<uint64_t*>(&scale._x));
            std::bitset<64> scaleYBits(*reinterpret_cast<uint64_t*>(&scale._y));
            std::bitset<64> scaleZBits(*reinterpret_cast<uint64_t*>(&scale._z));

            std::bitset<8> typeBits(static_cast<std::uint8_t>(type));

            std::bitset<554> result;

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
                result.set(i + 482, scaleXBits[i]);
                result.set(i + 546, scaleYBits[i]);
                result.set(i + 610, scaleZBits[i]);
            }

            for (int i = 0; i < 8; ++i)
                result.set(i + 674, typeBits[i]);

            return result;
        }

        void changeEntityTypeInBitset(std::bitset<554> &x, rt::ENTITY_TYPE type)
        {
            std::bitset<8> typeBits(static_cast<std::uint8_t>(type));

            for (int i = 0; i < 8; ++i)
                x.set(i + 674, typeBits[i]);
        }

        static std::uint32_t getECSIdFromBitset(std::bitset<554> x)
        {
            std::bitset<32> ecsIdBits;
            std::uint32_t ecsID;

            for (int i = 0; i < 32; ++i)
                ecsIdBits[i] = x[i];
            
            ecsID = static_cast<std::uint32_t>(ecsIdBits.to_ulong());
        
            return ecsID;
        }

        static void convertBitsetToEntity(std::bitset<554> x, std::uint32_t &ecsID, tls::Vec3 &pos, tls::Vec4 &rotation, tls::Vec3 &scale, int &type)
        {
            std::bitset<32> ecsIdBits;
            std::array<bool, 3> signatureBits;

            // Extracting bits individually
            for (int i = 0; i < 32; ++i)
                ecsIdBits[i] = x[i];

            for (int i = 0; i < 2; ++i)
                signatureBits[i] = x[i + 32];

            std::bitset<64> posXBits, posYBits, posZBits;
            std::bitset<64> rotationXBits, rotationYBits, rotationZBits, rotationABits;
            std::bitset<64> scaleXBits, scaleYBits, scaleZBits;;

            for (int i = 0; i < 64; ++i)
            {
                posXBits[i] = x[i + 34];
                posYBits[i] = x[i + 98];
                posZBits[i] = x[i + 162];
                rotationXBits[i] = x[i + 226];
                rotationYBits[i] = x[i + 290];
                rotationZBits[i] = x[i + 354];
                rotationABits[i] = x[i + 418];
                scaleXBits[i] = x[i + 482];
                scaleYBits[i] = x[i + 546];
                scaleZBits[i] = x[i + 610];
            }

            std::bitset<32> typeBits;

            for (int i = 0; i < 32; ++i)
                typeBits[i] = x[i + 674];

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

            scale._x = *reinterpret_cast<double*>(&scaleXBits);
            scale._y = *reinterpret_cast<double*>(&scaleYBits);
            scale._z = *reinterpret_cast<double*>(&scaleZBits);

            type = static_cast<ENTITY_TYPE>(static_cast<std::uint8_t>(typeBits.to_ulong()));
        }

        Protocol getProtocol() const { return *_protocol.get(); }

    private:
        std::shared_ptr<Protocol> _protocol;

        void serializeEntity(std::ostringstream& oss, const Entity& entity) const
        {
            // Serialize ECSEntity
            oss.write(reinterpret_cast<const char*>(&entity.ECSEntity), sizeof(entity.ECSEntity));

            // Serialize signature
            std::bitset<15> signature = entity.signature;
            std::uint16_t signatureValue = static_cast<std::uint16_t>(signature.to_ulong());
            oss.write(reinterpret_cast<const char*>(&signatureValue), sizeof(signatureValue));

            // Serialize position
            if (entity.signature[0])
                oss.write(reinterpret_cast<const char*>(&entity.position._x), sizeof(entity.position._x));
            if (entity.signature[1])
                oss.write(reinterpret_cast<const char*>(&entity.position._y), sizeof(entity.position._y));
            if (entity.signature[2])
                oss.write(reinterpret_cast<const char*>(&entity.position._z), sizeof(entity.position._z));



            // Serialize rotation
            if (entity.signature[3])
                oss.write(reinterpret_cast<const char*>(&entity.rotation._x), sizeof(entity.rotation._x));
            if (entity.signature[4])
                oss.write(reinterpret_cast<const char*>(&entity.rotation._y), sizeof(entity.rotation._y));
            if (entity.signature[5])
                oss.write(reinterpret_cast<const char*>(&entity.rotation._z), sizeof(entity.rotation._z));
            if (entity.signature[6])
                oss.write(reinterpret_cast<const char*>(&entity.rotation._a), sizeof(entity.rotation._a));

            // Serialize scale
            if (entity.signature[7])
                oss.write(reinterpret_cast<const char*>(&entity.scale._x), sizeof(entity.scale._x));
            if (entity.signature[8])
                oss.write(reinterpret_cast<const char*>(&entity.scale._y), sizeof(entity.scale._y));
            if (entity.signature[9])
                oss.write(reinterpret_cast<const char*>(&entity.scale._z), sizeof(entity.scale._z));

            // Serialize entityType
            if (entity.signature[10])
                oss.write(reinterpret_cast<const char*>(&entity.entityType), sizeof(entity.entityType));

            oss.write(reinterpret_cast<const char*>(&entity.bounds.min._x), sizeof(entity.bounds.min._x));
            oss.write(reinterpret_cast<const char*>(&entity.bounds.min._y), sizeof(entity.bounds.min._y));
            oss.write(reinterpret_cast<const char*>(&entity.bounds.min._z), sizeof(entity.bounds.min._z));
            oss.write(reinterpret_cast<const char*>(&entity.bounds.max._x), sizeof(entity.bounds.max._x));
            oss.write(reinterpret_cast<const char*>(&entity.bounds.max._y), sizeof(entity.bounds.max._y));
            oss.write(reinterpret_cast<const char*>(&entity.bounds.max._z), sizeof(entity.bounds.max._z));
        }

        static void deserializeEntity(std::istringstream& iss, rt::Entity& entity)
        {
            // Deserialize ECSEntity
            iss.read(reinterpret_cast<char*>(&entity.ECSEntity), sizeof(entity.ECSEntity));

            // Deserialize signature
            std::uint16_t signatureValue;
            iss.read(reinterpret_cast<char*>(&signatureValue), sizeof(signatureValue));
            std::bitset<15> signature(signatureValue);
            entity.signature = signature;

            // Deserialize position
            if (entity.signature[0])
                iss.read(reinterpret_cast<char*>(&entity.position._x), sizeof(entity.position._x));
            if (entity.signature[1])
                iss.read(reinterpret_cast<char*>(&entity.position._y), sizeof(entity.position._y));
            if (entity.signature[2])
                iss.read(reinterpret_cast<char*>(&entity.position._z), sizeof(entity.position._z));

            // Deserialize rotation
            if (entity.signature[3])
                iss.read(reinterpret_cast<char*>(&entity.rotation._x), sizeof(entity.rotation._x));
            if (entity.signature[4])
                iss.read(reinterpret_cast<char*>(&entity.rotation._y), sizeof(entity.rotation._y));
            if (entity.signature[5])
                iss.read(reinterpret_cast<char*>(&entity.rotation._z), sizeof(entity.rotation._z));
            if (entity.signature[6])
                iss.read(reinterpret_cast<char*>(&entity.rotation._a), sizeof(entity.rotation._a));

            // Deserialize scale
            if (entity.signature[7]) {
                iss.read(reinterpret_cast<char*>(&entity.scale._x), sizeof(entity.scale._x));
            }
            if (entity.signature[8]) {
                iss.read(reinterpret_cast<char*>(&entity.scale._y), sizeof(entity.scale._y));
            }
            if (entity.signature[9]) {
                iss.read(reinterpret_cast<char*>(&entity.scale._z), sizeof(entity.scale._z));
            }

            // Deserialize entityType
            if (entity.signature[10]) {
                iss.read(reinterpret_cast<char*>(&entity.entityType), sizeof(entity.entityType));
            }

            iss.read(reinterpret_cast<char*>(&entity.bounds.min._x), sizeof(entity.bounds.min._x));
            iss.read(reinterpret_cast<char*>(&entity.bounds.min._y), sizeof(entity.bounds.min._y));
            iss.read(reinterpret_cast<char*>(&entity.bounds.min._z), sizeof(entity.bounds.min._z));
            iss.read(reinterpret_cast<char*>(&entity.bounds.max._x), sizeof(entity.bounds.max._x));
            iss.read(reinterpret_cast<char*>(&entity.bounds.max._y), sizeof(entity.bounds.max._y));
            iss.read(reinterpret_cast<char*>(&entity.bounds.max._z), sizeof(entity.bounds.max._z));
        }

    };

} // namespace rt

#endif /* !PROTOCOL_HPP_ */
