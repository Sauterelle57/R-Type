#include "GameController.hpp"

namespace rt {

    GameController::GameController()
    {
    }

    int GameController::exec() { 
        while (1) {
            // get data from queue
            if (!_receivedData.empty()) {
                ReceivedData data = _receivedData.front();
                commandHandler(data.data, data.ip, data.port);
                _receivedData.pop();
            }
        }
    }

    void GameController::addReceivedData(const std::string &data, const std::string &ip, const int port) {
        _receivedData.push({data, ip, port});
    }

    void GameController::addWrapper(IWrapper &wrapper) {
        _wrapper = &wrapper;
    }

    void GameController::commandHandler(const std::string &data, const std::string &ip, const int port) {
        std::cout << "-------------------" << std::endl;
        std::cout << "COMMAND HANDLER" << std::endl;
        std::cout << "data: " << data << std::endl;
        std::cout << "ip: " << ip << std::endl;
        std::cout << "port: " << port << std::endl;
        _wrapper->sendTo(data, ip, port);
        std::cout << "-------------------" << std::endl;
    }
}
