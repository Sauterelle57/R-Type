// ServerController.cpp
#include "ServerController.hpp"
#include "GameController.hpp"
#include <iostream>

namespace rt {

    ServerController::ServerController(short port)
        : asioWrapper(port, AsioWrapper::ReceiveHandler([this](int error, std::size_t bytes_transferred) {
            handleReceivedData(error, bytes_transferred);
        }))
    {
    }

    void ServerController::run()
    {
        std::cout << "Server is running..." << std::endl;

        asioWrapper.run();
    }

    void ServerController::handleReceivedData(const int error, std::size_t bytes_transferred)
    {
        if (!error) {
            std::cout << "Received data: " << asioWrapper.getReceivedData().data() << std::endl;
            this->_receivedQueue.push((ReceivedData){ asioWrapper.getReceivedData().data(), asioWrapper.getRemoteEndpoint().first, asioWrapper.getRemoteEndpoint().second });
            asioWrapper.sendTo("data", asioWrapper.getRemoteEndpoint().first, asioWrapper.getRemoteEndpoint().second);
        } else {
            std::cerr << "Error receiving data: " << error << std::endl;
        }
    }

} // namespace rt
