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
        _clock = tls::Clock(0.01);
        _clockBossChild = tls::Clock(5);
        _clockEnemySpawn = tls::Clock(10);
        _waveEnemy = 1;
        _clientController = std::make_shared<ClientController>();
        _pc = std::make_shared<ProtocolController>();
        _pc->init();
        _pc->setSender(rt::SENDER_TYPE::SERVER);
        _pc->setProtocol(rt::PROTOCOL_TYPE::ENTITIES);
    }

    void GameController::_initializeCommands() {
        _commands["PING"] = [&](const std::string &data, const std::string &ip, const int port) {
            commandPing(data, ip, port);
        };
        _commands["CONNECTION_REQUEST"] = [&](const std::string &data, const std::string &ip, const int port) {
            commandRequestConnection(data, ip, port);
        };
        _commands["ID"] = [&](const std::string &data, const std::string &ip, const int port) {
            commandID(data, ip, port);
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
                _systems._systemMove->update();
                _systems._systemAutoMove->update();
                // _systems._systemEnemy->update();
                _systems._systemClientUpdater->update();
                _systems._systemParent->update();
            }
            // static int i = 0;
            // if (_clockBossChild.isTimeElapsed() && i < 2) {
            //     if (_entities.size() > 1 && _coordinator->getComponent<ECS::Type>(*_entities.rbegin()).name == "BOSS") {
            //         std::cout << "create child" << std::endl;
            //         _createChild(*_entities.rbegin());
            //         i++;
            //     }
            // }
        }
    }

    void GameController::addReceivedData(const std::string &data, const std::string &ip, const int port) {
        _receivedData.push({data, ip, port});
    }

    void GameController::addWrapper(std::shared_ptr<IWrapper> wrapper) {
        _wrapper = wrapper;
    }

    void GameController::commandHandler(const std::string &data, const std::string &ip, const int port) {

        // std::cout << "-------------------" << std::endl;
        // std::cout << "COMMAND HANDLER" << std::endl;
        // std::cout << "from: " << ip << ":" << port << std::endl;
        // std::cout << "data: " << data << std::endl;
        // std::cout << "-------------------" << std::endl;

        std::istringstream iss(data);
        std::string command;
        iss >> command;


        try {
            // std::cout << "[" << command << "] " << data.length() << std::endl;
            if (command == "SHOOT" || command == "MOVE")
                _systems._systemPlayerManager->update(data, ip, port, _waveEnemy);
            else
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
        _coordinator->registerComponent<ECS::Trajectory>();
        _coordinator->registerComponent<ECS::Collider>();
        _coordinator->registerComponent<ECS::Type>();
        _coordinator->registerComponent<ECS::ClientUpdater>();
        _coordinator->registerComponent<ECS::Player>();
        // _coordinator->registerComponent<ECS::Enemy>();
        // _coordinator->registerComponent<ECS::Shooter>();
        _coordinator->registerComponent<ECS::Parent>();

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
        _systems._systemPlayerManager = _coordinator->registerSystem<ECS::PlayerManager>();
        _systems._systemParent = _coordinator->registerSystem<ECS::ParentManager>();
        _systems._systemMove = _coordinator->registerSystem<ECS::Move>();
        _systems._systemAutoMove = _coordinator->registerSystem<ECS::AutoMove>();
        // _systems._systemEnemy = _coordinator->registerSystem<ECS::EnemySystem>();
        // _systems._systemEnemy->init();

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
            signature.set(_coordinator->getComponentType<ECS::Trajectory>());
            _coordinator->setSystemSignature<ECS::AutoMove>(signature);
        }

        {
           ECS::Signature signature;
           signature.set(_coordinator->getComponentType<ECS::Transform>());
           signature.set(_coordinator->getComponentType<ECS::Weapon>());
            signature.set(_coordinator->getComponentType<ECS::ClientUpdater>());
            // signature.set(_coordinator->getComponentType<ECS::Shooter>());
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
            signature.set(_coordinator->getComponentType<ECS::Collider>());
            signature.set(_coordinator->getComponentType<ECS::ClientUpdater>());
            _coordinator->setSystemSignature<ECS::ClientUpdaterSystem>(signature);
        }

        {
            ECS::Signature signature;
            signature.set(_coordinator->getComponentType<ECS::Player>());
            signature.set(_coordinator->getComponentType<ECS::Type>());
            // signature.set(_coordinator->getComponentType<ECS::Shooter>());
            signature.set(_coordinator->getComponentType<ECS::Weapon>());
            _coordinator->setSystemSignature<ECS::PlayerManager>(signature);
        }

        {
            ECS::Signature signature;
            signature.set(_coordinator->getComponentType<ECS::Parent>());
            signature.set(_coordinator->getComponentType<ECS::Transform>());
            // signature.set(_coordinator->getComponentType<ECS::Shooter>());
            // signature.set(_coordinator->getComponentType<ECS::Weapon>());
            _coordinator->setSystemSignature<ECS::ParentManager>(signature);
        }

        {
            ECS::Signature signature;
            signature.set(_coordinator->getComponentType<ECS::Player>());
            signature.set(_coordinator->getComponentType<ECS::Traveling>());
            signature.set(_coordinator->getComponentType<ECS::Transform>());
            signature.set(_coordinator->getComponentType<ECS::Collider>());
            _coordinator->setSystemSignature<ECS::Move>(signature);
        }

        {
            ECS::Signature signature;
            // signature.set(_coordinator->getComponentType<ECS::Enemy>());
            signature.set(_coordinator->getComponentType<ECS::Transform>());
            signature.set(_coordinator->getComponentType<ECS::Collider>());
            // signature.set(_coordinator->getComponentType<ECS::Shooter>());
            // _coordinator->setSystemSignature<ECS::EnemySystem>(signature);
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
                .scale = {0.5f, 0.5f, 0.5f}
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
                ._pc = _pc,
                .wrapper = _wrapper,
                .clientController = _clientController
            }
        );
        _coordinator->addComponent(
            *_entities.rbegin(),
            ECS::Collider {
                .team = 8,
                .breakable = false,
                .movable = false,
                .bounds = tls::BoundingBox({-1000, -1000, -1000}, {-1000, -1000, -1000}),
            }
        );

        for (float i = -45; i < 55; i += 3) {
            _createTile({i, 35, 0});
            _createTile({i, -18, 0});
        }
        // _createTile({30, 29, 0});
        // _createBreakableTile({10, 20, 0});

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
                .scale = {0.5f, 0.5f, 0.5f}
            }
        );
        _coordinator->addComponent(
           *_entities.rbegin(),
           ECS::Weapon {
               .damage = 1.f,
               .speed = 1.f,
               .durability = 1.f,
               .create_projectile = ECS::Shoot::basicShot
           }
       );

        tls::BoundingBox bdb = tls::loadModelAndGetBoundingBox("./client/resources/models/player.glb");
        tls::Matrix matr = tls::MatrixIdentity();
        matr = tls::MatrixMultiply(matr, tls::MatrixRotateX(90 * DEG2RAD));
        matr = tls::MatrixMultiply(matr, tls::MatrixRotateZ(-90 * DEG2RAD));
        bdb.applyMatrix(matr);

       _coordinator->addComponent(
           *_entities.rbegin(),
           ECS::Collider {
               .team = 0,
               .breakable = true,
               .movable = true,
               .velocity = {0.01, 0, 0},
               .bounds = bdb,
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
                ._pc = _pc,
                .wrapper = _wrapper,
                .clientController = _clientController
            }
        );
        _coordinator->addComponent(
            *_entities.rbegin(),
            ECS::Player {
                .mooving = {0, 0, 0}
            }
        );
    }

    void GameController::_createEnemy(tls::Vec3 pos, float clockSpeed) {
        _entities.insert(_entities.end(), _coordinator->createEntity());

        _coordinator->addComponent(
            *_entities.rbegin(),
            ECS::Traveling {
                .speed = {-0.02, 0, 0}
            }
        );
        _coordinator->addComponent(
            *_entities.rbegin(),
            ECS::Transform {
                .position = pos,
                .rotation = {0, 0, 0, 0},
                .scale = {0.6f, 0.6f, 0.6f}
            }
        );
        static tls::BoundingBox bdb = tls::loadModelAndGetBoundingBox("./client/resources/models/spaceship2.glb");
        static tls::Matrix matr = tls::MatrixIdentity();
        static bool first = true;
        if (first) {
            matr = tls::MatrixMultiply(matr, tls::MatrixRotateX(-180 * DEG2RAD));
            bdb.applyMatrix(matr);
            first = false;
        }

        _coordinator->addComponent(
           *_entities.rbegin(),
           ECS::Collider {
               .team = 1,
               .breakable = true,
               .movable = true,
               .velocity = {0.005, 0, 0},
               .bounds = bdb
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
                ._pc = _pc,
                .wrapper = _wrapper,
                .clientController = _clientController
            }
        );
        static float shotSpeed = 1.f;
        _coordinator->addComponent(
            *_entities.rbegin(),
            ECS::Weapon {
                .damage = 0.5f,
                .speed = shotSpeed,
                .durability = 1.f,
                .autoShoot = true,
                .shootFrequency = tls::Clock(clockSpeed),
                .create_projectile = ECS::Shoot::basicEnemyShot
            }
        );
        _coordinator->addComponent(
            *_entities.rbegin(),
            ECS::Projectile {
                .damage = 0.5f,
                .speed = shotSpeed,
                .active = true
            }
        );
        static float speed = 0.003f;
        std::vector<std::function<tls::Vec3(tls::Vec3, std::shared_ptr<float>)>> trajectories = {
            [](tls::Vec3 pos, std::shared_ptr<float> t) {
                    (*t) += speed;
                    int amplitude = 14;
                    int height = 13;
                    int gap = 4;
                    int randAmplitude = 5;
                    int randHeight = 13;
                    int randGap = 4;
                    srand(time(0));
                    double randomY = asin(sin((*t) * randGap)) * randAmplitude + randHeight;
                return tls::Vec3{pos._x, asin(sin((*t) * gap)) * amplitude + height, pos._z};
            },
            [](tls::Vec3 pos, std::shared_ptr<float> t) {
                    (*t) += speed;
                    int amplitude = 14;
                    int height = 13;
                    int gap = 4;
                    int randAmplitude = 5;
                    int randHeight = 13;
                    int randGap = 4;
                    srand(time(0));
                    double randomY = acos(sin((*t) * randGap)) * randAmplitude + randHeight;
                return tls::Vec3{pos._x, acos(sin((*t) * gap)) * amplitude + height, pos._z};
            },
            [](tls::Vec3 pos, std::shared_ptr<float> t) {
                    (*t) += speed;
                    int amplitude = 1;
                    int height = 15;
                    int gap = 1.0;
                    int randAmplitude = 0.5;
                    int randHeight = 0.1;
                    int randGap = 0.2;
                    srand(time(0));
                    double randomY = atan(cos((*t) * randGap + rand() % 100)) * randAmplitude + randHeight;
                return tls::Vec3{pos._x, atan(cos((*t) * gap)) * amplitude + height + randomY, pos._z};
            },
            [](tls::Vec3 pos, std::shared_ptr<float> t) {
                    (*t) += speed;
                    static int maxY = -18 + rand() % 43 + 10;
                    static int minY = 35 - (rand() % 43 + 10);
                    srand(time(0));
                    static int tmp = 0.1;
                    if (pos._y >= maxY) {
                        tmp = -0.1;
                    }
                return tls::Vec3{pos._x, pos._y, pos._z};
            }
        };
        _coordinator->addComponent(
            *_entities.rbegin(),
            ECS::Trajectory {
                .t = std::make_shared<float>(rand() % 100),
                .trajectory = trajectories[0]
            }
        );
    }

    void GameController::_createChild(ECS::Entity parent, float offset, bool armed) {
        _entities.insert(_entities.end(), _coordinator->createEntity());
        auto &traveling = _coordinator->getComponent<ECS::Traveling>(parent);
        auto &transform = _coordinator->getComponent<ECS::Transform>(parent);
        auto &weapon = _coordinator->getComponent<ECS::Weapon>(parent);
        auto &collider = _coordinator->getComponent<ECS::Collider>(parent);
        auto &clientUpdater = _coordinator->getComponent<ECS::ClientUpdater>(parent);
        auto &trajectory = _coordinator->getComponent<ECS::Trajectory>(parent);

        _coordinator->addComponent(
            *_entities.rbegin(),
            ECS::Traveling {
                .speed = traveling.speed
            }
        );
        float tmp = offset;
        _coordinator->addComponent(
            *_entities.rbegin(),
            ECS::Trajectory {
                .t = std::make_shared<float>(tmp),
                .trajectory = trajectory.trajectory
            }
        );
        auto &ownTrajectory = _coordinator->getComponent<ECS::Trajectory>(*_entities.rbegin());
        _coordinator->addComponent(*_entities.rbegin(),
            ECS::Transform {
                .position = trajectory.trajectory(transform.position, ownTrajectory.t),
                .rotation = {0, 0, 0, 0},
                .scale = {0.25f, 0.25f, 0.25f}
            }
        );
        if (armed) {
            _coordinator->addComponent(
                *_entities.rbegin(),
                ECS::Weapon {
                    .damage = weapon.damage / 2,
                    .speed = weapon.speed,
                    .durability = weapon.durability,
                    .autoShoot = true,
                    .shootFrequency = tls::Clock(1.5),
                    .create_projectile = ECS::Shoot::basicEnemyShot
                }
            );
        }

        static tls::BoundingBox bdb = tls::loadModelAndGetBoundingBox("./client/resources/models/cube.glb");
        static bool first = true;
        if (first) {
            first = false;
        }

        _coordinator->addComponent(*_entities.rbegin(),
            ECS::Collider {
                .team = 1,
                .breakable = true,
                .movable = false,
                .velocity = {0.005, 0, 0},
                .bounds = bdb
            }
        );
        _coordinator->addComponent(
            *_entities.rbegin(),
            ECS::Type {
                .name = "CHILD"
            }
        );
        _coordinator->addComponent(
            *_entities.rbegin(),
            ECS::ClientUpdater {
                ._pc = _pc,
                .wrapper = _wrapper,
                .clientController = _clientController
            }
        );
    }

    void GameController::_createBoss(tls::Vec3 pos, float clockSpeed, int nbChildren) {
        _entities.insert(_entities.end(), _coordinator->createEntity());

        _coordinator->addComponent(
            *_entities.rbegin(),
            ECS::Traveling {
                .speed = {0.02, 0, 0}
            }
        );
        _coordinator->addComponent(
            *_entities.rbegin(),
            ECS::Transform {
                .position = pos,
                .rotation = {0, 0, 0, 0},
                .scale = {0.5f, 0.5f, 0.5f}
            }
        );
        _coordinator->addComponent(
           *_entities.rbegin(),
           ECS::Weapon {
               .damage = 2.f,
               .speed = .3f,
               .durability = 1.f,
               .autoShoot = true,
               .shootFrequency = tls::Clock(clockSpeed),
               .create_projectile = ECS::Shoot::basicEnemyShot
           }
        );
        static tls::BoundingBox bdb = tls::loadModelAndGetBoundingBox("./client/resources/models/cube.glb");
        static bool first = true;
        if (first) {
            first = false;
        }
        _coordinator->addComponent(
           *_entities.rbegin(),
           ECS::Collider {
               .team = 1,
               .breakable = true,
               .movable = false,
               .velocity = {0.005, 0, 0},
               .bounds = bdb
           }
        );
        _coordinator->addComponent(
            *_entities.rbegin(),
            ECS::Type {
                .name = "BOSS"
            }
        );
        _coordinator->addComponent(
            *_entities.rbegin(),
            ECS::ClientUpdater {
                ._pc = _pc,
                .wrapper = _wrapper,
                .clientController = _clientController
            }
        );
        static float speed = .1;
        _coordinator->addComponent(
            *_entities.rbegin(),
            ECS::Trajectory {
                .trajectory = [](tls::Vec3 pos, std::shared_ptr<float> t) {
                    (*t) += speed;
                    // static int amplitude = 11;
                    // static int height = 10;
                    // static float gap = 4;
                    // static int maxX = 50;
                    // static int minX = 25;
                    // static float step = 0.05f;
                    // if (pos._x > maxX)
                    //     step = 0.05f;
                    // else if (pos._x < minX)
                    //     step = -0.05f;
                    // return tls::Vec3{pos._x - step, asin(sin((*t) * gap)) * amplitude + height, pos._z};
                    static float radiusH = 10;
                    static float radiusV = 20;
                    return tls::Vec3{40 + radiusH * cos((*t) * 0.2), 7 + radiusV * sin((*t) * 0.2), pos._z};
                }
            }
        );

        static float offset = -speed*6;
        for (int i = 0; i < nbChildren; i++) {
            _createChild(*_entities.rbegin(), offset, i % 3 == 2 ? true : false);
            offset -= speed*6;
        }
    }

    void GameController::_createTile(tls::Vec3 pos) {
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
                .position = pos,
                .rotation = {0, 0, 0, 0},
                .scale = {1.5f, 1.5f, 1.5f}
            }
        );

        static auto bounds = tls::loadModelAndGetBoundingBox("./client/resources/models/obstacle.glb");
        _coordinator->addComponent(
            *_entities.rbegin(),
            ECS::Collider {
                .team = 1,
                .breakable = false,
                .movable = false,
                .velocity = {0.01, 0, 0},
                .bounds = bounds,
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
                ._pc = _pc,
                .wrapper = _wrapper,
                .clientController = _clientController
            }
        );
    }

    void GameController::_createBreakableTile(tls::Vec3 pos) {
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
                .position = pos,
                .rotation = {0, 0, 0, 0},
                .scale = {1.0f, 1.0f, 1.0f}
            }
        );
        static auto bounds = tls::loadModelAndGetBoundingBox("./client/resources/models/obstacle.glb");
        _coordinator->addComponent(
            *_entities.rbegin(),
            ECS::Collider {
                .team = 1,
                .breakable = true,
                .movable = false,
                .velocity = {0.01, 0, 0},
                .bounds = bounds,
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
                ._pc = _pc,
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

    void GameController::commandRequestConnection(const std::string &data, const std::string &ip, const int port) {
        if (!_clientController->isClientExist(ip, port))
            _clientController->addClient(ip, port);
        _createPlayer(ip, port);
        if (!_cameraInit) {
            _cameraInit = true;
            _initializeECSEntities();
            // _createEnemy({50, 0, 0}, 1.0);
            // _createEnemy({50, 0, 0}, 4.5);
            // _createEnemy({55, 0, 0}, 1.2);
            // _createEnemy({35, -6, 0}, 2);
            _createBoss({50, 0, 0}, 1.5, 10);
        }
    }

    void GameController::commandID(const std::string &data, const std::string &ip, const int port) {
        // std::cout << "ID: " << data << std::endl;
        if (!_clientController->isClientExist(ip, port)) {
            return;
        }

        std::shared_ptr<rt::Client> _client = _clientController->getClient(ip, port);
        long long id;
        std::string command;
        std::istringstream iss(data);

        iss >> command;
        iss >> id;
        _client->getDeltaManager()->validatePacket(id);
    }
}
