/*
** EPITECH PROJECT, 2023
** B-CPP-500-STG-5-2-rtype-noah.gosciniak
** File description:
** ServerController
*/

#include "ServerController.hpp"
#include "GameController.hpp"

namespace rt {

ServerController::ServerController(short port)
    : asioWrapper(port, [this](const boost::system::error_code& error, std::size_t bytes_transferred) {
        handleReceivedData(error, bytes_transferred);
    })
{
}

void ServerController::run()
{
    std::cout << "Server is running..." << std::endl;

    asioWrapper.run();
}

void ServerController::handleReceivedData(const boost::system::error_code& error, std::size_t bytes_transferred)
{
    if (!error) {
        std::string message(asioWrapper.getRecvBuffer().data(), bytes_transferred);
        std::cout << "Received message 2: " << message << std::endl;

        asioWrapper.sendTo("Hello from server!", asioWrapper.getRemoteEndpoint());

    } else {
        std::cerr << "Error receiving data: " << error.message() << std::endl;
    }
}

}
