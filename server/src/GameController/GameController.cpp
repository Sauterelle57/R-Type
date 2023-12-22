#include "GameController.hpp"
#include <sstream>
#include <string>
#include <iostream>
#include <iomanip>

#define DEBUG_GAMECONTROLLER 0 // Only for testing purposes

namespace rt {

    GameController::GameController()
    {
        _initializeCommands();
        _initializeECS();
        _clock = tls::Clock(1.0);
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
        _commands["CONNECTION_REQUEST"] = [&](const std::string &data, const std::string &ip, const int port) {
            command_request_connection(data, ip, port);
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
            if (_clock.isTimeElapsed()) {
                _systems._systemTraveling->update();
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
        _initializeECSEntities();

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

        {
            ECS::Signature signature;
            signature.set(_coordinator->getComponentType<ECS::Transform>());
            signature.set(_coordinator->getComponentType<ECS::Traveling>());
            _coordinator->setSystemSignature<ECS::TravelingSystem>(signature);
        }

        std::cout << "SERVER/ECS systems configured" << std::endl;
    }

    void GameController::_initializeECSEntities() {
        std::cout << "SERVER/ECS initializing entities..." << std::endl;

        std::cout << "SERVER/ECS entities configured" << std::endl;
    }

    ECS::Entity GameController::_createPlayer() {
        _entities.insert(_entities.end(), _coordinator->createEntity());
        _player = *_entities.rbegin();

        _coordinator->addComponent(
            *_entities.rbegin(),
            ECS::Traveling {
                .speed = {0.1, 0, 0}
            }
        );
        _coordinator->addComponent(
            *_entities.rbegin(),
            ECS::Transform {
                .position = {0, 0, 0},
                .rotation = {0, 0, 0, 0},
                .scale = 0.5f
            }
        );

        std::cout << "Player created as ID: " << _player << std::endl;
        return _player;
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

        if (DEBUG_GAMECONTROLLER) {
            if (!_clientController.checkClientIDExist(0))
                command_request_connection(data, ip, port);
            auto playerID = 0;
            std::cout << "Player ID: " << playerID << std::endl;
        } else {
            if (!_clientController.isClientExist(ip, port))
                return;
            auto playerID = _clientController.getPlayerID(ip, port);
        }

        if (iss >> command >> x >> y >> z) {
            if ((x >= -1 && x <= 1) && (y >= -1 && y <= 1) && (z >= -1 && z <= 1)) {
                std::cout << "Command: " << command << ", x: " << x << ", y: " << y << ", z: " << z << std::endl;
                auto &transform = _coordinator->getComponent<ECS::Transform>(_player);

                transform.position._x += x;
                transform.position._y += y;
                transform.position._z += z;
            }
        } else {
            std::cerr << "Error extracting values from the string." << std::endl;
        }
    }

    void GameController::command_shoot(const std::string &data, const std::string &ip, const int port) {
        //
    }

    void GameController::command_request_connection(const std::string &data, const std::string &ip, const int port) {
        if (!_clientController.isClientExist(ip, port))
            _clientController.addClient(ip, port);
        auto id = _createPlayer();
        _clientController.addPlayerID(ip, port, id);

        auto transform = _coordinator->getComponent<ECS::Transform>(_clientController.getPlayerID(ip, port));

        std::cout << "position: " << transform.position._x << ", " << transform.position._y << ", " << transform.position._z << std::endl;
        std::cout << "rotation: " << transform.rotation._x << ", " << transform.rotation._y << ", " << transform.rotation._z << ", " << transform.rotation._a << std::endl;
        std::cout << "scale: " << transform.scale << std::endl;

        std::ostringstream responseStream;
        responseStream << "CREATE " << id << " TRANSFORM " << std::fixed << std::setprecision(2)
                    << transform.position._x << " " << transform.position._y << " " << transform.position._z << " "
                    << transform.rotation._x << " " << transform.rotation._y << " " << transform.rotation._z << " "
                    << transform.rotation._a << " " << transform.scale << " PLAYER_1";

        std::string response = responseStream.str();

        _wrapper->sendTo(response, ip, port);
    }
}
