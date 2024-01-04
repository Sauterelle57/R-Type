
#include "AsioWrapper.hpp"
#include <iostream>

namespace rt {

    AsioWrapper::AsioWrapper(short port, ReceiveHandler receiveHandler)
        : socket(ioService, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), port)),
        receiveHandler(std::move(receiveHandler))
    {
        startReceive();
    }

    void AsioWrapper::run()
    {
        ioService.run();
    }

    void AsioWrapper::startReceive()
    {
        recvBuffer.fill(0);
        socket.async_receive_from(
            boost::asio::buffer(recvBuffer), remoteEndpoint,
            [this](const boost::system::error_code& error, std::size_t bytes_transferred) {
                handleReceive(error, bytes_transferred);
            });
    }

    void AsioWrapper::handleReceive(const boost::system::error_code& error, std::size_t bytes_transferred)
    {
        if (!error) {
            std::string message(recvBuffer.data(), bytes_transferred);
            //std::cout << "(<) Received message: [" << message << "]" << std::endl;

            // Call the custom receive handler
            // assign recvBuffer to message
            receiveHandler(error.value(), bytes_transferred);

            startReceive();
        } else {
            std::cerr << "Error receiving data: " << error.message() << std::endl;
            startReceive();
        }
    }

    void AsioWrapper::sendTo(const std::string& message, const std::string& ipAddress, unsigned short port)
    {
        try {
            boost::asio::ip::udp::endpoint destination(boost::asio::ip::address::from_string(ipAddress), port);
            boost::system::error_code ignored_ec;
            socket.send_to(boost::asio::buffer(message), destination, 0, ignored_ec);
            if (ignored_ec) {
                std::cerr << "Error sending response: " << ignored_ec.message() << std::endl;
            }
        } catch (std::exception& e) {
            std::cerr << "Exception: " << e.what() << std::endl;
        }
    }

    void AsioWrapper::sendStruct(Protocol &protocol, const std::string& ipAddress, unsigned short port)
    {
        try {
            boost::asio::ip::udp::endpoint destination(boost::asio::ip::address::from_string(ipAddress), port);
            boost::system::error_code ignored_ec;
            rt::ProtocolController pc;

            std::string tosend = pc.serialize(protocol);

            socket.send_to(boost::asio::buffer(tosend), destination, 0, ignored_ec);
            if (ignored_ec) {
                std::cerr << "Error sending response: " << ignored_ec.message() << std::endl;
            }
        } catch (std::exception& e) {
            std::cerr << "Exception: " << e.what() << std::endl;
        }
    }

    std::vector<char> AsioWrapper::getReceivedData() const
    {
        return std::vector<char>(recvBuffer.begin(), recvBuffer.begin() + recvBuffer.size());
    }

    const std::array<char, 2048>& AsioWrapper::getRecvBuffer() const
    {
        return recvBuffer;
    }

    std::pair<std::string, int> AsioWrapper::getRemoteEndpoint() const
    {
        return {remoteEndpoint.address().to_string(), static_cast<int>(remoteEndpoint.port())};
    }

} // namespace rt