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

            void run();
            void startReceive();
            void sendTo(const std::string& message, const std::string& ipAddress, unsigned short port);

            std::vector<char> getReceivedData() const;

            const std::array<char, 1024>& getRecvBuffer() const;
            std::pair<std::string, int> getRemoteEndpoint() const;

        private:
            boost::asio::io_service ioService;
            boost::asio::ip::udp::socket socket;
            boost::asio::ip::udp::endpoint remoteEndpoint;
            std::array<char, 1024> recvBuffer;

            ReceiveHandler receiveHandler;

            void handleReceive(const boost::system::error_code& error, std::size_t bytes_transferred);
    };

} // namespace rt

#endif
