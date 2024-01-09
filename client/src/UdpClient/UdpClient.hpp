#ifndef UDP_CLIENT_HPP_
#define UDP_CLIENT_HPP_

#include "IUdpClient.hpp"
#include "Protocol.hpp"
#include <SFML/Network.hpp>
#include <iostream>
#include <queue>
#include <memory>

namespace rt {
    class UdpClient : public IUdpClient {
    public:
        UdpClient() = default;
        ~UdpClient() = default;


        void setup(const std::string& serverIP, unsigned short serverPort, std::shared_ptr<std::queue<ReceivedMessage>> receivedMessages, std::shared_ptr<std::mutex> messageQueueMutex, std::shared_ptr<std::mutex> isRunningMutex);

        void send(const std::string& message);
        void sendStruct(rt::Protocol &protocol);

        std::string receive();
        rt::Protocol receiveStruct();

        void run(std::shared_ptr<bool> running);

    private:
        sf::UdpSocket socket;
        sf::IpAddress serverEndpoint;
        unsigned short serverPortNumber{};

        std::shared_ptr<std::queue<ReceivedMessage>> _receivedMessages;
        std::shared_ptr<std::mutex> _messageQueueMutex;
        std::shared_ptr<bool> _isSetup = std::make_shared<bool>(false);
        std::shared_ptr<std::mutex> _isSetupMutex = std::make_shared<std::mutex>();
        std::shared_ptr<std::mutex> _isRunningMutex;
    };

} // namespace rt

#endif // UDP_CLIENT_HPP_