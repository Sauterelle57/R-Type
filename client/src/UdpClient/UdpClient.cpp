// UDPClient.cpp
#include "UdpClient.hpp"
#include <iostream>

namespace rt {

    UdpClient::UdpClient(const std::string& serverIP, unsigned short serverPort, std::shared_ptr<std::queue<ReceivedMessage>> receivedMessages)
        : ioService(), socket(ioService), serverEndpoint(boost::asio::ip::udp::endpoint(boost::asio::ip::address::from_string(serverIP), serverPort))
    {
        socket.open(boost::asio::ip::udp::v4());
        this->receivedMessages = receivedMessages;
    }

    void UdpClient::send(const Protocol& message)
    {
        try {
            // Send the raw data of the Protocol struct
            socket.send_to(boost::asio::buffer(&message, sizeof(Protocol)), serverEndpoint);
        } catch (std::exception& e) {
            std::cerr << "Exception: " << e.what() << std::endl;
        }
    }

    Protocol UdpClient::receive()
    {
        try {
            Protocol receivedMessage;
            boost::system::error_code error;

            // Receive the raw data of the Protocol struct
            size_t bytesRead = socket.receive_from(boost::asio::buffer(&receivedMessage, sizeof(Protocol)), serverEndpoint, 0, error);

            if (!error)
            {
                // Handle receivedMessage as needed
                std::cout << "Received message of size " << bytesRead << " bytes." << std::endl;
            }
            else
            {
                std::cerr << "Error receiving data: " << error.message() << std::endl;
            }

            return receivedMessage;
        } catch (std::exception& e) {
            std::cerr << "Exception during receiving: " << e.what() << std::endl;
            return Protocol(); // Return a default-constructed Protocol in case of exception
        }
    }

    void UdpClient::run()
    {
        std::cout << "Receiving messages..." << std::endl;
        while (true)
        {
            Protocol receivedMessage = receive();
            // Handle receivedMessage as needed
            std::cout << "Received message: " << std::endl;
            //receivedMessages->push({receivedMessage, serverEndpoint.address().to_string(), serverEndpoint.port()});
        }
    }

} // namespace rt
