#include "GameController.hpp"

namespace rt {

    GameController::GameController()
    {
        _initializeCommands();
        _initializeECS();
    }

    void GameController::_initializeCommands() {
        _commands["PING"] = [&](const std::string &data, const std::string &ip, const int port) {
            command_ping(data, ip, port);
        };
    }

    int GameController::exec() { 
        while (1) {
            // get data from queue
            if (!_receivedData.empty()) {
                ReceivedData data = _receivedData.front();
                commandHandler(data.data, data.ip, data.port);
                _receivedData.pop();
            }
            //std::cout << "HERE IS THE MAIN WHILE" << std::endl;
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
        std::cout << "from: " << ip << ":" << port << std::endl;
        std::cout << "data: " << data << std::endl;
        std::cout << "-------------------" << std::endl;

        try {
            std::cout << "[" << data << "] " << data.length() << std::endl;
            _commands.at(data)(data, ip, port);
        } catch (const std::out_of_range &e) {
            //_wrapper->sendTo("404", ip, port);
        }
    }

    // ECS
    void GameController::_initializeECS() {
        std::cout << "SERVER/ECS initializing..." << std::endl;

        // ECS init
        _coordinator = std::make_shared<ECS::Coordinator>();
        _coordinator->init();

        _initializeECSComponents();
        _initializeECSSystems();

        std::cout << "SERVER/ECS configured" << std::endl;
    }

    void GameController::_initializeECSComponents() {
        std::cout << "SERVER/ECS initializing components..." << std::endl;

        // ECS components
        _coordinator->registerComponent<ECS::Transform>();
        _coordinator->registerComponent<ECS::Traveling>();

        std::cout << "SERVER/ECS components configured" << std::endl;
    }

    void GameController::_initializeECSSystems() {
        std::cout << "SERVER/ECS initializing systems..." << std::endl;

        // ECS systems
        _systems._systemTraveling = _coordinator->registerSystem<ECS::TravelingSystem>();

        std::cout << "SERVER/ECS systems configured" << std::endl;
    }

    // Commands
    void GameController::command_ping(const std::string &data, const std::string &ip, const int port) {
        _wrapper->sendTo("OK", ip, port);
        std::cout << "(>) Sent information" << std::endl;
    }
}
