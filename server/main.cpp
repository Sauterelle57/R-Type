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

#include "ServerController.hpp"
#include "GameController.hpp"
#include "Protocol.hpp"

void signalHandler(int signum) {
    if (signum == SIGINT) {
        std::cout << "Received Ctrl+C. Stopping server..." << std::endl;
        exit(0);
    }
}

int main() {
    rt::ProtocolController pc;
    pc.init();

    pc.setSender(rt::SENDER_TYPE::SERVER);
    pc.setProtocol(rt::PROTOCOL_TYPE::ENTITIES);

    pc.addEntity(1, {1, 2, 3}, {0, 0, 0, 90}, 0.25f, rt::ENTITY_TYPE::PLAYER);
    pc.addEntity(2, {10, 11, 12}, {90, 0, 90, 180}, 1, rt::ENTITY_TYPE::ENEMY);
    pc.addEntity(3, {13, 14, 15}, {1, 1, 0, 180}, 2, rt::ENTITY_TYPE::ENEMY);

    auto result = pc.serialize();

    auto uncompressed = rt::ProtocolController::deserialize(result);

    std::cout << uncompressed.sender << std::endl;
    std::cout << uncompressed.protocol << std::endl;
    for (auto &x : uncompressed.server.entities) {
        std::cout << "entity : ";
        std::cout << x.ECSEntity << std::endl;
        std::cout << "pos :" << x.position._x << ", " << x.position._y << ", " << x.position._z << std::endl;
        std::cout << "rotation: " << x.rotation._x << ", " << x.rotation._y << ", " << x.rotation._z << ", " << x.rotation._a << std::endl;
        std::cout << "scale: "  << x.scale << std::endl;
        std::cout << "type: " << x.entityType << std::endl;
        std::cout << "---------------" << std::endl;
    }
    


    return 0;
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
