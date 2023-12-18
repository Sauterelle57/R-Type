// ServerController.hpp
#ifndef SERVERCONTROLLER_HPP_
#define SERVERCONTROLLER_HPP_

#include "AsioWrapper.hpp"
#include "GameController.hpp"
#include <iostream>
#include <functional>
#include <queue>

namespace rt {

class ServerController {
public:
    using ReceiveHandler = std::function<void(const boost::system::error_code&, std::size_t)>;

    ServerController(short port);

    void run();

    void handleReceivedData(const int error, std::size_t bytes_transferred);

    struct ReceivedData {
        std::string data;
        std::string ip;
        int port;
    };

    struct SendData {
        std::string data;
        std::string ip;
        int port;
    };

    std::queue<ReceivedData> _receivedQueue;
    std::queue<SendData> _sendQueue;

private:
    AsioWrapper asioWrapper;
    GameController gameController;
};

} // namespace rt

#endif /* !SERVERCONTROLLER_HPP_ */
