// AsioWrapper.cpp
#include "AsioWrapper.hpp"
#include <iostream>
#include <sstream>
#include <boost/archive/text_iarchive.hpp>

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
        recvBuffer.resize(sizeof(Protocol));
        socket.async_receive_from(
            boost::asio::buffer(recvBuffer), remoteEndpoint,
            [this](const boost::system::error_code& error, std::size_t bytes_transferred) {
                handleReceive(error, bytes_transferred);
            });
    }

    void AsioWrapper::handleReceive(const boost::system::error_code& error, std::size_t bytes_transferred)
    {
        if (!error) {
            receiveHandler(error.value(), bytes_transferred);

            recvBuffer.resize(bytes_transferred);

            startReceive();
        } else {
            std::cerr << "Error receiving data: " << error.message() << std::endl;
            startReceive();
        }
    }

    void AsioWrapper::sendToByStruct(const Protocol& message, const std::string& ipAddress, unsigned short port)
    {
        try {
            boost::asio::ip::udp::endpoint destination(boost::asio::ip::address::from_string(ipAddress), port);
            boost::system::error_code ignored_ec;
            auto buffer = boost::asio::buffer(&message, sizeof(message));
            socket.send_to(buffer, destination, 0, ignored_ec);
            if (ignored_ec) {
                std::cerr << "Error sending response: " << ignored_ec.message() << std::endl;
            }
        } catch (std::exception& e) {
            std::cerr << "Exception: " << e.what() << std::endl;
        }
    }

    std::vector<char> AsioWrapper::getReceivedData() const
    {
        return recvBuffer;
    }

    Protocol AsioWrapper::getReceivedDataByStruct() const
    {
        try {
            Protocol result;

            if (recvBuffer.size() == sizeof(Protocol)) {
                std::memcpy(&result, recvBuffer.data(), sizeof(Protocol));
            } else {
                std::cerr << "Error: Incomplete data received." << std::endl;
                return Protocol();
            }

            return result;
        } catch (std::exception& e) {
            std::cerr << "Exception during deserialization: " << e.what() << std::endl;
            return Protocol();
        }
    }


    std::pair<std::string, int> AsioWrapper::getRemoteEndpoint() const
    {
        return {remoteEndpoint.address().to_string(), static_cast<int>(remoteEndpoint.port())};
    }

} // namespace rt
