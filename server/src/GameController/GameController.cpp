#include "GameController.hpp"
#include <sstream>
#include <string>
#include <iostream>
#include <iomanip>

#define DEBUG_GAMECONTROLLER 0 // Only for testing purposes

namespace rt {

    GameController::GameController()
    {
        _cameraInit = false;
        _initializeCommands();
        _initializeECS();
        _clock = tls::Clock(0.006);
        _clientController = std::make_shared<ClientController>();
    }

    void GameController::_initializeCommands() {
        _commands["PING"] = [&](const std::string &data, const std::string &ip, const int port) {
            commandPing(data, ip, port);
        };
        _commands["MOVE"] = [&](const std::string &data, const std::string &ip, const int port) {
            commandMove(data, ip, port);
        };
        _commands["SHOOT"] = [&](const std::string &data, const std::string &ip, const int port) {
            commandShoot(data, ip, port);
        };
        _commands["CONNECTION_REQUEST"] = [&](const std::string &data, const std::string &ip, const int port) {
            commandRequestConnection(data, ip, port);
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
                _systems._systemProjectile->update(_camera);
                _systems._systemShoot->update();
                _systems._systemCollider->update();
                _systems._systemClientUpdater->update();
//                _eventController();
//                for (auto &client: _clientController->getClients()) {
//                    auto &collider = _coordinator->getComponent<ECS::Collider>();
//                    collider.velocity = {0.01, 0, 0};
//                }
            }
        }
    }

    void GameController::addReceivedData(const std::string &data, const std::string &ip, const int port) {
        _receivedData.push({data, ip, port});
    }

    void GameController::addWrapper(std::shared_ptr<IWrapper> wrapper) {
        _wrapper = wrapper;
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

    void GameController::_initializeECS() {
        std::cout << "SERVER/ECS initializing..." << std::endl;

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
        _coordinator->registerComponent<ECS::Weapon>();
        _coordinator->registerComponent<ECS::Projectile>();
        _coordinator->registerComponent<ECS::Collider>();
        _coordinator->registerComponent<ECS::Type>();
        _coordinator->registerComponent<ECS::ClientUpdater>();

        std::cout << "SERVER/ECS components configured" << std::endl;
    }

    void GameController::_initializeECSSystems() {
        std::cout << "SERVER/ECS initializing systems..." << std::endl;

        // ECS systems
        _systems._systemTraveling = _coordinator->registerSystem<ECS::TravelingSystem>();
        _systems._systemShoot = _coordinator->registerSystem<ECS::Shoot>();
        _systems._systemProjectile = _coordinator->registerSystem<ECS::ProjectileSystem>();
        _systems._systemCollider = _coordinator->registerSystem<ECS::ColliderSystem>();
        _systems._systemClientUpdater = _coordinator->registerSystem<ECS::ClientUpdaterSystem>();

        {
            ECS::Signature signature;
            signature.set(_coordinator->getComponentType<ECS::Transform>());
            signature.set(_coordinator->getComponentType<ECS::Traveling>());
            _coordinator->setSystemSignature<ECS::TravelingSystem>(signature);
        }

        {
            ECS::Signature signature;
            signature.set(_coordinator->getComponentType<ECS::Transform>());
            signature.set(_coordinator->getComponentType<ECS::Projectile>());
            signature.set(_coordinator->getComponentType<ECS::Type>());
            signature.set(_coordinator->getComponentType<ECS::ClientUpdater>());
            _coordinator->setSystemSignature<ECS::ProjectileSystem>(signature);
        }

        {
           ECS::Signature signature;
           signature.set(_coordinator->getComponentType<ECS::Transform>());
           signature.set(_coordinator->getComponentType<ECS::Weapon>());
            signature.set(_coordinator->getComponentType<ECS::ClientUpdater>());
            _coordinator->setSystemSignature<ECS::Shoot>(signature);
        }

        {
           ECS::Signature signature;
           signature.set(_coordinator->getComponentType<ECS::Transform>());
           signature.set(_coordinator->getComponentType<ECS::Collider>());
            signature.set(_coordinator->getComponentType<ECS::Type>());
            signature.set(_coordinator->getComponentType<ECS::ClientUpdater>());
            _coordinator->setSystemSignature<ECS::ColliderSystem>(signature);
        }

        {
            ECS::Signature signature;
            signature.set(_coordinator->getComponentType<ECS::Transform>());
            signature.set(_coordinator->getComponentType<ECS::Type>());
            signature.set(_coordinator->getComponentType<ECS::ClientUpdater>());
            _coordinator->setSystemSignature<ECS::ClientUpdaterSystem>(signature);
        }

        std::cout << "SERVER/ECS systems configured" << std::endl;
    }

    void GameController::_initializeECSEntities() {
        std::cout << "SERVER/ECS initializing entities..." << std::endl;

        _entities.insert(_entities.end(), _coordinator->createEntity());
        _camera = *_entities.rbegin();

        _coordinator->addComponent(
            *_entities.rbegin(),
            ECS::Traveling {
                .speed = {0.01, 0, 0}
            }
        );
        _coordinator->addComponent(
            *_entities.rbegin(),
            ECS::Transform {
                .position = {0.0, 10, 100},
                .rotation = {0, 0, 0, 0},
                .scale = 0.5f
            }
        );
        _coordinator->addComponent(
            *_entities.rbegin(),
            ECS::Type {
                .name = "CAMERA"
            }
        );
        _coordinator->addComponent(
            *_entities.rbegin(),
            ECS::ClientUpdater {
                .wrapper = _wrapper,
                .clientController = _clientController
            }
        );

        _createTile();
        _createBreakableTile();

        std::cout << "SERVER/ECS entities configured" << std::endl;
    }

    void GameController::_createPlayer(std::string ip, int port) {
        _entities.insert(_entities.end(), _coordinator->createEntity());

        _coordinator->addComponent(
            *_entities.rbegin(),
            ECS::Traveling {
                .speed = {0.01, 0, 0}
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
        _coordinator->addComponent(
           *_entities.rbegin(),
           ECS::Weapon {
               .damage = 1,
               .speed = 1,
               .durability = 1,
               .create_projectile = ECS::Shoot::basicShot
           }
       );
       _coordinator->addComponent(
           *_entities.rbegin(),
           ECS::Collider {
               .team = 0,
               .breakable = true,
               .movable = true,
               .velocity = {0.01, 0, 0},
           }
        );
        _coordinator->addComponent(
            *_entities.rbegin(),
            ECS::Type {
                .name = "PLAYER",
                .different = true,
                .ip = ip,
                .port = port
            }
        );
        _coordinator->addComponent(
            *_entities.rbegin(),
            ECS::ClientUpdater {
                .wrapper = _wrapper,
                .clientController = _clientController
            }
        );
    }

    void GameController::_createEnnemy() {
        _entities.insert(_entities.end(), _coordinator->createEntity());

        _coordinator->addComponent(
            *_entities.rbegin(),
            ECS::Traveling {
                .speed = {0.005, 0, 0}
            }
        );
        _coordinator->addComponent(
            *_entities.rbegin(),
            ECS::Transform {
                .position = {40, 0, 0},
                .rotation = {0, 0, 0, 0},
                .scale = .1f
            }
        );
        _coordinator->addComponent(
           *_entities.rbegin(),
           ECS::Weapon {
               .damage = 1,
               .speed = 1,
               .durability = 1,
               .create_projectile = ECS::Shoot::basicShot
           }
       );
        _coordinator->addComponent(
           *_entities.rbegin(),
           ECS::Collider {
               .team = 1,
               .breakable = true,
               .movable = true,
               .velocity = {0.005, 0, 0}
           }
        );
        _coordinator->addComponent(
            *_entities.rbegin(),
            ECS::Type {
                .name = "ENEMY"
            }
        );
        _coordinator->addComponent(
            *_entities.rbegin(),
            ECS::ClientUpdater {
                .wrapper = _wrapper,
                .clientController = _clientController
            }
        );
    }

    void GameController::_createTile() {
        _entities.insert(_entities.end(), _coordinator->createEntity());

        _coordinator->addComponent(
            *_entities.rbegin(),
            ECS::Traveling {
                .speed = {0.005, 0, 0}
            }
        );
        _coordinator->addComponent(
            *_entities.rbegin(),
            ECS::Transform {
                .position = {40, 5, 0},
                .rotation = {0, 0, 0, 0},
                .scale = 5.0f
            }
        );
        _coordinator->addComponent(
            *_entities.rbegin(),
            ECS::Collider {
                .team = 1,
                .breakable = false,
                .movable = false,
                .velocity = {0.005, 0, 0}
            }
        );
        _coordinator->addComponent(
            *_entities.rbegin(),
            ECS::Type {
                .name = "TILE"
            }
        );
        _coordinator->addComponent(
            *_entities.rbegin(),
            ECS::ClientUpdater {
                .wrapper = _wrapper,
                .clientController = _clientController
            }
        );
    }

    void GameController::_createBreakableTile() {
        _entities.insert(_entities.end(), _coordinator->createEntity());

        _coordinator->addComponent(
            *_entities.rbegin(),
            ECS::Traveling {
                .speed = {0.005, 0, 0}
            }
        );
        _coordinator->addComponent(
            *_entities.rbegin(),
            ECS::Transform {
                .position = {40, 10, 0},
                .rotation = {0, 0, 0, 0},
                .scale = 5.0f
            }
        );
        _coordinator->addComponent(
            *_entities.rbegin(),
            ECS::Collider {
                .team = 1,
                .breakable = true,
                .movable = false,
                .velocity = {0.005, 0, 0}
            }
        );
        _coordinator->addComponent(
            *_entities.rbegin(),
            ECS::Type {
                .name = "TILE_BREAKABLE"
            }
        );
        _coordinator->addComponent(
            *_entities.rbegin(),
            ECS::ClientUpdater {
                .wrapper = _wrapper,
                .clientController = _clientController
            }
        );
    }

    // Commands
    void GameController::commandPing(const std::string &data, const std::string &ip, const int port) {
        _wrapper->sendTo("OK", ip, port);
        std::cout << "(>) Sent information" << std::endl;
    }

    void GameController::commandMove(const std::string &data, const std::string &ip, const int port) {
//        // Assuming data is "MOVE 1 2 3"
//        std::istringstream iss(data);
//        std::string command;
//        int x, y, z;
//        int playerID = 0;
//
//        if (DEBUG_GAMECONTROLLER) {
//            if (!_clientController->checkClientIDExist(0))
//                commandRequestConnection(data, ip, port);
//            playerID = 0;
//            std::cout << "Player ID: " << playerID << std::endl;
//        } else {
//            if (!_clientController->isClientExist(ip, port))
//                return;
//            playerID = _clientController->getPlayerID(ip, port);
//        }
//
//        if (iss >> command >> x >> y >> z) {
//            if ((x >= -1 && x <= 1) && (y >= -1 && y <= 1) && (z >= -1 && z <= 1)) {
//                std::cout << "Command: " << command << ", x: " << x << ", y: " << y << ", z: " << z << std::endl;
//                auto &transform = _coordinator->getComponent<ECS::Transform>(playerID);
//                auto &collider = _coordinator->getComponent<ECS::Collider>(playerID);
//
//                transform.position._x += x * 0.25f;
//                transform.position._y += y * 0.25f;
//                transform.position._z += z * 0.25f;
//                collider.velocity += {x * 0.25f, y * 0.25f, z * 0.25f};
//            }
//        } else {
//            std::cerr << "Error extracting values from the string." << std::endl;
//        }
    }

    void GameController::commandShoot(const std::string &data, const std::string &ip, const int port) {
        int playerID = 0;

        if (DEBUG_GAMECONTROLLER) {
//            if (!_clientController->checkClientIDExist(0))
//                commandRequestConnection(data, ip, port);
//            playerID = 0;
//            std::cout << "Player ID: " << playerID << std::endl;
        } else {
            if (!_clientController->isClientExist(ip, port))
                return;
//            playerID = _clientController->getPlayerID(ip, port);
        }

//        _entitiesShoot[playerID] = true;
    }

    void GameController::commandRequestConnection(const std::string &data, const std::string &ip, const int port) {
        if (!_clientController->isClientExist(ip, port))
            _clientController->addClient(ip, port);
        _createPlayer(ip, port);
        if (!_cameraInit) {
            _cameraInit = true;
            _initializeECSEntities();
            _createEnnemy();
        }
    }
}
