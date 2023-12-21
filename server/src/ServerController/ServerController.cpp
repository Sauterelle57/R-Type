/*
** EPITECH PROJECT, 2023
** B-CPP-500-STG-5-2-rtype-noah.gosciniak
** File description:
** ServerController
*/

// ServerController.cpp
#include "ServerController.hpp"
#include "GameController.hpp"
#include <iostream>

namespace rt {

    ServerController::ServerController(short port, std::shared_ptr<IGameController> &gameCtrl)
        : asioWrapper(port, AsioWrapper::ReceiveHandler([this](int error, std::size_t bytes_transferred) {
            handleReceivedData(error, bytes_transferred);
        }))
    {
        _gameCtrl = gameCtrl;
    }

    void ServerController::run()
    {
        std::cout << "Server is running..." << std::endl;

        asioWrapper.run();
    }

    void ServerController::handleReceivedData(const int error, std::size_t bytes_transferred)
    {
        if (!error) {
            auto x = this->asioWrapper.getRecvBuffer();
            std::string result = std::string(x.data(), bytes_transferred);
            std::cout << "(<) Received data: [" << result << "]" << std::endl;
            //asioWrapper.sendTo("data", asioWrapper.getRemoteEndpoint().first, asioWrapper.getRemoteEndpoint().second);
            _gameCtrl->addReceivedData(result, asioWrapper.getRemoteEndpoint().first, asioWrapper.getRemoteEndpoint().second);
        } else {
            std::cerr << "Error receiving data: " << error << std::endl;
        }
    }

} // namespace rt