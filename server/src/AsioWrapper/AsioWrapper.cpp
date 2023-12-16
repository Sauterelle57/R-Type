/*
** EPITECH PROJECT, 2023
** B-CPP-500-STG-5-2-rtype-noah.gosciniak
** File description:
** AsioWrapper.cpp
*/

#include "AsioWrapper.hpp"
#include <iostream>

namespace rt {

    AsioWrapper::AsioWrapper(short port, ReceiveHandler receiveHandler)
        : socket(ioService, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), port)),
        receiveHandler(std::move(receiveHandler))
    {
        startReceive();
    }

    void AsioWrapper::run()
    {
        ioService.run();
    }

    void AsioWrapper::startReceive()
    {
        socket.async_receive_from(
            boost::asio::buffer(recvBuffer), remoteEndpoint,
            [this](const boost::system::error_code& error, std::size_t bytes_transferred) {
                handleReceive(error, bytes_transferred);
            });
    }

    void AsioWrapper::handleReceive(const boost::system::error_code& error, std::size_t bytes_transferred)
    {
        if (!error) {
            std::string message(recvBuffer.data(), bytes_transferred);
            std::cout << "Received message: " << message << std::endl;

            // Call the custom receive handler
            receiveHandler(error, bytes_transferred);

            startReceive();
        } else {
            std::cerr << "Error receiving data: " << error.message() << std::endl;
            startReceive();
        }
    }

    void AsioWrapper::sendTo(const std::string& message, const boost::asio::ip::udp::endpoint& endpoint)
    {
        boost::system::error_code ignored_ec;
        socket.send_to(boost::asio::buffer(message), endpoint, 0, ignored_ec);
        if (ignored_ec) {
            std::cerr << "Error sending response: " << ignored_ec.message() << std::endl;
        }
    }

    std::vector<char> AsioWrapper::getReceivedData() const
    {
        return std::vector<char>(recvBuffer.begin(), recvBuffer.begin() + recvBuffer.size());
    }

    const std::array<char, 1024>& AsioWrapper::getRecvBuffer() const
    {
        return recvBuffer;
    }

    const boost::asio::ip::udp::endpoint& AsioWrapper::getRemoteEndpoint() const
    {
        return remoteEndpoint;
    }

}
