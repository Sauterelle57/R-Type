/*
** EPITECH PROJECT, 2023
** B-CPP-500-STG-5-2-rtype-noah.gosciniak
** File description:
** UdpClient
*/

#ifndef UDP_CLIENT_HPP_
#define UDP_CLIENT_HPP_

#include "IUdpClient.hpp"
#include <iostream>
#include <boost/asio.hpp>
#include <optional>

namespace rt {

    class UdpClient : public IUdpClient {
        public:
            UdpClient(const std::string& serverIP, unsigned short serverPort, std::shared_ptr<std::queue<ReceivedMessage>> receivedMessages);

            void send(const std::string& message) override;
            std::string receive() override;
            void run() override;

        private:
            boost::asio::io_service ioService;
            boost::asio::ip::udp::socket socket;
            boost::asio::ip::udp::endpoint serverEndpoint;
            std::shared_ptr<std::queue<ReceivedMessage>> receivedMessages;
    };

}

#endif // UDP_CLIENT_HPP_