#ifndef UDP_CLIENT_HPP_
#define UDP_CLIENT_HPP_

#include "IUdpClient.hpp"
#include <SFML/Network.hpp>
#include <iostream>
#include <queue>
#include <memory>

namespace rt {
    class UdpClient : public IUdpClient {
    public:
        UdpClient() = default;
        ~UdpClient() = default;

        void setup(const std::string& serverIP, unsigned short serverPort, std::shared_ptr<std::queue<ReceivedMessage>> receivedMessages);

        void send(const std::string& message);

        std::string receive();

        void run(std::shared_ptr<bool> running);

    private:
        sf::UdpSocket socket;
        sf::IpAddress serverEndpoint;
        unsigned short serverPortNumber{};
        std::shared_ptr<std::queue<ReceivedMessage>> receivedMessages;
    };

} // namespace rt

#endif // UDP_CLIENT_HPP_