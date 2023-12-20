/*
** EPITECH PROJECT, 2023
** B-CPP-500-STG-5-2-rtype-noah.gosciniak
** File description:
** IUdpClient
*/

#ifndef IUDP_CLIENT_HPP_
#define IUDP_CLIENT_HPP_

#include <string>
#include <optional>
#include <memory>
#include <queue>

namespace rt {

    struct ReceivedMessage {
        std::string message;
        std::string senderIp;
        unsigned short senderPort;
    };

    class IUdpClient {
        public:
            virtual ~IUdpClient() = default;

            virtual void send(const std::string& message) = 0;
            virtual std::string receive() = 0;
            virtual void run() = 0;
    };

}

#endif // IUDP_CLIENT_HPP_