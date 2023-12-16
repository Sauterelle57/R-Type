/*
** EPITECH PROJECT, 2023
** B-CPP-500-STG-5-2-rtype-noah.gosciniak
** File description:
** Asiowrapper.hpp
*/

#ifndef ASIOWRAPPER_HPP_
#define ASIOWRAPPER_HPP_

#include <boost/asio.hpp>
#include <functional>
#include <vector>
#include <array>

namespace rt {

class AsioWrapper {
public:
    using ReceiveHandler = std::function<void(const boost::system::error_code&, std::size_t)>;

    AsioWrapper(short port, ReceiveHandler receiveHandler);

    void run();
    void startReceive();
    void sendTo(const std::string& message, const boost::asio::ip::udp::endpoint& endpoint);

    std::vector<char> getReceivedData() const;

    const std::array<char, 1024>& getRecvBuffer() const;
    const boost::asio::ip::udp::endpoint& getRemoteEndpoint() const;

private:
    boost::asio::io_service ioService;
    boost::asio::ip::udp::socket socket;
    boost::asio::ip::udp::endpoint remoteEndpoint;
    std::array<char, 1024> recvBuffer;

    ReceiveHandler receiveHandler;

    void handleReceive(const boost::system::error_code& error, std::size_t bytes_transferred);
};

}

#endif /* !ASIOWRAPPER_HPP_ */
