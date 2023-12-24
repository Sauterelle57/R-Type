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

            ServerController(short port, std::shared_ptr<IGameController> &gameCtrl);

            void run();

            void handleReceivedData(const int error, std::size_t bytes_transferred);

            std::shared_ptr<AsioWrapper> getWrapper() { return _asioWrapper; }
        private:
            std::shared_ptr<AsioWrapper> _asioWrapper;
            std::shared_ptr<IGameController> _gameCtrl;
    };

} // namespace rt

#endif /* !SERVERCONTROLLER_HPP_ */