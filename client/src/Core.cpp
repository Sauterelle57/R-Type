/*
** EPITECH PROJECT, 2023
** B-CPP-500-STG-5-2-rtype-noah.gosciniak
** File description:
** Core
*/

#include <thread>
#include "renderer/Window.hpp"
#include "renderer/Camera.hpp"
#include "renderer/Cursor.hpp"
#include "renderer/Event.hpp"
#include "renderer/Model.hpp"
#include "renderer/Texture.hpp"
#include "renderer/Utils.hpp"
#include "Core.hpp"
#include "Utils.hpp"
#include "DrawModel.hpp"
#include "Move.hpp"
#include "Play.hpp"
#include "MultipleLink.hpp"
#include "Listener.hpp"

namespace RT {

    void Core::checkCollision(ECS::Entity entity1, ECS::Entity entity2) {
        auto coordinatorPtr = _coordinator;
        if (!coordinatorPtr)
            return;

        auto &collision1 = coordinatorPtr->getComponent<ECS::Transform>(entity1);
        auto &collision2 = coordinatorPtr->getComponent<ECS::Transform>(entity2);

        std::cout << collision1.position._x << " " << collision2.position._x << std::endl;
        if (RL::Utils::checkCollisionBoxes(collision1.bounds, collision2.bounds))
            std::cout << "Collision detected between entities" << std::endl;
    }

    Core::Core() {
        _window = std::make_shared<RL::ZWindow>(_screenWidth, _screenHeight, "R TYPE");

        _cursor = std::make_shared<RL::ZCursor>();
        _cursor->disable();
        _event = std::make_shared<RL::ZEvent>();
        _event->setExitKey(KEY_F4);

        _coordinator = std::make_shared<ECS::Coordinator>();

        RL::Utils::setTargetFPS(60);

        _entities = std::make_shared<std::set<ECS::Entity>>();
        _listener = std::make_unique<Listener>(_coordinator, _entities);
        _receivedMessages = std::make_shared<std::queue<rt::ReceivedMessage>>();
        _udpClient = std::make_shared<rt::UdpClient>();
        _udpClient->setup("127.0.0.1", 1234, _receivedMessages);

        _udpClientThread = std::make_unique<std::thread>(([&]() {
            _udpClient->run();
        }));
        _udpClient->send("CONNECTION_REQUEST");
    }

    Core::~Core() {
        _udpClientThread->join();
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
        _coordinator->registerComponent<ECS::Weapon>();
        _coordinator->registerComponent<ECS::Cam>();
        _coordinator->registerComponent<ECS::Traveling>();
        _coordinator->registerComponent<ECS::MultipleLink>();
    }

    void Core::initSystem() {
        _systems._systemMove = _coordinator->registerSystem<ECS::Move>();
        _systems._systemDrawModel = _coordinator->registerSystem<ECS::DrawModel>();
        _systems._systemPlayer = _coordinator->registerSystem<ECS::Play>();
        _systems._systemParticles = _coordinator->registerSystem<ECS::ParticleSystem>();
        _systems._systemShoot = _coordinator->registerSystem<ECS::Shoot>();
        _systems._systemProjectile = _coordinator->registerSystem<ECS::ProjectileSystem>();
        _systems._systemCamera = _coordinator->registerSystem<ECS::CamSystem>();
        _systems._systemTraveling = _coordinator->registerSystem<ECS::TravelingSystem>();

        {
            ECS::Signature signature;
            signature.set(_coordinator->getComponentType<ECS::Transform>());
            _coordinator->setSystemSignature<ECS::Move>(signature);
        }

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
            _coordinator->setSystemSignature<ECS::ParticleSystem>(signature);
        }

        {
            ECS::Signature signature;
            signature.set(_coordinator->getComponentType<ECS::Transform>());
            signature.set(_coordinator->getComponentType<ECS::Weapon>());
            _coordinator->setSystemSignature<ECS::Shoot>(signature);
        }

        {
            ECS::Signature signature;
            signature.set(_coordinator->getComponentType<ECS::Transform>());
            signature.set(_coordinator->getComponentType<ECS::Projectile>());
            _coordinator->setSystemSignature<ECS::ProjectileSystem>(signature);
        }

        {
            ECS::Signature signature;
            signature.set(_coordinator->getComponentType<ECS::Transform>());
            signature.set(_coordinator->getComponentType<ECS::Cam>());
            _coordinator->setSystemSignature<ECS::CamSystem>(signature);
        }

        {
            ECS::Signature signature;
            signature.set(_coordinator->getComponentType<ECS::Transform>());
            signature.set(_coordinator->getComponentType<ECS::Traveling>());
            _coordinator->setSystemSignature<ECS::TravelingSystem>(signature);
        }
    }

    void Core::loop() {
        initComponents();
        initSystem();
        initEntities();

        std::shared_ptr<RL::ZShader> shader = std::make_shared<RL::ZShader>("./client/resources/shaders/particle.vs", "./client/resources/shaders/particle.fs");
        int glowIntensityLoc = shader->getLocation("glowIntensity");
        float glowIntensity = 3.0f;
        shader->setValue(glowIntensityLoc, &glowIntensity, SHADER_UNIFORM_FLOAT);

        while (!_window->shouldClose()) {
            while (!_receivedMessages->empty()) {
                std::string message = _receivedMessages->front().message;
                _listener->addEvent(message);
                _receivedMessages->pop();
            }
            _listener->onEvent();
            _window->beginDrawing();
            _window->clearBackground(BLACK);
            _systems._systemCamera->begin();

            _systems._systemDrawModel->update();
//            _systems._systemMove->update();
            _systems._systemPlayer->update(_event, _udpClient);
//            _systems._systemParticles->update(_camera, shader);
//            _systems._systemShoot->update(_event);
//            _systems._systemProjectile->update();
            _systems._systemCamera->update();
//            _systems._systemTraveling->update();

            // checkCollision(*_entities->rbegin(), *_entities->rend());

            _window->drawGrid(10, 1.0f);
            _systems._systemCamera->end();
            _window->drawFPS(10, 10);
            _window->endDrawing();
        }
    }
};
