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
#include <mutex>
#include "Protocol.hpp"

namespace rt {
    struct ReceivedMessage {
        std::string message;
        std::string address;
        unsigned short port;
    };

    class IUdpClient {
    public:
        virtual ~IUdpClient() = default;
        virtual void setup(const std::string& serverIP, unsigned short serverPort, std::shared_ptr<std::queue<ReceivedMessage>> receivedMessages, std::shared_ptr<std::mutex> messageQueueMutex, std::shared_ptr<std::mutex> isRunningMutex) = 0;

        virtual void send(const std::string& message) = 0;
        virtual void sendStruct(rt::Protocol &protocol) = 0;

        virtual std::string receive() = 0;
        virtual rt::Protocol receiveStruct() = 0;
        virtual void run(std::shared_ptr<bool> running) = 0;
    };

}

#endif // IUDP_CLIENT_HPP_
