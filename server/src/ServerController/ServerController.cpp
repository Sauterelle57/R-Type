// ServerController.cpp
#include "ServerController.hpp"
#include "GameController.hpp"
#include <iostream>  // Add this include for std::cout and std::cerr
#include <boost/system/error_code.hpp>  // Add this include for boost::system::error_code

namespace rt {

ServerController::ServerController(short port)
    : asioWrapper(port, AsioWrapper::ReceiveHandler([this](int error, std::size_t bytes_transferred) {
        handleReceivedData(boost::system::error_code(error, boost::system::system_category()), bytes_transferred);
    }))
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
        std::cout << "Received data: " << asioWrapper.getReceivedData().data() << std::endl;
        asioWrapper.sendTo("Hello from server!\n", asioWrapper.getRemoteEndpoint().first, asioWrapper.getRemoteEndpoint().second);
        asioWrapper.sendTo("Server said goooooood byyyyye !\n", asioWrapper.getRemoteEndpoint().first, asioWrapper.getRemoteEndpoint().second);
        std::string data = "Your current ID : " + std::to_string(gameController.exec()) + "\n";
        asioWrapper.sendTo(data, asioWrapper.getRemoteEndpoint().first, asioWrapper.getRemoteEndpoint().second);
    } else {
        std::cerr << "Error receiving data: " << error.message() << std::endl;
    }
}

} // namespace rt
