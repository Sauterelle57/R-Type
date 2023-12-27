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
#include "AsioWrapper.hpp"

void signalHandler(int signum) {
    if (signum == SIGINT) {
        std::cout << "Received Ctrl+C. Stopping server..." << std::endl;
        exit(0);
    }
}

int main() {
    rt::Protocol protocol;
    protocol.id = rt::MOVE;
    protocol.event = rt::PLAYER_MOVED;
    std::string result = rt::AsioWrapper::_serializeData(protocol);
    std::cout << result.size() << std::endl;
    auto result2 = rt::AsioWrapper::_deserializeData(result);
    std::cout << result2.id << std::endl;
    std::cout << result2.event << std::endl;

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
