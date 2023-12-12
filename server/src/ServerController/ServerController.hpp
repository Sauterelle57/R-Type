// ServerController.hpp
#ifndef RTYPE_SERVERCONTROLLER_HPP
#define RTYPE_SERVERCONTROLLER_HPP

#include "IServerController.hpp"
#include <memory>
#include <iostream>
#include <boost/asio.hpp>

namespace rt {

    class ServerController : public IServerController {
    public:
        ServerController(short port);

        ~ServerController() = default;

        void run() override;

    private:
        boost::asio::io_service _io_service;
        boost::asio::ip::udp::socket _socket;
        boost::asio::ip::udp::endpoint _remoteEndpoint;
        std::array<char, 1024> _recvBuffer;

        void startReceive();

        void handleReceive(const boost::system::error_code& error, std::size_t bytes_transferred);

        void handleRequest(const std::string& message);
    };

} // rt

#endif //RTYPE_SERVERCONTROLLER_HPP
