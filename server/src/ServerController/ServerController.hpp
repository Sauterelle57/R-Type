// ServerController.hpp
#ifndef SERVERCONTROLLER_HPP_
#define SERVERCONTROLLER_HPP_

#include "AsioWrapper.hpp"
#include "GameController.hpp"
#include <iostream>
#include <functional> // Add this include for std::function

namespace rt {

class ServerController {
public:
    using ReceiveHandler = std::function<void(const boost::system::error_code&, std::size_t)>;

    ServerController(short port);

    void run();

    void handleReceivedData(const boost::system::error_code& error, std::size_t bytes_transferred);

private:
    AsioWrapper asioWrapper;
    GameController gameController;
};

} // namespace rt

#endif /* !SERVERCONTROLLER_HPP_ */
