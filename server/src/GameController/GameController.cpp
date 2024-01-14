#include "GameController.hpp"
#include "Random.hpp"
#include "../../map/LibJson.hpp"
#include <sstream>
#include <string>
#include <iostream>
#include <iomanip>

#define DEBUG_GAMECONTROLLER 0 // Only for testing purposes

namespace rt {

    GameController::GameController(bool debug, std::string mapFilePath)
    {
        try {
            const std::string path = mapFilePath;
            _data = lvl::jsonParsing(path);
        } catch (const std::exception &e) {
            std::cerr << e.what() << std::endl;
            exit(84);
        }


        _cameraInit = false;
        _initializeCommands();
        _initializeECS();
        _clock = tls::Clock(0.01);
        _clockBossChild = tls::Clock(5);
        _waveEnemy = 1;
        _clientController = std::make_shared<ClientController>();
        _pc = std::make_shared<ProtocolController>();
        _pc->init();
        _pc->setSender(rt::SENDER_TYPE::SERVER);
        _pc->setProtocol(rt::PROTOCOL_TYPE::ENTITIES);
        _receivedMutex = std::make_shared<std::mutex>();
        _debug = debug;
    }

    void GameController::_initializeCommands() {
        _commands[rt::PROTOCOL_TYPE::PING] = [&](const rt::Protocol &data, const std::string &ip, const int port) {
            commandPing(data, ip, port);
        };
        _commands[rt::PROTOCOL_TYPE::CONNECTION_REQUEST] = [&](const rt::Protocol &data, const std::string &ip, const int port) {
            commandRequestConnection(data, ip, port);
        };
        _commands[rt::PROTOCOL_TYPE::ID] = [&](const rt::Protocol &data, const std::string &ip, const int port) {
            commandID(data, ip, port);
        };
    }

    void GameController::_pushToReceivedList() {
        static tls::Clock tickrate_manager(0.01667);

        if (!tickrate_manager.isTimeElapsed()) {
            return;
        }

        std::lock_guard<std::mutex> lock(*_receivedMutex);
        for (auto &x : _receivedDataBuffer) {
            rt::ProtocolController pc;
            tls::Vec3 pos = {0, 0, 0};
            bool isShooting = false;

            rt::Protocol p;
            p.sender = rt::SENDER_TYPE::CLIENT;
            while (!x.second.second.second.empty()) {
                PROTOCOL_TYPE ptype = x.second.second.second.front().protocol;
                p_client client = x.second.second.second.front().client;
                if (ptype == rt::PROTOCOL_TYPE::MOVE) {
                    pos += client.move;
                } else if (ptype == rt::PROTOCOL_TYPE::SHOOT) {
                    isShooting = true;
                }

                // if (p.client.move._x != 0 || p.client.move._y != 0 || p.client.move._z != 0)
                //     std::cout << "isShooting: " << isShooting << std::endl;
                x.second.second.second.pop();
            }
            p.protocol = rt::PROTOCOL_TYPE::MOVE;
            p.client.move = pos;
            if (isShooting)
                p.protocol = rt::PROTOCOL_TYPE::SHOOT;
            else if (isShooting && (p.client.move._x != 0 || p.client.move._y != 0 || p.client.move._z != 0))
                p.protocol = rt::PROTOCOL_TYPE::MOVE_AND_SHOOT;
            _receivedData.push({p, x.second.first.first, x.second.first.second});
        }
    }

    int GameController::exec() {
        while (1) {
            _pushToReceivedList();
            // get data from queue
            if (!_receivedData.empty()) {
                ReceivedData data = _receivedData.front();
                // std::cout << "Received : " << data.data.sender << ", " << data.data.protocol << std::endl;
                commandHandler(data.data, data.ip, data.port);
                // std::cout << "End of traitment" << std::endl;
                _receivedData.pop();
            }
            if (_clock.isTimeElapsed()) {
                _systems._systemTraveling->update();
                _systems._systemProjectile->update(_camera);
                _systems._systemShoot->update();
                _systems._systemCollider->update();
                _systems._systemMove->update();
                _systems._systemAutoMove->update();
                _systems._systemClientUpdater->update(_debug);
                _systems._systemLvlManager->update(*this);
            }
        }
        return 0;
    }

    void GameController::addReceivedData(const rt::Protocol &data, const std::string &ip, const int port) {
        // std::cout << "=> Pushing to buffer(-1)" << std::endl;

        if (data.sender == rt::SENDER_TYPE::CLIENT && data.protocol == rt::PROTOCOL_TYPE::PING || data.protocol == rt::PROTOCOL_TYPE::ID || data.protocol == rt::PROTOCOL_TYPE::CONNECTION_REQUEST) {
            _receivedData.push({data, ip, port});
            return;
        }
        std::lock_guard<std::mutex> lock(*_receivedMutex);
        if (_receivedDataBuffer.find(ip + ":" + std::to_string(port)) == _receivedDataBuffer.end()) {
            _receivedDataBuffer[ip + ":" + std::to_string(port)] = std::make_pair(std::make_pair(ip, port), std::make_pair(tls::Clock::getTimeStamp(), std::queue<rt::Protocol>()));
        }
        _receivedDataBuffer[ip + ":" + std::to_string(port)].second.second.push(data);
        // std::cout << "Received data from " << ip << ":" << port << std::endl;
        // _receivedData.push({data, ip, port});
    }

    void GameController::addWrapper(std::shared_ptr<IWrapper> wrapper) {
        _wrapper = wrapper;
    }

    void GameController::commandHandler(const rt::Protocol &data, const std::string &ip, const int port) {

        // std::cout << "-------------------" << std::endl;
        // std::cout << "COMMAND HANDLER" << std::endl;
        // std::cout << "from: " << ip << ":" << port << std::endl;
        // std::cout << "data: " << data << std::endl;
        // std::cout << "-------------------" << std::endl;

        try {
            // std::cout << "[" << command << "] " << data.length() << std::endl;
            if (data.protocol == rt::PROTOCOL_TYPE::SHOOT || data.protocol == rt::PROTOCOL_TYPE::MOVE || data.protocol == rt::PROTOCOL_TYPE::MOVE_AND_SHOOT)
                _systems._systemPlayerManager->update(data, ip, port, _waveEnemy);
            else
                _commands.at(data.protocol)(data, ip, port);
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
        _coordinator->registerComponent<ECS::Level>();
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
        _systems._systemLvlManager = _coordinator->registerSystem<ECS::LvlManager>();
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
            signature.set(_coordinator->getComponentType<ECS::Level>());
             _coordinator->setSystemSignature<ECS::LvlManager>(signature);
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
                .bounds = tls::BoundingBox({-45, -45, -45}, {45, 45, 45}),
            }
        );

        for (float i = -50; i < 55; i += 3) {
            _createTile({i, 35, 0});
            _createTile({i, -15, 0});
        }
        // _createTile({30, 29, 0});
        // _createBreakableTile({10, 20, 0});

        std::cout << "SERVER/ECS entities configured" << std::endl;
    }

    void GameController::_createPlayer(std::string ip, int port) {
        auto entityCreated = _coordinator->createEntity();
        _entities.insert(_entities.end(), entityCreated);
        _players.push_back(entityCreated);

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
        static float damage = 50.f;
        _coordinator->addComponent(
           *_entities.rbegin(),
            ECS::Weapon {
                .damage = damage,
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
               .maxLife = 100.0,
               .damage = damage
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

    void GameController::_createFloorEnemy(tls::Vec3 pos, float size, double speed) {
        _entities.insert(_entities.end(), _coordinator->createEntity());

        _coordinator->addComponent(
            *_entities.rbegin(),
            ECS::Transform {
                .position = pos,
                .rotation = {0, 0, 0, 0},
                .scale = {size, size, size}
            }
        );
        static tls::BoundingBox bdb = tls::loadModelAndGetBoundingBox("./client/resources/models/mob5.glb");
        static bool first = true;
        if (first) {
            first = false;
        }
        static float damage = 45.0f;
        _coordinator->addComponent(
           *_entities.rbegin(),
           ECS::Collider {
               .team = 1,
               .breakable = true,
               .movable = true,
               .velocity = {0.005, 0, 0},
               .bounds = bdb,
               .life = 100.0f,
               .maxLife = 100.0f,
               .damage = damage
           }
        );
        _coordinator->addComponent(
            *_entities.rbegin(),
            ECS::Type {
                .name = "FLOOR_ENEMY"
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
        static double speed2 = speed;
        _coordinator->addComponent(
            *_entities.rbegin(),
            ECS::Trajectory {
                .t = std::make_shared<float>(0.0f),
                .trajectory = [](tls::Vec3 pos, std::shared_ptr<float> t) {
                    return tls::Vec3{pos._x - speed2, pos._y, pos._z};
                }
            }
        );
    }

    void GameController::_createEnemy(tls::Vec3 pos, float clockSpeed) {
        std::cout << "Creating enemy : " << pos._x << ", " << pos._y << ", " << pos._z << std::endl;
        _entities.insert(_entities.end(), _coordinator->createEntity());

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
            matr = tls::MatrixMultiply(matr, tls::MatrixRotateX(180 * DEG2RAD));
            bdb.applyMatrix(matr);
            first = false;
        }
        static float damage = 35.0f;
        _coordinator->addComponent(
           *_entities.rbegin(),
           ECS::Collider {
               .team = 1,
               .breakable = true,
               .movable = true,
               .velocity = {0.005, 0, 0},
               .bounds = bdb,
               .life = 50.0f,
               .maxLife = 50.0f,
               .damage = damage
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
                .damage = damage,
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
                .speed = shotSpeed,
                .active = true
            }
        );
        static tls::Random random(42);
        std::vector<std::function<tls::Vec3(tls::Vec3, std::shared_ptr<float>)>> trajectories = {
            [](tls::Vec3 pos, std::shared_ptr<float> t) {
                    (*t) += 0.003f;
                    static int amplitude = 13;
                    static float height = 12.5;
                    static int gap = 4;
                return tls::Vec3{pos._x, asin(sin((*t) * gap)) * amplitude + height, pos._z};
            },
            [](tls::Vec3 pos, std::shared_ptr<float> t) {
                    (*t) += 0.01f;
                    static int centerX = pos._x;
                    static int centerY = pos._y;
                    static int size = 8;
                return tls::Vec3{centerX + size * cos(*t) - (*t)*0.2, centerY + size * sin((*t) * 2), pos._z};
            },
            [](tls::Vec3 pos, std::shared_ptr<float> t) {
                (*t) += .003f;
                static float speed = 0.1f;
                static int direction = random.getRandomNumber(0, 1);
                static int targetY = direction ? random.getRandomNumber(0, 34) : random.getRandomNumber(0, 17);
                static int targetX = pos._x + random.getRandomNumber(0, 44) + pos._x + 1;
                if (pos._x <= targetX)
                    targetX = pos._x + random.getRandomNumber(0, 44) + pos._x + 1;
                if (pos._y >= targetY) {
                    direction = random.getRandomNumber(0, 1);
                    targetY = direction ? random.getRandomNumber(0, 34) : random.getRandomNumber(0, 17);
                }
                return tls::Vec3{pos._x - speed, pos._y - targetY < 0 ? pos._y + speed : pos._y - speed, pos._z};
            },
            [](tls::Vec3 pos, std::shared_ptr<float> t) {
                    static float speed = 0.06f;
                    (*t) += speed;
                return tls::Vec3{pos._x - speed, cos((*t))*7, pos._z};
            }
        };
        _coordinator->addComponent(
            *_entities.rbegin(),
            ECS::Trajectory {
                .t = std::make_shared<float>(0.0f),
                .trajectory = trajectories[random.getRandomNumber(0, trajectories.size() - 1)]
            }
        );
    }

    void GameController::_createChild(ECS::Entity parent, float offset, bool armed) {
        auto &traveling = _coordinator->getComponent<ECS::Traveling>(parent);
        auto &transform = _coordinator->getComponent<ECS::Transform>(parent);
        auto &weapon = _coordinator->getComponent<ECS::Weapon>(parent);
        auto &collider = _coordinator->getComponent<ECS::Collider>(parent);
        auto &clientUpdater = _coordinator->getComponent<ECS::ClientUpdater>(parent);
        auto &trajectory = _coordinator->getComponent<ECS::Trajectory>(parent);
        _entities.insert(_entities.end(), _coordinator->createEntity());

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
                .trajectory = trajectory.trajectory,
                .oriented = true
            }
        );
        auto &ownTrajectory = _coordinator->getComponent<ECS::Trajectory>(*_entities.rbegin());
        _coordinator->addComponent(*_entities.rbegin(),
            ECS::Transform {
                .position = trajectory.trajectory(transform.position, ownTrajectory.t),
                .rotation = {0, 0, 0, 0},
                .scale = {2.f, 2.f, 2.f}
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
                    .shootFrequency = tls::Clock(weapon.shootFrequency.getInterval()),
                    .create_projectile = ECS::Shoot::basicEnemyShot
                }
            );
        }

        static tls::BoundingBox bdb = tls::loadModelAndGetBoundingBox("./client/resources/models/boss_body2.glb");
        static bool first = true;
        if (first) {
            first = false;
        }

        _coordinator->addComponent(*_entities.rbegin(),
            ECS::Collider {
                .team = collider.team,
                .breakable = collider.breakable,
                .movable = collider.movable,
                .velocity = collider.velocity,
                .bounds = bdb,
                .life = collider.life / 2,
                .maxLife = collider.life / 2,
                .damage = collider.damage / 2
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
                .scale = {2.5f, 2.5f, 2.5f}
            }
        );
        static float damage = 75.0f;
        _coordinator->addComponent(
           *_entities.rbegin(),
           ECS::Weapon {
               .damage = damage,
               .speed = .3f,
               .durability = 1.f,
               .autoShoot = true,
               .shootFrequency = tls::Clock(clockSpeed),
               .create_projectile = ECS::Shoot::basicEnemyShot
           }
        );
        static tls::BoundingBox bdb = tls::loadModelAndGetBoundingBox("./client/resources/models/boss2.glb");
        _coordinator->addComponent(
           *_entities.rbegin(),
           ECS::Collider {
               .team = 1,
               .breakable = true,
               .movable = true,
               .velocity = {0.005, 0, 0},
               .bounds = bdb,
               .life = 300.0f,
               .maxLife = 300.0f,
               .damage = damage
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
                    static float radiusH = 10;
                    static float radiusV = 18;
                    return tls::Vec3{40 + radiusH * cos((*t) * 0.2), 11 + radiusV * sin((*t) * 0.2), pos._z};
                },
                .oriented = true
            }
        );

        static float offset = -speed*9;
        static int parentId =  *_entities.rbegin();

        for (int i = 0; i < nbChildren; i++) {
            _createChild(parentId, offset, i % 5 == 2 ? true : false);
            offset -= speed*9;
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
                .life = INFINITY,
                .maxLife = INFINITY
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

    void GameController::_createTileWithoutTraveling(tls::Vec3 pos) {
        _entities.insert(_entities.end(), _coordinator->createEntity());

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
                .life = INFINITY,
                .maxLife = INFINITY
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
                .life = 1.0,
                .maxLife = 1.0
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

    void GameController::_createBreakableTileWithoutTraveling(tls::Vec3 pos) {
        _entities.insert(_entities.end(), _coordinator->createEntity());

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
                .life = 1.0,
                .maxLife = 1.0,
                .damage = 25.0
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

    void GameController::_createLvl() {
        _entities.insert(_entities.end(), _coordinator->createEntity());

        _coordinator->addComponent(
            *_entities.rbegin(),
            ECS::Level {
                .data = _data,
            }
        );
    }

    // Commands
    void GameController::commandPing(const rt::Protocol &data, const std::string &ip, const int port) {
        rt::ProtocolController pc;
        pc.responseOK();
        auto toSend = pc.getProtocol();
        _wrapper->sendStruct(toSend, ip, port);
    }

    void GameController::commandRequestConnection(const rt::Protocol &data, const std::string &ip, const int port) {
        if (!_clientController->isClientExist(ip, port)) {
            _clientController->addClient(ip, port);

            rt::ProtocolController pc;
            pc.responseOK();
            auto toSend = pc.getProtocol();
            
            _wrapper->sendStruct(toSend, ip, port);
        } else {
            return;
        }
        _createPlayer(ip, port);
        if (!_cameraInit) {
            tls::Random random(42);
            _cameraInit = true;
            _initializeECSEntities();
            _createLvl();
        }
    }

    void GameController::commandID(const rt::Protocol &data, const std::string &ip, const int port) {
        if (!_clientController->isClientExist(ip, port)) {
            return;
        }

        std::shared_ptr<rt::Client> _client = _clientController->getClient(ip, port);
        long long id = data.packetId;

        _client->getDeltaManager()->validatePacket(id);
    }
}
