#include "GameController.hpp"
#include <sstream>
#include <string>  

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
        _commands["MOVE"] = [&](const std::string &data, const std::string &ip, const int port) {
            command_move(data, ip, port);
        };
        _commands["SHOOT"] = [&](const std::string &data, const std::string &ip, const int port) {
            command_shoot(data, ip, port);
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

        std::istringstream iss(data);
        std::string command;
        iss >> command;


        try {
            std::cout << "[" << command << "] " << data.length() << std::endl;
            _commands.at(command)(data, ip, port);
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

    void GameController::command_move(const std::string &data, const std::string &ip, const int port) {
        // Assuming data is "MOVE 1 2 3"
        std::istringstream iss(data);
        std::string command;
        int x, y, z;

        if (iss >> command >> x >> y >> z) {
            if ((x >= -1 && x <= 1) && (y >= -1 && y <= 1) && (z >= -1 && z <= 1)) {
            std::cout << "Command: " << command << ", x: " << x << ", y: " << y << ", z: " << z << std::endl;
            
            _wrapper->sendTo(command, ip, port);
            }
        } else {
            std::cerr << "Error extracting values from the string." << std::endl;
        }
    }

    void GameController::command_shoot(const std::string &data, const std::string &ip, const int port) {
        //
    }
}
