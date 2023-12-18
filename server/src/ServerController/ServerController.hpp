// ServerController.hpp
#ifndef SERVERCONTROLLER_HPP_
#define SERVERCONTROLLER_HPP_

#include "AsioWrapper.hpp"
#include "GameController.hpp"
#include <iostream>
#include <functional>
#include <queue>
#include "IServerController.hpp"

namespace rt {

    class ServerController : public IServerController {
        public:
            using ReceiveHandler = std::function<void(const boost::system::error_code&, std::size_t)>;

            ServerController(short port);

            void run();

            void handleReceivedData(const int error, std::size_t bytes_transferred);


            std::queue<ReceivedData> &getReceivedQueue() { return _receivedQueue; }
            IWrapper &getWrapper() { return asioWrapper; }
        private:
            GameController gameController;
            std::queue<ReceivedData> _receivedQueue;
            AsioWrapper asioWrapper;
    };

} // namespace rt

#endif /* !SERVERCONTROLLER_HPP_ */
