// ServerController.cpp
#include "ServerController.hpp"
#include "GameController.hpp"
#include <iostream>

namespace rt {

    ServerController::ServerController(short port, std::shared_ptr<IGameController> &gameCtrl) {
        _asioWrapper = std::make_shared<AsioWrapper>(port, AsioWrapper::ReceiveHandler([this](int error, std::size_t bytes_transferred) {
            handleReceivedData(error, bytes_transferred);
        }));
        _gameCtrl = gameCtrl;
    }

    void ServerController::run()
    {
        std::cout << "Server is running..." << std::endl;

        _asioWrapper->run();
    }

    void ServerController::handleReceivedData(const int error, std::size_t bytes_transferred)
    {
        if (!error) {
            auto x = _asioWrapper->getRecvBuffer();
            std::string result = std::string(x.data(), bytes_transferred);
            rt::ProtocolController pc;
            auto rslt = pc.deserialize(result);
            std::cout << "(<) Received data: " << std::endl;
            std::cout << "Sender: " << rslt.sender << std::endl;
            std::cout << "Protocol: " << rslt.protocol << std::endl;
            //asioWrapper.sendTo("data", asioWrapper.getRemoteEndpoint().first, asioWrapper.getRemoteEndpoint().second);
            //_gameCtrl->addReceivedData(result, _asioWrapper->getRemoteEndpoint().first, _asioWrapper->getRemoteEndpoint().second);
            pc.init();
            _asioWrapper->sendStruct(pc.setSender(rt::SERVER).setProtocol(rt::OK).getProtocol(), _asioWrapper->getRemoteEndpoint().first, _asioWrapper->getRemoteEndpoint().second);
        } else {
            std::cerr << "Error receiving data: " << error << std::endl;
        }
    }

} // namespace rt