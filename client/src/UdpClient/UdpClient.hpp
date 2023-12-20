#ifndef UDP_CLIENT_HPP_
#define UDP_CLIENT_HPP_

#include "IUdpClient.hpp"
#include <SFML/Network.hpp>
#include <iostream>
#include <queue>

namespace rt {

    class UdpClient : public IUdpClient {
    public:
        UdpClient() : receivedMessages(std::make_shared<std::queue<ReceivedMessage>>()) {}

        void setup(const std::string& serverIP, unsigned short serverPort, std::shared_ptr<std::queue<ReceivedMessage>> receivedMessages) {
            serverEndpoint = sf::IpAddress(serverIP);
            serverPortNumber = serverPort;
            this->receivedMessages = receivedMessages;

            if (socket.bind(0) != sf::Socket::Done) {
                std::cerr << "Error binding to a port" << std::endl;
            }
        }

        void send(const std::string& message) override {
            sf::Packet packet;
            packet << message;

            if (socket.send(packet, serverEndpoint, serverPortNumber) != sf::Socket::Done) {
                std::cerr << "Error sending message" << std::endl;
            } else {
                std::cout << "Sending message: " << message << std::endl;
            }
        }

        std::string receive() override {
            sf::Packet packet;
            sf::IpAddress sender;
            unsigned short senderPort;

            if (socket.receive(packet, sender, senderPort) != sf::Socket::Done) {
                std::cerr << "Error receiving data" << std::endl;
                return "<error>";
            } else {
                std::string receivedMessage;
                packet >> receivedMessage;

                std::cout << "Received message: " << receivedMessage << std::endl;
                return receivedMessage;
            }
        }

        void run() override {
            std::cout << "Receiving messages..." << std::endl;
            while (true) {
                std::string message = receive();
                receivedMessages->push({message, serverEndpoint.toString(), serverPortNumber});
            }
        }

    private:
        sf::UdpSocket socket;
        sf::IpAddress serverEndpoint;
        unsigned short serverPortNumber;
        std::shared_ptr<std::queue<ReceivedMessage>> receivedMessages;
    };

} // namespace rt

#endif // UDP_CLIENT_HPP_