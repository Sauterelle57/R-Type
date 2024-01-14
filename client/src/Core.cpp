/*
** EPITECH PROJECT, 2023
** B-CPP-500-STG-5-2-rtype-noah.gosciniak
** File description:
** Core
*/

#include <thread>
#include "../Tools/ECS/Managers/Components/ComponentStructs.hpp"
#include "../Tools/ECS/Managers/Systems/Sound.hpp"
#include "renderer/Window.hpp"
#include "renderer/Camera.hpp"
#include "renderer/Cursor.hpp"
#include "renderer/Event.hpp"
#include "renderer/Model.hpp"
#include "renderer/Texture.hpp"
#include "renderer/Utils.hpp"
#include "Core.hpp"
#include "Move.hpp"
#include "DrawModel.hpp"
#include "Play.hpp"
#include "MultipleLink.hpp"
#include "Listener.hpp"
#include "renderer/Audio.hpp"
#include "Menu.hpp"
#define RLIGHTS_IMPLEMENTATION
#include "rlights.h"
#include "renderer/RenderTexture.hpp"
#include "ModelAnimation.hpp"

namespace RT {

    void Core::checkCollision(ECS::Entity entity1, ECS::Entity entity2) {
        auto coordinatorPtr = _coordinator;
        if (!coordinatorPtr)
            return;

        auto &collision1 = coordinatorPtr->getComponent<ECS::Transform>(entity1);
        auto &collision2 = coordinatorPtr->getComponent<ECS::Transform>(entity2);

//        std::cout << collision1.position._x << " " << collision2.position._x << std::endl;
//        if (RL::Utils::checkCollisionBoxes(collision1.bounds, collision2.bounds))
//            std::cout << "Collision detected between entities" << std::endl;
    }

    Core::Core() {
        _window = std::make_shared<RL::ZWindow>(_screenWidth, _screenHeight, "R TYPE");
        _audio = std::make_unique<RL::ZAudio>();
        _audio->setMasterVolume(0.5f);

        // _cursor = std::make_shared<RL::ZCursor>();
        // _cursor->disable();
        _event = std::make_shared<RL::ZEvent>();
        _event->setExitKey(KEY_F4);

        _coordinator = std::make_shared<ECS::Coordinator>();

        _isRunning = std::make_shared<bool>(true);

        RL::Utils::setTargetFPS(60);

        _entities = std::make_shared<std::set<ECS::Entity>>();
        _camera = std::make_shared<RL::ZCamera>();
        _camera->setPosition({ 0.0f, 0.0f, 0.0f });
        _camera->setTarget({ 0.0f, 0.0f, 0.0f });
        _camera->setUp({ 0.0f, 1.0f, 0.0f });
        _camera->setFovy(30.0f);
        _camera->setProjection(CAMERA_PERSPECTIVE);
        _receivedMessages = std::make_shared<std::queue<rt::ReceivedMessage>>();
        _udpClient = std::make_shared<rt::UdpClient>();
        _messageQueueMutex = std::make_shared<std::mutex>();

        _isRunningMutex = std::make_shared<std::mutex>();
        {
            std::lock_guard<std::mutex> lock(*_isRunningMutex);
            _udpClientThread = std::make_unique<std::thread>(([&]() {
                _udpClient->run(_isRunning);
            }));
        }

        Menu menu;
        menu.loop(_window, _event, false);
        bool canReach = false;
        rt::ProtocolController pc;
        pc.actionPing();
        auto dt1 = pc.getProtocol();
        while (!canReach) {
            _udpClient->setup(menu.getHost(), menu.getPort(), _receivedMessages, _messageQueueMutex, _isRunningMutex);
            tls::Clock tryingToConnect(0.1);
            while (!tryingToConnect.isTimeElapsed() && !canReach) {
                _udpClient->sendStruct(dt1);
                {
                    std::lock_guard<std::mutex> lock(*_messageQueueMutex);
                    while (!_receivedMessages->empty()) {
                        std::string message = _receivedMessages->front().message;
                        auto data = rt::ProtocolController::deserialize(message);
                        if (data.sender == rt::SENDER_TYPE::SERVER && data.protocol == rt::PROTOCOL_TYPE::OK) {
                            canReach = true;
                        }
                        _receivedMessages->pop();
                    }
                }
            }
            if (!canReach) {
                {
                    std::lock_guard<std::mutex> lock(*_isRunningMutex);
                    *_isRunning = false;
                }

                _udpClientThread->join();
                _isRunning = std::make_shared<bool>(true);
                _udpClientThread = std::make_unique<std::thread>(([&]() {
                    _udpClient->run(_isRunning);
                }));
                menu.loop(_window, _event, true);
            }
        }
        pc.init();
        pc.actionConnectionRequest();
        auto _dataToSend = pc.getProtocol();
        _udpClient->sendStruct(_dataToSend);
        _listener = std::make_unique<Listener>(_coordinator, _entities, _camera, _udpClient);
        _clock = std::make_unique<tls::Clock>(0.01);
    }

    Core::~Core() {
        {
            std::lock_guard<std::mutex> lock(*_isRunningMutex);
            *_isRunning = false;
        }

        _udpClientThread->join();
        exit(0);
    }

    void Core::initEntities() {
//        _coordinator->addComponent(
//            *_entities->rbegin(),
//            ECS::Weapon {
//                .damage = 1,
//                .speed = 1,
//                .durability = 1,
//                .create_projectile = ECS::Shoot::basicShot
//            }
//        );

//        _camera = std::make_shared<RL::ZCamera>();
//        _camera->setPosition({ 0.0f, 10.0f, 100.0f });
//        _camera->setTarget({ 0.0f, 10.0f, 0.0f });
//        _camera->setUp({ 0.0f, 1.0f, 0.0f });
//        _camera->setFovy(30.0f);
//        _camera->setProjection(CAMERA_PERSPECTIVE);
//
//        _entities->insert(_entities->end(), _coordinator->createEntity());
//        Entity cam = *_entities->rbegin();
//        _coordinator->addComponent(
//            *_entities->rbegin(),
//            ECS::Cam {
//                .camera = _camera
//            }
//        );
//        _coordinator->addComponent(
//            *_entities->rbegin(),
//            ECS::Transform {
//                {0, 10, 100},
//                {0, 0, 0, 0},
//                1.0f
//            }
//        );
//        _coordinator->addComponent(
//            *_entities->rbegin(),
//            ECS::Traveling {
//                .speed = {0.1, 0, 0}
//            }
//        );
//        ECS::MultipleLinkManager::createLink(_coordinator, cam, player, "target");

//        _entities->insert(_entities->end(), _coordinator->createEntity());
//        _coordinator->addComponent(
//            *_entities->rbegin(),
//            ECS::Model {
//                .model = std::make_shared<RL::ZModel>("./client/resources/models/boom.glb"),
//            }
//        );
//        _coordinator->addComponent(
//            *_entities->rbegin(),
//            ECS::Transform {
//                .position = {0, 5, 0},
//                .rotation = {0, 0, 0, 0},
//                .scale = 1.0f
//            }
//        );
    }

    void Core::initComponents() {
        _coordinator->init();

        _coordinator->registerComponent<ECS::Transform>();
        _coordinator->registerComponent<ECS::Model>();
        _coordinator->registerComponent<ECS::Player>();
        _coordinator->registerComponent<ECS::Particles>();
        _coordinator->registerComponent<ECS::Projectile>();
        _coordinator->registerComponent<ECS::Trajectory>();
        _coordinator->registerComponent<ECS::Weapon>();
        _coordinator->registerComponent<ECS::Cam>();
        _coordinator->registerComponent<ECS::Traveling>();
        _coordinator->registerComponent<ECS::MultipleLink>();
        _coordinator->registerComponent<ECS::Sound>();
        _coordinator->registerComponent<ECS::SelfDestruct>();
        _coordinator->registerComponent<ECS::LightComponent>();
        _coordinator->registerComponent<ECS::ShaderComponent>();
        _coordinator->registerComponent<ECS::Velocity>();
        _coordinator->registerComponent<ECS::Bdb>();
        _coordinator->registerComponent<ECS::Modal>();
        _coordinator->registerComponent<ECS::Music>();
        _coordinator->registerComponent<ECS::Animation>();
    }

    void Core::initSystem() {
        _systems._systemMusic = _coordinator->registerSystem<ECS::MusicSystem>();
        _systems._systemDrawModel = _coordinator->registerSystem<ECS::DrawModel>();
        _systems._systemPlayer = _coordinator->registerSystem<ECS::Play>();
        _systems._systemParticles = _coordinator->registerSystem<ECS::ParticleSystem>();
        _systems._systemCamera = _coordinator->registerSystem<ECS::CamSystem>();
        _systems._systemSound = _coordinator->registerSystem<ECS::SoundSystem>();
        _systems._systemSelfDestruct = _coordinator->registerSystem<ECS::SelfDestructSystem>();
        _systems._systemLight = _coordinator->registerSystem<ECS::LightSystem>();
        _systems._systemTraveling = _coordinator->registerSystem<ECS::TravelingSystem>();
        _systems._systemShaderUpdater = _coordinator->registerSystem<ECS::ShaderUpdaterSystem>();
        _systems._systemVelocity = _coordinator->registerSystem<ECS::VelocitySystem>();
        _systems._systemBdb = _coordinator->registerSystem<ECS::BdbSystem>();
        _systems._systemModal = _coordinator->registerSystem<ECS::ModalSystem>();
        _systems._systemAnimation = _coordinator->registerSystem<ECS::ModelAnimationSystem>();

        {
            ECS::Signature signature;
            signature.set(_coordinator->getComponentType<ECS::Transform>());
            signature.set(_coordinator->getComponentType<ECS::Model>());
            _coordinator->setSystemSignature<ECS::DrawModel>(signature);
        }
        {
            ECS::Signature signature;
            signature.set(_coordinator->getComponentType<ECS::Transform>());
            signature.set(_coordinator->getComponentType<ECS::Model>());
            signature.set(_coordinator->getComponentType<ECS::Player>());
            _coordinator->setSystemSignature<ECS::Play>(signature);
        }
        {
            ECS::Signature signature;
            signature.set(_coordinator->getComponentType<ECS::Transform>());
            signature.set(_coordinator->getComponentType<ECS::Particles>());
            signature.set(_coordinator->getComponentType<ECS::Velocity>());
            _coordinator->setSystemSignature<ECS::ParticleSystem>(signature);
        }
        {
            ECS::Signature signature;
            signature.set(_coordinator->getComponentType<ECS::Transform>());
            signature.set(_coordinator->getComponentType<ECS::Cam>());
            _coordinator->setSystemSignature<ECS::CamSystem>(signature);
        }
        {
            ECS::Signature signature;
            signature.set(_coordinator->getComponentType<ECS::Sound>());
            _coordinator->setSystemSignature<ECS::SoundSystem>(signature);
        }
        {
            ECS::Signature signature;
            signature.set(_coordinator->getComponentType<ECS::SelfDestruct>());
            _coordinator->setSystemSignature<ECS::SelfDestructSystem>(signature);
        }
        {
            ECS::Signature signature;
            signature.set(_coordinator->getComponentType<ECS::Transform>());
            signature.set(_coordinator->getComponentType<ECS::LightComponent>());
            signature.set(_coordinator->getComponentType<ECS::ShaderComponent>());
            _coordinator->setSystemSignature<ECS::LightSystem>(signature);
        }
        {
            ECS::Signature signature;
            signature.set(_coordinator->getComponentType<ECS::Transform>());
            signature.set(_coordinator->getComponentType<ECS::Traveling>());
            _coordinator->setSystemSignature<ECS::TravelingSystem>(signature);
        }
        {
            ECS::Signature signature;
            signature.set(_coordinator->getComponentType<ECS::ShaderComponent>());
            signature.set(_coordinator->getComponentType<ECS::Model>());
            _coordinator->setSystemSignature<ECS::ShaderUpdaterSystem>(signature);
        }
        {
            ECS::Signature signature;
            signature.set(_coordinator->getComponentType<ECS::Transform>());
            signature.set(_coordinator->getComponentType<ECS::Velocity>());
            _coordinator->setSystemSignature<ECS::VelocitySystem>(signature);
        }
        {
            ECS::Signature signature;
            signature.set(_coordinator->getComponentType<ECS::Bdb>());
            _coordinator->setSystemSignature<ECS::BdbSystem>(signature);
        }
        {
            ECS::Signature signature;
            signature.set(_coordinator->getComponentType<ECS::Music>());
            _coordinator->setSystemSignature<ECS::MusicSystem>(signature);
        }
        {
            ECS::Signature signature;
            signature.set(_coordinator->getComponentType<ECS::Modal>());
            _coordinator->setSystemSignature<ECS::ModalSystem>(signature);
        }
        {
            ECS::Signature signature;
            signature.set(_coordinator->getComponentType<ECS::Model>());
            signature.set(_coordinator->getComponentType<ECS::Animation>());
            _coordinator->setSystemSignature<ECS::ModelAnimationSystem>(signature);
        }
    }

    void Core::loop() {
        initComponents();
        initSystem();
        initEntities();

        SetConfigFlags(FLAG_MSAA_4X_HINT);

        std::shared_ptr<RL::IRenderTexture> target = std::make_shared<RL::ZRenderTexture2D>(_window->getRenderWidth(), _window->getRenderHeight());

        while (!_window->shouldClose() && !_shouldClose) {
            _systems._systemVelocity->getOldPosition();
            {
                std::lock_guard<std::mutex> lock(*_messageQueueMutex);
                while (!_receivedMessages->empty()) {
                    std::string message = _receivedMessages->front().message;
                    _receivedMessages->pop();
                    if (message == "OK" || message == "<error>") {
                        continue;
                    }
                    _listener->addEvent(message);
                }
            }
            _listener->onEvent(_shouldClose, _debug);
            if (_clock->isTimeElapsed()) {
                _systems._systemMusic->update();

                target->beginMode();
                _window->clearBackground(BLACK);
                _systems._systemCamera->begin();
                _systems._systemCamera->update();
                _systems._systemLight->update();
                _systems._systemShaderUpdater->update(_camera->getPosition());
                _systems._systemAnimation->update();
                _systems._systemDrawModel->update();
                if (_debug)
                    _systems._systemBdb->update();
                _systems._systemPlayer->update(_event, _udpClient);
                _systems._systemVelocity->update();
                _systems._systemParticles->update(_camera);
                _systems._systemSound->update();
                _systems._systemSelfDestruct->update();
                _systems._systemTraveling->update();

                _systems._systemCamera->end();
                target->endMode();

                _window->beginDrawing();
                _window->clearBackground(BLACK);
                target->draw(0, 0, WHITE);
                _systems._systemModal->update(_window, target);
                _window->drawFPS(10, 10);
                _window->endDrawing();
            }
        }
    }
};
