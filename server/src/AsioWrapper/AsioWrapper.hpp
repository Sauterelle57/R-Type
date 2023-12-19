// AsioWrapper.hpp
#ifndef ASIOWRAPPER_HPP_
#define ASIOWRAPPER_HPP_

#include <boost/asio.hpp>
#include <functional>
#include <vector>
#include <array>
#include <string>

#include "IWrapper.hpp"

namespace rt {

    class AsioWrapper : public IWrapper {
    public:
        using ReceiveHandler = std::function<void(int, std::size_t)>;

        AsioWrapper(short port, ReceiveHandler receiveHandler);

        void run() override;
        void startReceive() override;
        void sendToByStruct(const Protocol& message, const std::string& ipAddress, unsigned short port) override;
        std::vector<char> getReceivedData() const override;
        Protocol getReceivedDataByStruct() const override;
        std::pair<std::string, int> getRemoteEndpoint() const override;

    private:
        boost::asio::io_service ioService;
        boost::asio::ip::udp::socket socket;
        boost::asio::ip::udp::endpoint remoteEndpoint;
        std::vector<char> recvBuffer;  // Store received data dynamically
        ReceiveHandler receiveHandler;

        void handleReceive(const boost::system::error_code& error, std::size_t bytes_transferred);
    };

} // namespace rt

#endif /* ASIOWRAPPER_HPP_ */
