// UDPClient.hpp
#ifndef UDP_CLIENT_HPP_
#define UDP_CLIENT_HPP_

#include "IUdpClient.hpp"
#include <iostream>
#include <boost/asio.hpp>
#include <optional>
#include <queue>

namespace rt {

    class UdpClient : public IUdpClient {
        public:
            UdpClient(const std::string& serverIP, unsigned short serverPort, std::shared_ptr<std::queue<ReceivedMessage>> receivedMessages);

            void send(const Protocol& message) override;
            Protocol receive() override;
            void run() override;

        private:
            boost::asio::io_service ioService;
            boost::asio::ip::udp::socket socket;
            boost::asio::ip::udp::endpoint serverEndpoint;
            std::shared_ptr<std::queue<ReceivedMessage>> receivedMessages;
    };

} // namespace rt

#endif // UDP_CLIENT_HPP_
