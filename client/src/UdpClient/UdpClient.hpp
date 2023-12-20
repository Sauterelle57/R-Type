#ifndef UDP_CLIENT_HPP_
#define UDP_CLIENT_HPP_

#include "IUdpClient.hpp"
#include <iostream>
#include <boost/asio.hpp>
#include <queue>

namespace rt {

    class UdpClient : public IUdpClient {
    public:
        UdpClient() : ioService(), socket(ioService), serverEndpoint(boost::asio::ip::udp::v4(), 0) {}

        void setup(const std::string& serverIP, unsigned short serverPort, std::shared_ptr<std::queue<ReceivedMessage>> receivedMessages) {
            serverEndpoint = boost::asio::ip::udp::endpoint(boost::asio::ip::address::from_string(serverIP), serverPort);
            socket.open(boost::asio::ip::udp::v4());
            socket.connect(serverEndpoint);
            this->receivedMessages = receivedMessages;
        }

        void send(const std::string& message) override {
            try {
                std::cout << "Sending message: " << message << std::endl;
                socket.send(boost::asio::buffer(message));
            } catch (std::exception& e) {
                std::cerr << "Exception: " << e.what() << std::endl;
            }
        }

        std::string receive() override {
            std::array<char, 1024> recvBuffer;
            boost::system::error_code error;

            recvBuffer.fill(0);

            size_t bytesRead = socket.receive(boost::asio::buffer(recvBuffer), 0, error);

            if (!error) {
                std::cout << "Received message: " << std::string(recvBuffer.data(), bytesRead) << std::endl;
                return std::string(recvBuffer.data(), bytesRead);
            } else {
                std::cerr << "Error receiving data: " << error.message() << std::endl;
                return "<error>";
            }
        }

        void run() override {
            std::cout << "Receiving messages..." << std::endl;
            while (true) {
                std::string message = receive();
                receivedMessages->push({message, serverEndpoint.address().to_string(), serverEndpoint.port()});
            }
        }

    private:
        boost::asio::io_service ioService;
        boost::asio::ip::udp::socket socket;
        boost::asio::ip::udp::endpoint serverEndpoint;
        std::shared_ptr<std::queue<ReceivedMessage>> receivedMessages;
    };

}

#endif // UDP_CLIENT_HPP_
