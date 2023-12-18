/*
** EPITECH PROJECT, 2023
** B-CPP-500-STG-5-2-rtype-noah.gosciniak
** File description:
** UdpClient
*/

#include "UdpClient.hpp"

namespace rt {

    UdpClient::UdpClient(const std::string& serverIP, unsigned short serverPort)
        : ioService(), socket(ioService), serverEndpoint(boost::asio::ip::address::from_string(serverIP), serverPort)
    {
        socket.open(boost::asio::ip::udp::v4());
        socket.connect(serverEndpoint);
    }

    void UdpClient::send(const std::string& message)
    {
        std::cout << "Sending message: " << message << std::endl;
        socket.send(boost::asio::buffer(message));
    }

    std::string UdpClient::receive()
    {
        std::array<char, 1024> recvBuffer;
        boost::system::error_code error;

        recvBuffer.fill(0);

        size_t bytesRead = socket.receive(boost::asio::buffer(recvBuffer), 0, error);

        if (!error)
        {
            std::cout << "Received message: " << std::string(recvBuffer.data(), bytesRead) << std::endl;
            return std::string(recvBuffer.data(), bytesRead);
        }
        else
        {
            std::cerr << "Error receiving data: " << error.message() << std::endl;
            return "<error>";
        }
    }
}