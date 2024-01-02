/*
** EPITECH PROJECT, 2023
** RType
** File description:
** main
*/

#include <iostream>
#include <thread>
#include <memory>
#include <csignal>
#include <array>
#include <cstring>
#include <bitset>

#include "ServerController.hpp"
#include "GameController.hpp"
#include "Protocol.hpp"

void signalHandler(int signum) {
    if (signum == SIGINT) {
        std::cout << "Received Ctrl+C. Stopping server..." << std::endl;
        exit(0);
    }
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

void convertBitsetToEntity(std::bitset<578> x)
{
    std::bitset<32> ecsIdBits;
    std::array<bool, 2> signatureBits;
    tls::Vec3 pos;
    tls::Vec4 rotation;
    float scale;
    int type;

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
    std::uint32_t ecsId = static_cast<std::uint32_t>(ecsIdBits.to_ulong());
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

    std::cout << "id : " << ecsId << std::endl;
    std::cout << "signature : " << signatureBits[0] << ", " << signatureBits[1] << std::endl;
    std::cout << "pos : " << pos._x << ", " << pos._y << ", " << pos._z << std::endl;
    std::cout << "rot : " << rotation._x << ", " << rotation._y << ", " << rotation._z << ", " << rotation._a << std::endl;
    std::cout << "scale : " << scale << std::endl;
    std::cout << "type : " << type << std::endl;
}




int main() {
    rt::ProtocolController pc;

    pc.setSender(rt::SENDER_TYPE::SERVER).setProtocol(rt::PROTOCOL_TYPE::ENTITIES);

    pc.addEntity(1, {1, 2, 3}, {0, 1, 1, 90}, .25f, rt::ENTITY_TYPE::PLAYER);
    pc.addEntity(2, {10, 11, 12}, {90, 0, 90, 180}, 1, rt::ENTITY_TYPE::ENEMY);
    pc.addEntity(3, {13, 14, 15}, {1, 1, 0, 180}, 2, rt::ENTITY_TYPE::ENEMY);
    auto str = pc.serialize();
    std::cout << str << std::endl;

    auto uncompressed = rt::ProtocolController::deserialize(str);

    std::cout << uncompressed.sender << std::endl;
    std::cout << uncompressed.protocol << std::endl;
    for (auto x : uncompressed.server.entities) {
        std::cout << x << std::endl;
        rt::ProtocolController::convertBitsetToEntity(x);
    }

    return 0;
    // rt::ProtocolController pc;
    // pc.init();

    // pc.setSender(rt::SENDER_TYPE::SERVER);
    // pc.setProtocol(rt::PROTOCOL_TYPE::ENTITIES);

    // pc.addEntity(1, {1, 2, 3}, {0, 0, 0, 90}, 0.25f, rt::ENTITY_TYPE::PLAYER);
    // pc.addEntity(2, {10, 11, 12}, {90, 0, 90, 180}, 1, rt::ENTITY_TYPE::ENEMY);
    // pc.addEntéity(3, {13, 14, 15}, {1, 1, 0, 180}, 2, rt::ENTITY_TYPE::ENEMY);

    // auto result = pc.serialize();

    // auto uncompressed = rt::ProtocolController::deserialize(result);

    // std::cout << uncompressed.sender << std::endl;
    // std::cout << uncompressed.protocol << std::endl;
    // for (auto &x : uncompressed.server.entities) {
    //     std::cout << "entity : ";
    //     std::cout << x.ECSEntity << std::endl;
    //     std::cout << "pos :" << x.position._x << ", " << x.position._y << ", " << x.position._z << std::endl;
    //     std::cout << "rotation: " << x.rotation._x << ", " << x.rotation._y << ", " << x.rotation._z << ", " << x.rotation._a << std::endl;
    //     std::cout << "scale: "  << x.scale << std::endl;
    //     std::cout << "type: " << x.entityType << std::endl;
    //     std::cout << "---------------" << std::endl;
    // }
    


    // return 0;
    std::signal(SIGINT, signalHandler);
    std::shared_ptr<rt::IGameController> gameCtrl = std::make_shared<rt::GameController>();
    std::shared_ptr<rt::IServerController> serverCtrl = std::make_shared<rt::ServerController>(1234, gameCtrl);

    gameCtrl->addWrapper(serverCtrl->getWrapper());

    std::thread gameThread([&]() {
        gameCtrl->exec();
    });

    serverCtrl->run();
    return 0;
}
