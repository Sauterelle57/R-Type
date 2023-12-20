//
// Created by noahg on 20/12/2023.
//

#include "UdpClient.hpp"

namespace rt {
    void UdpClient::setup(const std::string& serverIP, unsigned short serverPort, std::shared_ptr<std::queue<ReceivedMessage>> receivedMessages) {
        serverEndpoint = sf::IpAddress(serverIP);
        serverPortNumber = serverPort;
        this->receivedMessages = receivedMessages;

        if (socket.bind(0) != sf::Socket::Done) {
            std::cerr << "Error binding to a port" << std::endl;
        }
    }

    void UdpClient::send(const std::string& message) {
        sf::Packet packet;
        packet.append(message.c_str(), message.size());


        if (socket.send(packet, serverEndpoint, serverPortNumber) != sf::Socket::Done) {
            std::cerr << "Error sending message" << std::endl;
        } else {
            std::cout << "Sending message: " << message << std::endl;
        }
    }

    std::string UdpClient::receive() {
        sf::Packet packet;
        sf::IpAddress sender;
        unsigned short senderPort;

        if (socket.receive(packet, sender, senderPort) != sf::Socket::Done) {
            std::cerr << "Error receiving data" << std::endl;
            return "<error>";
        } else {
            // Get the data directly from the packet
            const void* data = packet.getData();
            std::size_t dataSize = packet.getDataSize();
            // Print debug information
            std::cout << "Received packet size: " << dataSize << " bytes" << std::endl;
            // Convert the received data to a string
            std::string receivedMessage(static_cast<const char*>(data), dataSize);
            // Print the string representation of the received data
            std::cout << "Received message: " << receivedMessage << std::endl;

            return receivedMessage;
        }
    }

    void UdpClient::run() {
        std::cout << "Receiving messages..." << std::endl;
        while (true) {
            std::string message = receive();
            std::cout << "message..." << std::endl;
            receivedMessages->push({message, serverEndpoint.toString(), serverPortNumber});
        }
    }
} // namespace rt