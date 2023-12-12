// ServerController.cpp
#include "ServerController.hpp"

namespace rt {

    ServerController::ServerController(short port) : _io_service(), _socket(this->_io_service, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), port))
    {
        this->startReceive();
    }

    void ServerController::run()
    {
        std::cout << "Server is running..." << std::endl;
        this->_io_service.run();
    }

    void ServerController::startReceive()
    {
        this->_socket.async_receive_from(boost::asio::buffer(this->_recvBuffer), this->_remoteEndpoint,
                [this](const boost::system::error_code& error, std::size_t bytes_transferred) {
                    this->handleReceive(error, bytes_transferred);
                });
    }

    void ServerController::handleReceive(const boost::system::error_code& error, std::size_t bytes_transferred)
    {
        if (!error) {
            std::string message(this->_recvBuffer.data(), bytes_transferred);
            std::cout << "Received message: " << message << std::endl;

            this->handleRequest(message);
            this->startReceive();
        } else {
            std::cerr << "Error receiving data: " << error.message() << std::endl;
        }
    }

    void ServerController::handleRequest(const std::string& message)
    {
        boost::system::error_code ignored_ec;

        this->_socket.send_to(boost::asio::buffer("Hello Client!"), this->_remoteEndpoint, 0, ignored_ec);
        if (ignored_ec) {
            std::cerr << "Error sending response: " << ignored_ec.message() << std::endl;
        }
    }

}
